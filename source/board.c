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

void BOARD_PrintPrettyBoard(BOARD_BoardState* board)
{
  printf("Pretty board:\n");
  for(int i=0;i<64;i++){
    if(BITBOARD_GetBit(&board->black_king, i)) printf("k ");
    else if(BITBOARD_GetBit(&board->black_queens, i)) printf("q ");
    else if(BITBOARD_GetBit(&board->black_rooks, i)) printf("r ");
    else if(BITBOARD_GetBit(&board->black_bishops, i)) printf("b ");
    else if(BITBOARD_GetBit(&board->black_knights, i)) printf("n ");
    else if(BITBOARD_GetBit(&board->black_pawns, i)) printf("p ");
    else if(BITBOARD_GetBit(&board->white_king, i)) printf("K ");
    else if(BITBOARD_GetBit(&board->white_queens, i)) printf("Q ");
    else if(BITBOARD_GetBit(&board->white_rooks, i)) printf("R ");
    else if(BITBOARD_GetBit(&board->white_bishops, i)) printf("B ");
    else if(BITBOARD_GetBit(&board->white_knights, i)) printf("N ");
    else if(BITBOARD_GetBit(&board->white_pawns, i)) printf("P ");
    else printf(". ");
    if((i+1)%8==0) printf("\n");
  }
  printf("\n");
}

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

  printf("PAWNS:                  ROOKS:                  KNIGHTS:        \n");
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

  board.board.enPassant = -1;
  board.board.bools = 0;
  
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
      UTIL_SetBoolInBools(&board.board.bools, INDEX_ON_TURN, 1);
    }
    if(symbol=='b'){
      UTIL_SetBoolInBools(&board.board.bools, INDEX_ON_TURN, 0);
    }
    if(symbol=='K'){
      UTIL_SetBoolInBools(&board.board.bools, INDEX_CCWK, 1);
    }
    if(symbol=='Q'){
      UTIL_SetBoolInBools(&board.board.bools, INDEX_CCWQ, 1);
    }
    if(symbol=='k'){
      UTIL_SetBoolInBools(&board.board.bools, INDEX_CCBK, 1);
    }
    if(symbol=='q'){
      UTIL_SetBoolInBools(&board.board.bools, INDEX_CCBQ, 1);
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

  BOARD_GeneratePseudoMoves(&board.board);
  BOARD_FilterLegalMoves(&board.board);
  
  return board;
}

