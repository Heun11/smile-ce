#include "board.h"
#include "bitboard.h"
#include "main.h"
#include "util.h"
#include <raylib.h>
#include <stdint.h>
#include <stdio.h>
#include <ctype.h>
#include "bitboard_func.h"


// ===================================== SETUP & RENDERING =====================================

void BOARD_PrintBitmaps(BOARD_Board* board)
{
  // P R N
  // B Q K

  printf("=========================WHITE=PIECES===========================\n\n");
  
  printf("PAWNS:                  ROOKS:                  KNIGHTS:        \n");
  for(int8_t i=0;i<8;i++){
    for(uint8_t j=0;j<8;j++){
      printf("%c ", BITBOARD_GetBit(&board->board.white_pawns, i*8+j)?'1':'-');
    }printf("\t");
    for(uint8_t j=0;j<8;j++){
      printf("%c ", BITBOARD_GetBit(&board->board.white_rooks, i*8+j)?'1':'-');
    }printf("\t");
    for(uint8_t j=0;j<8;j++){
      printf("%c ", BITBOARD_GetBit(&board->board.white_knights, i*8+j)?'1':'-');
    }
    printf("\n");
  }

  printf("BISHOPS:                QUEENS:                 KING:         \n");
  for(int8_t i=0;i<8;i++){
    for(uint8_t j=0;j<8;j++){
      printf("%c ", BITBOARD_GetBit(&board->board.white_bishops, i*8+j)?'1':'-');
    }printf("\t");
    for(uint8_t j=0;j<8;j++){
      printf("%c ", BITBOARD_GetBit(&board->board.white_queens, i*8+j)?'1':'-');
    }printf("\t");
    for(uint8_t j=0;j<8;j++){
      printf("%c ", BITBOARD_GetBit(&board->board.white_king, i*8+j)?'1':'-');
    }
    printf("\n");
  }

  printf("\n=========================BLACK=PIECES===========================\n\n");

  for(int8_t i=0;i<8;i++){
    for(uint8_t j=0;j<8;j++){
      printf("%c ", BITBOARD_GetBit(&board->board.black_pawns, i*8+j)?'1':'-');
    }printf("\t");
    for(uint8_t j=0;j<8;j++){
      printf("%c ", BITBOARD_GetBit(&board->board.black_rooks, i*8+j)?'1':'-');
    }printf("\t");
    for(uint8_t j=0;j<8;j++){
      printf("%c ", BITBOARD_GetBit(&board->board.black_knights, i*8+j)?'1':'-');
    }
    printf("\n");
  }

  printf("BISHOPS:                QUEENS:                 KING:         \n");
  for(int8_t i=0;i<8;i++){
    for(uint8_t j=0;j<8;j++){
      printf("%c ", BITBOARD_GetBit(&board->board.black_bishops, i*8+j)?'1':'-');
    }printf("\t");
    for(uint8_t j=0;j<8;j++){
      printf("%c ", BITBOARD_GetBit(&board->board.black_queens, i*8+j)?'1':'-');
    }printf("\t");
    for(uint8_t j=0;j<8;j++){
      printf("%c ", BITBOARD_GetBit(&board->board.black_king, i*8+j)?'1':'-');
    }
    printf("\n");
  }

  printf("\n===========================ALL=PIECES===========================\n\n");

  printf("WHITE:                  BLACK:                  ALL:        \n");
  for(int8_t i=0;i<8;i++){
    for(uint8_t j=0;j<8;j++){
      printf("%c ", BITBOARD_GetBit(&board->board.white_pieces, i*8+j)?'1':'-');
    }printf("\t");
    for(uint8_t j=0;j<8;j++){
      printf("%c ", BITBOARD_GetBit(&board->board.black_pieces, i*8+j)?'1':'-');
    }printf("\t");
    for(uint8_t j=0;j<8;j++){
      printf("%c ", BITBOARD_GetBit(&board->board.all_pieces, i*8+j)?'1':'-');
    }
    printf("\n");
  }
}

BOARD_Board BOARD_SetupBoard(char* fen)
{
  BOARD_Board board;

  board.pointingX = -1;
  board.pointingY = -1;
  board.selectedX = -1;
  board.selectedY = -1;

  board.enPassant = -1;
  board.bools = 1<<4;
  
  board.board.white_pawns=(BITBOARD_Bitboard){{0,0}}, board.board.white_rooks=(BITBOARD_Bitboard){{0,0}}, 
    board.board.white_knights=(BITBOARD_Bitboard){{0,0}}, board.board.white_bishops=(BITBOARD_Bitboard){{0,0}}, 
    board.board.white_queens=(BITBOARD_Bitboard){{0,0}}, board.board.white_king=(BITBOARD_Bitboard){{0,0}};
  board.board.black_pawns=(BITBOARD_Bitboard){{0,0}}, board.board.black_rooks=(BITBOARD_Bitboard){{0,0}}, 
    board.board.black_knights=(BITBOARD_Bitboard){{0,0}}, board.board.black_bishops=(BITBOARD_Bitboard){{0,0}}, 
    board.board.black_queens=(BITBOARD_Bitboard){{0,0}}, board.board.black_king=(BITBOARD_Bitboard){{0,0}};
  board.board.white_pieces=(BITBOARD_Bitboard){{0,0}}, board.board.black_pieces=(BITBOARD_Bitboard){{0,0}}, 
    board.board.all_pieces=(BITBOARD_Bitboard){{0,0}};

  // helping vars
  uint8_t file = 0, rank = 0;
  char symbol;
  uint8_t setup_info = 0;

  // load fen pieces
  for(int i=0;i<strlen(fen);i++){
    symbol = fen[i];
    if(symbol==' '){
      setup_info = i;
      break;
    }
    if(symbol=='/'){
      file = 0;
      rank++;
    }
    else{
      if(isdigit(symbol)!=0){
        file+=symbol-'0';
      }
      else{
        uint8_t index = rank*8+file;
        printf("%d %c\n", index, symbol);
        switch(symbol){
          case 'P': BITBOARD_SetBitToH(&board.board.white_pawns, index); break;
          case 'R': BITBOARD_SetBitToH(&board.board.white_rooks, index); break;
          case 'N': BITBOARD_SetBitToH(&board.board.white_knights, index); break;
          case 'B': BITBOARD_SetBitToH(&board.board.white_bishops, index); break;
          case 'Q': BITBOARD_SetBitToH(&board.board.white_queens, index); break;
          case 'K': BITBOARD_SetBitToH(&board.board.white_king, index); break;
          
          case 'p': BITBOARD_SetBitToH(&board.board.black_pawns, index); break;
          case 'r': BITBOARD_SetBitToH(&board.board.black_rooks, index); break;
          case 'n': BITBOARD_SetBitToH(&board.board.black_knights, index); break;
          case 'b': BITBOARD_SetBitToH(&board.board.black_bishops, index); break;
          case 'q': BITBOARD_SetBitToH(&board.board.black_queens, index); break;
          case 'k': BITBOARD_SetBitToH(&board.board.black_king, index); break;
        }
        file++;
      }
    }
  }

  // set fen info
  for(int i=setup_info;i<strlen(fen);i++){
    symbol = fen[i];
    if(symbol=='w'){
      UTIL_SetBoolInBools(&board.bools, INDEX_ON_TURN, 1);
    }
    if(symbol=='b'){
      UTIL_SetBoolInBools(&board.bools, INDEX_ON_TURN, 0);
    }
    if(symbol=='K'){
      UTIL_SetBoolInBools(&board.bools, INDEX_CCWK, 1);
    }
    if(symbol=='Q'){
      UTIL_SetBoolInBools(&board.bools, INDEX_CCWQ, 1);
    }
    if(symbol=='k'){
      UTIL_SetBoolInBools(&board.bools, INDEX_CCBK, 1);
    }
    if(symbol=='q'){
      UTIL_SetBoolInBools(&board.bools, INDEX_CCBQ, 1);
    }
  }
  
  BITBOARD_BitwiseOR(&board.board.white_pieces, 6, &board.board.white_pawns, &board.board.white_rooks, 
    &board.board.white_knights, &board.board.white_bishops, &board.board.white_queens, &board.board.white_king);
  BITBOARD_BitwiseOR(&board.board.black_pieces, 6, &board.board.black_pawns, &board.board.black_rooks, 
    &board.board.black_knights, &board.board.black_bishops, &board.board.black_queens, &board.board.black_king);
  BITBOARD_BitwiseOR(&board.board.all_pieces, 2, &board.board.white_pieces, &board.board.black_pieces);

  // printing board
  printf("Show Boards:\n\n");
  BOARD_PrintBitmaps(&board);

  BOARD_GeneratePseudoMoves(&board);
  BOARD_FilterLegalMoves(&board);
  
  return board;
}

