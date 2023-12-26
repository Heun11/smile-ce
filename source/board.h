#ifndef BOARD_H
#define BOARD_H

// pieces using FEN
// p P - pawn
// r R - rook
// n N - knight
// b B - biship
// q Q - queen
// k K - king

typedef struct{
  char board[8][8];

  int onTurn;

  int canCastleWK;
  int canCastleWQ;
  int canCastleBK;
  int canCastleBQ;
}BOARD_Board;

#include "raylib.h"
#include <string.h>
#include <ctype.h>

BOARD_Board BOARD_SetupBoard(char* fen);
void BOARD_DrawBoard(BOARD_Board* board, int offx, int offy);

#endif
