// void split64to232(uint64_t original, uint32_t* dest_l, uint32_t* dest_h)
// {
//   *dest_l = (uint32_t)(original & 0xFFFFFFFF);    
//   *dest_h = (uint32_t)((original >> 32) & 0xFFFFFFFF);
// }
#include <stdlib.h>

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define BOARD_SIZE 64
#define MAX_ROOK_ATTACKS 4096

// Provided rook magic numbers
uint64_t rook_magic_numbers[64] = {
    0x8a80104000800020ULL, 0x140002000100040ULL,  0x2801880a0017001ULL,  0x100081001000420ULL,
    0x200020010080420ULL,  0x3001c0002010008ULL,  0x8480008002000100ULL, 0x2080088004402900ULL,
    0x800098204000ULL,     0x2024401000200040ULL, 0x100802000801000ULL,  0x120800800801000ULL,
    0x208808088000400ULL,  0x2802200800400ULL,    0x2200800100020080ULL, 0x801000060821100ULL,
    0x80044006422000ULL,   0x100808020004000ULL,  0x12108a0010204200ULL, 0x140848010000802ULL,
    0x481828014002800ULL,  0x8094004002004100ULL, 0x4010040010010802ULL, 0x20008806104ULL,
    0x100400080208000ULL,  0x2040002120081000ULL, 0x21200680100081ULL,   0x20100080080080ULL,
    0x2000a00200410ULL,    0x20080800400ULL,      0x80088400100102ULL,   0x80004600042881ULL,
    0x4040008040800020ULL, 0x440003000200801ULL,  0x4200011004500ULL,    0x188020010100100ULL,
    0x14800401802800ULL,   0x2080040080800200ULL, 0x124080204001001ULL,  0x200046502000484ULL,
    0x480400080088020ULL,  0x1000422010034000ULL, 0x30200100110040ULL,   0x100021010009ULL,
    0x2002080100110004ULL, 0x202008004008002ULL,  0x20020004010100ULL,   0x2048440040820001ULL,
    0x101002200408200ULL,  0x40802000401080ULL,   0x4008142004410100ULL, 0x2060820c0120200ULL,
    0x1001004080100ULL,    0x20c020080040080ULL,  0x2935610830022400ULL, 0x44440041009200ULL,
    0x280001040802101ULL,  0x2100190040002085ULL, 0x80c0084100102001ULL, 0x4024081001000421ULL,
    0x20030a0244872ULL,    0x12001008414402ULL,   0x2006104900a0804ULL,  0x1004081002402ULL
};

// Attack masks and tables
uint64_t rook_attack_masks[64];
uint64_t rook_attack_table[64][MAX_ROOK_ATTACKS];
int rook_shift[64];

// Population count
int pop_count(uint64_t x) {
    int count = 0;
    while (x) {
        count += (x & 1);
        x >>= 1;
    }
    return count;
}

// Compute relevant rook attack mask
uint64_t calculate_rook_attack_mask(int square) {
    uint64_t mask = 0ULL;
    int rank = square / 8, file = square % 8;

    // Horizontal (rank) moves
    for (int f = file + 1; f < 7; f++) mask |= (1ULL << (rank * 8 + f));
    for (int f = file - 1; f > 0; f--) mask |= (1ULL << (rank * 8 + f));

    // Vertical (file) moves
    for (int r = rank + 1; r < 7; r++) mask |= (1ULL << (r * 8 + file));
    for (int r = rank - 1; r > 0; r--) mask |= (1ULL << (r * 8 + file));

    return mask;
}

// Generate all subsets of a mask
void generate_occupancy_variations(uint64_t mask, uint64_t *variations, int *count) {
    int num_bits = pop_count(mask);
    *count = (1 << num_bits);

    for (int i = 0; i < *count; i++) {
        uint64_t occupancy = 0ULL;
        int bit_index = 0;
        for (int bit = 0; bit < 64; bit++) {
            if (mask & (1ULL << bit)) {
                if (i & (1 << bit_index)) {
                    occupancy |= (1ULL << bit);
                }
                bit_index++;
            }
        }
        variations[i] = occupancy;
    }
}

