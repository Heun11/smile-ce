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
//
// WHITE -> 1
// BLACK -> 0

#define INDEX_ON_TURN 5
#define INDEX_WIN 4
#define INDEX_CCWK 3
#define INDEX_CCWQ 2
#define INDEX_CCBK 1
#define INDEX_CCBQ 0

typedef struct{
  uint8_t x, y;
}BOARD_Vec2;

typedef struct{
  uint8_t len;
  BOARD_Vec2 moves[27]; // najviac tahov co sa da spravit (queen)
}BOARD_Moves;

typedef struct{
  uint8_t bools;
  // bools: kazdy bit je jeden bool (v takomto poradi, odhora dole) 
  // 0
  // b
  // 0                7
  // 0                6
  // onTurn;          5
  // win;             4
  // canCastleWK;     3
  // canCastleWQ;     2
  // canCastleBK;     1
  // canCastleBQ;     0

  // (info)                        (high) 1 | 0 (low)
  // 0b 11111111 11111111 00000000 00000000 | 00000000 00000000 11111111 11111111

  uint32_t white_pawns[2], white_rooks[2], white_knights[2], white_bishops[2], white_queens[2], white_king[2];
  uint32_t black_pawns[2], black_rooks[2], black_knights[2], black_bishops[2], black_queens[2], black_king[2];
  uint32_t white_pieces[2], black_pieces[2], all_pieces[2];
}BOARD_Board;

#include "raylib.h"
#include "main.h"
#include <string.h>
#include <ctype.h>

void BOARD_PrintBitmaps(BOARD_Board* board);
BOARD_Board BOARD_SetupBoard(char* fen);
void BOARD_DrawBoard(BOARD_Board* board, int offx, int offy);

#endif