void BOARD_DrawBoard(BOARD_Board* board, int offx, int offy)
{
  uint8_t row, col;
  uint8_t pos;
  #if FANCY_BOARD
  uint8_t isWhite = UTIL_GetBoolFromBools(board->bools, INDEX_ON_TURN);
  #endif

  for(row=0;row<8;row++){
    for(col=0;col<8;col++){

      if((row+col)%2==0){
        #if FANCY_BOARD
        DrawTexturePro(tileset, (Rectangle){6*TILE_REAL_W, 0*TILE_REAL_H, TILE_REAL_W, TILE_REAL_H}, 
          (Rectangle){offx+TS*col, offy+TS*row, TS, TS*1.3125}, (Vector2){0,0}, 0, RAYWHITE);
        #else
        DrawRectangle(offx+col*TS, offy+row*TS, TS, TS, (Color){ 247, 243, 220, 255 });
        #endif
      }
      else{
        #if FANCY_BOARD
        DrawTexturePro(tileset, (Rectangle){6*TILE_REAL_W, 1*TILE_REAL_H, TILE_REAL_W, TILE_REAL_H}, 
          (Rectangle){offx+TS*col, offy+TS*row, TS, TS*1.3125}, (Vector2){0,0}, 0, RAYWHITE);
        #else
        DrawRectangle(offx+col*TS, offy+row*TS, TS, TS, (Color){ 51, 107, 163, 255 });
        #endif
      }
      
      pos = row*8+col;
      #if FANCY_BOARD
      DrawText(TextFormat("%d", pos), offx+TS*col, offy+TS*row, TS*0.2, WHITE);
      #else 
      DrawText(TextFormat("%d", pos), offx+TS*col+TS*0.05, offy+TS*row+TS*0.05, TS*0.2, BLACK);
      #endif

      for(uint8_t i=0;i<board->legalMoves.count;i++){
       if(board->legalMoves.list[i].from==board->selectedY*8+board->selectedX && board->legalMoves.list[i].to==pos){
          #if FANCY_BOARD
          if(isWhite){
            DrawTexturePro(tileset, (Rectangle){7*TILE_REAL_W, 0*TILE_REAL_H, TILE_REAL_W, TILE_REAL_H}, 
              (Rectangle){offx+TS*col, offy+TS*row, TS, TS*1.3125}, (Vector2){0,0}, 0, RAYWHITE);
          }
          else{
            DrawTexturePro(tileset, (Rectangle){7*TILE_REAL_W, 1*TILE_REAL_H, TILE_REAL_W, TILE_REAL_H}, 
              (Rectangle){offx+TS*col, offy+TS*row, TS, TS*1.3125}, (Vector2){0,0}, 0, RAYWHITE);
          }
          #else
          DrawRectangle(offx+col*TS, offy+row*TS, TS, TS, (Color){255, 0, 0, 100});
          #endif
        }
      }
      
      if(BITBOARD_GetBit(&board->board.all_pieces, pos)){
        if(BITBOARD_GetBit(&board->board.white_pawns, pos)){
          #if FANCY_BOARD
          DrawTexturePro(tileset, (Rectangle){0*TILE_REAL_W, 0*TILE_REAL_H, TILE_REAL_W, TILE_REAL_H}, 
            (Rectangle){offx+TS*col, offy+TS*row-TS*0.623, TS, TS*1.3125}, (Vector2){0,0}, 0, RAYWHITE);
          #else
          DrawTexturePro(tileset, (Rectangle){0*TILE_REAL, 0*TILE_REAL, TILE_REAL, TILE_REAL}, 
            (Rectangle){offx+TS*col, offy+TS*row, TS, TS}, (Vector2){0,0}, 0, RAYWHITE);
          #endif
        }
        if(BITBOARD_GetBit(&board->board.white_rooks, pos)){
          #if FANCY_BOARD
          DrawTexturePro(tileset, (Rectangle){1*TILE_REAL_W, 0*TILE_REAL_H, TILE_REAL_W, TILE_REAL_H}, 
            (Rectangle){offx+TS*col, offy+TS*row-TS*0.623, TS, TS*1.3125}, (Vector2){0,0}, 0, RAYWHITE);
          #else
          DrawTexturePro(tileset, (Rectangle){1*TILE_REAL, 0*TILE_REAL, TILE_REAL, TILE_REAL}, 
            (Rectangle){offx+TS*col, offy+TS*row, TS, TS}, (Vector2){0,0}, 0, RAYWHITE);
          #endif
        }
        if(BITBOARD_GetBit(&board->board.white_knights, pos)){
          #if FANCY_BOARD
          DrawTexturePro(tileset, (Rectangle){2*TILE_REAL_W, 0*TILE_REAL_H, TILE_REAL_W, TILE_REAL_H}, 
            (Rectangle){offx+TS*col, offy+TS*row-TS*0.623, TS, TS*1.3125}, (Vector2){0,0}, 0, RAYWHITE);
          #else
          DrawTexturePro(tileset, (Rectangle){2*TILE_REAL, 0*TILE_REAL, TILE_REAL, TILE_REAL}, 
            (Rectangle){offx+TS*col, offy+TS*row, TS, TS}, (Vector2){0,0}, 0, RAYWHITE);
          #endif
        }
        if(BITBOARD_GetBit(&board->board.white_bishops, pos)){
          #if FANCY_BOARD
          DrawTexturePro(tileset, (Rectangle){3*TILE_REAL_W, 0*TILE_REAL_H, TILE_REAL_W, TILE_REAL_H}, 
            (Rectangle){offx+TS*col, offy+TS*row-TS*0.623, TS, TS*1.3125}, (Vector2){0,0}, 0, RAYWHITE);
          #else
          DrawTexturePro(tileset, (Rectangle){3*TILE_REAL, 0*TILE_REAL, TILE_REAL, TILE_REAL}, 
            (Rectangle){offx+TS*col, offy+TS*row, TS, TS}, (Vector2){0,0}, 0, RAYWHITE);
          #endif
        }
        if(BITBOARD_GetBit(&board->board.white_queens, pos)){
          #if FANCY_BOARD
          DrawTexturePro(tileset, (Rectangle){4*TILE_REAL_W, 0*TILE_REAL_H, TILE_REAL_W, TILE_REAL_H}, 
            (Rectangle){offx+TS*col, offy+TS*row-TS*0.623, TS, TS*1.3125}, (Vector2){0,0}, 0, RAYWHITE);
          #else
          DrawTexturePro(tileset, (Rectangle){4*TILE_REAL, 0*TILE_REAL, TILE_REAL, TILE_REAL}, 
            (Rectangle){offx+TS*col, offy+TS*row, TS, TS}, (Vector2){0,0}, 0, RAYWHITE);
          #endif
        }
        if(BITBOARD_GetBit(&board->board.white_king, pos)){
          #if FANCY_BOARD
          DrawTexturePro(tileset, (Rectangle){5*TILE_REAL_W, 0*TILE_REAL_H, TILE_REAL_W, TILE_REAL_H}, 
            (Rectangle){offx+TS*col, offy+TS*row-TS*0.623, TS, TS*1.3125}, (Vector2){0,0}, 0, RAYWHITE);
          #else
          DrawTexturePro(tileset, (Rectangle){5*TILE_REAL, 0*TILE_REAL, TILE_REAL, TILE_REAL}, 
            (Rectangle){offx+TS*col, offy+TS*row, TS, TS}, (Vector2){0,0}, 0, RAYWHITE);
          #endif
        }
        
        if(BITBOARD_GetBit(&board->board.black_pawns, pos)){
          #if FANCY_BOARD
          DrawTexturePro(tileset, (Rectangle){0*TILE_REAL_W, 1*TILE_REAL_H, TILE_REAL_W, TILE_REAL_H}, 
            (Rectangle){offx+TS*col, offy+TS*row-TS*0.623, TS, TS*1.3125}, (Vector2){0,0}, 0, RAYWHITE);
          #else
          DrawTexturePro(tileset, (Rectangle){0*TILE_REAL, 1*TILE_REAL, TILE_REAL, TILE_REAL}, 
            (Rectangle){offx+TS*col, offy+TS*row, TS, TS}, (Vector2){0,0}, 0, RAYWHITE);
          #endif
        }
        if(BITBOARD_GetBit(&board->board.black_rooks, pos)){
          #if FANCY_BOARD
          DrawTexturePro(tileset, (Rectangle){1*TILE_REAL_W, 1*TILE_REAL_H, TILE_REAL_W, TILE_REAL_H}, 
            (Rectangle){offx+TS*col, offy+TS*row-TS*0.623, TS, TS*1.3125}, (Vector2){0,0}, 0, RAYWHITE);
          #else
          DrawTexturePro(tileset, (Rectangle){1*TILE_REAL, 1*TILE_REAL, TILE_REAL, TILE_REAL}, 
            (Rectangle){offx+TS*col, offy+TS*row, TS, TS}, (Vector2){0,0}, 0, RAYWHITE);
          #endif
        }
        if(BITBOARD_GetBit(&board->board.black_knights, pos)){
          #if FANCY_BOARD
          DrawTexturePro(tileset, (Rectangle){2*TILE_REAL_W, 1*TILE_REAL_H, TILE_REAL_W, TILE_REAL_H}, 
            (Rectangle){offx+TS*col, offy+TS*row-TS*0.623, TS, TS*1.3125}, (Vector2){0,0}, 0, RAYWHITE);
          #else
          DrawTexturePro(tileset, (Rectangle){2*TILE_REAL, 1*TILE_REAL, TILE_REAL, TILE_REAL}, 
            (Rectangle){offx+TS*col, offy+TS*row, TS, TS}, (Vector2){0,0}, 0, RAYWHITE);
          #endif
        }
        if(BITBOARD_GetBit(&board->board.black_bishops, pos)){
          #if FANCY_BOARD
          DrawTexturePro(tileset, (Rectangle){3*TILE_REAL_W, 1*TILE_REAL_H, TILE_REAL_W, TILE_REAL_H}, 
            (Rectangle){offx+TS*col, offy+TS*row-TS*0.623, TS, TS*1.3125}, (Vector2){0,0}, 0, RAYWHITE);
          #else
          DrawTexturePro(tileset, (Rectangle){3*TILE_REAL, 1*TILE_REAL, TILE_REAL, TILE_REAL}, 
            (Rectangle){offx+TS*col, offy+TS*row, TS, TS}, (Vector2){0,0}, 0, RAYWHITE);
          #endif
        }
        if(BITBOARD_GetBit(&board->board.black_queens, pos)){
          #if FANCY_BOARD
          DrawTexturePro(tileset, (Rectangle){4*TILE_REAL_W, 1*TILE_REAL_H, TILE_REAL_W, TILE_REAL_H}, 
            (Rectangle){offx+TS*col, offy+TS*row-TS*0.623, TS, TS*1.3125}, (Vector2){0,0}, 0, RAYWHITE);
          #else
          DrawTexturePro(tileset, (Rectangle){4*TILE_REAL, 1*TILE_REAL, TILE_REAL, TILE_REAL}, 
            (Rectangle){offx+TS*col, offy+TS*row, TS, TS}, (Vector2){0,0}, 0, RAYWHITE);
          #endif
        }
        if(BITBOARD_GetBit(&board->board.black_king, pos)){
          #if FANCY_BOARD
          DrawTexturePro(tileset, (Rectangle){5*TILE_REAL_W, 1*TILE_REAL_H, TILE_REAL_W, TILE_REAL_H}, 
            (Rectangle){offx+TS*col, offy+TS*row-TS*0.623, TS, TS*1.3125}, (Vector2){0,0}, 0, RAYWHITE);
          #else
          DrawTexturePro(tileset, (Rectangle){5*TILE_REAL, 1*TILE_REAL, TILE_REAL, TILE_REAL}, 
            (Rectangle){offx+TS*col, offy+TS*row, TS, TS}, (Vector2){0,0}, 0, RAYWHITE);
          #endif
        }
      }
    }
  }
}


