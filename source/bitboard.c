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

void BITBOARD_Multiply(BITBOARD_Bitboard* bitboard_dest, BITBOARD_Bitboard* bitboard_a, BITBOARD_Bitboard* bitboard_b)
{
  // toto nefunguje lebo chatgpt odmieta spolupracovat :D
}


// bitboards definition

BITBOARD_Bitboard BITBOARD_Masks_knight[64] = {
    (BITBOARD_Bitboard){{0x00020400, 0x00000000}},
    (BITBOARD_Bitboard){{0x00050800, 0x00000000}},
    (BITBOARD_Bitboard){{0x000A1100, 0x00000000}},
    (BITBOARD_Bitboard){{0x00142200, 0x00000000}},
    (BITBOARD_Bitboard){{0x00284400, 0x00000000}},
    (BITBOARD_Bitboard){{0x00508800, 0x00000000}},
    (BITBOARD_Bitboard){{0x00A01000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00402000, 0x00000000}},
    (BITBOARD_Bitboard){{0x02040004, 0x00000000}},
    (BITBOARD_Bitboard){{0x05080008, 0x00000000}},
    (BITBOARD_Bitboard){{0x0A110011, 0x00000000}},
    (BITBOARD_Bitboard){{0x14220022, 0x00000000}},
    (BITBOARD_Bitboard){{0x28440044, 0x00000000}},
    (BITBOARD_Bitboard){{0x50880088, 0x00000000}},
    (BITBOARD_Bitboard){{0xA0100010, 0x00000000}},
    (BITBOARD_Bitboard){{0x40200020, 0x00000000}},
    (BITBOARD_Bitboard){{0x04000402, 0x00000002}},
    (BITBOARD_Bitboard){{0x08000805, 0x00000005}},
    (BITBOARD_Bitboard){{0x1100110A, 0x0000000A}},
    (BITBOARD_Bitboard){{0x22002214, 0x00000014}},
    (BITBOARD_Bitboard){{0x44004428, 0x00000028}},
    (BITBOARD_Bitboard){{0x88008850, 0x00000050}},
    (BITBOARD_Bitboard){{0x100010A0, 0x000000A0}},
    (BITBOARD_Bitboard){{0x20002040, 0x00000040}},
    (BITBOARD_Bitboard){{0x00040200, 0x00000204}},
    (BITBOARD_Bitboard){{0x00080500, 0x00000508}},
    (BITBOARD_Bitboard){{0x00110A00, 0x00000A11}},
    (BITBOARD_Bitboard){{0x00221400, 0x00001422}},
    (BITBOARD_Bitboard){{0x00442800, 0x00002844}},
    (BITBOARD_Bitboard){{0x00885000, 0x00005088}},
    (BITBOARD_Bitboard){{0x0010A000, 0x0000A010}},
    (BITBOARD_Bitboard){{0x00204000, 0x00004020}},
    (BITBOARD_Bitboard){{0x04020000, 0x00020400}},
    (BITBOARD_Bitboard){{0x08050000, 0x00050800}},
    (BITBOARD_Bitboard){{0x110A0000, 0x000A1100}},
    (BITBOARD_Bitboard){{0x22140000, 0x00142200}},
    (BITBOARD_Bitboard){{0x44280000, 0x00284400}},
    (BITBOARD_Bitboard){{0x88500000, 0x00508800}},
    (BITBOARD_Bitboard){{0x10A00000, 0x00A01000}},
    (BITBOARD_Bitboard){{0x20400000, 0x00402000}},
    (BITBOARD_Bitboard){{0x02000000, 0x02040004}},
    (BITBOARD_Bitboard){{0x05000000, 0x05080008}},
    (BITBOARD_Bitboard){{0x0A000000, 0x0A110011}},
    (BITBOARD_Bitboard){{0x14000000, 0x14220022}},
    (BITBOARD_Bitboard){{0x28000000, 0x28440044}},
    (BITBOARD_Bitboard){{0x50000000, 0x50880088}},
    (BITBOARD_Bitboard){{0xA0000000, 0xA0100010}},
    (BITBOARD_Bitboard){{0x40000000, 0x40200020}},
    (BITBOARD_Bitboard){{0x00000000, 0x04000402}},
    (BITBOARD_Bitboard){{0x00000000, 0x08000805}},
    (BITBOARD_Bitboard){{0x00000000, 0x1100110A}},
    (BITBOARD_Bitboard){{0x00000000, 0x22002214}},
    (BITBOARD_Bitboard){{0x00000000, 0x44004428}},
    (BITBOARD_Bitboard){{0x00000000, 0x88008850}},
    (BITBOARD_Bitboard){{0x00000000, 0x100010A0}},
    (BITBOARD_Bitboard){{0x00000000, 0x20002040}},
    (BITBOARD_Bitboard){{0x00000000, 0x00040200}},
    (BITBOARD_Bitboard){{0x00000000, 0x00080500}},
    (BITBOARD_Bitboard){{0x00000000, 0x00110A00}},
    (BITBOARD_Bitboard){{0x00000000, 0x00221400}},
    (BITBOARD_Bitboard){{0x00000000, 0x00442800}},
    (BITBOARD_Bitboard){{0x00000000, 0x00885000}},
    (BITBOARD_Bitboard){{0x00000000, 0x0010A000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00204000}}
};

