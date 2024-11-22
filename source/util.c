#include "util.h"
#include <stdint.h>

uint8_t UTIL_GetBoolFromBools(uint8_t bool_8, uint8_t index)
{
  // daj mi hodnotu na indexovom bite 
  return (bool_8&1<<index)==1<<index;
}

void UTIL_SetBoolFromBools(uint8_t* bool_8, uint8_t index, uint8_t value)
{
  // nastav mi hodnotu value na indexovom bite 
  (value)?(*bool_8|=1<<index):(*bool_8&=255-(1<<index));
}
