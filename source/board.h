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

  uint64_t white_pawns, white_rooks, white_knights, 
           white_bishops, white_queens, white_king;
  uint64_t black_pawns, black_rooks, black_knights, 
           black_bishops, black_queens, black_king;
  uint64_t white_pieces, black_pieces, all_pieces;
}BOARD_Board;


extern uint64_t BOARD_attackMask_Knight[64];
extern uint64_t BOARD_attackMask_Rook[64];
extern uint64_t BOARD_attackMask_Bishop[64];


#include "raylib.h"
#include "main.h"
#include <string.h>
#include <ctype.h>

void BOARD_PrintBitmaps(BOARD_Board* board);
BOARD_Board BOARD_SetupBoard(char* fen);
void BOARD_DrawBoard(BOARD_Board* board, int offx, int offy);

#endif
