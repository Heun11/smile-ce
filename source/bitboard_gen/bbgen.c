// void split64to232(uint64_t original, uint32_t* dest_l, uint32_t* dest_h)
// {
//   *dest_l = (uint32_t)(original & 0xFFFFFFFF);    
//   *dest_h = (uint32_t)((original >> 32) & 0xFFFFFFFF);
// }
#include <stdlib.h>

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define BOARD_SIZE 64
#define MAX_BISHOP_ATTACKS 512

// Provided bishop magic numbers
uint64_t bishop_magic_numbers[64] = {
    0x89a1121896040240ULL, 0x2004844802002010ULL, 0x2068080051921000ULL, 0x62880a0220200808ULL,
    0x4042004000000ULL,    0x100822020200011ULL,  0xc00444222012000aULL, 0x28808801216001ULL,
    0x400492088408100ULL,  0x201c401040c0084ULL,  0x840800910a0010ULL,   0x82080240060ULL,
    0x2000840504006000ULL, 0x30010c4108405004ULL, 0x1008005410080802ULL, 0x8144042209100900ULL,
    0x208081020014400ULL,  0x4800201208ca00ULL,   0xf18140408012008ULL,  0x1004002802102001ULL,
    0x841000820080811ULL,  0x40200200a42008ULL,   0x800054042000ULL,     0x88010400410c9000ULL,
    0x520040470104290ULL,  0x1004040051500081ULL, 0x2002081833080021ULL, 0x400c00c010142ULL,
    0x941408200c002000ULL, 0x658810000806011ULL,  0x188071040440a00ULL,  0x4800404002011c00ULL,
    0x104442040404200ULL,  0x511080202091021ULL,  0x4022401120400ULL,    0x80c0040400080120ULL,
    0x8040010040820802ULL, 0x480810700020090ULL,  0x102008e00040242ULL,  0x809005202050100ULL,
    0x8002024220104080ULL, 0x431008804142000ULL,  0x19001802081400ULL,   0x200014208040080ULL,
    0x3308082008200100ULL, 0x41010500040c020ULL,  0x4012020c04210308ULL, 0x208220a202004080ULL,
    0x111040120082000ULL,  0x6803040141280a00ULL, 0x2101004202410000ULL, 0x8200000041108022ULL,
    0x21082088000ULL,      0x2410204010040ULL,    0x40100400809000ULL,   0x822088220820214ULL,
    0x40808090012004ULL,   0x910224040218c9ULL,   0x402814422015008ULL,  0x814021148200820ULL,
    0x2081080200140ULL,    0x4800201208ca00ULL,   0xf18140408012008ULL,  0x1004002802102001ULL
};

// Attack masks and tables
uint64_t bishop_attack_masks[64];
uint64_t bishop_attack_table[64][MAX_BISHOP_ATTACKS];
int bishop_shift[64];

// Population count
int pop_count(uint64_t x) {
    int count = 0;
    while (x) {
        count += x & 1;
        x >>= 1;
    }
    return count;
}

// Compute relevant bishop attack mask
uint64_t calculate_bishop_attack_mask(int square) {
    uint64_t mask = 0ULL;
    int rank = square / 8, file = square % 8;

    for (int dr = -1; dr <= 1; dr += 2) {
        for (int df = -1; df <= 1; df += 2) {
            int r = rank + dr, f = file + df;
            while (r >= 1 && r <= 6 && f >= 1 && f <= 6) {
                mask |= (1ULL << (r * 8 + f));
                r += dr;
                f += df;
            }
        }
    }
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

// Generate bishop attacks
uint64_t calculate_bishop_attacks(int square, uint64_t occupancy) {
    uint64_t attacks = 0ULL;
    int rank = square / 8, file = square % 8;

    for (int dr = -1; dr <= 1; dr += 2) {
        for (int df = -1; df <= 1; df += 2) {
            int r = rank + dr, f = file + df;
            while (r >= 0 && r < 8 && f >= 0 && f < 8) {
                attacks |= (1ULL << (r * 8 + f));
                if (occupancy & (1ULL << (r * 8 + f))) break;
                r += dr;
                f += df;
            }
        }
    }
    return attacks;
}

// Initialize bishop attack table and shifts
void initialize_bishop_attacks() {
    for (int square = 0; square < BOARD_SIZE; square++) {
        // Compute attack mask
        bishop_attack_masks[square] = calculate_bishop_attack_mask(square);

        // Compute shift amount
        bishop_shift[square] = 64 - pop_count(bishop_attack_masks[square]);

        // Generate attack table
        uint64_t variations[MAX_BISHOP_ATTACKS];
        int variation_count;
        generate_occupancy_variations(bishop_attack_masks[square], variations, &variation_count);

        for (int i = 0; i < variation_count; i++) {
            uint64_t occupancy = variations[i];
            uint64_t index = (occupancy * bishop_magic_numbers[square]) >> bishop_shift[square];
            bishop_attack_table[square][index] = calculate_bishop_attacks(square, occupancy);
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
    initialize_bishop_attacks();

    
    uint32_t* l = malloc(sizeof(uint32_t));
    uint32_t* h = malloc(sizeof(uint32_t));

    FILE* fp = fopen("out.txt", "w");

    fprintf(fp, "bitboard = {\n");
    for(int i=0;i<64;i++){
      fprintf(fp, "\t{\n");
      for(int j=0;j<512;j++){
        split64to232(bishop_attack_table[i][j], l, h);
        fprintf(fp, "\t\t(BITBOARD_Bitboard){{0x%08llX, 0x%08llX}},", *l, *h);
        if(j%3==0){
          fprintf(fp, "\n");
        }
      }
      fprintf(fp, "\n\t},\n");
    }
    fprintf(fp, "};\n");
   
    printf("magics = {\n");
    for(int i=0;i<64;i++){
      split64to232(bishop_magic_numbers[i], l, h);
      printf("  (BITBOARD_Bitboard){{0x%08llX, 0x%08llX}},\n", *l, *h);
    }
    printf("};\n");

    printf("shift = {\n");
    for(int i=0;i<64;i++){
      printf("%d, ", bishop_shift[i]);
      if((i+1)%8==0) printf("\n");
    }
    printf("};\n");

    free(l);
    free(h);
      
    return 0;
}