// ===================================== CHESS CALCULATIONS =====================================


uint8_t BOARD_IsCheck(BOARD_BoardState* board, uint8_t isWhite)
{
  BITBOARD_Bitboard temp, temp1;
  int8_t kingSquare;
  uint8_t isCheck = 0;
  BITBOARD_SetBitboardToBitboard(&board->enemyAttack, &(BITBOARD_Bitboard){{0,0}});

  if(isWhite){
    // white is on turn
    kingSquare = BITBOARD_CountTrailingZeros(&board->white_king);
    if(kingSquare==-1) return 1;

    // pawn 
    BITBOARD_SetBitboardToBitboard(&temp, &BITBOARD_AttackMasks_pawn[1][kingSquare]);
    BITBOARD_BitwiseOR(&board->enemyAttack, 1, &temp);
    BITBOARD_BitwiseAND(&temp, 1, &board->black_pawns);
    // BITBOARD_Print(&temp);
    if(BITBOARD_IsBitboardTrue(&temp)) isCheck = 1;

    // knight 
    BITBOARD_SetBitboardToBitboard(&temp, &BITBOARD_Masks_knight[kingSquare]);
    BITBOARD_BitwiseOR(&board->enemyAttack, 1, &temp);
    BITBOARD_BitwiseAND(&temp, 1, &board->black_knights);
    // BITBOARD_Print(&temp);
    if(BITBOARD_IsBitboardTrue(&temp)) isCheck = 1;

    // diagonal (queen & bishop)
    BITBOARD_GetAttackMask_bishop(&temp1, kingSquare, &board->all_pieces);
    BITBOARD_BitwiseOR(&temp, 2, &board->black_bishops, &board->black_queens);
    BITBOARD_BitwiseOR(&board->enemyAttack, 1, &temp);
    BITBOARD_BitwiseAND(&temp, 1, &temp1);
    // BITBOARD_Print(&temp);
    if(BITBOARD_IsBitboardTrue(&temp)) isCheck = 1;

    // straight lines (queen & rook)
    BITBOARD_GetAttackMask_rook(&temp1, kingSquare, &board->all_pieces);
    BITBOARD_BitwiseOR(&temp, 2, &board->black_rooks, &board->black_queens);
    BITBOARD_BitwiseOR(&board->enemyAttack, 1, &temp);
    BITBOARD_BitwiseAND(&temp, 1, &temp1);
    // BITBOARD_Print(&temp);
    if(BITBOARD_IsBitboardTrue(&temp)) isCheck = 1;

    // king 
    BITBOARD_SetBitboardToBitboard(&temp, &BITBOARD_Masks_king[kingSquare]);
    BITBOARD_BitwiseOR(&board->enemyAttack, 1, &temp);
    BITBOARD_BitwiseAND(&temp, 1, &board->black_king);
    // BITBOARD_Print(&temp);
    if(BITBOARD_IsBitboardTrue(&temp)) isCheck = 1;
  }
  else{ 
    // black is on turn
    kingSquare = BITBOARD_CountTrailingZeros(&board->black_king);
    if(kingSquare==-1) return 1;
    
    // pawn 
    BITBOARD_SetBitboardToBitboard(&temp, &BITBOARD_AttackMasks_pawn[1][kingSquare]);
    BITBOARD_BitwiseOR(&board->enemyAttack, 1, &temp);
    BITBOARD_BitwiseAND(&temp, 1, &board->white_pawns);
    // BITBOARD_Print(&temp);
    if(BITBOARD_IsBitboardTrue(&temp)) isCheck = 1;

    // knight 
    BITBOARD_SetBitboardToBitboard(&temp, &BITBOARD_Masks_knight[kingSquare]);
    BITBOARD_BitwiseOR(&board->enemyAttack, 1, &temp);
    BITBOARD_BitwiseAND(&temp, 1, &board->white_knights);
    // BITBOARD_Print(&temp);
    if(BITBOARD_IsBitboardTrue(&temp)) isCheck = 1;

    // diagonal (queen & bishop)
    BITBOARD_GetAttackMask_bishop(&temp1, kingSquare, &board->all_pieces);
    BITBOARD_BitwiseOR(&temp, 2, &board->white_bishops, &board->white_queens);
    BITBOARD_BitwiseOR(&board->enemyAttack, 1, &temp);
    BITBOARD_BitwiseAND(&temp, 1, &temp1);
    if(BITBOARD_IsBitboardTrue(&temp)) isCheck = 1;

    // straight lines (queen & rook)
    BITBOARD_GetAttackMask_rook(&temp1, kingSquare, &board->all_pieces);
    BITBOARD_BitwiseOR(&temp, 2, &board->white_rooks, &board->white_queens);
    BITBOARD_BitwiseOR(&board->enemyAttack, 1, &temp);
    BITBOARD_BitwiseAND(&temp, 1, &temp1);
    if(BITBOARD_IsBitboardTrue(&temp)) isCheck = 1;

    // king 
    BITBOARD_SetBitboardToBitboard(&temp, &BITBOARD_Masks_king[kingSquare]);
    BITBOARD_BitwiseOR(&board->enemyAttack, 1, &temp);
    BITBOARD_BitwiseAND(&temp, 1, &board->white_king);
    // BITBOARD_Print(&temp);
    if(BITBOARD_IsBitboardTrue(&temp)) return 1; 
  }
  return isCheck;
}

