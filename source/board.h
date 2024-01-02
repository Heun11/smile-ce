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
  int x, y;
}BOARD_Vec2;

typedef struct{
  int len;
  BOARD_Vec2* moves;
}BOARD_Moves;

typedef struct{
  char board[8][8];

  int onTurn;
  int win;

  BOARD_Vec2 selectedPiece;
  BOARD_Vec2 kingPosW;
  BOARD_Vec2 kingPosB;

  BOARD_Vec2 enPassant;
  int enPassantColor;

  char promotion;

  int canCastleWK;
  int canCastleWQ;
  int canCastleBK;
  int canCastleBQ;
}BOARD_Board;

#include "raylib.h"
#include "main.h"
#include <string.h>
#include <ctype.h>

BOARD_Board BOARD_SetupBoard(char* fen);
void BOARD_DrawBoard(BOARD_Board* board, int offx, int offy);

int BOARD_IsGameEnd(BOARD_Board *board, int color);
int BOARD_IsCheck(BOARD_Board* board, int color);
BOARD_Moves BOARD_GenerateMoves(BOARD_Board* board);
void BOARD_AppendMove(BOARD_Board* board, BOARD_Moves* moves, int nx, int ny);
void BOARD_MakeMove(BOARD_Board* board, int ox, int oy);

#endif
