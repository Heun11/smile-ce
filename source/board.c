#include "board.h"
#include "main.h"
#include "util.h"
#include <stdint.h>
#include <stdio.h>

void BOARD_PrintBitmaps(BOARD_Board* board)
{
  // P R N
  // B Q K

  // printf("%ld %ld %ld %ld %ld %ld \n", 
  //   board->white_pawns, board->white_rooks, board->white_knights, board->white_bishops, board->white_queens, board->white_king);

  printf("=========================WHITE=PIECES===========================\n\n");
  
  printf("PAWNS:                  ROOKS:                  KNIGHTS:        \n");
  for(int8_t i=0;i<8;i++){
    for(uint8_t j=0;j<8;j++){
      uint8_t index = i*8+j;
      printf("%c ", UTIL_GetBitFrom64(board->white_pawns, index)?'1':'-');
    }printf("\t");
    for(uint8_t j=0;j<8;j++){
      uint8_t index = i*8+j;
      printf("%c ", UTIL_GetBitFrom64(board->white_rooks, index)?'1':'-');
    }printf("\t");
    for(uint8_t j=0;j<8;j++){
      uint8_t index = i*8+j;
      printf("%c ", UTIL_GetBitFrom64(board->white_knights, index)?'1':'-');
    }
    printf("\n");
  }

  printf("BISHOPS:                QUEENS:                 KING:         \n");
  for(int8_t i=0;i<8;i++){
    for(uint8_t j=0;j<8;j++){
      printf("%c ", UTIL_GetBitFrom64(board->white_bishops, i*8+j)?'1':'-');
    }printf("\t");
    for(uint8_t j=0;j<8;j++){
      printf("%c ", UTIL_GetBitFrom64(board->white_queens, i*8+j)?'1':'-');
    }printf("\t");
    for(uint8_t j=0;j<8;j++){
      printf("%c ", UTIL_GetBitFrom64(board->white_king, i*8+j)?'1':'-');
    }
    printf("\n");
  }

  printf("\n=========================BLACK=PIECES===========================\n\n");

  printf("PAWNS:                  ROOKS:                  KNIGHTS:        \n");
  for(int8_t i=0;i<8;i++){
    for(uint8_t j=0;j<8;j++){
      uint8_t index = i*8+j;
      printf("%c ", UTIL_GetBitFrom64(board->black_pawns, index)?'1':'-');
    }printf("\t");
    for(uint8_t j=0;j<8;j++){
      printf("%c ", UTIL_GetBitFrom64(board->black_rooks, i*8+j)?'1':'-');
    }printf("\t");
    for(uint8_t j=0;j<8;j++){
      printf("%c ", UTIL_GetBitFrom64(board->black_knights, i*8+j)?'1':'-');
    }
    printf("\n");
  }

  printf("BISHOPS:                QUEENS:                 KING:         \n");
  for(int8_t i=0;i<8;i++){
    for(uint8_t j=0;j<8;j++){
      printf("%c ", UTIL_GetBitFrom64(board->black_bishops, i*8+j)?'1':'-');
    }printf("\t");
    for(uint8_t j=0;j<8;j++){
      printf("%c ", UTIL_GetBitFrom64(board->black_queens, i*8+j)?'1':'-');
    }printf("\t");
    for(uint8_t j=0;j<8;j++){
      printf("%c ", UTIL_GetBitFrom64(board->black_king, i*8+j)?'1':'-');
    }
    printf("\n");
  }

  printf("\n===========================ALL=PIECES===========================\n\n");

  printf("WHITE:                  BLACK:                  ALL:        \n");
  for(int8_t i=0;i<8;i++){
    for(uint8_t j=0;j<8;j++){
      uint8_t index = i*8+j;
      printf("%c ", UTIL_GetBitFrom64(board->white_pieces, index)?'1':'-');
    }printf("\t");
    for(uint8_t j=0;j<8;j++){
      printf("%c ", UTIL_GetBitFrom64(board->black_pieces, i*8+j)?'1':'-');
    }printf("\t");
    for(uint8_t j=0;j<8;j++){
      printf("%c ", UTIL_GetBitFrom64(board->all_pieces, i*8+j)?'1':'-');
    }
    printf("\n");
  }
}