BITBOARD_Bitboard BITBOARD_Masks_king[64] = {
    (BITBOARD_Bitboard){{0x00000302, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000705, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000E0A, 0x00000000}},
    (BITBOARD_Bitboard){{0x00001C14, 0x00000000}},
    (BITBOARD_Bitboard){{0x00003828, 0x00000000}},
    (BITBOARD_Bitboard){{0x00007050, 0x00000000}},
    (BITBOARD_Bitboard){{0x0000E0A0, 0x00000000}},
    (BITBOARD_Bitboard){{0x0000C040, 0x00000000}},
    (BITBOARD_Bitboard){{0x00030203, 0x00000000}},
    (BITBOARD_Bitboard){{0x00070507, 0x00000000}},
    (BITBOARD_Bitboard){{0x000E0A0E, 0x00000000}},
    (BITBOARD_Bitboard){{0x001C141C, 0x00000000}},
    (BITBOARD_Bitboard){{0x00382838, 0x00000000}},
    (BITBOARD_Bitboard){{0x00705070, 0x00000000}},
    (BITBOARD_Bitboard){{0x00E0A0E0, 0x00000000}},
    (BITBOARD_Bitboard){{0x00C040C0, 0x00000000}},
    (BITBOARD_Bitboard){{0x03020300, 0x00000000}},
    (BITBOARD_Bitboard){{0x07050700, 0x00000000}},
    (BITBOARD_Bitboard){{0x0E0A0E00, 0x00000000}},
    (BITBOARD_Bitboard){{0x1C141C00, 0x00000000}},
    (BITBOARD_Bitboard){{0x38283800, 0x00000000}},
    (BITBOARD_Bitboard){{0x70507000, 0x00000000}},
    (BITBOARD_Bitboard){{0xE0A0E000, 0x00000000}},
    (BITBOARD_Bitboard){{0xC040C000, 0x00000000}},
    (BITBOARD_Bitboard){{0x02030000, 0x00000003}},
    (BITBOARD_Bitboard){{0x05070000, 0x00000007}},
    (BITBOARD_Bitboard){{0x0A0E0000, 0x0000000E}},
    (BITBOARD_Bitboard){{0x141C0000, 0x0000001C}},
    (BITBOARD_Bitboard){{0x28380000, 0x00000038}},
    (BITBOARD_Bitboard){{0x50700000, 0x00000070}},
    (BITBOARD_Bitboard){{0xA0E00000, 0x000000E0}},
    (BITBOARD_Bitboard){{0x40C00000, 0x000000C0}},
    (BITBOARD_Bitboard){{0x03000000, 0x00000302}},
    (BITBOARD_Bitboard){{0x07000000, 0x00000705}},
    (BITBOARD_Bitboard){{0x0E000000, 0x00000E0A}},
    (BITBOARD_Bitboard){{0x1C000000, 0x00001C14}},
    (BITBOARD_Bitboard){{0x38000000, 0x00003828}},
    (BITBOARD_Bitboard){{0x70000000, 0x00007050}},
    (BITBOARD_Bitboard){{0xE0000000, 0x0000E0A0}},
    (BITBOARD_Bitboard){{0xC0000000, 0x0000C040}},
    (BITBOARD_Bitboard){{0x00000000, 0x00030203}},
    (BITBOARD_Bitboard){{0x00000000, 0x00070507}},
    (BITBOARD_Bitboard){{0x00000000, 0x000E0A0E}},
    (BITBOARD_Bitboard){{0x00000000, 0x001C141C}},
    (BITBOARD_Bitboard){{0x00000000, 0x00382838}},
    (BITBOARD_Bitboard){{0x00000000, 0x00705070}},
    (BITBOARD_Bitboard){{0x00000000, 0x00E0A0E0}},
    (BITBOARD_Bitboard){{0x00000000, 0x00C040C0}},
    (BITBOARD_Bitboard){{0x00000000, 0x03020300}},
    (BITBOARD_Bitboard){{0x00000000, 0x07050700}},
    (BITBOARD_Bitboard){{0x00000000, 0x0E0A0E00}},
    (BITBOARD_Bitboard){{0x00000000, 0x1C141C00}},
    (BITBOARD_Bitboard){{0x00000000, 0x38283800}},
    (BITBOARD_Bitboard){{0x00000000, 0x70507000}},
    (BITBOARD_Bitboard){{0x00000000, 0xE0A0E000}},
    (BITBOARD_Bitboard){{0x00000000, 0xC040C000}},
    (BITBOARD_Bitboard){{0x00000000, 0x02030000}},
    (BITBOARD_Bitboard){{0x00000000, 0x05070000}},
    (BITBOARD_Bitboard){{0x00000000, 0x0A0E0000}},
    (BITBOARD_Bitboard){{0x00000000, 0x141C0000}},
    (BITBOARD_Bitboard){{0x00000000, 0x28380000}},
    (BITBOARD_Bitboard){{0x00000000, 0x50700000}},
    (BITBOARD_Bitboard){{0x00000000, 0xA0E00000}},
    (BITBOARD_Bitboard){{0x00000000, 0x40C00000}}
};

