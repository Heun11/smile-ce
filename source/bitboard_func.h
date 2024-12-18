#ifndef BITBOARD_FUNC
#define BITBOARD_FUNC

#include "bitboard.h"
#include <stdint.h>

void BITBOARD_SetBitToH(BITBOARD_Bitboard* bitboard, uint8_t bit_index);
uint8_t BITBOARD_GetBit(BITBOARD_Bitboard* bitboard, uint8_t bit_index);
void BITBOARD_BitwiseOR(BITBOARD_Bitboard* bitboard_dest, int num_of_bitboards, ...);  // bitboard_dest |= ...
void BITBOARD_BitwiseAND(BITBOARD_Bitboard* bitboard_dest, int num_of_bitboards, ...); // bitboard_dest &= ...
void BITBOARD_Multiply(BITBOARD_Bitboard* bitboard_dest, BITBOARD_Bitboard* bitboard_a, BITBOARD_Bitboard* bitboard_b); 

#endif // !BITBOARD_FUNC

