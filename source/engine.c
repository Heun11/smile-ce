#include "engine.h"
#include "bitboard_func.h"
#include "board.h"
#include "util.h"
#include <stdint.h>

int8_t ENGINE_EvaluatePosition(BOARD_BoardState *board)
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

uint8_t ENGINE_Minimax(BOARD_BoardState *board, uint8_t depth, uint8_t isWhite, uint8_t *bestMove)
{
  int8_t enPassant[2];
  BITBOARD_Bitboard* capturedPiece;
  BOARD_MoveList pseudoMoves, legalMoves;
  BOARD_GeneratePseudoMoves(board, &pseudoMoves, isWhite);
  BOARD_FilterLegalMoves(board, &pseudoMoves, &legalMoves, isWhite);
 
  if(depth==ENGINE_DEPTH || BOARD_IsGameEnded(board, isWhite, &legalMoves, 1)){
    return ENGINE_EvaluatePosition(board);
  }

  // getchar();
  
  if(isWhite){ // maximizing player
    int16_t maxEval, eval;
    maxEval = 0x8000; 
    for(uint8_t i=0;i<legalMoves.count;i++){
      // BOARD_PrintPrettyBoard(board);
      // BOARD_PrintBitmaps(board);
      // printf("move from %d to %d | capturedPiece=%p | isWhite=%d\n", legalMoves.list[i].from, legalMoves.list[i].to, board->capturedPiece, isWhite);
      // BITBOARD_Print(&board->black_pieces);
      // BOARD_PrintBitmaps(board);
      BOARD_MakeMove(board, &legalMoves.list[i], isWhite);
      // BOARD_PrintBitmaps(board);
      // BITBOARD_Print(&board->black_pieces);
      capturedPiece = board->capturedPiece;
      enPassant[0] = board->enPassant[0];
      enPassant[1] = board->enPassant[1];
      // printf("po tahu AI %p\n", capturedPiece);
      // BOARD_PrintPrettyBoard(board);
      eval = ENGINE_Minimax(board, depth+1, false, bestMove);
      board->capturedPiece = capturedPiece;
      board->enPassant[0] = enPassant[0];
      board->enPassant[1] = enPassant[1];
      BOARD_UndoMove(board, &legalMoves.list[i], isWhite);
      // printf("po undo tahu AI\n");
      // BOARD_PrintBitmaps(board);
      // BOARD_PrintPrettyBoard(board);
      // maxEval = UTIL_Max_int16(maxEval, eval);
      if(eval>maxEval){
        maxEval = eval;
        if(depth==0){
          *bestMove = i;
        }
      }
    }
    return maxEval;
  }
  else{ // minimizing player
    int16_t minEval, eval;
    minEval = 0x7FFF; 
    for(uint8_t i=0;i<legalMoves.count;i++){
      // printf("move from %d to %d | capturedPiece=%p | isWhite=%d\n", legalMoves.list[i].from, legalMoves.list[i].to, board->capturedPiece, isWhite);
      // BOARD_PrintBitmaps(board);
      BOARD_MakeMove(board, &legalMoves.list[i], isWhite);
      // BOARD_PrintBitmaps(board);
      capturedPiece = board->capturedPiece;
      enPassant[0] = board->enPassant[0];
      enPassant[1] = board->enPassant[1];
      eval = ENGINE_Minimax(board, depth+1, true, bestMove);
      board->capturedPiece = capturedPiece;
      board->enPassant[0] = enPassant[0];
      board->enPassant[1] = enPassant[1];
      BOARD_UndoMove(board, &legalMoves.list[i], isWhite);
      // minEval = UTIL_Min_int16(minEval, eval);
      if(eval<minEval){
        minEval = eval;
        if(depth==0){
          *bestMove = i;
        }
      }
      // printf("%d %d\n", eval, minEval);
    }
    return minEval;
  }
}

uint8_t ENGINE_FindBestMove(BOARD_Board *board, uint8_t isWhite)
{
  uint8_t bestMove = 0;
  
  BOARD_BoardState boardCopy;
  BOARD_InitBoardStateCopy(&board->board, &boardCopy);

  ENGINE_Minimax(&boardCopy, 0, isWhite, &bestMove);
  // ENGINE_Minimax(&board->board, 0, isWhite, &bestMove);
  BOARD_PrintBitmaps(&board->board);
  
  return bestMove;
}

void ENGINE_PlayTurn(BOARD_Board *board)
{
  uint8_t isWhite = UTIL_GetBoolFromBools(board->board.bools, INDEX_ON_TURN);
  
  BOARD_BoardState boardCopy; 
  BOARD_InitBoardStateCopy(&board->board, &boardCopy);
  
  uint8_t i = ENGINE_FindBestMove(board, isWhite);
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

  BOARD_GeneratePseudoMoves(&board->board, &board->board.pseudoMoves, isWhite);
  BOARD_FilterLegalMoves(&board->board, &board->board.pseudoMoves, &board->board.legalMoves, isWhite);

  BOARD_IsGameEnded(&board->board, isWhite, &board->board.legalMoves, 0);
}


