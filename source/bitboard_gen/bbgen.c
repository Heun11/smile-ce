#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define U64 uint64_t
#define BOARD_SIZE 64





U64 generate_rook_mask(int square) {
    U64 mask = 0ULL;

    int rank = square / 8; // Row (0-7)
    int file = square % 8; // Column (0-7)

    // Generate squares along the file (up and down)
    for (int r = 0; r < 8; r++) {
        if (r != rank) { // Skip the current square
            int new_square = r * 8 + file;
            mask |= (1ULL << new_square);
        }
    }

    // Generate squares along the rank (left and right)
    for (int f = 0; f < 8; f++) {
        if (f != file) { // Skip the current square
            int new_square = rank * 8 + f;
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
    U64 knight_masks[BOARD_SIZE] = {
    0x8a80104000800020ULL, 0x1400020008001200ULL, 0x8000808004000200ULL, 0x8001008002000040ULL,
    0x100100080002000ULL,  0x200200040100020ULL,  0x300080020080040ULL,  0x8200084001080080ULL,
    0x4000808008004000ULL, 0x401000400220080ULL,  0x800080004000ULL,     0x200080080080ULL,
    0x100080100080ULL,     0x400080200080ULL,     0x800080800400ULL,     0x800040008080ULL,
    0x200040008080ULL,     0x800400080200040ULL,  0x800200200400ULL,     0x100200200080ULL,
    0x200100200040ULL,     0x400080200020ULL,     0x800040008020ULL,     0x800200800400ULL,
    0x1000800400080ULL,    0x8002000400100ULL,    0x8000802002004ULL,    0x80020008080040ULL,
    0x80040020020080ULL,   0x80020040008020ULL,   0x80010040020040ULL,   0x80080008040040ULL,
    0x802000404000ULL,     0x802000808000ULL,     0x804000800040ULL,     0x804000400040ULL,
    0x800100800040ULL,     0x800100400040ULL,     0x802000400020ULL,     0x802000800040ULL,
    0x804000400200ULL,     0x800800400200ULL,     0x800400800200ULL,     0x800400800100ULL,
    0x800200800400ULL,     0x800200400400ULL,     0x800100800400ULL,     0x800100800200ULL,
    0x800800400040ULL,     0x800400800040ULL,     0x800400400080ULL,     0x800400400100ULL,
    0x800200400200ULL,     0x800200400100ULL,     0x800100400200ULL,     0x800100800100ULL,
    0x800800400080ULL,     0x800800800100ULL,     0x800800400200ULL,     0x800800800200ULL,
};

    // Generate knight masks for all squares
    // for (int square = 0; square < BOARD_SIZE; square++) {
    //     knight_masks[square] = generate_rook_mask(square);
    // }


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
