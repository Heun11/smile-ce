#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>

void UTIL_SetBoolInBools(uint8_t* bool_8, uint8_t index, uint8_t value);
uint8_t UTIL_GetBoolFromBools(uint8_t bool_8, uint8_t index);
void UTIL_SetBitIn64ToH(uint64_t* bitmap, uint8_t bit_index);
uint8_t UTIL_GetBitFrom64(uint64_t bitmap, uint8_t bit_index);
void UTIL_PrintBinary64(uint64_t num);

#endif