// Generate rook attacks
uint64_t calculate_rook_attacks(int square, uint64_t occupancy) {
    uint64_t attacks = 0ULL;
    int rank = square / 8, file = square % 8;

    // Horizontal (rank) moves
    for (int f = file + 1; f < 8; f++) {
        attacks |= (1ULL << (rank * 8 + f));
        if (occupancy & (1ULL << (rank * 8 + f))) break;
    }
    for (int f = file - 1; f >= 0; f--) {
        attacks |= (1ULL << (rank * 8 + f));
        if (occupancy & (1ULL << (rank * 8 + f))) break;
    }

    // Vertical (file) moves
    for (int r = rank + 1; r < 8; r++) {
        attacks |= (1ULL << (r * 8 + file));
        if (occupancy & (1ULL << (r * 8 + file))) break;
    }
    for (int r = rank - 1; r >= 0; r--) {
        attacks |= (1ULL << (r * 8 + file));
        if (occupancy & (1ULL << (r * 8 + file))) break;
    }

    return attacks;
}

// Initialize rook attack table and shifts
void initialize_rook_attacks() {
    for (int square = 0; square < BOARD_SIZE; square++) {
        // Compute attack mask
        rook_attack_masks[square] = calculate_rook_attack_mask(square);

        // Compute shift amount
        rook_shift[square] = 64 - pop_count(rook_attack_masks[square]);

        // Generate attack table
        uint64_t variations[MAX_ROOK_ATTACKS];
        int variation_count;
        generate_occupancy_variations(rook_attack_masks[square], variations, &variation_count);

        for (int i = 0; i < variation_count; i++) {
            uint64_t occupancy = variations[i];
            uint64_t masked_occupancy = occupancy & rook_attack_masks[square];
            uint64_t index = (masked_occupancy * rook_magic_numbers[square]) >> rook_shift[square];
            rook_attack_table[square][index] = calculate_rook_attacks(square, occupancy);
        }
    }
}




void split64to232(uint64_t original, uint32_t* dest_l, uint32_t* dest_h)
{
  *dest_l = (uint32_t)(original & 0xFFFFFFFF);    
  *dest_h = (uint32_t)((original >> 32) & 0xFFFFFFFF);
}

int main() {
    printf("Generating bishop attack table...\n");
    initialize_rook_attacks();

    
    uint32_t* l = malloc(sizeof(uint32_t));
    uint32_t* h = malloc(sizeof(uint32_t));

    FILE* fp = fopen("out.txt", "w");
    if(fp){
      printf("file opened successfully\n");
    }

    fprintf(fp, "bitboard = {\n");
    for(int i=0;i<64;i++){
      fprintf(fp, "\t{\n");
      for(int j=0;j<MAX_ROOK_ATTACKS;j++){
        split64to232(rook_attack_table[i][j], l, h);
        fprintf(fp, "\t\t(BITBOARD_Bitboard){{0x%08llX, 0x%08llX}},", *l, *h);
        if(j%3==0){
          fprintf(fp, "\n");
        }
      }
      fprintf(fp, "\t},\n");
    }
    fprintf(fp, "};\n");
   
    printf("magics = {\n");
    for(int i=0;i<64;i++){
      split64to232(rook_magic_numbers[i], l, h);
      printf("  (BITBOARD_Bitboard){{0x%08llX, 0x%08llX}},\n", *l, *h);
    }
    printf("};\n");

    printf("\nshift = {\n");
    for(int i=0;i<64;i++){
      printf("%d, ", rook_shift[i]);
      if((i+1)%8==0) printf("\n");
    }
    printf("};\n");

    printf("masks = {\n");
    for(int i=0;i<64;i++){
      split64to232(rook_attack_masks[i], l, h);
      printf("  (BITBOARD_Bitboard){{0x%08llX, 0x%08llX}},\n", *l, *h);
    }
    printf("};\n");

    free(l);
    free(h);
    fclose(fp);
      
    return 0;
}

