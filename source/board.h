#ifndef BOARD_H
#define BOARD_H

#include <string.h>
#include <stdint.h>
#include "bitboard.h"

// WHITE -> 1
// BLACK -> 0

#define INDEX_WIN 7
#define INDEX_DRAW 6
#define INDEX_ON_TURN 5
#define INDEX_GAME_END 4
#define INDEX_CCWK 3
#define INDEX_CCWQ 2
#define INDEX_CCBK 1
#define INDEX_CCBQ 0

typedef struct{
  int8_t from;
  int8_t to;
  int8_t promotion; // pre pesiakov
}BOARD_Move;

typedef struct{
  BOARD_Move list[256]; // malo by to stacit xd
  uint8_t count;
}BOARD_MoveList;

typedef struct{
  uint8_t bools;
  // bools: kazdy bit je jeden bool (v takomto poradi, odhora dole) 
  // 0
  // b
  // win;             7
  // draw;            6
  // onTurn;          5
  // gameEnd;         4    4
  // canCastleWK;     3
  // canCastleWQ;     2
  // canCastleBK;     1
  // canCastleBQ;     0

  // moves 
  BOARD_MoveList pseudoMoves;
  BOARD_MoveList legalMoves;

  int8_t enPassant;
  
  // (info)                        (high) 1 | 0 (low)
  // 0b 11111111 11111111 00000000 00000000 | 00000000 00000000 11111111 11111111
  BITBOARD_Bitboard white_pawns, white_rooks, white_knights, white_bishops, white_queens, white_king;
  BITBOARD_Bitboard black_pawns, black_rooks, black_knights, black_bishops, black_queens, black_king;
  BITBOARD_Bitboard white_pieces, black_pieces, all_pieces;
}BOARD_BoardState;

typedef struct{
  BOARD_BoardState board;
  // toto je len pre estetickost tejto verzie
  int selectedX, selectedY, pointingX, pointingY;
}BOARD_Board;

#include "raylib.h"
#include "main.h"
#include "bitboard.h"

void BOARD_PrintPrettyBoard(BOARD_BoardState* board);
void BOARD_PrintBitmaps(BOARD_Board* board);

BOARD_Board BOARD_SetupBoard(char* fen);
void BOARD_DrawBoard(BOARD_Board* board, int offx, int offy, uint8_t* bools);

uint8_t BOARD_IsCheck(BOARD_BoardState* board, int8_t square, uint8_t isWhite);

void BOARD_AddMove(BOARD_MoveList* moves, int8_t from, int8_t to, int8_t promotion);
void BOARD_MakeMove(BOARD_BoardState* board, BOARD_Move* move, uint8_t isWhite);
void BOARD_UndoMove(BOARD_BoardState* board, BOARD_Move* move, uint8_t isWhite);
void BOARD_PrintMoves(BOARD_MoveList* moves);
void BOARD_InitBoardStateCopy(BOARD_BoardState* board, BOARD_BoardState* boardCopy);

void BOARD_GeneratePseudoMoves_Pawn(BOARD_BoardState* board, uint8_t isWhite);
void BOARD_GeneratePseudoMoves_Knight(BOARD_BoardState* board, uint8_t isWhite);
void BOARD_GeneratePseudoMoves_Bishop(BOARD_BoardState* board, uint8_t isWhite);
void BOARD_GeneratePseudoMoves_Rook(BOARD_BoardState* board, uint8_t isWhite);
void BOARD_GeneratePseudoMoves_Queen(BOARD_BoardState* board, uint8_t isWhite);
void BOARD_GeneratePseudoMoves_King(BOARD_BoardState* board, uint8_t isWhite);
void BOARD_GenerateCastlingMoves(BOARD_BoardState* board, uint8_t isWhite);
void BOARD_GeneratePseudoMoves(BOARD_BoardState* board);
void BOARD_FilterLegalMoves(BOARD_BoardState* board);

void BOARD_PlayTurn(BOARD_Board* board, int offx, int offy);

#endif