void BOARD_AddMove(BOARD_MoveList* moves, int8_t from, int8_t to, int8_t promotion)
{
  moves->list[moves->count].from = from;
  moves->list[moves->count].to = to;
  moves->list[moves->count].promotion = promotion;
  moves->count++;
}

void BOARD_MakeMove(BOARD_BoardState* board, BOARD_Move* move, uint8_t isWhite, int8_t enPassant)
{
  BITBOARD_Bitboard temp, removeMask, pieceMask=(BITBOARD_Bitboard){{0,0}}, moveMask=(BITBOARD_Bitboard){{0,0}};
  BITBOARD_LeftShift(&pieceMask, &(BITBOARD_Bitboard){{1,0}}, move->from);
  BITBOARD_LeftShift(&moveMask, &(BITBOARD_Bitboard){{1,0}}, move->to);
  BITBOARD_Subtract(&removeMask, &(BITBOARD_Bitboard){{0xFFFFFFFF,0xFFFFFFFF}}, &pieceMask);
  
  if(isWhite){
    BITBOARD_SetBitboardToBitboard(&temp, &(BITBOARD_Bitboard){{0xFFFFFFFF,0xFFFFFFFF}});
    BITBOARD_BitwiseAND(&temp, 2, &pieceMask, &board->white_pawns);
    if(BITBOARD_IsBitboardTrue(&temp)){
      BITBOARD_BitwiseAND(&board->white_pawns, 1, &removeMask);
      BITBOARD_BitwiseOR(&board->white_pawns, 1, &moveMask);

      if(move->to==enPassant){
        BITBOARD_LeftShift(&pieceMask, &(BITBOARD_Bitboard){{1,0}}, enPassant+8);
        BITBOARD_Subtract(&temp, &(BITBOARD_Bitboard){{0xFFFFFFFF,0xFFFFFFFF}}, &pieceMask);
        BITBOARD_BitwiseAND(&board->all_pieces, 1, &temp);
        BITBOARD_BitwiseAND(&board->black_pieces, 1, &temp);
        BITBOARD_BitwiseAND(&board->black_pawns, 1, &temp);
      }
    }
    BITBOARD_SetBitboardToBitboard(&temp, &(BITBOARD_Bitboard){{0xFFFFFFFF,0xFFFFFFFF}});
    BITBOARD_BitwiseAND(&temp, 2, &pieceMask, &board->white_knights);
    if(BITBOARD_IsBitboardTrue(&temp)){
      BITBOARD_BitwiseAND(&board->white_knights, 1, &removeMask);
      BITBOARD_BitwiseOR(&board->white_knights, 1, &moveMask);
    }
    BITBOARD_SetBitboardToBitboard(&temp, &(BITBOARD_Bitboard){{0xFFFFFFFF,0xFFFFFFFF}});
    BITBOARD_BitwiseAND(&temp, 2, &pieceMask, &board->white_bishops);
    if(BITBOARD_IsBitboardTrue(&temp)){
      BITBOARD_BitwiseAND(&board->white_bishops, 1, &removeMask);
      BITBOARD_BitwiseOR(&board->white_bishops, 1, &moveMask);
    }
    BITBOARD_SetBitboardToBitboard(&temp, &(BITBOARD_Bitboard){{0xFFFFFFFF,0xFFFFFFFF}});
    BITBOARD_BitwiseAND(&temp, 2, &pieceMask, &board->white_rooks);
    if(BITBOARD_IsBitboardTrue(&temp)){
      BITBOARD_BitwiseAND(&board->white_rooks, 1, &removeMask);
      BITBOARD_BitwiseOR(&board->white_rooks, 1, &moveMask);
    }
    BITBOARD_SetBitboardToBitboard(&temp, &(BITBOARD_Bitboard){{0xFFFFFFFF,0xFFFFFFFF}});
    BITBOARD_BitwiseAND(&temp, 2, &pieceMask, &board->white_queens);
    if(BITBOARD_IsBitboardTrue(&temp)){
      BITBOARD_BitwiseAND(&board->white_queens, 1, &removeMask);
      BITBOARD_BitwiseOR(&board->white_queens, 1, &moveMask);
    }
    BITBOARD_SetBitboardToBitboard(&temp, &(BITBOARD_Bitboard){{0xFFFFFFFF,0xFFFFFFFF}});
    BITBOARD_BitwiseAND(&temp, 2, &pieceMask, &board->white_king);
    if(BITBOARD_IsBitboardTrue(&temp)){
      BITBOARD_BitwiseAND(&board->white_king, 1, &removeMask);
      BITBOARD_BitwiseOR(&board->white_king, 1, &moveMask);
    }
    BITBOARD_BitwiseAND(&board->white_pieces, 1, &removeMask);
    BITBOARD_BitwiseOR(&board->white_pieces, 1, &moveMask);

    BITBOARD_Subtract(&temp, &(BITBOARD_Bitboard){{0xFFFFFFFF,0xFFFFFFFF}}, &moveMask);
    BITBOARD_BitwiseAND(&board->black_pieces, 1, &temp);
    BITBOARD_BitwiseAND(&board->black_pawns, 1, &temp);
    BITBOARD_BitwiseAND(&board->black_knights, 1, &temp);
    BITBOARD_BitwiseAND(&board->black_bishops, 1, &temp);
    BITBOARD_BitwiseAND(&board->black_rooks, 1, &temp);
    BITBOARD_BitwiseAND(&board->black_queens, 1, &temp);
    BITBOARD_BitwiseAND(&board->black_king, 1, &temp);
  } 
  else{
    BITBOARD_SetBitboardToBitboard(&temp, &(BITBOARD_Bitboard){{0xFFFFFFFF,0xFFFFFFFF}});
    BITBOARD_BitwiseAND(&temp, 2, &pieceMask, &board->black_pawns);
    if(BITBOARD_IsBitboardTrue(&temp)){
      BITBOARD_BitwiseAND(&board->black_pawns, 1, &removeMask);
      BITBOARD_BitwiseOR(&board->black_pawns, 1, &moveMask);

      if(move->to==enPassant){
        BITBOARD_LeftShift(&pieceMask, &(BITBOARD_Bitboard){{1,0}}, enPassant-8);
        BITBOARD_Subtract(&temp, &(BITBOARD_Bitboard){{0xFFFFFFFF,0xFFFFFFFF}}, &pieceMask);
        BITBOARD_BitwiseAND(&board->all_pieces, 1, &temp);
        BITBOARD_BitwiseAND(&board->white_pieces, 1, &temp);
        BITBOARD_BitwiseAND(&board->white_pawns, 1, &temp);
      }
    }
    BITBOARD_SetBitboardToBitboard(&temp, &(BITBOARD_Bitboard){{0xFFFFFFFF,0xFFFFFFFF}});
    BITBOARD_BitwiseAND(&temp, 2, &pieceMask, &board->black_knights);
    if(BITBOARD_IsBitboardTrue(&temp)){
      BITBOARD_BitwiseAND(&board->black_knights, 1, &removeMask);
      BITBOARD_BitwiseOR(&board->black_knights, 1, &moveMask);
    }
    BITBOARD_SetBitboardToBitboard(&temp, &(BITBOARD_Bitboard){{0xFFFFFFFF,0xFFFFFFFF}});
    BITBOARD_BitwiseAND(&temp, 2, &pieceMask, &board->black_bishops);
    if(BITBOARD_IsBitboardTrue(&temp)){
      BITBOARD_BitwiseAND(&board->black_bishops, 1, &removeMask);
      BITBOARD_BitwiseOR(&board->black_bishops, 1, &moveMask);
    }
    BITBOARD_SetBitboardToBitboard(&temp, &(BITBOARD_Bitboard){{0xFFFFFFFF,0xFFFFFFFF}});
    BITBOARD_BitwiseAND(&temp, 2, &pieceMask, &board->black_rooks);
    if(BITBOARD_IsBitboardTrue(&temp)){
      BITBOARD_BitwiseAND(&board->black_rooks, 1, &removeMask);
      BITBOARD_BitwiseOR(&board->black_rooks, 1, &moveMask);
    }
    BITBOARD_SetBitboardToBitboard(&temp, &(BITBOARD_Bitboard){{0xFFFFFFFF,0xFFFFFFFF}});
    BITBOARD_BitwiseAND(&temp, 2, &pieceMask, &board->black_queens);
    if(BITBOARD_IsBitboardTrue(&temp)){
      BITBOARD_BitwiseAND(&board->black_queens, 1, &removeMask);
      BITBOARD_BitwiseOR(&board->black_queens, 1, &moveMask);
    }
    BITBOARD_SetBitboardToBitboard(&temp, &(BITBOARD_Bitboard){{0xFFFFFFFF,0xFFFFFFFF}});
    BITBOARD_BitwiseAND(&temp, 2, &pieceMask, &board->black_king);
    if(BITBOARD_IsBitboardTrue(&temp)){
      BITBOARD_BitwiseAND(&board->black_king, 1, &removeMask);
      BITBOARD_BitwiseOR(&board->black_king, 1, &moveMask);
    }
    BITBOARD_BitwiseAND(&board->black_pieces, 1, &removeMask);
    BITBOARD_BitwiseOR(&board->black_pieces, 1, &moveMask);
    
    BITBOARD_Subtract(&temp, &(BITBOARD_Bitboard){{0xFFFFFFFF,0xFFFFFFFF}}, &moveMask);
    BITBOARD_BitwiseAND(&board->white_pieces, 1, &temp);
    BITBOARD_BitwiseAND(&board->white_pawns, 1, &temp);
    BITBOARD_BitwiseAND(&board->white_knights, 1, &temp);
    BITBOARD_BitwiseAND(&board->white_bishops, 1, &temp);
    BITBOARD_BitwiseAND(&board->white_rooks, 1, &temp);
    BITBOARD_BitwiseAND(&board->white_queens, 1, &temp);
    BITBOARD_BitwiseAND(&board->white_king, 1, &temp);
  }
  BITBOARD_BitwiseAND(&board->all_pieces, 1, &removeMask);
  BITBOARD_BitwiseOR(&board->all_pieces, 1, &moveMask);
}