BITBOARD_Bitboard BITBOARD_Masks_pawnSinglePush[2][64] = {
  { 
    (BITBOARD_Bitboard){{0x00000100, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000200, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000400, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000800, 0x00000000}},
    (BITBOARD_Bitboard){{0x00001000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00002000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00004000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00008000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00010000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00020000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00040000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00080000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00100000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00200000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00400000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00800000, 0x00000000}},
    (BITBOARD_Bitboard){{0x01000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x02000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x04000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x08000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x10000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x20000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x40000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x80000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000001}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000002}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000004}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000008}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000010}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000020}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000040}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000080}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000100}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000200}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000400}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000800}},
    (BITBOARD_Bitboard){{0x00000000, 0x00001000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00002000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00004000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00008000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00010000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00020000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00040000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00080000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00100000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00200000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00400000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00800000}},
    (BITBOARD_Bitboard){{0x00000000, 0x01000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x02000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x04000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x08000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x10000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x20000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x40000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x80000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}}
  },
  {
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000001, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000002, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000004, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000008, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000010, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000020, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000040, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000080, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000100, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000200, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000400, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000800, 0x00000000}},
    (BITBOARD_Bitboard){{0x00001000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00002000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00004000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00008000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00010000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00020000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00040000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00080000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00100000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00200000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00400000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00800000, 0x00000000}},
    (BITBOARD_Bitboard){{0x01000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x02000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x04000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x08000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x10000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x20000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x40000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x80000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000001}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000002}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000004}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000008}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000010}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000020}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000040}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000080}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000100}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000200}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000400}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000800}},
    (BITBOARD_Bitboard){{0x00000000, 0x00001000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00002000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00004000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00008000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00010000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00020000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00040000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00080000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00100000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00200000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00400000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00800000}}
  }
};

