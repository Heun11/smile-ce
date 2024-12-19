#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// #define U64 uint64_t
// #define BOARD_SIZE 64
//
//
//
//
//
// #define MAX_BISHOP_MAGIC_ENTRIES 512 // Maximum possible table size for bishops
// #define RELEVANT_BITS_BISHOP 9       // Maximum number of relevant bits for bishop occupancy
//
// // Directions for bishop movement
// const int BISHOP_DIRECTIONS[4] = {9, 7, -9, -7};
//
// // Function to check if a square is within the board boundaries
// int is_within_bounds(int rank, int file) {
//     return rank >= 0 && rank < 8 && file >= 0 && file < 8;
// }
//
// // Generate a bishop occupancy mask
// U64 generate_bishop_mask(int square) {
//     U64 mask = 0ULL;
//
//     int rank = square / 8;
//     int file = square % 8;
//
//     for (int dir = 0; dir < 4; dir++) {
//         int r = rank;
//         int f = file;
//         while (1) {
//             r += BISHOP_DIRECTIONS[dir] / 8;
//             f += BISHOP_DIRECTIONS[dir] % 8;
//             if (!is_within_bounds(r, f)) break; // Stop if out of bounds
//             if (r == 0 || r == 7 || f == 0 || f == 7) break; // Stop before edge
//             mask |= (1ULL << (r * 8 + f));
//         }
//     }
//
//     return mask;
// }
//
// // Generate all possible occupancies for a given bishop mask
// int generate_occupancies(U64 mask, U64 *occupancies) {
//     int bit_count = __builtin_popcountll(mask);
//     int occupancy_count = 1 << bit_count;
//
//     for (int i = 0; i < occupancy_count; i++) {
//         U64 occ = 0ULL;
//         int bit_index = 0;
//
//         for (int j = 0; j < 64; j++) {
//             if (mask & (1ULL << j)) {
//                 if (i & (1 << bit_index)) {
//                     occ |= (1ULL << j);
//                 }
//                 bit_index++;
//             }
//         }
//         occupancies[i] = occ;
//     }
//
//     return occupancy_count;
// }
//
// // Generate the attack bitboard for a bishop
// U64 generate_bishop_attack(int square, U64 occupancy) {
//     U64 attacks = 0ULL;
//
//     int rank = square / 8;
//     int file = square % 8;
//
//     for (int dir = 0; dir < 4; dir++) {
//         int r = rank;
//         int f = file;
//         while (1) {
//             r += BISHOP_DIRECTIONS[dir] / 8;
//             f += BISHOP_DIRECTIONS[dir] % 8;
//
//             if (!is_within_bounds(r, f)) break; // Out of bounds
//             attacks |= (1ULL << (r * 8 + f));
//             if (occupancy & (1ULL << (r * 8 + f))) break; // Stop if blocker found
//         }
//     }
//
//     return attacks;
// }
//
// // Function to find a magic number for a bishop square
// U64 find_magic_number(int square, int relevant_bits) {
//     U64 occupancies[512], attacks[512], used[512];
//     memset(used, 0, sizeof(used));
//
//     U64 mask = generate_bishop_mask(square);
//     int occupancy_count = generate_occupancies(mask, occupancies);
//
//     for (int i = 0; i < occupancy_count; i++) {
//         attacks[i] = generate_bishop_attack(square, occupancies[i]);
//     }
//
//     srand(time(NULL));
//
//     while (1) {
//         U64 candidate = (rand() & 0xFFFF) | ((U64)(rand() & 0xFFFF) << 16) | ((U64)(rand() & 0xFFFF) << 32) |
//                         ((U64)(rand() & 0xFFFF) << 48);
//
//         memset(used, 0, sizeof(used));
//
//         int success = 1;
//         for (int i = 0; i < occupancy_count; i++) {
//             int index = (occupancies[i] * candidate) >> (64 - relevant_bits);
//
//             if (used[index] == 0ULL) {
//                 used[index] = attacks[i];
//             } else if (used[index] != attacks[i]) {
//                 success = 0;
//                 break;
//             }
//         }
//
//         if (success) return candidate;
//     }
// }
//
//
//
//
//
// void split64to232(uint64_t original, uint32_t* dest_l, uint32_t* dest_h)
// {
//   *dest_l = (uint32_t)(original & 0xFFFFFFFF);    
//   *dest_h = (uint32_t)((original >> 32) & 0xFFFFFFFF);
// }
//
// int main() {
//     U64 bishop_magics[BOARD_SIZE];
//
//     uint32_t* l = malloc(4);
//     uint32_t* h = malloc(4);
//
//     // Print the generated knight masks
//     printf("moja maska = {\n");
//     for (int square = 0; square < BOARD_SIZE; square++) {
//
//       int relevant_bits = RELEVANT_BITS_BISHOP;
//       bishop_magics[square] = find_magic_number(square, relevant_bits);
//       
//       split64to232(bishop_magics[square], l, h);
//       printf("    (BITBOARD_Bitboard){{0x%08llX, 0x%08llX}}%s\n", *l, *h, (square < BOARD_SIZE - 1) ? "," : "");
//     }
//     printf("};\n");
//
//     free(l);
//     free(h);
//
//     return 0;
// }




