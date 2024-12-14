#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define U64 uint64_t
#define BOARD_SIZE 64




// King movement directions (row offset, column offset)
const int king_offsets[8][2] = {
    { 1,  0}, {-1,  0}, { 0,  1}, { 0, -1}, // Vertical and Horizontal
    { 1,  1}, { 1, -1}, {-1,  1}, {-1, -1}  // Diagonals
};

// Function to check if a square is within bounds
int is_within_bounds(int rank, int file) {
    return rank >= 0 && rank < 8 && file >= 0 && file < 8;
}

// Function to generate king moves bitboard for a square
U64 generate_king_mask(int square) {
    U64 mask = 0ULL;

    int rank = square / 8; // Row (0-7)
    int file = square % 8; // Column (0-7)

    for (int i = 0; i < 8; i++) {
        int new_rank = rank + king_offsets[i][0];
        int new_file = file + king_offsets[i][1];

        if (is_within_bounds(new_rank, new_file)) {
            int new_square = new_rank * 8 + new_file;
            mask |= (1ULL << new_square);
        }
    }

    return mask;
}




void split64to232(uint64_t original, uint32_t* dest_l, uint32_t* dest_h)
{
  *dest_l = (uint32_t)(original & 0xFFFFFFFF);    
  *dest_h = (uint32_t)((original >> 32) & 0xFFFFFFFF);
}

int main() {
    U64 knight_masks[BOARD_SIZE];

    // Generate knight masks for all squares
    for (int square = 0; square < BOARD_SIZE; square++) {
        knight_masks[square] = generate_king_mask(square);
    }


    uint32_t* l = malloc(4);
    uint32_t* h = malloc(4);

    // Print the generated knight masks
    printf("moja maska = {\n");
    for (int square = 0; square < BOARD_SIZE; square++) {
      
      split64to232(knight_masks[square], l, h);
      printf("    (BITBOARD_Bitboard){{0x%08llX, 0x%08llX}}%s\n", *l, *h, (square < BOARD_SIZE - 1) ? "," : "");
    }
    printf("};\n");

    free(l);
    free(h);

    return 0;
}