BITBOARD_Bitboard BITBOARD_Masks_pawnDoublePush[2][64] = {
  {
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x01000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x02000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x04000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x08000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x10000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x20000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x40000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x80000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}}
  },
  {
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000001}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000002}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000004}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000008}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000010}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000020}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000040}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000080}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}}
  }
};

BITBOARD_Bitboard BITBOARD_AttackMasks_pawn[2][64] = {
  {
    (BITBOARD_Bitboard){{0x00000200, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000500, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000A00, 0x00000000}},
    (BITBOARD_Bitboard){{0x00001400, 0x00000000}},
    (BITBOARD_Bitboard){{0x00002800, 0x00000000}},
    (BITBOARD_Bitboard){{0x00005000, 0x00000000}},
    (BITBOARD_Bitboard){{0x0000A000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00004000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00020000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00050000, 0x00000000}},
    (BITBOARD_Bitboard){{0x000A0000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00140000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00280000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00500000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00A00000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00400000, 0x00000000}},
    (BITBOARD_Bitboard){{0x02000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x05000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x0A000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x14000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x28000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x50000000, 0x00000000}},
    (BITBOARD_Bitboard){{0xA0000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x40000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000002}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000005}},
    (BITBOARD_Bitboard){{0x00000000, 0x0000000A}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000014}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000028}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000050}},
    (BITBOARD_Bitboard){{0x00000000, 0x000000A0}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000040}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000200}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000500}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000A00}},
    (BITBOARD_Bitboard){{0x00000000, 0x00001400}},
    (BITBOARD_Bitboard){{0x00000000, 0x00002800}},
    (BITBOARD_Bitboard){{0x00000000, 0x00005000}},
    (BITBOARD_Bitboard){{0x00000000, 0x0000A000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00004000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00020000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00050000}},
    (BITBOARD_Bitboard){{0x00000000, 0x000A0000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00140000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00280000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00500000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00A00000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00400000}},
    (BITBOARD_Bitboard){{0x00000000, 0x02000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x05000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x0A000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x14000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x28000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x50000000}},
    (BITBOARD_Bitboard){{0x00000000, 0xA0000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x40000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}}
  },
  {
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000002, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000005, 0x00000000}},
    (BITBOARD_Bitboard){{0x0000000A, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000014, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000028, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000050, 0x00000000}},
    (BITBOARD_Bitboard){{0x000000A0, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000040, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000200, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000500, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000A00, 0x00000000}},
    (BITBOARD_Bitboard){{0x00001400, 0x00000000}},
    (BITBOARD_Bitboard){{0x00002800, 0x00000000}},
    (BITBOARD_Bitboard){{0x00005000, 0x00000000}},
    (BITBOARD_Bitboard){{0x0000A000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00004000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00020000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00050000, 0x00000000}},
    (BITBOARD_Bitboard){{0x000A0000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00140000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00280000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00500000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00A00000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00400000, 0x00000000}},
    (BITBOARD_Bitboard){{0x02000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x05000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x0A000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x14000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x28000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x50000000, 0x00000000}},
    (BITBOARD_Bitboard){{0xA0000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x40000000, 0x00000000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000002}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000005}},
    (BITBOARD_Bitboard){{0x00000000, 0x0000000A}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000014}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000028}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000050}},
    (BITBOARD_Bitboard){{0x00000000, 0x000000A0}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000040}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000200}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000500}},
    (BITBOARD_Bitboard){{0x00000000, 0x00000A00}},
    (BITBOARD_Bitboard){{0x00000000, 0x00001400}},
    (BITBOARD_Bitboard){{0x00000000, 0x00002800}},
    (BITBOARD_Bitboard){{0x00000000, 0x00005000}},
    (BITBOARD_Bitboard){{0x00000000, 0x0000A000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00004000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00020000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00050000}},
    (BITBOARD_Bitboard){{0x00000000, 0x000A0000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00140000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00280000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00500000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00A00000}},
    (BITBOARD_Bitboard){{0x00000000, 0x00400000}}
  }
};

