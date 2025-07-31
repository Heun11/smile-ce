#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>

void UTIL_SetBoolInBools(uint8_t* bool_8, uint8_t index, uint8_t value);
uint8_t UTIL_GetBoolFromBools(uint8_t bool_8, uint8_t index);
void UTIL_SetBitIn32ToH(uint32_t* bitmap, uint8_t bit_index);
uint8_t UTIL_GetBitFrom32(uint32_t bitmap, uint8_t bit_index);

#include "board.h"

void UTIL_ShuffleMoves(BOARD_MoveList* moves);

#endif
