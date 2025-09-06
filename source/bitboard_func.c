#include "bitboard_func.h"
#include "bitboard.h"
#include "util.h"
#include <raylib.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>

uint8_t BITBOARD_IsBitboardTrue(BITBOARD_Bitboard* bitboard)
{
  return bitboard->half[0]||bitboard->half[1];
}

void BITBOARD_Print(BITBOARD_Bitboard* bitboard)
{
  printf("Bitboard: (0x%08X%08X)\n", bitboard->half[1], bitboard->half[0]);
  for(uint8_t i=0;i<64;i++){
    printf("%c ", BITBOARD_GetBit(bitboard, i)?'1':'-');
    if((i+1)%8==0) printf("\n");
  }
  printf("\n");
}

void BITBOARD_SetBitToH(BITBOARD_Bitboard* bitboard, uint8_t bit_index)
{
  if(bit_index<32){
    bitboard->half[0]|=((uint32_t)1<<bit_index);
  }
  else{
    bitboard->half[1]|=((uint32_t)1<<bit_index);
  }
}

uint8_t BITBOARD_GetBit(BITBOARD_Bitboard* bitboard, uint8_t bit_index)
{
  if(bit_index<32){
    return (bitboard->half[0]&((uint32_t)1<<bit_index))>>(bit_index);
  }
  bit_index-=32;
  return (bitboard->half[1]&((uint32_t)1<<bit_index))>>(bit_index);
}

void BITBOARD_BitwiseOR(BITBOARD_Bitboard* bitboard_dest, int num_of_bitboards, ...)
{
  va_list args;
  va_start(args, num_of_bitboards);

  for(uint8_t i=0;i<num_of_bitboards;i++){
    BITBOARD_Bitboard* bitboard = va_arg(args, BITBOARD_Bitboard*);
    bitboard_dest->half[0] |= bitboard->half[0];
    bitboard_dest->half[1] |= bitboard->half[1];
  }

  va_end(args);
}

void BITBOARD_BitwiseAND(BITBOARD_Bitboard* bitboard_dest, int num_of_bitboards, ...)
{
  va_list args;
  va_start(args, num_of_bitboards);

  for(uint8_t i=0;i<num_of_bitboards;i++){
    BITBOARD_Bitboard* bitboard = va_arg(args, BITBOARD_Bitboard*);
    bitboard_dest->half[0] &= bitboard->half[0];
    bitboard_dest->half[1] &= bitboard->half[1];
  }

  va_end(args);
}

void BITBOARD_BitwiseNOT(BITBOARD_Bitboard* bitboard_dest, BITBOARD_Bitboard* bitboard)
{
  bitboard_dest->half[0] = ~bitboard->half[0];
  bitboard_dest->half[1] = ~bitboard->half[1];
}

void BITBOARD_Multiply(BITBOARD_Bitboard* bitboard_dest, BITBOARD_Bitboard* bitboard_a, BITBOARD_Bitboard* bitboard_b)
{
  uint64_t low_low = (uint64_t)bitboard_a->half[0] * bitboard_b->half[0];   
  uint64_t low_high = (uint64_t)bitboard_a->half[0] * bitboard_b->half[1];   
  uint64_t high_low = (uint64_t)bitboard_a->half[1] * bitboard_b->half[0];   

  uint64_t temp = (low_low & 0xFFFFFFFFFFFFFFFFULL) + ((low_high & 0xFFFFFFFF) << 32) + ((high_low & 0xFFFFFFFF) << 32);   

  bitboard_dest->half[0] = (uint32_t)(temp & 0xFFFFFFFF);
  bitboard_dest->half[1] = (uint32_t)((temp >> 32) & 0xFFFFFFFF);
}

void BITBOARD_Subtract(BITBOARD_Bitboard* bitboard_dest, BITBOARD_Bitboard* bitboard_a, BITBOARD_Bitboard* bitboard_b)
{
  if(bitboard_a->half[0]<bitboard_b->half[0]){
    bitboard_dest->half[0] = (uint32_t)(bitboard_a->half[0] - bitboard_b->half[0]);
    bitboard_a->half[1]--; 
  }else{
    bitboard_dest->half[0] = bitboard_a->half[0] - bitboard_b->half[0];
  }
  bitboard_dest->half[1] = bitboard_a->half[1] - bitboard_b->half[1];
}

