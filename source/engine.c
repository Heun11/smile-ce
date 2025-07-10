#include "engine.h"
#include "bitboard_func.h"
#include "board.h"
#include "util.h"
#include <stdint.h>

uint8_t ENGINE_EvaluatePosition(BOARD_BoardState* board)
{
  int8_t black_count = 0, white_count = 0;

  black_count += __builtin_popcount(board->black_pawns.half[0])*1+__builtin_popcount(board->black_pawns.half[1])*1; 
  black_count += __builtin_popcount(board->black_knights.half[0])*3+__builtin_popcount(board->black_knights.half[1])*3; 
  black_count += __builtin_popcount(board->black_bishops.half[0])*3+__builtin_popcount(board->black_bishops.half[1])*3; 
  black_count += __builtin_popcount(board->black_rooks.half[0])*5+__builtin_popcount(board->black_rooks.half[1])*5; 
  black_count += __builtin_popcount(board->black_queens.half[0])*9+__builtin_popcount(board->black_queens.half[1])*9;

  white_count += __builtin_popcount(board->white_pawns.half[0])*1+__builtin_popcount(board->white_pawns.half[1])*1; 
  white_count += __builtin_popcount(board->white_knights.half[0])*3+__builtin_popcount(board->white_knights.half[1])*3; 
  white_count += __builtin_popcount(board->white_bishops.half[0])*3+__builtin_popcount(board->white_bishops.half[1])*3; 
  white_count += __builtin_popcount(board->white_rooks.half[0])*5+__builtin_popcount(board->white_rooks.half[1])*5; 
  white_count += __builtin_popcount(board->white_queens.half[0])*9+__builtin_popcount(board->white_queens.half[1])*9;

  return white_count-black_count; 
}

uint8_t ENGINE_Minimax(BOARD_BoardState* board, uint8_t depth, uint8_t isWhite)
{
  BOARD_BoardState boardCopy;
  BOARD_InitBoardStateCopy(board, &boardCopy);

  BOARD_GeneratePseudoMoves(&boardCopy);
  BOARD_FilterLegalMoves(&boardCopy);

  return 0;
}

uint8_t ENGINE_FindBestMove(BOARD_Board* board, uint8_t depth, uint8_t isWhite)
{
  uint8_t bestMove;
  int16_t bestScore = (isWhite)?-10000:10000; 

  ENGINE_Minimax(&board->board, depth, isWhite);
  
  return 0;
}

void ENGINE_PlayTurn(BOARD_Board* board, uint8_t depth)
{
  uint8_t isWhite = UTIL_GetBoolFromBools(board->board.bools, INDEX_ON_TURN);
  
  BOARD_BoardState boardCopy; 
  BOARD_InitBoardStateCopy(&board->board, &boardCopy);
  
  uint8_t i = ENGINE_FindBestMove(board, depth, isWhite);
  BOARD_MakeMove(&board->board, &board->board.legalMoves.list[i], isWhite);
  
  if(((isWhite && BITBOARD_GetBit(&boardCopy.white_pawns, board->board.legalMoves.list[i].from)==1) || 
  (!isWhite && BITBOARD_GetBit(&boardCopy.black_pawns, board->board.legalMoves.list[i].from)==1)) &&
  (abs(board->board.legalMoves.list[i].to-board->board.legalMoves.list[i].from)==16)){
    board->board.enPassant[!isWhite] = (board->board.legalMoves.list[i].to+board->board.legalMoves.list[i].from)/2;
  }
  else{
    board->board.enPassant[isWhite] = -1;
  }

  isWhite = !isWhite;
  UTIL_SetBoolInBools(&board->board.bools, INDEX_ON_TURN, isWhite);
  board->selectedX = board->selectedY = -1;

  BOARD_PrintPrettyBoard(&board->board);
  printf("%s isCheck = %s\n", isWhite?"white":"black", BOARD_IsCheck(&board->board, isWhite
    ?BITBOARD_CountTrailingZeros(&board->board.white_king)
    :BITBOARD_CountTrailingZeros(&board->board.black_king), isWhite)?"true":"false");
  printf("%s Q%d K%d\n",isWhite?"white":"black", UTIL_GetBoolFromBools(board->board.bools, (isWhite)?INDEX_CCWQ:INDEX_CCBQ), 
    UTIL_GetBoolFromBools(board->board.bools, (isWhite)?INDEX_CCWK:INDEX_CCBK));

  BOARD_GeneratePseudoMoves(&board->board);
  BOARD_FilterLegalMoves(&board->board);

  if(board->board.legalMoves.count==0){
    if(BOARD_IsCheck(&board->board, isWhite?BITBOARD_CountTrailingZeros(&board->board.white_king)
    :BITBOARD_CountTrailingZeros(&board->board.black_king), isWhite)){
      // !isWhite vyhral checkmateom
      printf("checkmate %d\n", isWhite);
      UTIL_SetBoolInBools(&board->board.bools, INDEX_GAME_END, 1);
      UTIL_SetBoolInBools(&board->board.bools, INDEX_WIN, !isWhite);
    }
    else{
      // stalemate
      printf("stalemate\n");
      UTIL_SetBoolInBools(&board->board.bools, INDEX_GAME_END, 1);
      UTIL_SetBoolInBools(&board->board.bools, INDEX_DRAW, 1);
    }
  }
  else if(__builtin_popcount(board->board.all_pieces.half[0])+__builtin_popcount(board->board.all_pieces.half[1])==2){
    // only kings left
    UTIL_SetBoolInBools(&board->board.bools, INDEX_GAME_END, 1);
    UTIL_SetBoolInBools(&board->board.bools, INDEX_DRAW, 1);
  }
}