void BOARD_PrintMoves(BOARD_MoveList* moves)
{
  int8_t prev = -1;
  printf("moves (%d):\n", moves->count);
  for(uint8_t i=0;i<moves->count;i++){
    if(prev!=moves->list[i].from){ 
      prev=moves->list[i].from;
      printf("\n");
    }
    printf("move %03d = %02d -> %02d (%d)\n", i, moves->list[i].from, moves->list[i].to, moves->list[i].promotion);
  }
  printf("\n");
}

void BOARD_InitBoardStateCopy(BOARD_Board* board)
{
  BITBOARD_SetBitboardToBitboard(&board->boardCopy.all_pieces, &board->board.all_pieces);
  BITBOARD_SetBitboardToBitboard(&board->boardCopy.white_pawns, &board->board.white_pawns);
  BITBOARD_SetBitboardToBitboard(&board->boardCopy.white_knights, &board->board.white_knights);
  BITBOARD_SetBitboardToBitboard(&board->boardCopy.white_bishops, &board->board.white_bishops);
  BITBOARD_SetBitboardToBitboard(&board->boardCopy.white_rooks, &board->board.white_rooks);
  BITBOARD_SetBitboardToBitboard(&board->boardCopy.white_queens, &board->board.white_queens);
  BITBOARD_SetBitboardToBitboard(&board->boardCopy.white_king, &board->board.white_king);
  BITBOARD_SetBitboardToBitboard(&board->boardCopy.black_pawns, &board->board.black_pawns);
  BITBOARD_SetBitboardToBitboard(&board->boardCopy.black_knights, &board->board.black_knights);
  BITBOARD_SetBitboardToBitboard(&board->boardCopy.black_bishops, &board->board.black_bishops);
  BITBOARD_SetBitboardToBitboard(&board->boardCopy.black_rooks, &board->board.black_rooks);
  BITBOARD_SetBitboardToBitboard(&board->boardCopy.black_queens, &board->board.black_queens);
  BITBOARD_SetBitboardToBitboard(&board->boardCopy.black_king, &board->board.black_king);
}