BOARD_Board BOARD_SetupBoard(char* fen)
{
  BOARD_Board board;
  board.bools = 1<<4;
  
  board.white_pawns=0, board.white_rooks=0, board.white_knights=0, 
    board.white_bishops=0, board.white_queens=0, board.white_king=0;
  board.black_pawns=0, board.black_rooks=0, board.black_knights=0, 
    board.black_bishops=0, board.black_queens=0, board.black_king=0;
  board.white_pieces=0, board.black_pieces=0, board.all_pieces=0;


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
          case 'P': UTIL_SetBitIn64ToH(&board.white_pawns, index); break;
          case 'R': UTIL_SetBitIn64ToH(&board.white_rooks, index); break;
          case 'N': UTIL_SetBitIn64ToH(&board.white_knights, index); break;
          case 'B': UTIL_SetBitIn64ToH(&board.white_bishops, index); break;
          case 'Q': UTIL_SetBitIn64ToH(&board.white_queens, index); break;
          case 'K': UTIL_SetBitIn64ToH(&board.white_king, index); break;
          
          case 'p': UTIL_SetBitIn64ToH(&board.black_pawns, index); break;
          case 'r': UTIL_SetBitIn64ToH(&board.black_rooks, index); break;
          case 'n': UTIL_SetBitIn64ToH(&board.black_knights, index); break;
          case 'b': UTIL_SetBitIn64ToH(&board.black_bishops, index); break;
          case 'q': UTIL_SetBitIn64ToH(&board.black_queens, index); break;
          case 'k': UTIL_SetBitIn64ToH(&board.black_king, index); break;
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

  board.white_pieces = board.white_pawns | board.white_rooks | board.white_knights | 
    board.white_bishops | board.white_queens | board.white_king;
  board.black_pieces = board.black_pawns | board.black_rooks | board.black_knights | 
    board.black_bishops | board.black_queens | board.black_king;
  board.all_pieces = board.white_pieces | board.black_pieces;

  // printing board
  printf("Show Boards:\n\n");
  BOARD_PrintBitmaps(&board);

  return board;
}

