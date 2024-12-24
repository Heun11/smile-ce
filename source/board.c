#include "board.h"
#include "bitboard.h"
#include "main.h"
#include "util.h"
#include <stdint.h>
#include <stdio.h>
#include <ctype.h>
#include "bitboard_func.h"


// ===================================== SETUP & RENDERING =====================================

void BOARD_PrintBitmaps(BOARD_Board* board)
{
  // P R N
  // B Q K

  // uint64_t res = 0x00000000ffffffff << (64-9);
  // BITBOARD_Bitboard result;
  // 
  // BITBOARD_Multiply(&result, &(BITBOARD_Bitboard){{0, 0xffffffff}}, &(BITBOARD_Bitboard){{0x00000002, 0}});
  // BITBOARD_RightShift(&result, &(BITBOARD_Bitboard){{0, 0xffffffff}}, 64-9);
  // BITBOARD_LeftShift(&result, &(BITBOARD_Bitboard){{0xffffffff, 0}}, 64-9);
  //
  // printf("0x%016llX\n", res);
  // BITBOARD_Print(&result);


  printf("=========================WHITE=PIECES===========================\n\n");
  
  printf("PAWNS:                  ROOKS:                  KNIGHTS:        \n");
  for(int8_t i=0;i<8;i++){
    for(uint8_t j=0;j<8;j++){
      printf("%c ", BITBOARD_GetBit(&board->white_pawns, i*8+j)?'1':'-');
    }printf("\t");
    for(uint8_t j=0;j<8;j++){
      printf("%c ", BITBOARD_GetBit(&board->white_rooks, i*8+j)?'1':'-');
    }printf("\t");
    for(uint8_t j=0;j<8;j++){
      printf("%c ", BITBOARD_GetBit(&board->white_knights, i*8+j)?'1':'-');
    }
    printf("\n");
  }

  printf("BISHOPS:                QUEENS:                 KING:         \n");
  for(int8_t i=0;i<8;i++){
    for(uint8_t j=0;j<8;j++){
      printf("%c ", BITBOARD_GetBit(&board->white_bishops, i*8+j)?'1':'-');
    }printf("\t");
    for(uint8_t j=0;j<8;j++){
      printf("%c ", BITBOARD_GetBit(&board->white_queens, i*8+j)?'1':'-');
    }printf("\t");
    for(uint8_t j=0;j<8;j++){
      printf("%c ", BITBOARD_GetBit(&board->white_king, i*8+j)?'1':'-');
    }
    printf("\n");
  }

  printf("\n=========================BLACK=PIECES===========================\n\n");

  for(int8_t i=0;i<8;i++){
    for(uint8_t j=0;j<8;j++){
      printf("%c ", BITBOARD_GetBit(&board->black_pawns, i*8+j)?'1':'-');
    }printf("\t");
    for(uint8_t j=0;j<8;j++){
      printf("%c ", BITBOARD_GetBit(&board->black_rooks, i*8+j)?'1':'-');
    }printf("\t");
    for(uint8_t j=0;j<8;j++){
      printf("%c ", BITBOARD_GetBit(&board->black_knights, i*8+j)?'1':'-');
    }
    printf("\n");
  }

  printf("BISHOPS:                QUEENS:                 KING:         \n");
  for(int8_t i=0;i<8;i++){
    for(uint8_t j=0;j<8;j++){
      printf("%c ", BITBOARD_GetBit(&board->black_bishops, i*8+j)?'1':'-');
    }printf("\t");
    for(uint8_t j=0;j<8;j++){
      printf("%c ", BITBOARD_GetBit(&board->black_queens, i*8+j)?'1':'-');
    }printf("\t");
    for(uint8_t j=0;j<8;j++){
      printf("%c ", BITBOARD_GetBit(&board->black_king, i*8+j)?'1':'-');
    }
    printf("\n");
  }

  printf("\n===========================ALL=PIECES===========================\n\n");

  printf("WHITE:                  BLACK:                  ALL:        \n");
  for(int8_t i=0;i<8;i++){
    for(uint8_t j=0;j<8;j++){
      printf("%c ", BITBOARD_GetBit(&board->white_pieces, i*8+j)?'1':'-');
    }printf("\t");
    for(uint8_t j=0;j<8;j++){
      printf("%c ", BITBOARD_GetBit(&board->black_pieces, i*8+j)?'1':'-');
    }printf("\t");
    for(uint8_t j=0;j<8;j++){
      printf("%c ", BITBOARD_GetBit(&board->all_pieces, i*8+j)?'1':'-');
    }
    printf("\n");
  }
}