void BOARD_GeneratePseudoMoves_Pawn(BOARD_Board* board, uint8_t isWhite)
{
  uint8_t square, attackSquare;
  BITBOARD_Bitboard pawns, emptySquares, temp, push;
  BITBOARD_SetBitboardToBitboard(&pawns, (isWhite)?(&board->board.white_pawns):(&board->board.black_pawns));
  BITBOARD_BitwiseNOT(&emptySquares, &board->board.all_pieces);
  
  while(BITBOARD_IsBitboardTrue(&pawns)){
    square = BITBOARD_CountTrailingZeros(&pawns);
    BITBOARD_SetBitboardToBitboard(&temp, &pawns);
    BITBOARD_Subtract(&temp, &temp, &(BITBOARD_Bitboard){{1,0}});
    BITBOARD_BitwiseAND(&pawns, 1, &temp);

    BITBOARD_LeftShift(&temp, &(BITBOARD_Bitboard){{1,0}}, square);
    if(isWhite){
      BITBOARD_RightShift(&push, &temp, 8);
    }else{
      BITBOARD_LeftShift(&push, &temp, 8);
    }
    
    BITBOARD_SetBitboardToBitboard(&temp, &(BITBOARD_Bitboard){{0xFFFFFFFF,0xFFFFFFFF}});
    BITBOARD_BitwiseAND(&temp, 2, &push, &emptySquares);
    if(BITBOARD_IsBitboardTrue(&temp)){
      BOARD_AddMove(&board->pseudoMoves, square, BITBOARD_CountTrailingZeros(&push), 0);

      BITBOARD_SetBitboardToBitboard(&temp, &push);
      if(isWhite){
        BITBOARD_RightShift(&push, &temp, 8);
      }else{
        BITBOARD_LeftShift(&push, &temp, 8);
      }

      BITBOARD_SetBitboardToBitboard(&temp, &(BITBOARD_Bitboard){{0xFFFFFFFF,0xFFFFFFFF}});
      BITBOARD_BitwiseAND(&temp, 2, &push, &emptySquares);
      if((square/8==(isWhite?6:1)) && BITBOARD_IsBitboardTrue(&temp)){
        BOARD_AddMove(&board->pseudoMoves, square, BITBOARD_CountTrailingZeros(&push), 0);
      } 
    }

    BITBOARD_SetBitboardToBitboard(&push, &(BITBOARD_Bitboard){{0xFFFFFFFF,0xFFFFFFFF}});
    BITBOARD_BitwiseAND(&push, 2, &BITBOARD_AttackMasks_pawn[isWhite?1:0][square], 
      (isWhite)?(&board->board.black_pieces):(&board->board.white_pieces));
    while(BITBOARD_IsBitboardTrue(&push)){
      attackSquare = BITBOARD_CountTrailingZeros(&push);
      BITBOARD_SetBitboardToBitboard(&temp, &push);
      BITBOARD_Subtract(&temp, &temp, &(BITBOARD_Bitboard){{1,0}});
      BITBOARD_BitwiseAND(&push, 1, &temp);

      BOARD_AddMove(&board->pseudoMoves, square, attackSquare, 0);
    }

    if(board->enPassant>=0){
      BITBOARD_LeftShift(&temp, &(BITBOARD_Bitboard){{1,0}}, board->enPassant);
      BITBOARD_BitwiseAND(&temp, 1, &BITBOARD_AttackMasks_pawn[isWhite?1:0][square]);
      if(BITBOARD_IsBitboardTrue(&temp)){
        BOARD_AddMove(&board->pseudoMoves, square, board->enPassant, 0);
      }
    }
  }
}

void BOARD_GeneratePseudoMoves_Knight(BOARD_Board* board, uint8_t isWhite)
{
  uint8_t square, moveSquare;
  BITBOARD_Bitboard knights, emptySquares, temp, movesMask;
  BITBOARD_SetBitboardToBitboard(&knights, isWhite?(&board->board.white_knights):(&board->board.black_knights));
  BITBOARD_BitwiseNOT(&emptySquares, &board->board.all_pieces);

  while(BITBOARD_IsBitboardTrue(&knights)){
    square = BITBOARD_CountTrailingZeros(&knights);
    BITBOARD_SetBitboardToBitboard(&temp, &knights);
    BITBOARD_Subtract(&temp, &temp, &(BITBOARD_Bitboard){{1,0}});
    BITBOARD_BitwiseAND(&knights, 1, &temp);

    BITBOARD_SetBitboardToBitboard(&temp, &(BITBOARD_Bitboard){{0,0}});
    BITBOARD_BitwiseOR(&temp, 2, &emptySquares, isWhite?(&board->board.black_pieces):(&board->board.white_pieces));
    BITBOARD_SetBitboardToBitboard(&movesMask, &(BITBOARD_Bitboard){{0xFFFFFFFF,0xFFFFFFFF}});
    BITBOARD_BitwiseAND(&movesMask, 2, &temp, &BITBOARD_Masks_knight[square]);
    while(BITBOARD_IsBitboardTrue(&movesMask)){
      moveSquare = BITBOARD_CountTrailingZeros(&movesMask);
      BITBOARD_SetBitboardToBitboard(&temp, &movesMask);
      BITBOARD_Subtract(&temp, &temp, &(BITBOARD_Bitboard){{1,0}});
      BITBOARD_BitwiseAND(&movesMask, 1, &temp);

      BOARD_AddMove(&board->pseudoMoves, square, moveSquare, 0);
    }
  }
}

void BOARD_GeneratePseudoMoves_Bishop(BOARD_Board* board, uint8_t isWhite)
{
  uint8_t square, moveSquare;
  BITBOARD_Bitboard bishops, emptySquares, temp, movesMask;
  BITBOARD_SetBitboardToBitboard(&bishops, isWhite?(&board->board.white_bishops):(&board->board.black_bishops));
  BITBOARD_BitwiseNOT(&emptySquares, &board->board.all_pieces);

  while(BITBOARD_IsBitboardTrue(&bishops)){
    square = BITBOARD_CountTrailingZeros(&bishops);
    BITBOARD_SetBitboardToBitboard(&temp, &bishops);
    BITBOARD_Subtract(&temp, &temp, &(BITBOARD_Bitboard){{1,0}});
    BITBOARD_BitwiseAND(&bishops, 1, &temp);

    BITBOARD_GetAttackMask_bishop(&temp, square, &board->board.all_pieces);
    BITBOARD_SetBitboardToBitboard(&movesMask, &(BITBOARD_Bitboard){{0,0}});
    BITBOARD_BitwiseOR(&movesMask, 2, &emptySquares, isWhite?(&board->board.black_pieces):(&board->board.white_pieces));
    BITBOARD_BitwiseAND(&movesMask, 1, &temp);
    while(BITBOARD_IsBitboardTrue(&movesMask)){
      moveSquare = BITBOARD_CountTrailingZeros(&movesMask);
      BITBOARD_SetBitboardToBitboard(&temp, &movesMask);
      BITBOARD_Subtract(&temp, &temp, &(BITBOARD_Bitboard){{1,0}});
      BITBOARD_BitwiseAND(&movesMask, 1, &temp);

      BOARD_AddMove(&board->pseudoMoves, square, moveSquare, 0);
    }
  }
}

