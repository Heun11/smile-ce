#include "board.h"
#include "main.h"
#include "util.h"
#include <stdint.h>
#include <stdio.h>


uint64_t BOARD_attackMask_Knight[64] = {
  0x0000000000020400ULL, 0x0000000000050800ULL, 0x00000000000A1100ULL, 0x0000000000142200ULL,
  0x0000000000284400ULL, 0x0000000000508800ULL, 0x0000000000A01000ULL, 0x0000000000402000ULL,
  0x0000000002040004ULL, 0x0000000005080008ULL, 0x000000000A110011ULL, 0x0000000014220022ULL,
  0x0000000028440044ULL, 0x0000000050880088ULL, 0x00000000A0100010ULL, 0x0000000040200020ULL,
  0x0000000204000402ULL, 0x0000000508000805ULL, 0x0000000A1100110AULL, 0x0000001422002214ULL,
  0x0000002844004428ULL, 0x0000005088008850ULL, 0x000000A0100010A0ULL, 0x0000004020002040ULL,
  0x0000020400040200ULL, 0x0000050800080500ULL, 0x00000A1100110A00ULL, 0x0000142200221400ULL,
  0x0000284400442800ULL, 0x0000508800885000ULL, 0x0000A0100010A000ULL, 0x0000402000204000ULL,
  0x0002040004020000ULL, 0x0005080008050000ULL, 0x000A1100110A0000ULL, 0x0014220022140000ULL,
  0x0028440044280000ULL, 0x0050880088500000ULL, 0x00A0100010A00000ULL, 0x0040200020400000ULL,
  0x0204000402000000ULL, 0x0508000805000000ULL, 0x0A1100110A000000ULL, 0x1422002214000000ULL,
  0x2844004428000000ULL, 0x5088008850000000ULL, 0xA0100010A0000000ULL, 0x4020002040000000ULL,
  0x0400040200000000ULL, 0x0800080500000000ULL, 0x1100110A00000000ULL, 0x2200221400000000ULL,
  0x4400442800000000ULL, 0x8800885000000000ULL, 0x100010A000000000ULL, 0x2000204000000000ULL,
  0x0004020000000000ULL, 0x0008050000000000ULL, 0x00110A0000000000ULL, 0x0022140000000000ULL,
  0x0044280000000000ULL, 0x0088500000000000ULL, 0x0010A00000000000ULL, 0x0020400000000000ULL
};

uint64_t BOARD_attackMask_Rook[64] = {
  0x101010101017EULL, 0x202020202027CULL, 0x404040404047AULL, 0x8080808080876ULL,
  0x1010101010106EULL, 0x2020202020205EULL, 0x4040404040403EULL, 0x8080808080807EULL,
  0x1010101017E00ULL, 0x2020202027C00ULL, 0x4040404047A00ULL, 0x8080808087600ULL,
  0x10101010106E00ULL, 0x20202020205E00ULL, 0x40404040403E00ULL, 0x80808080807E00ULL,
  0x10101017E0100ULL, 0x20202027C0200ULL, 0x40404047A0400ULL, 0x8080808760800ULL,
  0x101010106E1000ULL, 0x202020205E2000ULL, 0x404040403E4000ULL, 0x808080807E8000ULL,
  0x101017E010100ULL, 0x202027C020200ULL, 0x404047A040400ULL, 0x8080876080800ULL,
  0x1010106E101000ULL, 0x2020205E202000ULL, 0x4040403E404000ULL, 0x8080807E808000ULL,
  0x1017E01010100ULL, 0x2027C02020200ULL, 0x4047A04040400ULL, 0x8087608080800ULL,
  0x10106E10101000ULL, 0x20205E20202000ULL, 0x40403E40404000ULL, 0x80807E80808000ULL,
  0x17E0101010100ULL, 0x27C0202020200ULL, 0x47A0404040400ULL, 0x8760808080800ULL,
  0x106E1010101000ULL, 0x205E2020202000ULL, 0x403E4040404000ULL, 0x807E8080808000ULL,
  0x7E010101010100ULL, 0x7C020202020200ULL, 0x7A040404040400ULL, 0x76080808080800ULL,
  0x6E101010101000ULL, 0x5E202020202000ULL, 0x3E404040404000ULL, 0x7E808080808000ULL
};