BOARD_Board BOARD_SetupBoard(char* fen)
{
  BOARD_Board board;
  board.bools = 1<<4;
  
  board.white_pawns=(BITBOARD_Bitboard){{0,0}}, board.white_rooks=(BITBOARD_Bitboard){{0,0}}, board.white_knights=(BITBOARD_Bitboard){{0,0}}, 
    board.white_bishops=(BITBOARD_Bitboard){{0,0}}, board.white_queens=(BITBOARD_Bitboard){{0,0}}, board.white_king=(BITBOARD_Bitboard){{0,0}};
  board.black_pawns=(BITBOARD_Bitboard){{0,0}}, board.black_rooks=(BITBOARD_Bitboard){{0,0}}, board.black_knights=(BITBOARD_Bitboard){{0,0}}, 
    board.black_bishops=(BITBOARD_Bitboard){{0,0}}, board.black_queens=(BITBOARD_Bitboard){{0,0}}, board.black_king=(BITBOARD_Bitboard){{0,0}};
  board.white_pieces=(BITBOARD_Bitboard){{0,0}}, board.black_pieces=(BITBOARD_Bitboard){{0,0}}, board.all_pieces=(BITBOARD_Bitboard){{0,0}};

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
          case 'P': BITBOARD_SetBitToH(&board.white_pawns, index); break;
          case 'R': BITBOARD_SetBitToH(&board.white_rooks, index); break;
          case 'N': BITBOARD_SetBitToH(&board.white_knights, index); break;
          case 'B': BITBOARD_SetBitToH(&board.white_bishops, index); break;
          case 'Q': BITBOARD_SetBitToH(&board.white_queens, index); break;
          case 'K': BITBOARD_SetBitToH(&board.white_king, index); break;
          
          case 'p': BITBOARD_SetBitToH(&board.black_pawns, index); break;
          case 'r': BITBOARD_SetBitToH(&board.black_rooks, index); break;
          case 'n': BITBOARD_SetBitToH(&board.black_knights, index); break;
          case 'b': BITBOARD_SetBitToH(&board.black_bishops, index); break;
          case 'q': BITBOARD_SetBitToH(&board.black_queens, index); break;
          case 'k': BITBOARD_SetBitToH(&board.black_king, index); break;
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
  
  BITBOARD_BitwiseOR(&board.white_pieces, 6, &board.white_pawns, &board.white_rooks, 
    &board.white_knights, &board.white_bishops, &board.white_queens, &board.white_king);
  BITBOARD_BitwiseOR(&board.black_pieces, 6, &board.black_pawns, &board.black_rooks, 
    &board.black_knights, &board.black_bishops, &board.black_queens, &board.black_king);
  BITBOARD_BitwiseOR(&board.all_pieces, 2, &board.white_pieces, &board.black_pieces);

  // printing board
  printf("Show Boards:\n\n");
  BOARD_PrintBitmaps(&board);

  return board;
}

