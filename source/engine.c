#include "engine.h"
#include "bitboard.h"
#include "bitboard_func.h"
#include "board.h"
#include "util.h"
#include <stdint.h>
#include <stdio.h>

int16_t ENGINE_EvaluatePosition(BOARD_BoardState *board, uint8_t depth)
{
  // check for checkmate
  uint8_t white_king_square = BITBOARD_CountTrailingZeros(&board->white_king);
  uint8_t black_king_square = BITBOARD_CountTrailingZeros(&board->black_king);

  if(board->legalMoves.count==0){
    if(BOARD_IsCheck(board, white_king_square, 1)){
      return -32768+depth;
    }
    else if(BOARD_IsCheck(board, black_king_square, 0)){
      return 32767-depth;
    }
    else{
      return 0;
    }
  }


  int16_t black_count = 0, white_count = 0;
  int16_t total_nonpawn = 0;

  // material counting
  black_count += (__builtin_popcount(board->black_knights.half[0])+__builtin_popcount(board->black_knights.half[1]))*300; 
  black_count += (__builtin_popcount(board->black_bishops.half[0])+__builtin_popcount(board->black_bishops.half[1]))*330; 
  black_count += (__builtin_popcount(board->black_rooks.half[0])+__builtin_popcount(board->black_rooks.half[1]))*500;
  black_count += (__builtin_popcount(board->black_queens.half[0])+__builtin_popcount(board->black_queens.half[1]))*900;
  total_nonpawn += black_count;
  black_count += (__builtin_popcount(board->black_pawns.half[0])+__builtin_popcount(board->black_pawns.half[1]))*100; 
  

  white_count += (__builtin_popcount(board->white_knights.half[0])+__builtin_popcount(board->white_knights.half[1]))*300; 
  white_count += (__builtin_popcount(board->white_bishops.half[0])+__builtin_popcount(board->white_bishops.half[1]))*330; 
  white_count += (__builtin_popcount(board->white_rooks.half[0])+__builtin_popcount(board->white_rooks.half[1]))*500; 
  white_count += (__builtin_popcount(board->white_queens.half[0])+__builtin_popcount(board->white_queens.half[1]))*900;
  total_nonpawn += white_count;
  white_count += (__builtin_popcount(board->white_pawns.half[0])+__builtin_popcount(board->white_pawns.half[1]))*100; 


  // Piece Square Table
  uint8_t indexes[10], count;

  if(total_nonpawn>2000){ 
    // total_nonpawn > 2000 → Middlegame
    white_count += BITBOARD_PST_King[0][white_king_square];
    black_count += BITBOARD_PST_King[0][black_king_square];
  }
  else{ 
    // total_nonpawn <= 2000 → Endgame
    white_count += BITBOARD_PST_King[1][white_king_square];
    black_count += BITBOARD_PST_King[1][black_king_square];
  }

  count = BITBOARD_FindSetBits(&board->white_pawns, indexes);
  for(;count>0;count--){
    white_count += BITBOARD_PST_Pawn[indexes[count]];
  }
  count = BITBOARD_FindSetBits(&board->white_knights, indexes);
  for(;count>0;count--){
    white_count += BITBOARD_PST_Knight[indexes[count]];
  }
  count = BITBOARD_FindSetBits(&board->white_bishops, indexes);
  for(;count>0;count--){
    white_count += BITBOARD_PST_Bishop[indexes[count]];
  }
  count = BITBOARD_FindSetBits(&board->white_rooks, indexes);
  for(;count>0;count--){
    white_count += BITBOARD_PST_Rook[indexes[count]];
  }
  count = BITBOARD_FindSetBits(&board->white_queens, indexes);
  for(;count>0;count--){
    white_count += BITBOARD_PST_Queen[indexes[count]];
  }

  count = BITBOARD_FindSetBits(&board->black_pawns, indexes);
  for(;count>0;count--){
    black_count += BITBOARD_PST_Pawn[indexes[count]^56];
  }
  count = BITBOARD_FindSetBits(&board->black_knights, indexes);
  for(;count>0;count--){
    black_count += BITBOARD_PST_Knight[indexes[count]^56];
  }
  count = BITBOARD_FindSetBits(&board->black_bishops, indexes);
  for(;count>0;count--){
    black_count += BITBOARD_PST_Bishop[indexes[count]^56];
  }
  count = BITBOARD_FindSetBits(&board->black_rooks, indexes);
  for(;count>0;count--){
    black_count += BITBOARD_PST_Rook[indexes[count]^56];
  }
  count = BITBOARD_FindSetBits(&board->black_queens, indexes);
  for(;count>0;count--){
    black_count += BITBOARD_PST_Queen[indexes[count]^56];
  }
   
  // printf("white = %d | black = %d\n", white_count, black_count);
  return white_count-black_count; 
}