int8_t BITBOARD_CountTrailingZeros(BITBOARD_Bitboard* bitboard) {
  if (bitboard->half[0] != 0) {
      return __builtin_ctz(bitboard->half[0]);
  }
  if (bitboard->half[1] != 0) {
      return 32 + __builtin_ctz(bitboard->half[1]);
  }
  return -1;
}

void BITBOARD_SetBitboardToBitboard(BITBOARD_Bitboard* bitboard_dest, BITBOARD_Bitboard* bitboard)
{
  bitboard_dest->half[0] = bitboard->half[0];
  bitboard_dest->half[1] = bitboard->half[1];
}

uint8_t BITBOARD_FindSetBits(BITBOARD_Bitboard* bitboard, uint8_t* indexes)
{
  uint32_t lower = bitboard->half[0];
  uint32_t higher = bitboard->half[1];
  uint8_t count = 0;
  for(;lower;){
    indexes[count++] = __builtin_ctz(lower);
    lower &= (lower-1);
  }
  for(;higher;){
    indexes[count++] = 32+__builtin_ctz(higher);
    higher &= (higher-1);
  }
  return count;
}

void BITBOARD_RightShift(BITBOARD_Bitboard* bitboard_dest, BITBOARD_Bitboard* bitboard, uint8_t shift)
{
  *bitboard_dest = (BITBOARD_Bitboard){{0, 0}};
  if(shift==0){
    BITBOARD_SetBitboardToBitboard(bitboard_dest, bitboard);
    return;
  }

  if (shift >= 64) {
    bitboard_dest->half[0] = 0;
    bitboard_dest->half[1] = 0;
  } else if (shift >= 32) {
    bitboard_dest->half[0] = bitboard->half[1] >> (shift - 32);
    bitboard_dest->half[1] = 0;
  } else {
    bitboard_dest->half[0] = (bitboard->half[0] >> shift) | (bitboard->half[1] << (32 - shift));
    bitboard_dest->half[1] = bitboard->half[1] >> shift;
  }
}

void BITBOARD_LeftShift(BITBOARD_Bitboard* bitboard_dest, BITBOARD_Bitboard* bitboard, uint8_t shift)
{
  *bitboard_dest = (BITBOARD_Bitboard){{0, 0}};
  if(shift==0){
    BITBOARD_SetBitboardToBitboard(bitboard_dest, bitboard);
    return;
  }

  if (shift >= 64) {
    bitboard_dest->half[0] = 0;
    bitboard_dest->half[1] = 0;
  } else if (shift >= 32) {
    bitboard_dest->half[1] = bitboard->half[0] << (shift - 32);
    bitboard_dest->half[0] = 0;
  } else {
    bitboard_dest->half[1] = (bitboard->half[1] << shift) | (bitboard->half[0] >> (32 - shift));
    bitboard_dest->half[0] = bitboard->half[0] << shift;
  }
}

void BITBOARD_GetAttackMask_bishop(BITBOARD_Bitboard* bitboard_dest, uint8_t square, BITBOARD_Bitboard* bitboard_occupancy)
{
  BITBOARD_Bitboard temp1, temp2, temp3;
  BITBOARD_SetBitboardToBitboard(&temp1, bitboard_occupancy);
  BITBOARD_BitwiseAND(&temp1, 1, &BITBOARD_Masks_bishop[square]);
  BITBOARD_Multiply(&temp2, &temp1, &BITBOARD_Magics_bishop[square]);
  BITBOARD_RightShift(&temp3, &temp2, BITBOARD_Shift_bishop);
  BITBOARD_SetBitboardToBitboard(bitboard_dest, &BITBOARD_AttackTable_bishop[square][temp3.half[0]]);
  // printf("FINAL\n");
  // BITBOARD_Print(bitboard_dest);
}

void BITBOARD_GetAttackMask_rook(BITBOARD_Bitboard* bitboard_dest, uint8_t square, BITBOARD_Bitboard* bitboard_occupancy)
{
  BITBOARD_Bitboard temp1, temp2, temp3;
  BITBOARD_SetBitboardToBitboard(&temp1, bitboard_occupancy);
  BITBOARD_BitwiseAND(&temp1, 1, &BITBOARD_Masks_rook[square]);
  BITBOARD_Multiply(&temp2, &temp1, &BITBOARD_Magics_rook[square]);
  BITBOARD_RightShift(&temp3, &temp2, BITBOARD_Shift_rook[square]);
  BITBOARD_SetBitboardToBitboard(bitboard_dest, &BITBOARD_AttackTable_rook[square][temp3.half[0]]);
  // printf("FINAL\n");
  // BITBOARD_Print(bitboard_dest);
}