#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define U64 uint64_t
#define BOARD_SIZE 64
#define ROOK_ATTACK_TABLE_SIZE 4096
#define RELEVANT_BITS_ROOK 12

const int ROOK_DIRECTIONS[4] = {8, -8, 1, -1}; // Directions for rook moves

// Precomputed magic numbers for rooks
const U64 rook_magics[64] = {
    0x8a80104000800020ULL, 0x1400020008001200ULL, 0x8008004002004100ULL, 0x280100100080084ULL,
    0x8000808004000200ULL, 0x60004000800080ULL, 0x8100480080ULL, 0x280020001001080ULL,
    0x101000208000400ULL, 0x800040008000ULL, 0x402000100080ULL, 0x802000400080ULL,
    0x401000800040ULL, 0x408000800040ULL, 0x808000400020ULL, 0x800040008000ULL,
    0x800200080010ULL, 0x800080400080ULL, 0x200040100080ULL, 0x800080801000ULL,
    0x800040080080ULL, 0x10002000400080ULL, 0x800080200040ULL, 0x10000800040080ULL,
    0x208000400080ULL, 0x4000802000400ULL, 0x800040008000ULL, 0x8002000800100ULL,
    0x1001000200080ULL, 0x4000800800080ULL, 0x8000802000400ULL, 0x10004000800080ULL,
    0x20008000800040ULL, 0x800200400080ULL, 0x8004000800080ULL, 0x1000400200080ULL,
    0x2000800100080ULL, 0x8004002000100ULL, 0x1000800400080ULL, 0x8000401000800ULL,
    0x200040200100ULL, 0x800100200100ULL, 0x800080401000ULL, 0x400800800040ULL,
    0x800080008040ULL, 0x200020008040ULL, 0x100040008040ULL, 0x8002000200080ULL,
    0x4000800080080ULL, 0x8001000400080ULL, 0x40008000800040ULL, 0x80004000800040ULL,
    0x10002000800040ULL, 0x20004000800040ULL, 0x80008000400040ULL, 0x80008000400080ULL,
    0x40008000400080ULL, 0x10008000400080ULL, 0x20008000400080ULL, 0x800400800080ULL,
    0x1002000800100ULL, 0x80008080100080ULL, 0x4000400100080ULL, 0x8000800200080ULL
};

// Check if a square is within board boundaries
int is_within_bounds(int rank, int file) {
    return rank >= 0 && rank < 8 && file >= 0 && file < 8;
}