uint64_t BOARD_attackMask_Bishop[64] = {
  0x40201008040200ULL, 0x402010080400ULL, 0x4020100A00ULL, 0x40221400ULL,
  0x2442800ULL, 0x204085000ULL, 0x20408102000ULL, 0x2040810204000ULL,
  0x20100804020000ULL, 0x40201008040000ULL, 0x4020100A0000ULL, 0x4022140000ULL,
  0x244280000ULL, 0x20408500000ULL, 0x2040810200000ULL, 0x4081020400000ULL,
  0x10080402000200ULL, 0x20100804000400ULL, 0x4020100A000A00ULL, 0x402214001400ULL,
  0x24428002800ULL, 0x2040850005000ULL, 0x4081020002000ULL, 0x8102040004000ULL,
  0x8040200020400ULL, 0x10080400040800ULL, 0x20100A000A1000ULL, 0x40221400142200ULL,
  0x2442800284400ULL, 0x4085000500800ULL, 0x8102000201000ULL, 0x10204000402000ULL,
  0x4020002040800ULL, 0x8040004081000ULL, 0x100A000A102000ULL, 0x22140014224000ULL,
  0x44280028440200ULL, 0x8500050080400ULL, 0x10200020100800ULL, 0x20400040201000ULL,
  0x2000204081000ULL, 0x4000408102000ULL, 0xA000A10204000ULL, 0x14001422400000ULL,
  0x28002844020000ULL, 0x50005008040000ULL, 0x20002010080000ULL, 0x40004020100000ULL,
  0x20408102000ULL, 0x40810204000ULL, 0xA1020400000ULL, 0x142240000000ULL,
  0x284402000000ULL, 0x500804000000ULL, 0x201008000000ULL, 0x402010000000ULL,
  0x2040810204000ULL, 0x4081020400000ULL, 0xA102040000000ULL, 0x14224000000000ULL,
  0x28440200000000ULL, 0x50080400000000ULL, 0x20100800000000ULL, 0x40201000000000ULL
};

// ===================================== SETUP & RENDERING =====================================

