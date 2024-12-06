#include "util.h"
#include <stdint.h>
#include <stdio.h>

uint8_t UTIL_GetBoolFromBools(uint8_t bool_8, uint8_t index)
{
  // daj mi hodnotu na indexovom bite 
  return bool_8>>index&1;
}

void UTIL_SetBoolInBools(uint8_t* bool_8, uint8_t index, uint8_t value)
{
  // nastav mi hodnotu value na indexovom bite 
  // TODO: toto pravdepodobne nefunguje (toto moze byt chyba ktoru hladas)
  (value)?(*bool_8|=1<<index):(*bool_8&=255-(1<<index));
}

void UTIL_SetBitIn64ToH(uint64_t* bitmap, uint8_t bit_index)
{
  *bitmap|=((uint64_t)1<<bit_index);; 
}

uint8_t UTIL_GetBitFrom64(uint64_t bitmap, uint8_t bit_index)
{
  return bitmap>>bit_index&1;
}

void UTIL_PrintBinary64(uint64_t num) {
  for (int i = 63; i >= 0; i--) {
    uint64_t bit = (num >> i) & 1;
    printf("%lu", bit);
    if (i % 8 == 0 && i != 0) {
      printf(" ");
    }
  }
  printf("\n");
}
