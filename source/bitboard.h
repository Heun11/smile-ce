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

extern BITBOARD_Bitboard BITBOARD_Masks_bishop[64];             // Relevant blocker masks for bishops
extern BITBOARD_Bitboard BITBOARD_Magics_bishop[64];            // Magic numbers for bishops
extern BITBOARD_Bitboard BITBOARD_AttackTable_bishop[64][512];  // Precomputed bishop attack tables

// functions
void BITBOARD_SetBitToH(BITBOARD_Bitboard* bitboard, uint8_t bit_index);
uint8_t BITBOARD_GetBit(BITBOARD_Bitboard* bitboard, uint8_t bit_index);
void BITBOARD_BitwiseOR(BITBOARD_Bitboard* bitboard_dest, int num_of_bitboards, ...);  // bitboard_dest |= ...
void BITBOARD_BitwiseAND(BITBOARD_Bitboard* bitboard_dest, int num_of_bitboards, ...); // bitboard_dest &= ...

#endif