BITBOARD_Bitboard BITBOARD_Masks_rook[64] = {
  (BITBOARD_Bitboard){{0x010101FE, 0x01010101}},
  (BITBOARD_Bitboard){{0x020202FD, 0x02020202}},
  (BITBOARD_Bitboard){{0x040404FB, 0x04040404}},
  (BITBOARD_Bitboard){{0x080808F7, 0x08080808}},
  (BITBOARD_Bitboard){{0x101010EF, 0x10101010}},
  (BITBOARD_Bitboard){{0x202020DF, 0x20202020}},
  (BITBOARD_Bitboard){{0x404040BF, 0x40404040}},
  (BITBOARD_Bitboard){{0x8080807F, 0x80808080}},
  (BITBOARD_Bitboard){{0x0101FE01, 0x01010101}},
  (BITBOARD_Bitboard){{0x0202FD02, 0x02020202}},
  (BITBOARD_Bitboard){{0x0404FB04, 0x04040404}},
  (BITBOARD_Bitboard){{0x0808F708, 0x08080808}},
  (BITBOARD_Bitboard){{0x1010EF10, 0x10101010}},
  (BITBOARD_Bitboard){{0x2020DF20, 0x20202020}},
  (BITBOARD_Bitboard){{0x4040BF40, 0x40404040}},
  (BITBOARD_Bitboard){{0x80807F80, 0x80808080}},
  (BITBOARD_Bitboard){{0x01FE0101, 0x01010101}},
  (BITBOARD_Bitboard){{0x02FD0202, 0x02020202}},
  (BITBOARD_Bitboard){{0x04FB0404, 0x04040404}},
  (BITBOARD_Bitboard){{0x08F70808, 0x08080808}},
  (BITBOARD_Bitboard){{0x10EF1010, 0x10101010}},
  (BITBOARD_Bitboard){{0x20DF2020, 0x20202020}},
  (BITBOARD_Bitboard){{0x40BF4040, 0x40404040}},
  (BITBOARD_Bitboard){{0x807F8080, 0x80808080}},
  (BITBOARD_Bitboard){{0xFE010101, 0x01010101}},
  (BITBOARD_Bitboard){{0xFD020202, 0x02020202}},
  (BITBOARD_Bitboard){{0xFB040404, 0x04040404}},
  (BITBOARD_Bitboard){{0xF7080808, 0x08080808}},
  (BITBOARD_Bitboard){{0xEF101010, 0x10101010}},
  (BITBOARD_Bitboard){{0xDF202020, 0x20202020}},
  (BITBOARD_Bitboard){{0xBF404040, 0x40404040}},
  (BITBOARD_Bitboard){{0x7F808080, 0x80808080}},
  (BITBOARD_Bitboard){{0x01010101, 0x010101FE}},
  (BITBOARD_Bitboard){{0x02020202, 0x020202FD}},
  (BITBOARD_Bitboard){{0x04040404, 0x040404FB}},
  (BITBOARD_Bitboard){{0x08080808, 0x080808F7}},
  (BITBOARD_Bitboard){{0x10101010, 0x101010EF}},
  (BITBOARD_Bitboard){{0x20202020, 0x202020DF}},
  (BITBOARD_Bitboard){{0x40404040, 0x404040BF}},
  (BITBOARD_Bitboard){{0x80808080, 0x8080807F}},
  (BITBOARD_Bitboard){{0x01010101, 0x0101FE01}},
  (BITBOARD_Bitboard){{0x02020202, 0x0202FD02}},
  (BITBOARD_Bitboard){{0x04040404, 0x0404FB04}},
  (BITBOARD_Bitboard){{0x08080808, 0x0808F708}},
  (BITBOARD_Bitboard){{0x10101010, 0x1010EF10}},
  (BITBOARD_Bitboard){{0x20202020, 0x2020DF20}},
  (BITBOARD_Bitboard){{0x40404040, 0x4040BF40}},
  (BITBOARD_Bitboard){{0x80808080, 0x80807F80}},
  (BITBOARD_Bitboard){{0x01010101, 0x01FE0101}},
  (BITBOARD_Bitboard){{0x02020202, 0x02FD0202}},
  (BITBOARD_Bitboard){{0x04040404, 0x04FB0404}},
  (BITBOARD_Bitboard){{0x08080808, 0x08F70808}},
  (BITBOARD_Bitboard){{0x10101010, 0x10EF1010}},
  (BITBOARD_Bitboard){{0x20202020, 0x20DF2020}},
  (BITBOARD_Bitboard){{0x40404040, 0x40BF4040}},
  (BITBOARD_Bitboard){{0x80808080, 0x807F8080}},
  (BITBOARD_Bitboard){{0x01010101, 0xFE010101}},
  (BITBOARD_Bitboard){{0x02020202, 0xFD020202}},
  (BITBOARD_Bitboard){{0x04040404, 0xFB040404}},
  (BITBOARD_Bitboard){{0x08080808, 0xF7080808}},
  (BITBOARD_Bitboard){{0x10101010, 0xEF101010}},
  (BITBOARD_Bitboard){{0x20202020, 0xDF202020}},
  (BITBOARD_Bitboard){{0x40404040, 0xBF404040}},
  (BITBOARD_Bitboard){{0x80808080, 0x7F808080}}
};

