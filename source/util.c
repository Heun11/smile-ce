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

void UTIL_SetBitIn32ToH(uint32_t* bitmap, uint8_t bit_index)
{
  *bitmap|=((uint32_t)1<<bit_index); 
}

uint8_t UTIL_GetBitFrom32(uint32_t bitmap, uint8_t bit_index)
{
  return bitmap>>bit_index&1;
}

void UTIL_ShuffleMoves(BOARD_MoveList* moves) 
{
  for (int i = moves->count - 1; i > 0; i--) {
    int j = rand() % (i + 1);
    // Swap list[i] and list[j]
    BOARD_Move temp = moves->list[i];
    moves->list[i] = moves->list[j];
    moves->list[j] = temp;
  }
}
