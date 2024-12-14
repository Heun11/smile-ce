#include "bitboard.h"
#include <stdint.h>
#include <stdarg.h>

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