// Generate the rook attack mask for a given square
U64 generate_rook_mask(int square) {
    U64 mask = 0ULL;
    int rank = square / 8, file = square % 8;

    for (int dir = 0; dir < 4; dir++) {
        int r = rank, f = file;
        while (1) {
            r += ROOK_DIRECTIONS[dir] / 8;
            f += ROOK_DIRECTIONS[dir] % 8;
            if (!is_within_bounds(r, f)) break;
            if (r == 0 || r == 7 || f == 0 || f == 7) break; // Stop at edges
            mask |= (1ULL << (r * 8 + f));
        }
    }
    return mask;
}

// Generate rook attacks given an occupancy bitboard
U64 generate_rook_attack(int square, U64 occupancy) {
    U64 attacks = 0ULL;
    int rank = square / 8, file = square % 8;

    for (int dir = 0; dir < 4; dir++) {
        int r = rank, f = file;
        while (1) {
            r += ROOK_DIRECTIONS[dir] / 8;
            f += ROOK_DIRECTIONS[dir] % 8;
            if (!is_within_bounds(r, f)) break;
            attacks |= (1ULL << (r * 8 + f));
            if (occupancy & (1ULL << (r * 8 + f))) break; // Stop at blocker
        }
    }
    return attacks;
}

// Generate all possible occupancies and corresponding attack table
void generate_rook_attack_table(U64 attack_table[64][ROOK_ATTACK_TABLE_SIZE]) {
    for (int square = 0; square < 64; square++) {
        U64 mask = generate_rook_mask(square);
        int relevant_bits = __builtin_popcountll(mask);
        int occupancy_count = 1 << relevant_bits;

        for (int i = 0; i < occupancy_count; i++) {
            U64 occupancy = 0ULL;
            int bit_index = 0;

            for (int j = 0; j < 64; j++) {
                if (mask & (1ULL << j)) {
                    if (i & (1 << bit_index)) {
                        occupancy |= (1ULL << j);
                    }
                    bit_index++;
                }
            }

            int index = (occupancy * rook_magics[square]) >> (64 - RELEVANT_BITS_ROOK);
            attack_table[square][index] = generate_rook_attack(square, occupancy);
        }
    }
}

void split64to232(uint64_t original, uint32_t* dest_l, uint32_t* dest_h)
{
  *dest_l = (uint32_t)(original & 0xFFFFFFFF);    
  *dest_h = (uint32_t)((original >> 32) & 0xFFFFFFFF);
}

void print_bishop_attack_table(U64 attack_table[64][ROOK_ATTACK_TABLE_SIZE]) {

    uint32_t* l = malloc(sizeof(uint32_t));
    uint32_t* h = malloc(sizeof(uint32_t));

    FILE* fp = fopen("out.txt", "w");

    fprintf(fp, "U64 bishop_attack_table[64][512] = {\n");
    for (int square = 0; square < 64; square++) {
        fprintf(fp, " {\n");
        for (int i = 0; i < ROOK_ATTACK_TABLE_SIZE; i++) {
            split64to232(attack_table[square][i], l, h);
            fprintf(fp,"    (BITBOARD_Bitboard){{0x%08llX, 0x%08llX}},", *l, *h);

            if(i%3==0) fprintf(fp, "\n");
            
        }
        fprintf(fp, "\n\t},\n");
    }
    fprintf(fp, "};\n");

    free(l);
  free(h);
  
}

int main() {
    U64 bishop_attack_table[64][ROOK_ATTACK_TABLE_SIZE] = {0};
    generate_rook_attack_table(bishop_attack_table);
    print_bishop_attack_table(bishop_attack_table);
    
    uint32_t* l = malloc(sizeof(uint32_t));
    uint32_t* h = malloc(sizeof(uint32_t));

    printf("bitboard = {\n");
    for(int i=0;i<64;i++){
      split64to232(rook_magics[i], l, h);
      printf("\t(BITBOARD_Bitboard){{0x%08llX, 0x%08llX}},\n", *l, *h);
    }
    printf("};\n");
    
    free(l);
    free(h);
      
    return 0;
}