BITBOARD_Bitboard BITBOARD_Magics_rook[64] = {
  (BITBOARD_Bitboard){{0x00800020, 0x8A801040}},
  (BITBOARD_Bitboard){{0x08001200, 0x14000200}},
  (BITBOARD_Bitboard){{0x04000200, 0x80008080}},
  (BITBOARD_Bitboard){{0x02000040, 0x80010080}},
  (BITBOARD_Bitboard){{0x80002000, 0x01001000}},
  (BITBOARD_Bitboard){{0x40100020, 0x02002000}},
  (BITBOARD_Bitboard){{0x20080040, 0x03000800}},
  (BITBOARD_Bitboard){{0x01080080, 0x82000840}},
  (BITBOARD_Bitboard){{0x08004000, 0x40008080}},
  (BITBOARD_Bitboard){{0x00220080, 0x04010004}},
  (BITBOARD_Bitboard){{0x80004000, 0x00008000}},
  (BITBOARD_Bitboard){{0x80080080, 0x00002000}},
  (BITBOARD_Bitboard){{0x80100080, 0x00001000}},
  (BITBOARD_Bitboard){{0x80200080, 0x00004000}},
  (BITBOARD_Bitboard){{0x80800400, 0x00008000}},
  (BITBOARD_Bitboard){{0x40008080, 0x00008000}},
  (BITBOARD_Bitboard){{0x40008080, 0x00002000}},
  (BITBOARD_Bitboard){{0x80200040, 0x08004000}},
  (BITBOARD_Bitboard){{0x00200400, 0x00008002}},
  (BITBOARD_Bitboard){{0x00200080, 0x00001002}},
  (BITBOARD_Bitboard){{0x00200040, 0x00002001}},
  (BITBOARD_Bitboard){{0x80200020, 0x00004000}},
  (BITBOARD_Bitboard){{0x40008020, 0x00008000}},
  (BITBOARD_Bitboard){{0x00800400, 0x00008002}},
  (BITBOARD_Bitboard){{0x00400080, 0x00010008}},
  (BITBOARD_Bitboard){{0x00400100, 0x00080020}},
  (BITBOARD_Bitboard){{0x02002004, 0x00080008}},
  (BITBOARD_Bitboard){{0x08080040, 0x00800200}},
  (BITBOARD_Bitboard){{0x20020080, 0x00800400}},
  (BITBOARD_Bitboard){{0x40008020, 0x00800200}},
  (BITBOARD_Bitboard){{0x40020040, 0x00800100}},
  (BITBOARD_Bitboard){{0x08040040, 0x00800800}},
  (BITBOARD_Bitboard){{0x00404000, 0x00008020}},
  (BITBOARD_Bitboard){{0x00808000, 0x00008020}},
  (BITBOARD_Bitboard){{0x00800040, 0x00008040}},
  (BITBOARD_Bitboard){{0x00400040, 0x00008040}},
  (BITBOARD_Bitboard){{0x00800040, 0x00008001}},
  (BITBOARD_Bitboard){{0x00400040, 0x00008001}},
  (BITBOARD_Bitboard){{0x00400020, 0x00008020}},
  (BITBOARD_Bitboard){{0x00800040, 0x00008020}},
  (BITBOARD_Bitboard){{0x00400200, 0x00008040}},
  (BITBOARD_Bitboard){{0x00400200, 0x00008008}},
  (BITBOARD_Bitboard){{0x00800200, 0x00008004}},
  (BITBOARD_Bitboard){{0x00800100, 0x00008004}},
  (BITBOARD_Bitboard){{0x00800400, 0x00008002}},
  (BITBOARD_Bitboard){{0x00400400, 0x00008002}},
  (BITBOARD_Bitboard){{0x00800400, 0x00008001}},
  (BITBOARD_Bitboard){{0x00800200, 0x00008001}},
  (BITBOARD_Bitboard){{0x00400040, 0x00008008}},
  (BITBOARD_Bitboard){{0x00800040, 0x00008004}},
  (BITBOARD_Bitboard){{0x00400080, 0x00008004}},
  (BITBOARD_Bitboard){{0x00400100, 0x00008004}},
  (BITBOARD_Bitboard){{0x00400200, 0x00008002}},
  (BITBOARD_Bitboard){{0x00400100, 0x00008002}},
  (BITBOARD_Bitboard){{0x00400200, 0x00008001}},
  (BITBOARD_Bitboard){{0x00800100, 0x00008001}},
  (BITBOARD_Bitboard){{0x00400080, 0x00008008}},
  (BITBOARD_Bitboard){{0x00800100, 0x00008008}},
  (BITBOARD_Bitboard){{0x00400200, 0x00008008}},
  (BITBOARD_Bitboard){{0x00800200, 0x00008008}},
  (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
  (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
  (BITBOARD_Bitboard){{0x00000000, 0x00000000}},
  (BITBOARD_Bitboard){{0x00000000, 0x00000000}}
};

const uint8_t BITBOARD_Shifts[64] = {
  12, 11, 11, 11, 11, 11, 11, 12,
  11, 10, 10, 10, 10, 10, 10, 11,
  11, 10, 10, 10, 10, 10, 10, 11,
  11, 10, 10, 10, 10, 10, 10, 11,
  11, 10, 10, 10, 10, 10, 10, 11,
  11, 10, 10, 10, 10, 10, 10, 11,
  11, 10, 10, 10, 10, 10, 10, 11,
  12, 11, 11, 11, 11, 11, 11, 12,
};

