#ifndef BITBOARD_FUNC
#define BITBOARD_FUNC

#include "bitboard.h"
#include <stdint.h>

#define BITBOARD_IsBitboardTrue(bitboard) (bitboard.half[0]||bitboard.half[1])

void BITBOARD_Print(BITBOARD_Bitboard* bitboard);
void BITBOARD_SetBitToH(BITBOARD_Bitboard* bitboard, uint8_t bit_index);
uint8_t BITBOARD_GetBit(BITBOARD_Bitboard* bitboard, uint8_t bit_index);
void BITBOARD_BitwiseOR(BITBOARD_Bitboard* bitboard_dest, int num_of_bitboards, ...);  // bitboard_dest |= ...
void BITBOARD_BitwiseAND(BITBOARD_Bitboard* bitboard_dest, int num_of_bitboards, ...); // bitboard_dest &= ...
void BITBOARD_Multiply(BITBOARD_Bitboard* bitboard_dest, BITBOARD_Bitboard* bitboard_a, BITBOARD_Bitboard* bitboard_b); 
uint8_t BITBOARD_CountTrailingZeros(BITBOARD_Bitboard* bitboard);
void BITBOARD_SetBitboardToBitboard(BITBOARD_Bitboard* bitboard_dest, BITBOARD_Bitboard* bitboard);
void BITBOARD_RightShift(BITBOARD_Bitboard* bitboard_dest, BITBOARD_Bitboard* bitboard, uint8_t shift);
void BITBOARD_LeftShift(BITBOARD_Bitboard* bitboard_dest, BITBOARD_Bitboard* bitboard, uint8_t shift);


void BITBOARD_GetAttackMask_bishop(BITBOARD_Bitboard* bitboard_dest, uint8_t square, BITBOARD_Bitboard* bitboard_occupancy);
void BITBOARD_GetAttackMask_rook(BITBOARD_Bitboard* bitboard_dest, uint8_t square, BITBOARD_Bitboard* bitboard_occupancy);

#endif // !BITBOARD_FUNC