int16_t ENGINE_Minimax(BOARD_BoardState *board, uint8_t depth, int16_t alpha, int16_t beta, uint8_t isWhite, uint8_t *bestMove)
{
  int8_t enPassant[2];
  BITBOARD_Bitboard* capturedPiece;
  BOARD_MoveList pseudoMoves, legalMoves;
  BOARD_GeneratePseudoMoves(board, &pseudoMoves, isWhite);
  BOARD_FilterLegalMoves(board, &pseudoMoves, &legalMoves, isWhite);
 
  if(depth==ENGINE_DEPTH || BOARD_IsGameEnded(board, isWhite, &legalMoves, 1)){
    return ENGINE_EvaluatePosition(board, depth);
  }

  // getchar();
  
  if(isWhite){ // maximizing player
    int16_t maxEval, eval;
    maxEval = -32768; 
    for(uint8_t i=0;i<legalMoves.count;i++){
      BOARD_MakeMove(board, &legalMoves.list[i], isWhite);
      capturedPiece = board->capturedPiece;
      enPassant[0] = board->enPassant[0];
      enPassant[1] = board->enPassant[1];
      eval = ENGINE_Minimax(board, depth+1, alpha, beta, false, bestMove);
      board->capturedPiece = capturedPiece;
      board->enPassant[0] = enPassant[0];
      board->enPassant[1] = enPassant[1];
      BOARD_UndoMove(board, &legalMoves.list[i], isWhite);
      if(eval>maxEval){
        maxEval = eval;
        if(depth==0){
          *bestMove = i;
        }
      }
      alpha = (alpha>eval)?alpha:eval;
      if(beta<=alpha){
        // printf("pruned\n");
        break;
      }
    }

    return maxEval;
  }
  else{ // minimizing player
    int16_t minEval, eval;
    minEval = 32767; 
    for(uint8_t i=0;i<legalMoves.count;i++){
      BOARD_MakeMove(board, &legalMoves.list[i], isWhite);
      capturedPiece = board->capturedPiece;
      enPassant[0] = board->enPassant[0];
      enPassant[1] = board->enPassant[1];
      eval = ENGINE_Minimax(board, depth+1, alpha, beta, true, bestMove);

      // if(depth==0){
      //   printf("BOARDSTATE depth=%d, eval=%d\n", depth, eval);
      //   BOARD_PrintPrettyBoard(board);
      //   printf("FROM %d TO %d\n\n", legalMoves.list[i].from, legalMoves.list[i].to);
      // }

      board->capturedPiece = capturedPiece;
      board->enPassant[0] = enPassant[0];
      board->enPassant[1] = enPassant[1];
      BOARD_UndoMove(board, &legalMoves.list[i], isWhite);
      if(eval<minEval){
        minEval = eval;
        if(depth==0){
          *bestMove = i;
        }
      }
      beta = (beta<eval)?beta:eval;
      if(beta<=alpha){
        // printf("pruned\n");
        break;
      }
    }
    return minEval;
  }
}

uint8_t ENGINE_FindBestMove(BOARD_Board *board, uint8_t isWhite)
{
  uint8_t bestMove = 0;
    
  printf("\n==============================================================\n");
  ENGINE_Minimax(&board->board, 0, 0x8000, 0x7FFF, isWhite, &bestMove);
  // BOARD_PrintBitmaps(&board->board);
  
  return bestMove;
}

void ENGINE_PlayTurn(BOARD_Board *board)
{
  uint8_t isWhite = UTIL_GetBoolFromBools(board->board.bools, INDEX_ON_TURN);
  
  BOARD_BoardState boardCopy; 
  BOARD_InitBoardStateCopy(&board->board, &boardCopy);
  
  uint8_t i = ENGINE_FindBestMove(board, isWhite);
  BOARD_MakeMove(&board->board, &board->board.legalMoves.list[i], isWhite);
  memcpy(&board->lastMove, &board->board.legalMoves.list[i], sizeof(BOARD_Move));
  
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