void BOARD_DrawBoard(BOARD_Board* board, int offx, int offy)
{
  uint8_t row, col;
  uint8_t pos;

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

      if(BITBOARD_GetBit(&board->all_pieces, pos)){
        if(BITBOARD_GetBit(&board->white_pawns, pos)){
          DrawTexturePro(tileset, (Rectangle){0*TILE_REAL_W, 0*TILE_REAL_H, TILE_REAL_W, TILE_REAL_H}, 
            (Rectangle){offx+TS*col, offy+TS*row-TS*0.623, TS, TS*1.3125}, (Vector2){0,0}, 0, RAYWHITE);
          // DrawTexturePro(tileset, (Rectangle){0*TILE_REAL, 0*TILE_REAL, TILE_REAL, TILE_REAL}, 
          //   (Rectangle){offx+TS*col, offy+TS*row, TS, TS}, (Vector2){0,0}, 0, RAYWHITE);
        }
        if(BITBOARD_GetBit(&board->white_rooks, pos)){
          DrawTexturePro(tileset, (Rectangle){1*TILE_REAL_W, 0*TILE_REAL_H, TILE_REAL_W, TILE_REAL_H}, 
            (Rectangle){offx+TS*col, offy+TS*row-TS*0.623, TS, TS*1.3125}, (Vector2){0,0}, 0, RAYWHITE);
          // DrawTexturePro(tileset, (Rectangle){1*TILE_REAL, 0*TILE_REAL, TILE_REAL, TILE_REAL}, 
          //   (Rectangle){offx+TS*col, offy+TS*row, TS, TS}, (Vector2){0,0}, 0, RAYWHITE);
        }
        if(BITBOARD_GetBit(&board->white_knights, pos)){
          DrawTexturePro(tileset, (Rectangle){2*TILE_REAL_W, 0*TILE_REAL_H, TILE_REAL_W, TILE_REAL_H}, 
            (Rectangle){offx+TS*col, offy+TS*row-TS*0.623, TS, TS*1.3125}, (Vector2){0,0}, 0, RAYWHITE);
          // DrawTexturePro(tileset, (Rectangle){2*TILE_REAL, 0*TILE_REAL, TILE_REAL, TILE_REAL}, 
          //   (Rectangle){offx+TS*col, offy+TS*row, TS, TS}, (Vector2){0,0}, 0, RAYWHITE);
        }
        if(BITBOARD_GetBit(&board->white_bishops, pos)){
          DrawTexturePro(tileset, (Rectangle){3*TILE_REAL_W, 0*TILE_REAL_H, TILE_REAL_W, TILE_REAL_H}, 
            (Rectangle){offx+TS*col, offy+TS*row-TS*0.623, TS, TS*1.3125}, (Vector2){0,0}, 0, RAYWHITE);
          // DrawTexturePro(tileset, (Rectangle){3*TILE_REAL, 0*TILE_REAL, TILE_REAL, TILE_REAL}, 
          //   (Rectangle){offx+TS*col, offy+TS*row, TS, TS}, (Vector2){0,0}, 0, RAYWHITE);
        }
        if(BITBOARD_GetBit(&board->white_queens, pos)){
          DrawTexturePro(tileset, (Rectangle){4*TILE_REAL_W, 0*TILE_REAL_H, TILE_REAL_W, TILE_REAL_H}, 
            (Rectangle){offx+TS*col, offy+TS*row-TS*0.623, TS, TS*1.3125}, (Vector2){0,0}, 0, RAYWHITE);
          // DrawTexturePro(tileset, (Rectangle){4*TILE_REAL, 0*TILE_REAL, TILE_REAL, TILE_REAL}, 
          //   (Rectangle){offx+TS*col, offy+TS*row, TS, TS}, (Vector2){0,0}, 0, RAYWHITE);
        }
        if(BITBOARD_GetBit(&board->white_king, pos)){
          DrawTexturePro(tileset, (Rectangle){5*TILE_REAL_W, 0*TILE_REAL_H, TILE_REAL_W, TILE_REAL_H}, 
            (Rectangle){offx+TS*col, offy+TS*row-TS*0.623, TS, TS*1.3125}, (Vector2){0,0}, 0, RAYWHITE);
          // DrawTexturePro(tileset, (Rectangle){5*TILE_REAL, 0*TILE_REAL, TILE_REAL, TILE_REAL}, 
          //   (Rectangle){offx+TS*col, offy+TS*row, TS, TS}, (Vector2){0,0}, 0, RAYWHITE);
        }
        
        if(BITBOARD_GetBit(&board->black_pawns, pos)){
          DrawTexturePro(tileset, (Rectangle){0*TILE_REAL_W, 1*TILE_REAL_H, TILE_REAL_W, TILE_REAL_H}, 
            (Rectangle){offx+TS*col, offy+TS*row-TS*0.623, TS, TS*1.3125}, (Vector2){0,0}, 0, RAYWHITE);
          // DrawTexturePro(tileset, (Rectangle){0*TILE_REAL, 1*TILE_REAL, TILE_REAL, TILE_REAL}, 
          //   (Rectangle){offx+TS*col, offy+TS*row, TS, TS}, (Vector2){0,0}, 0, RAYWHITE);
        }
        if(BITBOARD_GetBit(&board->black_rooks, pos)){
          DrawTexturePro(tileset, (Rectangle){1*TILE_REAL_W, 1*TILE_REAL_H, TILE_REAL_W, TILE_REAL_H}, 
            (Rectangle){offx+TS*col, offy+TS*row-TS*0.623, TS, TS*1.3125}, (Vector2){0,0}, 0, RAYWHITE);
          // DrawTexturePro(tileset, (Rectangle){1*TILE_REAL, 1*TILE_REAL, TILE_REAL, TILE_REAL}, 
          //   (Rectangle){offx+TS*col, offy+TS*row, TS, TS}, (Vector2){0,0}, 0, RAYWHITE);
        }
        if(BITBOARD_GetBit(&board->black_knights, pos)){
          DrawTexturePro(tileset, (Rectangle){2*TILE_REAL_W, 1*TILE_REAL_H, TILE_REAL_W, TILE_REAL_H}, 
            (Rectangle){offx+TS*col, offy+TS*row-TS*0.623, TS, TS*1.3125}, (Vector2){0,0}, 0, RAYWHITE);
          // DrawTexturePro(tileset, (Rectangle){2*TILE_REAL, 1*TILE_REAL, TILE_REAL, TILE_REAL}, 
          //   (Rectangle){offx+TS*col, offy+TS*row, TS, TS}, (Vector2){0,0}, 0, RAYWHITE);
        }
        if(BITBOARD_GetBit(&board->black_bishops, pos)){
          DrawTexturePro(tileset, (Rectangle){3*TILE_REAL_W, 1*TILE_REAL_H, TILE_REAL_W, TILE_REAL_H}, 
            (Rectangle){offx+TS*col, offy+TS*row-TS*0.623, TS, TS*1.3125}, (Vector2){0,0}, 0, RAYWHITE);
          // DrawTexturePro(tileset, (Rectangle){3*TILE_REAL, 1*TILE_REAL, TILE_REAL, TILE_REAL}, 
          //   (Rectangle){offx+TS*col, offy+TS*row, TS, TS}, (Vector2){0,0}, 0, RAYWHITE);
        }
        if(BITBOARD_GetBit(&board->black_queens, pos)){
          DrawTexturePro(tileset, (Rectangle){4*TILE_REAL_W, 1*TILE_REAL_H, TILE_REAL_W, TILE_REAL_H}, 
            (Rectangle){offx+TS*col, offy+TS*row-TS*0.623, TS, TS*1.3125}, (Vector2){0,0}, 0, RAYWHITE);
          // DrawTexturePro(tileset, (Rectangle){4*TILE_REAL, 1*TILE_REAL, TILE_REAL, TILE_REAL}, 
          //   (Rectangle){offx+TS*col, offy+TS*row, TS, TS}, (Vector2){0,0}, 0, RAYWHITE);
        }
        if(BITBOARD_GetBit(&board->black_king, pos)){
          DrawTexturePro(tileset, (Rectangle){5*TILE_REAL_W, 1*TILE_REAL_H, TILE_REAL_W, TILE_REAL_H}, 
            (Rectangle){offx+TS*col, offy+TS*row-TS*0.623, TS, TS*1.3125}, (Vector2){0,0}, 0, RAYWHITE);
          // DrawTexturePro(tileset, (Rectangle){5*TILE_REAL, 1*TILE_REAL, TILE_REAL, TILE_REAL}, 
          //   (Rectangle){offx+TS*col, offy+TS*row, TS, TS}, (Vector2){0,0}, 0, RAYWHITE);
        }
      }
    }
  }
}


