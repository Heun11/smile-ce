#include "board.h"
#include <stdint.h>

uint8_t BOARD_GetBoolFromBools(uint8_t bool_8, uint8_t index)
{
  // daj mi hodnotu na indexovom bite 
  switch(index){
    case 0: return (bool_8&0b00000001)==0b00000001;
    case 1: return (bool_8&0b00000010)==0b00000010;
    case 2: return (bool_8&0b00000100)==0b00000100;
    case 3: return (bool_8&0b00001000)==0b00001000;
    case 4: return (bool_8&0b00010000)==0b00010000;
    case 5: return (bool_8&0b00100000)==0b00100000;
    case 6: return (bool_8&0b01000000)==0b01000000;
    case 7: return (bool_8&0b10000000)==0b10000000;
    default: return 0;
  } 
}

void BOARD_SetBoolFromBools(uint8_t* bool_8, uint8_t index, uint8_t value)
{
  // nastav mi hodnotu value na indexovom bite 
  switch(index){
    case 0: (value)?(*bool_8|=0b00000001):(*bool_8&=0b11111110); break;
    case 1: (value)?(*bool_8|=0b00000010):(*bool_8&=0b11111101); break;
    case 2: (value)?(*bool_8|=0b00000100):(*bool_8&=0b11111011); break;
    case 3: (value)?(*bool_8|=0b00001000):(*bool_8&=0b11110111); break;
    case 4: (value)?(*bool_8|=0b00010000):(*bool_8&=0b11101111); break;
    case 5: (value)?(*bool_8|=0b00100000):(*bool_8&=0b11011111); break;
    case 6: (value)?(*bool_8|=0b01000000):(*bool_8&=0b10111111); break;
    case 7: (value)?(*bool_8|=0b10000000):(*bool_8&=0b01111111); break;
  } 
}

