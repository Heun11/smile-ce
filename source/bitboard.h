#ifndef BITBOARD_H
#define BITBOARD_H

#include <stdint.h>

// bitboard struct
typedef struct{
  uint32_t half[2]; // 0 - lower half | 1 - higher half
}BITBOARD_Bitboard;

extern BITBOARD_Bitboard BITBOARD_Masks_knight[64];             
extern BITBOARD_Bitboard BITBOARD_Masks_king[64];              

extern BITBOARD_Bitboard BITBOARD_Masks_pawnSinglePush[2][64];  
extern BITBOARD_Bitboard BITBOARD_Masks_pawnDoublePush[2][64]; 
extern BITBOARD_Bitboard BITBOARD_AttackMasks_pawn[2][64];     

// !!!!! IMPORTANT -> od tejto ciary som si neni isty ci je to dobre tak sa na to kukni

extern BITBOARD_Bitboard BITBOARD_Masks_bishop[64];            
extern uint8_t BITBOARD_Shift_bishop[64];
extern BITBOARD_Bitboard BITBOARD_Magics_bishop[64];            
extern BITBOARD_Bitboard BITBOARD_AttackTable_bishop[64][512];  

extern BITBOARD_Bitboard BITBOARD_Masks_rook[64];               
extern uint8_t BITBOARD_Shift_rook[64];
extern BITBOARD_Bitboard BITBOARD_Magics_rook[64];              
extern BITBOARD_Bitboard BITBOARD_AttackTable_rook[64][4096];  

#endif