void BOARD_DrawBoard(BOARD_Board* board, int offx, int offy)
{
  uint8_t row, col;
  uint64_t pos;

  for(row=0;row<8;row++){
    for(col=0;col<8;col++){

      if((row+col)%2==0){
        // DrawRectangle(offx+col*TS, offy+row*TS, TS, TS, (Color){ 247, 243, 220, 255 });
        DrawTexturePro(tileset, (Rectangle){6*TILE_REAL_W, 0*TILE_REAL_H, TILE_REAL_W, TILE_REAL_H}, 
          (Rectangle){offx+TS*col, offy+TS*row, TS, TS*1.5}, (Vector2){0,0}, 0, RAYWHITE);
      }
      else{
        // DrawRectangle(offx+col*TS, offy+row*TS, TS, TS, (Color){ 51, 107, 163, 255 });
        DrawTexturePro(tileset, (Rectangle){6*TILE_REAL_W, 1*TILE_REAL_H, TILE_REAL_W, TILE_REAL_H}, 
          (Rectangle){offx+TS*col, offy+TS*row, TS, TS*1.5}, (Vector2){0,0}, 0, RAYWHITE);
      }

      pos = row*8+col;
      
      if((board->all_pieces>>pos)&1ULL){
        if((board->white_pawns>>pos)&1ULL){
          DrawTexturePro(tileset, (Rectangle){0*TILE_REAL_W, 0*TILE_REAL_H, TILE_REAL_W, TILE_REAL_H}, 
            (Rectangle){offx+TS*col, offy+TS*row-TS*0.5, TS, TS*1.5}, (Vector2){0,0}, 0, RAYWHITE);
        }
        if((board->white_rooks>>pos)&1ULL){
          DrawTexturePro(tileset, (Rectangle){1*TILE_REAL_W, 0*TILE_REAL_H, TILE_REAL_W, TILE_REAL_H}, 
            (Rectangle){offx+TS*col, offy+TS*row-TS*0.5, TS, TS*1.5}, (Vector2){0,0}, 0, RAYWHITE);
        }
        if((board->white_knights>>pos)&1ULL){
          DrawTexturePro(tileset, (Rectangle){2*TILE_REAL_W, 0*TILE_REAL_H, TILE_REAL_W, TILE_REAL_H}, 
            (Rectangle){offx+TS*col, offy+TS*row-TS*0.5, TS, TS*1.5}, (Vector2){0,0}, 0, RAYWHITE);
        }
        if((board->white_bishops>>pos)&1ULL){
          DrawTexturePro(tileset, (Rectangle){3*TILE_REAL_W, 0*TILE_REAL_H, TILE_REAL_W, TILE_REAL_H}, 
            (Rectangle){offx+TS*col, offy+TS*row-TS*0.5, TS, TS*1.5}, (Vector2){0,0}, 0, RAYWHITE);
        }
        if((board->white_queens>>pos)&1ULL){
          DrawTexturePro(tileset, (Rectangle){4*TILE_REAL_W, 0*TILE_REAL_H, TILE_REAL_W, TILE_REAL_H}, 
            (Rectangle){offx+TS*col, offy+TS*row-TS*0.5, TS, TS*1.5}, (Vector2){0,0}, 0, RAYWHITE);
        }
        if((board->white_king>>pos)&1ULL){
          DrawTexturePro(tileset, (Rectangle){5*TILE_REAL_W, 0*TILE_REAL_H, TILE_REAL_W, TILE_REAL_H}, 
            (Rectangle){offx+TS*col, offy+TS*row-TS*0.5, TS, TS*1.5}, (Vector2){0,0}, 0, RAYWHITE);
        }
        
        if((board->black_pawns>>pos)&1ULL){
          DrawTexturePro(tileset, (Rectangle){0*TILE_REAL_W, 1*TILE_REAL_H, TILE_REAL_W, TILE_REAL_H}, 
            (Rectangle){offx+TS*col, offy+TS*row-TS*0.5, TS, TS*1.5}, (Vector2){0,0}, 0, RAYWHITE);
        }
        if((board->black_rooks>>pos)&1ULL){
          DrawTexturePro(tileset, (Rectangle){1*TILE_REAL_W, 1*TILE_REAL_H, TILE_REAL_W, TILE_REAL_H}, 
            (Rectangle){offx+TS*col, offy+TS*row-TS*0.5, TS, TS*1.5}, (Vector2){0,0}, 0, RAYWHITE);
        }
        if((board->black_knights>>pos)&1ULL){
          DrawTexturePro(tileset, (Rectangle){2*TILE_REAL_W, 1*TILE_REAL_H, TILE_REAL_W, TILE_REAL_H}, 
            (Rectangle){offx+TS*col, offy+TS*row-TS*0.5, TS, TS*1.5}, (Vector2){0,0}, 0, RAYWHITE);
        }
        if((board->black_bishops>>pos)&1ULL){
          DrawTexturePro(tileset, (Rectangle){3*TILE_REAL_W, 1*TILE_REAL_H, TILE_REAL_W, TILE_REAL_H}, 
            (Rectangle){offx+TS*col, offy+TS*row-TS*0.5, TS, TS*1.5}, (Vector2){0,0}, 0, RAYWHITE);
        }
        if((board->black_queens>>pos)&1ULL){
          DrawTexturePro(tileset, (Rectangle){4*TILE_REAL_W, 1*TILE_REAL_H, TILE_REAL_W, TILE_REAL_H}, 
            (Rectangle){offx+TS*col, offy+TS*row-TS*0.5, TS, TS*1.5}, (Vector2){0,0}, 0, RAYWHITE);
        }
        if((board->black_king>>pos)&1ULL){
          DrawTexturePro(tileset, (Rectangle){5*TILE_REAL_W, 1*TILE_REAL_H, TILE_REAL_W, TILE_REAL_H}, 
            (Rectangle){offx+TS*col, offy+TS*row-TS*0.5, TS, TS*1.5}, (Vector2){0,0}, 0, RAYWHITE);
        }
      }
      
      
    }
  }
}