void BOARD_GeneratePseudoMoves_Rook(BOARD_Board* board, uint8_t isWhite)
{
  uint8_t square, moveSquare;
  BITBOARD_Bitboard rooks, emptySquares, temp, movesMask;
  BITBOARD_SetBitboardToBitboard(&rooks, isWhite?(&board->board.white_rooks):(&board->board.black_rooks));
  BITBOARD_BitwiseNOT(&emptySquares, &board->board.all_pieces);

  while(BITBOARD_IsBitboardTrue(&rooks)){
    square = BITBOARD_CountTrailingZeros(&rooks);
    BITBOARD_SetBitboardToBitboard(&temp, &rooks);
    BITBOARD_Subtract(&temp, &temp, &(BITBOARD_Bitboard){{1,0}});
    BITBOARD_BitwiseAND(&rooks, 1, &temp);

    BITBOARD_GetAttackMask_rook(&temp, square, &board->board.all_pieces);
    BITBOARD_SetBitboardToBitboard(&movesMask, &(BITBOARD_Bitboard){{0,0}});
    BITBOARD_BitwiseOR(&movesMask, 2, &emptySquares, isWhite?(&board->board.black_pieces):(&board->board.white_pieces));
    BITBOARD_BitwiseAND(&movesMask, 1, &temp);
    while(BITBOARD_IsBitboardTrue(&movesMask)){
      moveSquare = BITBOARD_CountTrailingZeros(&movesMask);
      BITBOARD_SetBitboardToBitboard(&temp, &movesMask);
      BITBOARD_Subtract(&temp, &temp, &(BITBOARD_Bitboard){{1,0}});
      BITBOARD_BitwiseAND(&movesMask, 1, &temp);

      BOARD_AddMove(&board->pseudoMoves, square, moveSquare, 0);
    }
  }
}

void BOARD_GeneratePseudoMoves_Queen(BOARD_Board* board, uint8_t isWhite)
{
  uint8_t square, moveSquare;
  BITBOARD_Bitboard queens, emptySquares, temp, movesMask;
  BITBOARD_SetBitboardToBitboard(&queens, isWhite?(&board->board.white_queens):(&board->board.black_queens));
  BITBOARD_BitwiseNOT(&emptySquares, &board->board.all_pieces);

  while(BITBOARD_IsBitboardTrue(&queens)){
    square = BITBOARD_CountTrailingZeros(&queens);
    BITBOARD_SetBitboardToBitboard(&temp, &queens);
    BITBOARD_Subtract(&temp, &temp, &(BITBOARD_Bitboard){{1,0}});
    BITBOARD_BitwiseAND(&queens, 1, &temp);

    BITBOARD_GetAttackMask_rook(&temp, square, &board->board.all_pieces);
    BITBOARD_SetBitboardToBitboard(&movesMask, &(BITBOARD_Bitboard){{0,0}});
    BITBOARD_BitwiseOR(&movesMask, 2, &emptySquares, isWhite?(&board->board.black_pieces):(&board->board.white_pieces));
    BITBOARD_BitwiseAND(&movesMask, 1, &temp);
    while(BITBOARD_IsBitboardTrue(&movesMask)){
      moveSquare = BITBOARD_CountTrailingZeros(&movesMask);
      BITBOARD_SetBitboardToBitboard(&temp, &movesMask);
      BITBOARD_Subtract(&temp, &temp, &(BITBOARD_Bitboard){{1,0}});
      BITBOARD_BitwiseAND(&movesMask, 1, &temp);

      BOARD_AddMove(&board->pseudoMoves, square, moveSquare, 0);
    }

    BITBOARD_GetAttackMask_bishop(&temp, square, &board->board.all_pieces);
    BITBOARD_SetBitboardToBitboard(&movesMask, &(BITBOARD_Bitboard){{0,0}});
    BITBOARD_BitwiseOR(&movesMask, 2, &emptySquares, isWhite?(&board->board.black_pieces):(&board->board.white_pieces));
    BITBOARD_BitwiseAND(&movesMask, 1, &temp);
    while(BITBOARD_IsBitboardTrue(&movesMask)){
      moveSquare = BITBOARD_CountTrailingZeros(&movesMask);
      BITBOARD_SetBitboardToBitboard(&temp, &movesMask);
      BITBOARD_Subtract(&temp, &temp, &(BITBOARD_Bitboard){{1,0}});
      BITBOARD_BitwiseAND(&movesMask, 1, &temp);

      BOARD_AddMove(&board->pseudoMoves, square, moveSquare, 0);
    }
  }
}

void BOARD_GeneratePseudoMoves_King(BOARD_Board* board, uint8_t isWhite)
{
  uint8_t square, moveSquare;
  BITBOARD_Bitboard emptySquares, temp, movesMask;
  BITBOARD_BitwiseNOT(&emptySquares, &board->board.all_pieces);

  
  square = BITBOARD_CountTrailingZeros(isWhite?(&board->board.white_king):(&board->board.black_king));
  BITBOARD_SetBitboardToBitboard(&movesMask, &(BITBOARD_Bitboard){{0,0}});
  BITBOARD_BitwiseOR(&movesMask, 2, &emptySquares, isWhite?(&board->board.black_pieces):(&board->board.white_pieces));
  BITBOARD_BitwiseAND(&movesMask, 1, &BITBOARD_Masks_king[square]);
  while(BITBOARD_IsBitboardTrue(&movesMask)){
    moveSquare = BITBOARD_CountTrailingZeros(&movesMask);
    BITBOARD_SetBitboardToBitboard(&temp, &movesMask);
    BITBOARD_Subtract(&temp, &temp, &(BITBOARD_Bitboard){{1,0}});
    BITBOARD_BitwiseAND(&movesMask, 1, &temp);

    BOARD_AddMove(&board->pseudoMoves, square, moveSquare, 0);
  }
}

void BOARD_UpdateCastlingRights(BOARD_Board* board, uint8_t isWhite)
{
  if(isWhite){
    if(UTIL_GetBoolFromBools(board->bools, INDEX_CCWK) 
    && !(BITBOARD_GetBit(&board->board.white_rooks, 63) && BITBOARD_GetBit(&board->board.white_king, 60))){
      UTIL_SetBoolInBools(&board->bools, INDEX_CCWK, 0);
    }
    if(UTIL_GetBoolFromBools(board->bools, INDEX_CCWQ) 
    && !(BITBOARD_GetBit(&board->board.white_rooks, 56) && BITBOARD_GetBit(&board->board.white_king, 60))){
      UTIL_SetBoolInBools(&board->bools, INDEX_CCWQ, 0);
    }
  }
  else{
    if(UTIL_GetBoolFromBools(board->bools, INDEX_CCBK) 
    && !(BITBOARD_GetBit(&board->board.black_rooks, 7) && BITBOARD_GetBit(&board->board.black_king, 4))){
      UTIL_SetBoolInBools(&board->bools, INDEX_CCBK, 0);
    }
    if(UTIL_GetBoolFromBools(board->bools, INDEX_CCBQ) 
    && !(BITBOARD_GetBit(&board->board.black_rooks, 0) && BITBOARD_GetBit(&board->board.black_king, 4))){
      UTIL_SetBoolInBools(&board->bools, INDEX_CCBQ, 0);
    }
  }
}

void BOARD_GenerateCastlingMoves(BOARD_Board* board, uint8_t isWhite)
{
  uint8_t kingsideRights = UTIL_GetBoolFromBools(board->bools, (isWhite)?INDEX_CCWK:INDEX_CCWQ);
  uint8_t kingSquare;
  uint8_t bools = 0;
  BITBOARD_Bitboard temp1, temp2 = (BITBOARD_Bitboard){{0,0}};
  
  BOARD_UpdateCastlingRights(board, isWhite);

  if(isWhite){
    kingSquare = BITBOARD_CountTrailingZeros(&board->board.white_king);
    
    if(kingsideRights){
      // ci ani teraz ani pocas ani potom nebude attackovany king
      BITBOARD_LeftShift(&temp1, &(BITBOARD_Bitboard){{1,0}}, kingSquare);
      BITBOARD_BitwiseOR(&temp2, 1, &temp1);
      BITBOARD_LeftShift(&temp1, &(BITBOARD_Bitboard){{1,0}}, kingSquare+1);
      BITBOARD_BitwiseOR(&temp2, 1, &temp1);
      BITBOARD_LeftShift(&temp1, &(BITBOARD_Bitboard){{1,0}}, kingSquare+2);
      BITBOARD_BitwiseOR(&temp2, 1, &temp1);
      BITBOARD_SetBitboardToBitboard(&temp1, &board->board.enemyAttack);
      BITBOARD_BitwiseAND(&temp1, 1, &temp2);
      UTIL_SetBoolInBools(&bools, 0, !BITBOARD_IsBitboardTrue(&temp1));

      // ci su volne policka medzi nimi
      UTIL_SetBoolInBools(&bools, 1,((!BITBOARD_GetBit(&board->board.all_pieces, kingSquare+1))
        &&(!BITBOARD_GetBit(&board->board.all_pieces, kingSquare+2))));
      
      if(UTIL_GetBoolFromBools(bools, 0) && UTIL_GetBoolFromBools(bools, 1)){
        BOARD_AddMove(&board->pseudoMoves, kingSquare, 63, 0);
      }
    }

    
  }
  else{

  }
}