void BOARD_PrintBitmaps(BOARD_Board* board)
{
  // P R N
  // B Q K
  
  printf("=========================ATTACK=MASKS===========================\n\n");
  printf("KNIGHT:                 ROOK:                   BISHOP:        \n");
 
  for(int8_t k=0;k<64;k++){

    for(int8_t i=0;i<8;i++){
      for(uint8_t j=0;j<8;j++){
        uint8_t index = i*8+j;
        printf("%c ", UTIL_GetBitFrom64(BOARD_attackMask_Knight[k], index)?'1':'-');
      }printf("\t");
      for(uint8_t j=0;j<8;j++){
        uint8_t index = i*8+j;
        printf("%c ", UTIL_GetBitFrom64(BOARD_attackMask_Rook[k], index)?'1':'-');
      }printf("\t");
      for(uint8_t j=0;j<8;j++){
        uint8_t index = i*8+j;
        printf("%c ", UTIL_GetBitFrom64(BOARD_attackMask_Bishop[k], index)?'1':'-');
      }
      printf("\n");
    }
    printf("\n");

  }

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
          (Rectangle){offx+TS*col, offy+TS*row, TS, TS*1.3125}, (Vector2){0,0}, 0, RAYWHITE);
      }
      else{
        // DrawRectangle(offx+col*TS, offy+row*TS, TS, TS, (Color){ 51, 107, 163, 255 });
        DrawTexturePro(tileset, (Rectangle){6*TILE_REAL_W, 1*TILE_REAL_H, TILE_REAL_W, TILE_REAL_H}, 
          (Rectangle){offx+TS*col, offy+TS*row, TS, TS*1.3125}, (Vector2){0,0}, 0, RAYWHITE);
      }

      pos = row*8+col;
      
      if((board->all_pieces>>pos)&1ULL){
        if((board->white_pawns>>pos)&1ULL){
          DrawTexturePro(tileset, (Rectangle){0*TILE_REAL_W, 0*TILE_REAL_H, TILE_REAL_W, TILE_REAL_H}, 
            (Rectangle){offx+TS*col, offy+TS*row-TS*0.3125, TS, TS*1.3125}, (Vector2){0,0}, 0, RAYWHITE);
          // DrawTexturePro(tileset, (Rectangle){0*TILE_REAL, 0*TILE_REAL, TILE_REAL, TILE_REAL}, 
          //   (Rectangle){offx+TS*col, offy+TS*row, TS, TS}, (Vector2){0,0}, 0, RAYWHITE);
        }
        if((board->white_rooks>>pos)&1ULL){
          DrawTexturePro(tileset, (Rectangle){1*TILE_REAL_W, 0*TILE_REAL_H, TILE_REAL_W, TILE_REAL_H}, 
            (Rectangle){offx+TS*col, offy+TS*row-TS*0.3125, TS, TS*1.3125}, (Vector2){0,0}, 0, RAYWHITE);
          // DrawTexturePro(tileset, (Rectangle){1*TILE_REAL, 0*TILE_REAL, TILE_REAL, TILE_REAL}, 
          //   (Rectangle){offx+TS*col, offy+TS*row, TS, TS}, (Vector2){0,0}, 0, RAYWHITE);
        }
        if((board->white_knights>>pos)&1ULL){
          DrawTexturePro(tileset, (Rectangle){2*TILE_REAL_W, 0*TILE_REAL_H, TILE_REAL_W, TILE_REAL_H}, 
            (Rectangle){offx+TS*col, offy+TS*row-TS*0.3125, TS, TS*1.3125}, (Vector2){0,0}, 0, RAYWHITE);
          // DrawTexturePro(tileset, (Rectangle){2*TILE_REAL, 0*TILE_REAL, TILE_REAL, TILE_REAL}, 
          //   (Rectangle){offx+TS*col, offy+TS*row, TS, TS}, (Vector2){0,0}, 0, RAYWHITE);
        }
        if((board->white_bishops>>pos)&1ULL){
          DrawTexturePro(tileset, (Rectangle){3*TILE_REAL_W, 0*TILE_REAL_H, TILE_REAL_W, TILE_REAL_H}, 
            (Rectangle){offx+TS*col, offy+TS*row-TS*0.3125, TS, TS*1.3125}, (Vector2){0,0}, 0, RAYWHITE);
          // DrawTexturePro(tileset, (Rectangle){3*TILE_REAL, 0*TILE_REAL, TILE_REAL, TILE_REAL}, 
          //   (Rectangle){offx+TS*col, offy+TS*row, TS, TS}, (Vector2){0,0}, 0, RAYWHITE);
        }
        if((board->white_queens>>pos)&1ULL){
          DrawTexturePro(tileset, (Rectangle){4*TILE_REAL_W, 0*TILE_REAL_H, TILE_REAL_W, TILE_REAL_H}, 
            (Rectangle){offx+TS*col, offy+TS*row-TS*0.3125, TS, TS*1.3125}, (Vector2){0,0}, 0, RAYWHITE);
          // DrawTexturePro(tileset, (Rectangle){4*TILE_REAL, 0*TILE_REAL, TILE_REAL, TILE_REAL}, 
          //   (Rectangle){offx+TS*col, offy+TS*row, TS, TS}, (Vector2){0,0}, 0, RAYWHITE);
        }
        if((board->white_king>>pos)&1ULL){
          DrawTexturePro(tileset, (Rectangle){5*TILE_REAL_W, 0*TILE_REAL_H, TILE_REAL_W, TILE_REAL_H}, 
            (Rectangle){offx+TS*col, offy+TS*row-TS*0.3125, TS, TS*1.3125}, (Vector2){0,0}, 0, RAYWHITE);
          // DrawTexturePro(tileset, (Rectangle){5*TILE_REAL, 0*TILE_REAL, TILE_REAL, TILE_REAL}, 
          //   (Rectangle){offx+TS*col, offy+TS*row, TS, TS}, (Vector2){0,0}, 0, RAYWHITE);
        }
        
        if((board->black_pawns>>pos)&1ULL){
          DrawTexturePro(tileset, (Rectangle){0*TILE_REAL_W, 1*TILE_REAL_H, TILE_REAL_W, TILE_REAL_H}, 
            (Rectangle){offx+TS*col, offy+TS*row-TS*0.3125, TS, TS*1.3125}, (Vector2){0,0}, 0, RAYWHITE);
          // DrawTexturePro(tileset, (Rectangle){0*TILE_REAL, 1*TILE_REAL, TILE_REAL, TILE_REAL}, 
          //   (Rectangle){offx+TS*col, offy+TS*row, TS, TS}, (Vector2){0,0}, 0, RAYWHITE);
        }
        if((board->black_rooks>>pos)&1ULL){
          DrawTexturePro(tileset, (Rectangle){1*TILE_REAL_W, 1*TILE_REAL_H, TILE_REAL_W, TILE_REAL_H}, 
            (Rectangle){offx+TS*col, offy+TS*row-TS*0.3125, TS, TS*1.3125}, (Vector2){0,0}, 0, RAYWHITE);
          // DrawTexturePro(tileset, (Rectangle){1*TILE_REAL, 1*TILE_REAL, TILE_REAL, TILE_REAL}, 
          //   (Rectangle){offx+TS*col, offy+TS*row, TS, TS}, (Vector2){0,0}, 0, RAYWHITE);
        }
        if((board->black_knights>>pos)&1ULL){
          DrawTexturePro(tileset, (Rectangle){2*TILE_REAL_W, 1*TILE_REAL_H, TILE_REAL_W, TILE_REAL_H}, 
            (Rectangle){offx+TS*col, offy+TS*row-TS*0.3125, TS, TS*1.3125}, (Vector2){0,0}, 0, RAYWHITE);
          // DrawTexturePro(tileset, (Rectangle){2*TILE_REAL, 1*TILE_REAL, TILE_REAL, TILE_REAL}, 
          //   (Rectangle){offx+TS*col, offy+TS*row, TS, TS}, (Vector2){0,0}, 0, RAYWHITE);
        }
        if((board->black_bishops>>pos)&1ULL){
          DrawTexturePro(tileset, (Rectangle){3*TILE_REAL_W, 1*TILE_REAL_H, TILE_REAL_W, TILE_REAL_H}, 
            (Rectangle){offx+TS*col, offy+TS*row-TS*0.3125, TS, TS*1.3125}, (Vector2){0,0}, 0, RAYWHITE);
          // DrawTexturePro(tileset, (Rectangle){3*TILE_REAL, 1*TILE_REAL, TILE_REAL, TILE_REAL}, 
          //   (Rectangle){offx+TS*col, offy+TS*row, TS, TS}, (Vector2){0,0}, 0, RAYWHITE);
        }
        if((board->black_queens>>pos)&1ULL){
          DrawTexturePro(tileset, (Rectangle){4*TILE_REAL_W, 1*TILE_REAL_H, TILE_REAL_W, TILE_REAL_H}, 
            (Rectangle){offx+TS*col, offy+TS*row-TS*0.3125, TS, TS*1.3125}, (Vector2){0,0}, 0, RAYWHITE);
          // DrawTexturePro(tileset, (Rectangle){4*TILE_REAL, 1*TILE_REAL, TILE_REAL, TILE_REAL}, 
          //   (Rectangle){offx+TS*col, offy+TS*row, TS, TS}, (Vector2){0,0}, 0, RAYWHITE);
        }
        if((board->black_king>>pos)&1ULL){
          DrawTexturePro(tileset, (Rectangle){5*TILE_REAL_W, 1*TILE_REAL_H, TILE_REAL_W, TILE_REAL_H}, 
            (Rectangle){offx+TS*col, offy+TS*row-TS*0.3125, TS, TS*1.3125}, (Vector2){0,0}, 0, RAYWHITE);
          // DrawTexturePro(tileset, (Rectangle){5*TILE_REAL, 1*TILE_REAL, TILE_REAL, TILE_REAL}, 
          //   (Rectangle){offx+TS*col, offy+TS*row, TS, TS}, (Vector2){0,0}, 0, RAYWHITE);
        }
      }
    }
  }
}

// ===================================== CHESS CALCULATIONS =====================================