void BOARD_DrawBoard(BOARD_Board* board, int offx, int offy, uint8_t* bools)
{
  uint8_t row, col;
  uint8_t pos;
  #if FANCY_BOARD
  uint8_t isWhite = UTIL_GetBoolFromBools(*bools, INDEX_ON_TURN);
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

      for(uint8_t i=0;i<board->board.legalMoves.count;i++){
       if(board->board.legalMoves.list[i].from==board->selectedY*8+board->selectedX && board->board.legalMoves.list[i].to==pos){
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

      if(pos==board->selectedY*8+board->selectedX){
        DrawRectangle(offx+col*TS, offy+row*TS, TS, TS, (Color){100, 0, 0, 100});
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


uint8_t BOARD_IsCheck(BOARD_BoardState* board, int8_t square, uint8_t isWhite)
{
  BITBOARD_Bitboard temp, temp1;

  if(square<0) return 1;

  if(isWhite){
    // white is on turn

    // pawn 
    BITBOARD_SetBitboardToBitboard(&temp, &BITBOARD_AttackMasks_pawn[1][square]);
    BITBOARD_BitwiseAND(&temp, 1, &board->black_pawns);
    // BITBOARD_Print(&temp);
    if(BITBOARD_IsBitboardTrue(&temp)) return 1;

    // knight 
    BITBOARD_SetBitboardToBitboard(&temp, &BITBOARD_Masks_knight[square]);
    BITBOARD_BitwiseAND(&temp, 1, &board->black_knights);
    // BITBOARD_Print(&temp);
    if(BITBOARD_IsBitboardTrue(&temp)) return 1;

    // diagonal (queen & bishop)
    BITBOARD_GetAttackMask_bishop(&temp1, square, &board->all_pieces);
    BITBOARD_BitwiseOR(&temp, 2, &board->black_bishops, &board->black_queens);
    BITBOARD_BitwiseAND(&temp, 1, &temp1);
    // BITBOARD_Print(&temp);
    if(BITBOARD_IsBitboardTrue(&temp)) return 1;

    // straight lines (queen & rook)
    BITBOARD_GetAttackMask_rook(&temp1, square, &board->all_pieces);
    BITBOARD_BitwiseOR(&temp, 2, &board->black_rooks, &board->black_queens);
    BITBOARD_BitwiseAND(&temp, 1, &temp1);
    // BITBOARD_Print(&temp);
    if(BITBOARD_IsBitboardTrue(&temp)) return 1;

    // king 
    BITBOARD_SetBitboardToBitboard(&temp, &BITBOARD_Masks_king[square]);
    BITBOARD_BitwiseAND(&temp, 1, &board->black_king);
    // BITBOARD_Print(&temp);
    if(BITBOARD_IsBitboardTrue(&temp)) return 1;
  }
  else{ 
    // black is on turn
    
    // pawn 
    BITBOARD_SetBitboardToBitboard(&temp, &BITBOARD_AttackMasks_pawn[0][square]);
    BITBOARD_BitwiseAND(&temp, 1, &board->white_pawns);
    // BITBOARD_Print(&temp);
    if(BITBOARD_IsBitboardTrue(&temp)) return 1;

    // knight 
    BITBOARD_SetBitboardToBitboard(&temp, &BITBOARD_Masks_knight[square]);
    BITBOARD_BitwiseAND(&temp, 1, &board->white_knights);
    // BITBOARD_Print(&temp);
    if(BITBOARD_IsBitboardTrue(&temp)) return 1;

    // diagonal (queen & bishop)
    BITBOARD_GetAttackMask_bishop(&temp1, square, &board->all_pieces);
    BITBOARD_BitwiseOR(&temp, 2, &board->white_bishops, &board->white_queens);
    BITBOARD_BitwiseAND(&temp, 1, &temp1);
    if(BITBOARD_IsBitboardTrue(&temp)) return 1;

    // straight lines (queen & rook)
    BITBOARD_GetAttackMask_rook(&temp1, square, &board->all_pieces);
    BITBOARD_BitwiseOR(&temp, 2, &board->white_rooks, &board->white_queens);
    BITBOARD_BitwiseAND(&temp, 1, &temp1);
    if(BITBOARD_IsBitboardTrue(&temp)) return 1;

    // king 
    BITBOARD_SetBitboardToBitboard(&temp, &BITBOARD_Masks_king[square]);
    BITBOARD_BitwiseAND(&temp, 1, &board->white_king);
    // BITBOARD_Print(&temp);
    if(BITBOARD_IsBitboardTrue(&temp)) return 1; 
  }
  return 0;
}

void BOARD_AddMove(BOARD_MoveList* moves, int8_t from, int8_t to, int8_t promotion)
{
  moves->list[moves->count].from = from;
  moves->list[moves->count].to = to;
  moves->list[moves->count].promotion = promotion;
  moves->count++;
}

void BOARD_MakeMove(BOARD_BoardState* board, BOARD_Move* move, uint8_t isWhite)
{
  BITBOARD_Bitboard temp=(BITBOARD_Bitboard){{1,0}}, removeMask, pieceMask=(BITBOARD_Bitboard){{0,0}}, moveMask=(BITBOARD_Bitboard){{0,0}};
  BITBOARD_LeftShift(&pieceMask, &temp, move->from);
  BITBOARD_LeftShift(&moveMask, &temp, move->to);
  BITBOARD_BitwiseNOT(&removeMask, &pieceMask);
 
  if(isWhite){
    BITBOARD_SetBitboardToBitboard(&temp, &(BITBOARD_Bitboard){{0xFFFFFFFF,0xFFFFFFFF}});
    BITBOARD_BitwiseAND(&temp, 2, &pieceMask, &board->white_pawns);
    if(BITBOARD_IsBitboardTrue(&temp)){
      BITBOARD_BitwiseAND(&board->white_pawns, 1, &removeMask);
      if(move->to<=7){
        BITBOARD_BitwiseOR(&board->white_queens, 1, &moveMask);
      }
      else{
        BITBOARD_BitwiseOR(&board->white_pawns, 1, &moveMask);
      }

      if(move->to==board->enPassant){
        BITBOARD_LeftShift(&pieceMask, &(BITBOARD_Bitboard){{1,0}}, board->enPassant+8);
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

      if(move->from==60 && move->to==62){
        // kingside
        BITBOARD_BitwiseAND(&board->white_rooks, 1, &(BITBOARD_Bitboard){{0xFFFFFFFF,0x7FFFFFFF}});
        BITBOARD_BitwiseAND(&board->white_pieces, 1, &(BITBOARD_Bitboard){{0xFFFFFFFF,0x7FFFFFFF}});
        BITBOARD_BitwiseAND(&board->all_pieces, 1, &(BITBOARD_Bitboard){{0xFFFFFFFF,0x7FFFFFFF}});
        BITBOARD_BitwiseOR(&board->white_rooks, 1, &(BITBOARD_Bitboard){{0,0x20000000}});
        BITBOARD_BitwiseOR(&board->white_pieces, 1, &(BITBOARD_Bitboard){{0,0x20000000}});
        BITBOARD_BitwiseOR(&board->all_pieces, 1, &(BITBOARD_Bitboard){{0,0x20000000}});
      }
      if(move->from==60 && move->to==58){
        // queenside 
        BITBOARD_BitwiseAND(&board->white_rooks, 1, &(BITBOARD_Bitboard){{0xFFFFFFFF,0xFEFFFFFF}});
        BITBOARD_BitwiseAND(&board->white_pieces, 1, &(BITBOARD_Bitboard){{0xFFFFFFFF,0xFEFFFFFF}});
        BITBOARD_BitwiseAND(&board->all_pieces, 1, &(BITBOARD_Bitboard){{0xFFFFFFFF,0xFEFFFFFF}});
        BITBOARD_BitwiseOR(&board->white_rooks, 1, &(BITBOARD_Bitboard){{0,0x08000000}});
        BITBOARD_BitwiseOR(&board->white_pieces, 1, &(BITBOARD_Bitboard){{0,0x08000000}});
        BITBOARD_BitwiseOR(&board->all_pieces, 1, &(BITBOARD_Bitboard){{0,0x08000000}});
      }
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
      if(move->to>=56){
        BITBOARD_BitwiseOR(&board->black_queens, 1, &moveMask);
      }
      else{
        BITBOARD_BitwiseOR(&board->black_pawns, 1, &moveMask);
      }

      if(move->to==board->enPassant){
        BITBOARD_LeftShift(&pieceMask, &(BITBOARD_Bitboard){{1,0}}, board->enPassant-8);
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

      if(move->from==4 && move->to==6){
        // kingside
        BITBOARD_BitwiseAND(&board->black_rooks, 1, &(BITBOARD_Bitboard){{0xFFFFFF7F,0xFFFFFFFF}});
        BITBOARD_BitwiseAND(&board->black_pieces, 1, &(BITBOARD_Bitboard){{0xFFFFFF7F,0xFFFFFFFF}});
        BITBOARD_BitwiseAND(&board->all_pieces, 1, &(BITBOARD_Bitboard){{0xFFFFFF7F,0xFFFFFFFF}});
        BITBOARD_BitwiseOR(&board->black_rooks, 1, &(BITBOARD_Bitboard){{0x00000020,0}});
        BITBOARD_BitwiseOR(&board->black_pieces, 1, &(BITBOARD_Bitboard){{0x00000020,0}});
        BITBOARD_BitwiseOR(&board->all_pieces, 1, &(BITBOARD_Bitboard){{0x00000020,0}});
      }
      if(move->from==4 && move->to==2){
        // queenside 
        BITBOARD_BitwiseAND(&board->black_rooks, 1, &(BITBOARD_Bitboard){{0xFFFFFFFE,0xFFFFFFFF}});
        BITBOARD_BitwiseAND(&board->black_pieces, 1, &(BITBOARD_Bitboard){{0xFFFFFFFE,0xFFFFFFFF}});
        BITBOARD_BitwiseAND(&board->all_pieces, 1, &(BITBOARD_Bitboard){{0xFFFFFFFE,0xFFFFFFFF}});
        BITBOARD_BitwiseOR(&board->black_rooks, 1, &(BITBOARD_Bitboard){{0x00000008,0}});
        BITBOARD_BitwiseOR(&board->black_pieces, 1, &(BITBOARD_Bitboard){{0x00000008,0}});
        BITBOARD_BitwiseOR(&board->all_pieces, 1, &(BITBOARD_Bitboard){{0x00000008,0}});
      }
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

void BOARD_UndoMove(BOARD_BoardState* board, BOARD_Move* move, uint8_t isWhite)
{
  BITBOARD_Bitboard temp=(BITBOARD_Bitboard){{1,0}}, removeMask, removeFrom, 
    pieceMask=(BITBOARD_Bitboard){{0,0}}, moveMask=(BITBOARD_Bitboard){{0,0}};
  BITBOARD_LeftShift(&pieceMask, &temp, move->to);
  BITBOARD_LeftShift(&moveMask, &temp, move->from);
  BITBOARD_BitwiseNOT(&removeMask, &pieceMask);
  BITBOARD_BitwiseNOT(&removeFrom, &moveMask);
 
  if(isWhite){
    BITBOARD_SetBitboardToBitboard(&temp, &(BITBOARD_Bitboard){{0xFFFFFFFF,0xFFFFFFFF}});
    BITBOARD_BitwiseAND(&temp, 2, &pieceMask, &board->white_pawns);
    if(BITBOARD_IsBitboardTrue(&temp)){
      BITBOARD_BitwiseAND(&board->white_pawns, 1, &removeMask);
        
      BITBOARD_BitwiseOR(&board->white_pawns, 1, &moveMask);

      if(move->to==board->enPassant){
        BITBOARD_LeftShift(&pieceMask, &(BITBOARD_Bitboard){{1,0}}, board->enPassant+8);
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

      if(move->to<=7){
        BITBOARD_BitwiseAND(&board->white_queens, 1, &removeFrom);
        BITBOARD_BitwiseOR(&board->white_pawns, 1, &moveMask);
      }
    }
    BITBOARD_SetBitboardToBitboard(&temp, &(BITBOARD_Bitboard){{0xFFFFFFFF,0xFFFFFFFF}});
    BITBOARD_BitwiseAND(&temp, 2, &pieceMask, &board->white_king);
    if(BITBOARD_IsBitboardTrue(&temp)){
      BITBOARD_BitwiseAND(&board->white_king, 1, &removeMask);
      BITBOARD_BitwiseOR(&board->white_king, 1, &moveMask);

      if(move->from==60 && move->to==62){
        // kingside
        BITBOARD_BitwiseAND(&board->white_rooks, 1, &(BITBOARD_Bitboard){{0xFFFFFFFF,0xDFFFFFFF}});
        BITBOARD_BitwiseAND(&board->white_pieces, 1, &(BITBOARD_Bitboard){{0xFFFFFFFF,0xDFFFFFFF}});
        BITBOARD_BitwiseAND(&board->all_pieces, 1, &(BITBOARD_Bitboard){{0xFFFFFFFF,0xDFFFFFFF}});
        BITBOARD_BitwiseOR(&board->white_rooks, 1, &(BITBOARD_Bitboard){{0,0x80000000}});
        BITBOARD_BitwiseOR(&board->white_pieces, 1, &(BITBOARD_Bitboard){{0,0x80000000}});
        BITBOARD_BitwiseOR(&board->all_pieces, 1, &(BITBOARD_Bitboard){{0,0x80000000}});
      }
      if(move->from==60 && move->to==58){
        // queenside 
        BITBOARD_BitwiseAND(&board->white_rooks, 1, &(BITBOARD_Bitboard){{0xFFFFFFFF,0xF7FFFFFF}});
        BITBOARD_BitwiseAND(&board->white_pieces, 1, &(BITBOARD_Bitboard){{0xFFFFFFFF,0xF7FFFFFF}});
        BITBOARD_BitwiseAND(&board->all_pieces, 1, &(BITBOARD_Bitboard){{0xFFFFFFFF,0xF7FFFFFF}});
        BITBOARD_BitwiseOR(&board->white_rooks, 1, &(BITBOARD_Bitboard){{0,0x01000000}});
        BITBOARD_BitwiseOR(&board->white_pieces, 1, &(BITBOARD_Bitboard){{0,0x01000000}});
        BITBOARD_BitwiseOR(&board->all_pieces, 1, &(BITBOARD_Bitboard){{0,0x01000000}});
      }
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
      if(move->to>=56){
        BITBOARD_BitwiseOR(&board->black_queens, 1, &moveMask);
      }
      else{
        BITBOARD_BitwiseOR(&board->black_pawns, 1, &moveMask);
      }

      if(move->to==board->enPassant){
        BITBOARD_LeftShift(&pieceMask, &(BITBOARD_Bitboard){{1,0}}, board->enPassant-8);
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

      if(move->from==4 && move->to==6){
        // kingside
        BITBOARD_BitwiseAND(&board->black_rooks, 1, &(BITBOARD_Bitboard){{0xFFFFFF7F,0xFFFFFFFF}});
        BITBOARD_BitwiseAND(&board->black_pieces, 1, &(BITBOARD_Bitboard){{0xFFFFFF7F,0xFFFFFFFF}});
        BITBOARD_BitwiseAND(&board->all_pieces, 1, &(BITBOARD_Bitboard){{0xFFFFFF7F,0xFFFFFFFF}});
        BITBOARD_BitwiseOR(&board->black_rooks, 1, &(BITBOARD_Bitboard){{0x00000020,0}});
        BITBOARD_BitwiseOR(&board->black_pieces, 1, &(BITBOARD_Bitboard){{0x00000020,0}});
        BITBOARD_BitwiseOR(&board->all_pieces, 1, &(BITBOARD_Bitboard){{0x00000020,0}});
      }
      if(move->from==4 && move->to==2){
        // queenside 
        BITBOARD_BitwiseAND(&board->black_rooks, 1, &(BITBOARD_Bitboard){{0xFFFFFFFE,0xFFFFFFFF}});
        BITBOARD_BitwiseAND(&board->black_pieces, 1, &(BITBOARD_Bitboard){{0xFFFFFFFE,0xFFFFFFFF}});
        BITBOARD_BitwiseAND(&board->all_pieces, 1, &(BITBOARD_Bitboard){{0xFFFFFFFE,0xFFFFFFFF}});
        BITBOARD_BitwiseOR(&board->black_rooks, 1, &(BITBOARD_Bitboard){{0x00000008,0}});
        BITBOARD_BitwiseOR(&board->black_pieces, 1, &(BITBOARD_Bitboard){{0x00000008,0}});
        BITBOARD_BitwiseOR(&board->all_pieces, 1, &(BITBOARD_Bitboard){{0x00000008,0}});
      }
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

void BOARD_InitBoardStateCopy(BOARD_BoardState* board, BOARD_BoardState* boardCopy)
{
  BITBOARD_SetBitboardToBitboard(&boardCopy->all_pieces, &board->all_pieces);
  BITBOARD_SetBitboardToBitboard(&boardCopy->white_pawns, &board->white_pawns);
  BITBOARD_SetBitboardToBitboard(&boardCopy->white_knights, &board->white_knights);
  BITBOARD_SetBitboardToBitboard(&boardCopy->white_bishops, &board->white_bishops);
  BITBOARD_SetBitboardToBitboard(&boardCopy->white_rooks, &board->white_rooks);
  BITBOARD_SetBitboardToBitboard(&boardCopy->white_queens, &board->white_queens);
  BITBOARD_SetBitboardToBitboard(&boardCopy->white_king, &board->white_king);
  BITBOARD_SetBitboardToBitboard(&boardCopy->black_pawns, &board->black_pawns);
  BITBOARD_SetBitboardToBitboard(&boardCopy->black_knights, &board->black_knights);
  BITBOARD_SetBitboardToBitboard(&boardCopy->black_bishops, &board->black_bishops);
  BITBOARD_SetBitboardToBitboard(&boardCopy->black_rooks, &board->black_rooks);
  BITBOARD_SetBitboardToBitboard(&boardCopy->black_queens, &board->black_queens);
  BITBOARD_SetBitboardToBitboard(&boardCopy->black_king, &board->black_king);
}

void BOARD_GeneratePseudoMoves_Pawn(BOARD_BoardState* board, uint8_t isWhite)
{
  uint8_t square, attackSquare;
  BITBOARD_Bitboard pawns, emptySquares, temp, push;
  BITBOARD_SetBitboardToBitboard(&pawns, (isWhite)?(&board->white_pawns):(&board->black_pawns));
  BITBOARD_BitwiseNOT(&emptySquares, &board->all_pieces);
  
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
      (isWhite)?(&board->black_pieces):(&board->white_pieces));
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

void BOARD_GeneratePseudoMoves_Knight(BOARD_BoardState* board, uint8_t isWhite)
{
  uint8_t square, moveSquare;
  BITBOARD_Bitboard knights, emptySquares, temp, movesMask;
  BITBOARD_SetBitboardToBitboard(&knights, isWhite?(&board->white_knights):(&board->black_knights));
  BITBOARD_BitwiseNOT(&emptySquares, &board->all_pieces);

  while(BITBOARD_IsBitboardTrue(&knights)){
    square = BITBOARD_CountTrailingZeros(&knights);
    BITBOARD_SetBitboardToBitboard(&temp, &knights);
    BITBOARD_Subtract(&temp, &temp, &(BITBOARD_Bitboard){{1,0}});
    BITBOARD_BitwiseAND(&knights, 1, &temp);

    BITBOARD_SetBitboardToBitboard(&temp, &(BITBOARD_Bitboard){{0,0}});
    BITBOARD_BitwiseOR(&temp, 2, &emptySquares, isWhite?(&board->black_pieces):(&board->white_pieces));
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

void BOARD_GeneratePseudoMoves_Bishop(BOARD_BoardState* board, uint8_t isWhite)
{
  uint8_t square, moveSquare;
  BITBOARD_Bitboard bishops, emptySquares, temp, movesMask;
  BITBOARD_SetBitboardToBitboard(&bishops, isWhite?(&board->white_bishops):(&board->black_bishops));
  BITBOARD_BitwiseNOT(&emptySquares, &board->all_pieces);

  while(BITBOARD_IsBitboardTrue(&bishops)){
    square = BITBOARD_CountTrailingZeros(&bishops);
    BITBOARD_SetBitboardToBitboard(&temp, &bishops);
    BITBOARD_Subtract(&temp, &temp, &(BITBOARD_Bitboard){{1,0}});
    BITBOARD_BitwiseAND(&bishops, 1, &temp);

    BITBOARD_GetAttackMask_bishop(&temp, square, &board->all_pieces);
    BITBOARD_SetBitboardToBitboard(&movesMask, &(BITBOARD_Bitboard){{0,0}});
    BITBOARD_BitwiseOR(&movesMask, 2, &emptySquares, isWhite?(&board->black_pieces):(&board->white_pieces));
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

void BOARD_GeneratePseudoMoves_Rook(BOARD_BoardState* board, uint8_t isWhite)
{
  uint8_t square, moveSquare;
  BITBOARD_Bitboard rooks, emptySquares, temp, movesMask;
  BITBOARD_SetBitboardToBitboard(&rooks, isWhite?(&board->white_rooks):(&board->black_rooks));
  BITBOARD_BitwiseNOT(&emptySquares, &board->all_pieces);

  while(BITBOARD_IsBitboardTrue(&rooks)){
    square = BITBOARD_CountTrailingZeros(&rooks);
    BITBOARD_SetBitboardToBitboard(&temp, &rooks);
    BITBOARD_Subtract(&temp, &temp, &(BITBOARD_Bitboard){{1,0}});
    BITBOARD_BitwiseAND(&rooks, 1, &temp);

    BITBOARD_GetAttackMask_rook(&temp, square, &board->all_pieces);
    BITBOARD_SetBitboardToBitboard(&movesMask, &(BITBOARD_Bitboard){{0,0}});
    BITBOARD_BitwiseOR(&movesMask, 2, &emptySquares, isWhite?(&board->black_pieces):(&board->white_pieces));
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

void BOARD_GeneratePseudoMoves_Queen(BOARD_BoardState* board, uint8_t isWhite)
{
  uint8_t square, moveSquare;
  BITBOARD_Bitboard queens, emptySquares, temp, movesMask;
  BITBOARD_SetBitboardToBitboard(&queens, isWhite?(&board->white_queens):(&board->black_queens));
  BITBOARD_BitwiseNOT(&emptySquares, &board->all_pieces);

  while(BITBOARD_IsBitboardTrue(&queens)){
    square = BITBOARD_CountTrailingZeros(&queens);
    BITBOARD_SetBitboardToBitboard(&temp, &queens);
    BITBOARD_Subtract(&temp, &temp, &(BITBOARD_Bitboard){{1,0}});
    BITBOARD_BitwiseAND(&queens, 1, &temp);

    BITBOARD_GetAttackMask_rook(&temp, square, &board->all_pieces);
    BITBOARD_SetBitboardToBitboard(&movesMask, &(BITBOARD_Bitboard){{0,0}});
    BITBOARD_BitwiseOR(&movesMask, 2, &emptySquares, isWhite?(&board->black_pieces):(&board->white_pieces));
    BITBOARD_BitwiseAND(&movesMask, 1, &temp);
    while(BITBOARD_IsBitboardTrue(&movesMask)){
      moveSquare = BITBOARD_CountTrailingZeros(&movesMask);
      BITBOARD_SetBitboardToBitboard(&temp, &movesMask);
      BITBOARD_Subtract(&temp, &temp, &(BITBOARD_Bitboard){{1,0}});
      BITBOARD_BitwiseAND(&movesMask, 1, &temp);

      BOARD_AddMove(&board->pseudoMoves, square, moveSquare, 0);
    }

    BITBOARD_GetAttackMask_bishop(&temp, square, &board->all_pieces);
    BITBOARD_SetBitboardToBitboard(&movesMask, &(BITBOARD_Bitboard){{0,0}});
    BITBOARD_BitwiseOR(&movesMask, 2, &emptySquares, isWhite?(&board->black_pieces):(&board->white_pieces));
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

void BOARD_GeneratePseudoMoves_King(BOARD_BoardState* board, uint8_t isWhite)
{
  uint8_t square, moveSquare;
  BITBOARD_Bitboard emptySquares, temp, movesMask;
  BITBOARD_BitwiseNOT(&emptySquares, &board->all_pieces);

  
  square = BITBOARD_CountTrailingZeros(isWhite?(&board->white_king):(&board->black_king));
  BITBOARD_SetBitboardToBitboard(&movesMask, &(BITBOARD_Bitboard){{0,0}});
  BITBOARD_BitwiseOR(&movesMask, 2, &emptySquares, isWhite?(&board->black_pieces):(&board->white_pieces));
  BITBOARD_BitwiseAND(&movesMask, 1, &BITBOARD_Masks_king[square]);
  while(BITBOARD_IsBitboardTrue(&movesMask)){
    moveSquare = BITBOARD_CountTrailingZeros(&movesMask);
    BITBOARD_SetBitboardToBitboard(&temp, &movesMask);
    BITBOARD_Subtract(&temp, &temp, &(BITBOARD_Bitboard){{1,0}});
    BITBOARD_BitwiseAND(&movesMask, 1, &temp);

    BOARD_AddMove(&board->pseudoMoves, square, moveSquare, 0);
  }
}

void BOARD_GenerateCastlingMoves(BOARD_BoardState* board, uint8_t isWhite)
{
  uint8_t kingsideRights = UTIL_GetBoolFromBools(board->bools, (isWhite)?INDEX_CCWK:INDEX_CCBK);
  uint8_t queensideRights = UTIL_GetBoolFromBools(board->bools, (isWhite)?INDEX_CCWQ:INDEX_CCBQ);
  uint8_t kingSquare;

  if(isWhite){
    kingSquare = BITBOARD_CountTrailingZeros(&board->white_king);

    if(kingsideRights && !(BITBOARD_GetBit(&board->white_rooks, 63) && kingSquare==60)){
      UTIL_SetBoolInBools(&board->bools, INDEX_CCWK, 0);
      kingsideRights = 0;
    }
    if(queensideRights && !(BITBOARD_GetBit(&board->white_rooks, 56) && kingSquare==60)){
      UTIL_SetBoolInBools(&board->bools, INDEX_CCWQ, 0);
      queensideRights = 0;
    }
    
    if(kingsideRights){
      if(!BITBOARD_GetBit(&board->all_pieces, kingSquare+1)
      && !BITBOARD_GetBit(&board->all_pieces, kingSquare+2) 
      && !BOARD_IsCheck(board, kingSquare, isWhite) 
      && !BOARD_IsCheck(board, kingSquare+1, isWhite)
      && !BOARD_IsCheck(board, kingSquare+2, isWhite)){
        BOARD_AddMove(&board->pseudoMoves, kingSquare, kingSquare+2, 0);
      }
    }

    if(queensideRights){
      if(!BITBOARD_GetBit(&board->all_pieces, kingSquare-1)
      && !BITBOARD_GetBit(&board->all_pieces, kingSquare-2) 
      && !BITBOARD_GetBit(&board->all_pieces, kingSquare-3) 
      && !BOARD_IsCheck(board, kingSquare, isWhite) 
      && !BOARD_IsCheck(board, kingSquare-1, isWhite)
      && !BOARD_IsCheck(board, kingSquare-2, isWhite)
      && !BOARD_IsCheck(board, kingSquare-3, isWhite)){
        BOARD_AddMove(&board->pseudoMoves, kingSquare, kingSquare-2, 0);
      }
    }
  }
  else{
    kingSquare = BITBOARD_CountTrailingZeros(&board->black_king);

    if(kingsideRights && !(BITBOARD_GetBit(&board->black_rooks, 7) && kingSquare==4)){
      UTIL_SetBoolInBools(&board->bools, INDEX_CCBK, 0);
      kingsideRights = 0;
    }
    if(queensideRights && !(BITBOARD_GetBit(&board->black_rooks, 0) && kingSquare==4)){
      UTIL_SetBoolInBools(&board->bools, INDEX_CCBQ, 0);
      queensideRights = 0;
    }

    if(kingsideRights){
      if(!BITBOARD_GetBit(&board->all_pieces, kingSquare+1)
      && !BITBOARD_GetBit(&board->all_pieces, kingSquare+2) 
      && !BOARD_IsCheck(board, kingSquare, isWhite) 
      && !BOARD_IsCheck(board, kingSquare+1, isWhite)
      && !BOARD_IsCheck(board, kingSquare+2, isWhite)){
        BOARD_AddMove(&board->pseudoMoves, kingSquare, kingSquare+2, 0);
      }
    }

    if(queensideRights){
      if(!BITBOARD_GetBit(&board->all_pieces, kingSquare-1)
      && !BITBOARD_GetBit(&board->all_pieces, kingSquare-2) 
      && !BITBOARD_GetBit(&board->all_pieces, kingSquare-3) 
      && !BOARD_IsCheck(board, kingSquare, isWhite) 
      && !BOARD_IsCheck(board, kingSquare-1, isWhite)
      && !BOARD_IsCheck(board, kingSquare-2, isWhite)
      && !BOARD_IsCheck(board, kingSquare-3, isWhite)){
        BOARD_AddMove(&board->pseudoMoves, kingSquare, kingSquare-2, 0);
      }
    }
  }
}

void BOARD_GeneratePseudoMoves(BOARD_BoardState* board)
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
  BOARD_GenerateCastlingMoves(board, isWhite);
}

void BOARD_FilterLegalMoves(BOARD_BoardState* board)
{
  board->legalMoves.count = 0;
  int8_t can=0, square=-1;
  uint8_t isWhite = UTIL_GetBoolFromBools(board->bools, INDEX_ON_TURN);
  int8_t kingSquare;
  BOARD_BoardState boardCopy;

  for(uint8_t i=0;i<board->pseudoMoves.count;i++){
    if(can && square==board->pseudoMoves.list[i].from){
      BOARD_AddMove(&board->legalMoves, board->pseudoMoves.list[i].from, board->pseudoMoves.list[i].to, board->pseudoMoves.list[i].promotion);
      continue;
    }
    else if(square!=board->pseudoMoves.list[i].from){
      BOARD_InitBoardStateCopy(board, &boardCopy);
      square = board->pseudoMoves.list[i].from;
      
      BITBOARD_Bitboard pieceMask=(BITBOARD_Bitboard){{0,0}}, removeMask;
      BITBOARD_LeftShift(&pieceMask, &(BITBOARD_Bitboard){{1,0}}, square);
      BITBOARD_Subtract(&removeMask, &(BITBOARD_Bitboard){{0xFFFFFFFF,0xFFFFFFFF}}, &pieceMask);

      if(isWhite){
        BITBOARD_BitwiseAND(&boardCopy.white_pieces, 1, &removeMask);
        BITBOARD_BitwiseAND(&boardCopy.white_pawns, 1, &removeMask);
        BITBOARD_BitwiseAND(&boardCopy.white_knights, 1, &removeMask);
        BITBOARD_BitwiseAND(&boardCopy.white_bishops, 1, &removeMask);
        BITBOARD_BitwiseAND(&boardCopy.white_rooks, 1, &removeMask);
        BITBOARD_BitwiseAND(&boardCopy.white_queens, 1, &removeMask);
        BITBOARD_BitwiseAND(&boardCopy.white_king, 1, &removeMask);
      }
      else{
        BITBOARD_BitwiseAND(&boardCopy.black_pieces, 1, &removeMask);
        BITBOARD_BitwiseAND(&boardCopy.black_pawns, 1, &removeMask);
        BITBOARD_BitwiseAND(&boardCopy.black_knights, 1, &removeMask);
        BITBOARD_BitwiseAND(&boardCopy.black_bishops, 1, &removeMask);
        BITBOARD_BitwiseAND(&boardCopy.black_rooks, 1, &removeMask);
        BITBOARD_BitwiseAND(&boardCopy.black_queens, 1, &removeMask);
        BITBOARD_BitwiseAND(&boardCopy.black_king, 1, &removeMask);
      }
      BITBOARD_BitwiseAND(&boardCopy.all_pieces, 1, &removeMask);
      
      kingSquare = isWhite?BITBOARD_CountTrailingZeros(&boardCopy.white_king):BITBOARD_CountTrailingZeros(&boardCopy.black_king);
      can = !BOARD_IsCheck(&boardCopy, kingSquare, isWhite); 
    }

    BOARD_InitBoardStateCopy(board, &boardCopy);
    BOARD_MakeMove(&boardCopy, &board->pseudoMoves.list[i], isWhite);

    kingSquare = isWhite?BITBOARD_CountTrailingZeros(&boardCopy.white_king):BITBOARD_CountTrailingZeros(&boardCopy.black_king);
    if(BOARD_IsCheck(&boardCopy, kingSquare, isWhite)==0){
      BOARD_AddMove(&board->legalMoves, board->pseudoMoves.list[i].from, board->pseudoMoves.list[i].to, board->pseudoMoves.list[i].promotion);
    }
  }
}


// ======================================= GAME FUNCTIONS ========================================


void BOARD_PlayTurn(BOARD_Board* board, int offx, int offy)
{
  uint8_t isWhite = UTIL_GetBoolFromBools(board->board.bools, INDEX_ON_TURN);
  
  int mx = GetMouseX();
  int my = GetMouseY();

  int px = (mx-offx)/TS;
  int py = (my-offy)/TS;
  int pos = -1;

  if(px>=0 && px<8 && py>=0 && py<8 && (mx-offx)>=0 && (my-offy)>=0){
    pos = py*8+px;
  }

  BOARD_BoardState boardCopy;

  if(IsMouseButtonPressed(0)){
    // printf("x%d y%d\n", px, py);
    
    if(pos>=0){
      if(board->selectedX>=0 && board->selectedY>=0){
        BOARD_InitBoardStateCopy(&board->board, &boardCopy);

        for(uint8_t i=0;i<board->board.legalMoves.count;i++){ 
          if(board->board.legalMoves.list[i].from==(board->selectedY*8+board->selectedX) && board->board.legalMoves.list[i].to==pos){
           
            BOARD_MakeMove(&board->board, &board->board.legalMoves.list[i], isWhite);
            BOARD_UndoMove(&board->board, &board->board.legalMoves.list[i], isWhite);

            if(((isWhite && BITBOARD_GetBit(&boardCopy.white_pawns, board->board.legalMoves.list[i].from)==1) || 
            (!isWhite && BITBOARD_GetBit(&boardCopy.black_pawns, board->board.legalMoves.list[i].from)==1)) &&
            (abs(board->board.legalMoves.list[i].to-board->board.legalMoves.list[i].from)==16)){
              board->board.enPassant = (board->board.legalMoves.list[i].to+board->board.legalMoves.list[i].from)/2;
            }
            else{
              board->board.enPassant = -1;
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