void BOARD_GeneratePseudoMoves(BOARD_Board* board)
{
  uint8_t isWhite = UTIL_GetBoolFromBools(board->bools, INDEX_ON_TURN);
  board->pseudoMoves.count = 0;

  // generate moves for all all_pieces
  BOARD_GeneratePseudoMoves_Pawn(board, isWhite);
  BOARD_GeneratePseudoMoves_Knight(board, isWhite);
  BOARD_GeneratePseudoMoves_Bishop(board, isWhite);
  BOARD_GeneratePseudoMoves_Rook(board, isWhite);
  BOARD_GeneratePseudoMoves_Queen(board, isWhite);
  BOARD_GeneratePseudoMoves_King(board, isWhite);
  // BOARD_GenerateCastlingMoves(board, isWhite);
}

void BOARD_FilterLegalMoves(BOARD_Board* board)
{
  board->legalMoves.count = 0;
  int8_t can=0, square=-1;
  uint8_t isWhite = UTIL_GetBoolFromBools(board->bools, INDEX_ON_TURN);

  for(uint8_t i=0;i<board->pseudoMoves.count;i++){
    if(can && square==board->pseudoMoves.list[i].from){
      BOARD_AddMove(&board->legalMoves, board->pseudoMoves.list[i].from, board->pseudoMoves.list[i].to, board->pseudoMoves.list[i].promotion);
      continue;
    }
    else if(square!=board->pseudoMoves.list[i].from){
      BOARD_InitBoardStateCopy(board);
      square = board->pseudoMoves.list[i].from;
      
      BITBOARD_Bitboard pieceMask=(BITBOARD_Bitboard){{0,0}}, removeMask;
      BITBOARD_LeftShift(&pieceMask, &(BITBOARD_Bitboard){{1,0}}, square);
      BITBOARD_Subtract(&removeMask, &(BITBOARD_Bitboard){{0xFFFFFFFF,0xFFFFFFFF}}, &pieceMask);

      if(isWhite){
        BITBOARD_BitwiseAND(&board->boardCopy.white_pieces, 1, &removeMask);
        BITBOARD_BitwiseAND(&board->boardCopy.white_pawns, 1, &removeMask);
        BITBOARD_BitwiseAND(&board->boardCopy.white_knights, 1, &removeMask);
        BITBOARD_BitwiseAND(&board->boardCopy.white_bishops, 1, &removeMask);
        BITBOARD_BitwiseAND(&board->boardCopy.white_rooks, 1, &removeMask);
        BITBOARD_BitwiseAND(&board->boardCopy.white_queens, 1, &removeMask);
        BITBOARD_BitwiseAND(&board->boardCopy.white_king, 1, &removeMask);
      }
      else{
        BITBOARD_BitwiseAND(&board->boardCopy.black_pieces, 1, &removeMask);
        BITBOARD_BitwiseAND(&board->boardCopy.black_pawns, 1, &removeMask);
        BITBOARD_BitwiseAND(&board->boardCopy.black_knights, 1, &removeMask);
        BITBOARD_BitwiseAND(&board->boardCopy.black_bishops, 1, &removeMask);
        BITBOARD_BitwiseAND(&board->boardCopy.black_rooks, 1, &removeMask);
        BITBOARD_BitwiseAND(&board->boardCopy.black_queens, 1, &removeMask);
        BITBOARD_BitwiseAND(&board->boardCopy.black_king, 1, &removeMask);
      }
      BITBOARD_BitwiseAND(&board->boardCopy.all_pieces, 1, &removeMask);
      can = !BOARD_IsCheck(&board->boardCopy, isWhite); 
    }

    BOARD_InitBoardStateCopy(board);
    BOARD_MakeMove(&board->boardCopy, &board->pseudoMoves.list[i], isWhite, board->enPassant);

    if(BOARD_IsCheck(&board->boardCopy, isWhite)==0){
      BOARD_AddMove(&board->legalMoves, board->pseudoMoves.list[i].from, board->pseudoMoves.list[i].to, board->pseudoMoves.list[i].promotion);
    }
  }
}


// ======================================= GAME FUNCTIONS ========================================


void BOARD_PlayTurn(BOARD_Board* board, int offx, int offy)
{
  uint8_t isWhite = UTIL_GetBoolFromBools(board->bools, INDEX_ON_TURN);
  
  int mx = GetMouseX();
  int my = GetMouseY();

  int px = (mx-offx)/TS;
  int py = (my-offy)/TS;
  int pos = -1;

  if(px>=0 && px<8 && py>=0 && py<8 && (mx-offx)>=0 && (my-offy)>=0){
    pos = py*8+px;
  }


  if(IsMouseButtonPressed(0)){
    // printf("x%d y%d\n", px, py);
    
    if(pos>=0){
      if(board->selectedX>=0 && board->selectedY>=0){
        BOARD_InitBoardStateCopy(board);

        for(uint8_t i=0;i<board->legalMoves.count;i++){ 
          if(board->legalMoves.list[i].from==(board->selectedY*8+board->selectedX) && board->legalMoves.list[i].to==pos){
            
            BOARD_MakeMove(&board->board, &board->legalMoves.list[i], isWhite, board->enPassant);
            
            if(((isWhite && BITBOARD_GetBit(&board->boardCopy.white_pawns, board->legalMoves.list[i].from)==1) || 
            (!isWhite && BITBOARD_GetBit(&board->boardCopy.black_pawns, board->legalMoves.list[i].from)==1)) &&
            (abs(board->legalMoves.list[i].to-board->legalMoves.list[i].from)==16)){
              board->enPassant = (board->legalMoves.list[i].to+board->legalMoves.list[i].from)/2;
            }
            else{
              board->enPassant = -1;
            }

            UTIL_SetBoolInBools(&board->bools, INDEX_ON_TURN, !isWhite);
            board->selectedX = board->selectedY = -1;
            BOARD_PrintBitmaps(board);
            printf("%s isCheck = %s\n", isWhite?"black":"white", BOARD_IsCheck(&board->board, isWhite)?"true":"false");
            printf("Q%d K%d\n", UTIL_GetBoolFromBools(board->bools, (isWhite)?INDEX_CCWQ:INDEX_CCBQ), 
              UTIL_GetBoolFromBools(board->bools, (isWhite)?INDEX_CCWK:INDEX_CCBK));
            BOARD_GeneratePseudoMoves(board);
            BOARD_FilterLegalMoves(board);
          }
        }
      }
      if(isWhite && BITBOARD_GetBit(&board->board.white_pieces, pos)){
        board->selectedX = px;
        board->selectedY = py;
      }
      else if(!isWhite && BITBOARD_GetBit(&board->board.black_pieces, pos)){
        board->selectedX = px;
        board->selectedY = py;
      }
    }
    else{
      board->selectedX = board->selectedY = -1;
    }
  }
}
