#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define U64 uint64_t
#define BOARD_SIZE 64





#define MAX_BISHOP_MAGIC_ENTRIES 512 // Maximum possible table size for bishops
#define RELEVANT_BITS_BISHOP 9       // Maximum number of relevant bits for bishop occupancy

// Directions for bishop movement
const int BISHOP_DIRECTIONS[4] = {9, 7, -9, -7};

// Function to check if a square is within the board boundaries
int is_within_bounds(int rank, int file) {
    return rank >= 0 && rank < 8 && file >= 0 && file < 8;
}

// Generate a bishop occupancy mask
U64 generate_bishop_mask(int square) {
    U64 mask = 0ULL;

    int rank = square / 8;
    int file = square % 8;

    for (int dir = 0; dir < 4; dir++) {
        int r = rank;
        int f = file;
        while (1) {
            r += BISHOP_DIRECTIONS[dir] / 8;
            f += BISHOP_DIRECTIONS[dir] % 8;
            if (!is_within_bounds(r, f)) break; // Stop if out of bounds
            if (r == 0 || r == 7 || f == 0 || f == 7) break; // Stop before edge
            mask |= (1ULL << (r * 8 + f));
        }
    }

    return mask;
}

// Generate all possible occupancies for a given bishop mask
int generate_occupancies(U64 mask, U64 *occupancies) {
    int bit_count = __builtin_popcountll(mask);
    int occupancy_count = 1 << bit_count;

    for (int i = 0; i < occupancy_count; i++) {
        U64 occ = 0ULL;
        int bit_index = 0;

        for (int j = 0; j < 64; j++) {
            if (mask & (1ULL << j)) {
                if (i & (1 << bit_index)) {
                    occ |= (1ULL << j);
                }
                bit_index++;
            }
        }
        occupancies[i] = occ;
    }

    return occupancy_count;
}

// Generate the attack bitboard for a bishop
U64 generate_bishop_attack(int square, U64 occupancy) {
    U64 attacks = 0ULL;

    int rank = square / 8;
    int file = square % 8;

    for (int dir = 0; dir < 4; dir++) {
        int r = rank;
        int f = file;
        while (1) {
            r += BISHOP_DIRECTIONS[dir] / 8;
            f += BISHOP_DIRECTIONS[dir] % 8;

            if (!is_within_bounds(r, f)) break; // Out of bounds
            attacks |= (1ULL << (r * 8 + f));
            if (occupancy & (1ULL << (r * 8 + f))) break; // Stop if blocker found
        }
    }

    return attacks;
}

// Function to find a magic number for a bishop square
U64 find_magic_number(int square, int relevant_bits) {
    U64 occupancies[512], attacks[512], used[512];
    memset(used, 0, sizeof(used));

    U64 mask = generate_bishop_mask(square);
    int occupancy_count = generate_occupancies(mask, occupancies);

    for (int i = 0; i < occupancy_count; i++) {
        attacks[i] = generate_bishop_attack(square, occupancies[i]);
    }

    srand(time(NULL));

    while (1) {
        U64 candidate = (rand() & 0xFFFF) | ((U64)(rand() & 0xFFFF) << 16) | ((U64)(rand() & 0xFFFF) << 32) |
                        ((U64)(rand() & 0xFFFF) << 48);

        memset(used, 0, sizeof(used));

        int success = 1;
        for (int i = 0; i < occupancy_count; i++) {
            int index = (occupancies[i] * candidate) >> (64 - relevant_bits);

            if (used[index] == 0ULL) {
                used[index] = attacks[i];
            } else if (used[index] != attacks[i]) {
                success = 0;
                break;
            }
        }

        if (success) return candidate;
    }
}





void split64to232(uint64_t original, uint32_t* dest_l, uint32_t* dest_h)
{
  *dest_l = (uint32_t)(original & 0xFFFFFFFF);    
  *dest_h = (uint32_t)((original >> 32) & 0xFFFFFFFF);
}

int main() {
    U64 bishop_magics[BOARD_SIZE];

    uint32_t* l = malloc(4);
    uint32_t* h = malloc(4);

    // Print the generated knight masks
    printf("moja maska = {\n");
    for (int square = 0; square < BOARD_SIZE; square++) {

      int relevant_bits = RELEVANT_BITS_BISHOP;
      bishop_magics[square] = find_magic_number(square, relevant_bits);
      
      split64to232(bishop_magics[square], l, h);
      printf("    (BITBOARD_Bitboard){{0x%08llX, 0x%08llX}}%s\n", *l, *h, (square < BOARD_SIZE - 1) ? "," : "");
    }
    printf("};\n");

    free(l);
    free(h);

    return 0;
}

