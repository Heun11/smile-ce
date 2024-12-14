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
