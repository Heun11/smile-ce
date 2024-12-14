#ifndef BITBOARD_H
#define BITBOARD_H

#include <stdint.h>

// bitboard struct
typedef struct{
  uint32_t half[2]; // 0 - lower half | 1 - higher half
}BITBOARD_Bitboard;

// Non-Sliding Pieces
extern BITBOARD_Bitboard BITBOARD_Masks_knight[64];             // Knight moves for all 64 squares
extern BITBOARD_Bitboard BITBOARD_Masks_king[64];               // King moves for all 64 squares

// Pawn Moves
extern BITBOARD_Bitboard BITBOARD_Masks_pawnSinglePush[2][64];  // Single push for white and black pawns
extern BITBOARD_Bitboard BITBOARD_Masks_pawnDoublePush[2][64];  // Double push for white and black pawns
extern BITBOARD_Bitboard BITBOARD_AttackMasks_pawn[2][64];      // Pawn attacks for white and black

// Sliding Pieces (Rooks and Bishops)
extern BITBOARD_Bitboard BITBOARD_Masks_rook[64];               // Relevant blocker masks for rooks
extern BITBOARD_Bitboard BITBOARD_Magics_rook[64];              // Magic numbers for rooks
extern BITBOARD_Bitboard BITBOARD_AttackTable_rook[64][4096];   // Precomputed rook attack tables
extern const uint8_t BITBOARD_Shifts[64];

extern BITBOARD_Bitboard BITBOARD_Masks_bishop[64];             // Relevant blocker masks for bishops
extern BITBOARD_Bitboard BITBOARD_Magics_bishop[64];            // Magic numbers for bishops
extern BITBOARD_Bitboard BITBOARD_AttackTable_bishop[64][512];  // Precomputed bishop attack tables

// U64 knight_masks[64];         // Knight moves for all 64 squares
// U64 king_masks[64];           // King moves for all 64 squares
//
// // 3. Pawn Moves
// U64 pawn_single_push_masks[2][64]; // Single push for white and black pawns
// U64 pawn_double_push_masks[2][64]; // Double push for white and black pawns
// U64 pawn_attack_masks[2][64];      // Pawn attacks for white and black
//
// // 4. Sliding Pieces (Rooks and Bishops)
// U64 rook_masks[64];           // Relevant blocker masks for rooks
// U64 rook_magics[64];          // Magic numbers for rooks
// U64 rook_attack_table[64][4096]; // Precomputed rook attack tables
//
// U64 bishop_masks[64];         // Relevant blocker masks for bishops
// U64 bishop_magics[64];        // Magic numbers for bishops
// U64 bishop_attack_table[64][512]

// functions
void BITBOARD_SetBitToH(BITBOARD_Bitboard* bitboard, uint8_t bit_index);
uint8_t BITBOARD_GetBit(BITBOARD_Bitboard* bitboard, uint8_t bit_index);
void BITBOARD_BitwiseOR(BITBOARD_Bitboard* bitboard_dest, int num_of_bitboards, ...);  // bitboard_dest |= ...
void BITBOARD_BitwiseAND(BITBOARD_Bitboard* bitboard_dest, int num_of_bitboards, ...); // bitboard_dest &= ...
void BITBOARD_Multiply(BITBOARD_Bitboard* bitboard_dest, BITBOARD_Bitboard* bitboard_a, BITBOARD_Bitboard* bitboard_b); 

#endif
