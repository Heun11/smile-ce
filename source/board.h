#ifndef BOARD_H
#define BOARD_H

#include "stdint.h"
#include <stdint.h>

// pieces using FEN
// p P - pawn
// r R - rook
// n N - knight
// b B - biship
// q Q - queen
// k K - king

typedef struct{
  uint8_t x, y;
}BOARD_Vec2;

typedef struct{
  uint8_t len;
  BOARD_Vec2 moves[27]; // najviac tahov co sa da spravit (queen)
}BOARD_Moves;

typedef struct{
  char board[8][8];

  BOARD_Vec2 selectedPiece;
  BOARD_Vec2 kingPosW;
  BOARD_Vec2 kingPosB;

  char promotion;
  
  BOARD_Vec2 enPassant;

  char bools;

  // bools: kazdy bit je jeden bool (v takomto poradi, odhora dole) 
  // 0
  // b
  // 0
  // enPassantColor;
  // onTurn;
  // win;
  // canCastleWK;
  // canCastleWQ;
  // canCastleBK;
  // canCastleBQ;

}BOARD_Board;

#include "raylib.h"
#include "main.h"
#include <string.h>
#include <ctype.h>

BOARD_Board BOARD_SetupBoard(char* fen);
void BOARD_DrawBoard(BOARD_Board* board, int offx, int offy);


uint8_t BOARD_GetBoolFromBools(uint8_t bool_8, uint8_t index);
void BOARD_SetBoolFromBools(uint8_t* bool_8, uint8_t index, uint8_t value);

#endif