// ===================================== CHESS CALCULATIONS =====================================


uint8_t BOARD_IsCheck(BOARD_Board* board, uint8_t isWhite)
{
  BITBOARD_Bitboard temp, temp1;
  int8_t kingSquare;

  if(isWhite){
    // white is on turn
    kingSquare = BITBOARD_CountTrailingZeros(&board->white_king);

    // pawn 
    BITBOARD_SetBitboardToBitboard(&temp, &BITBOARD_AttackMasks_pawn[1][kingSquare]);
    BITBOARD_BitwiseAND(&temp, 1, &board->black_pawns);
    // BITBOARD_Print(&temp);
    if(BITBOARD_IsBitboardTrue(temp)) return 1;

    // knight 
    BITBOARD_SetBitboardToBitboard(&temp, &BITBOARD_Masks_knight[kingSquare]);
    BITBOARD_BitwiseAND(&temp, 1, &board->black_knights);
    // BITBOARD_Print(&temp);
    if(BITBOARD_IsBitboardTrue(temp)) return 1;

    // diagonal (queen & bishop)
    BITBOARD_GetAttackMask_bishop(&temp1, kingSquare, &board->all_pieces);
    BITBOARD_BitwiseOR(&temp, 2, &board->black_bishops, &board->black_queens);
    BITBOARD_BitwiseAND(&temp, 1, &temp1);
    if(BITBOARD_IsBitboardTrue(temp)) return 1;

    // straight lines (queen & rook)
    BITBOARD_GetAttackMask_rook(&temp1, kingSquare, &board->all_pieces);
    BITBOARD_BitwiseOR(&temp, 2, &board->black_rooks, &board->black_queens);
    BITBOARD_BitwiseAND(&temp, 1, &temp1);
    if(BITBOARD_IsBitboardTrue(temp)) return 1;

    // king 
    BITBOARD_SetBitboardToBitboard(&temp, &BITBOARD_Masks_king[kingSquare]);
    BITBOARD_BitwiseAND(&temp, 1, &board->black_king);
    // BITBOARD_Print(&temp);
    if(BITBOARD_IsBitboardTrue(temp)) return 1;

  }
  else{ 
    // black is on turn
    kingSquare = BITBOARD_CountTrailingZeros(&board->black_king);
    
    // pawn 
    BITBOARD_SetBitboardToBitboard(&temp, &BITBOARD_AttackMasks_pawn[1][kingSquare]);
    BITBOARD_BitwiseAND(&temp, 1, &board->white_pawns);
    // BITBOARD_Print(&temp);
    if(BITBOARD_IsBitboardTrue(temp)) return 1;

    // knight 
    BITBOARD_SetBitboardToBitboard(&temp, &BITBOARD_Masks_knight[kingSquare]);
    BITBOARD_BitwiseAND(&temp, 1, &board->white_knights);
    // BITBOARD_Print(&temp);
    if(BITBOARD_IsBitboardTrue(temp)) return 1;

    // diagonal (queen & bishop)
    BITBOARD_GetAttackMask_bishop(&temp1, kingSquare, &board->all_pieces);
    BITBOARD_BitwiseOR(&temp, 2, &board->white_bishops, &board->white_queens);
    BITBOARD_BitwiseAND(&temp, 1, &temp1);
    if(BITBOARD_IsBitboardTrue(temp)) return 1;

    // straight lines (queen & rook)
    BITBOARD_GetAttackMask_rook(&temp1, kingSquare, &board->all_pieces);
    BITBOARD_BitwiseOR(&temp, 2, &board->white_rooks, &board->white_queens);
    BITBOARD_BitwiseAND(&temp, 1, &temp1);
    if(BITBOARD_IsBitboardTrue(temp)) return 1;

    // king 
    BITBOARD_SetBitboardToBitboard(&temp, &BITBOARD_Masks_king[kingSquare]);
    BITBOARD_BitwiseAND(&temp, 1, &board->white_king);
    // BITBOARD_Print(&temp);
    if(BITBOARD_IsBitboardTrue(temp)) return 1; 
  }
  return 0;
}


