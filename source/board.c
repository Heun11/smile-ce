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
      DrawText(TextFormat("%d", pos), offx+TS*col, offy+TS*row, TS*0.2, WHITE);

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
    if(BITBOARD_IsBitboardTrue(&temp)) return 1;

    // knight 
    BITBOARD_SetBitboardToBitboard(&temp, &BITBOARD_Masks_knight[kingSquare]);
    BITBOARD_BitwiseAND(&temp, 1, &board->black_knights);
    // BITBOARD_Print(&temp);
    if(BITBOARD_IsBitboardTrue(&temp)) return 1;

    // diagonal (queen & bishop)
    BITBOARD_GetAttackMask_bishop(&temp1, kingSquare, &board->all_pieces);
    BITBOARD_BitwiseOR(&temp, 2, &board->black_bishops, &board->black_queens);
    BITBOARD_BitwiseAND(&temp, 1, &temp1);
    // BITBOARD_Print(&temp);
    if(BITBOARD_IsBitboardTrue(&temp)) return 1;

    // straight lines (queen & rook)
    BITBOARD_GetAttackMask_rook(&temp1, kingSquare, &board->all_pieces);
    BITBOARD_BitwiseOR(&temp, 2, &board->black_rooks, &board->black_queens);
    BITBOARD_BitwiseAND(&temp, 1, &temp1);
    // BITBOARD_Print(&temp);
    if(BITBOARD_IsBitboardTrue(&temp)) return 1;

    // king 
    BITBOARD_SetBitboardToBitboard(&temp, &BITBOARD_Masks_king[kingSquare]);
    BITBOARD_BitwiseAND(&temp, 1, &board->black_king);
    // BITBOARD_Print(&temp);
    if(BITBOARD_IsBitboardTrue(&temp)) return 1;

  }
  else{ 
    // black is on turn
    kingSquare = BITBOARD_CountTrailingZeros(&board->black_king);
    
    // pawn 
    BITBOARD_SetBitboardToBitboard(&temp, &BITBOARD_AttackMasks_pawn[1][kingSquare]);
    BITBOARD_BitwiseAND(&temp, 1, &board->white_pawns);
    // BITBOARD_Print(&temp);
    if(BITBOARD_IsBitboardTrue(&temp)) return 1;

    // knight 
    BITBOARD_SetBitboardToBitboard(&temp, &BITBOARD_Masks_knight[kingSquare]);
    BITBOARD_BitwiseAND(&temp, 1, &board->white_knights);
    // BITBOARD_Print(&temp);
    if(BITBOARD_IsBitboardTrue(&temp)) return 1;

    // diagonal (queen & bishop)
    BITBOARD_GetAttackMask_bishop(&temp1, kingSquare, &board->all_pieces);
    BITBOARD_BitwiseOR(&temp, 2, &board->white_bishops, &board->white_queens);
    BITBOARD_BitwiseAND(&temp, 1, &temp1);
    if(BITBOARD_IsBitboardTrue(&temp)) return 1;

    // straight lines (queen & rook)
    BITBOARD_GetAttackMask_rook(&temp1, kingSquare, &board->all_pieces);
    BITBOARD_BitwiseOR(&temp, 2, &board->white_rooks, &board->white_queens);
    BITBOARD_BitwiseAND(&temp, 1, &temp1);
    if(BITBOARD_IsBitboardTrue(&temp)) return 1;

    // king 
    BITBOARD_SetBitboardToBitboard(&temp, &BITBOARD_Masks_king[kingSquare]);
    BITBOARD_BitwiseAND(&temp, 1, &board->white_king);
    // BITBOARD_Print(&temp);
    if(BITBOARD_IsBitboardTrue(&temp)) return 1; 
  }
  return 0;
}

void BOARD_AddMove(BOARD_MoveList* moves, int8_t from, int8_t to)
{
  moves->list[moves->count].from = from;
  moves->list[moves->count].to = to;
  moves->list[moves->count].promotion = 0;
  moves->count++;
}

void BOARD_PrintMoves(BOARD_MoveList* moves)
{
  int8_t prev = -1;
  printf("all possible moves (%d):\n", moves->count);
  for(uint8_t i=0;i<moves->count;i++){
    if(prev!=moves->list[i].from){ 
      prev=moves->list[i].from;
      printf("\n");
    }
    printf("move %03d = %02d -> %02d (%d)\n", i, moves->list[i].from, moves->list[i].to, moves->list[i].promotion);
  }
  printf("\n");
}

void BOARD_GeneratePseudoMoves_Pawn(BOARD_Board* board, uint8_t isWhite)
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
      BOARD_AddMove(&board->pseudoMoves, square, BITBOARD_CountTrailingZeros(&push));

      BITBOARD_SetBitboardToBitboard(&temp, &push);
      if(isWhite){
        BITBOARD_RightShift(&push, &temp, 8);
      }else{
        BITBOARD_LeftShift(&push, &temp, 8);
      }

      BITBOARD_SetBitboardToBitboard(&temp, &(BITBOARD_Bitboard){{0xFFFFFFFF,0xFFFFFFFF}});
      BITBOARD_BitwiseAND(&temp, 2, &push, &emptySquares);
      if((square/8==(isWhite?6:1)) && BITBOARD_IsBitboardTrue(&temp)){
        BOARD_AddMove(&board->pseudoMoves, square, BITBOARD_CountTrailingZeros(&push));
      } 
    }

    BITBOARD_SetBitboardToBitboard(&push, &(BITBOARD_Bitboard){{0xFFFFFFFF,0xFFFFFFFF}});
    BITBOARD_BitwiseAND(&push, 2, &BITBOARD_AttackMasks_pawn[isWhite?1:0][square], (isWhite)?(&board->black_pieces):(&board->white_pieces));
    while(BITBOARD_IsBitboardTrue(&push)){
      attackSquare = BITBOARD_CountTrailingZeros(&push);
      BITBOARD_SetBitboardToBitboard(&temp, &push);
      BITBOARD_Subtract(&temp, &temp, &(BITBOARD_Bitboard){{1,0}});
      BITBOARD_BitwiseAND(&push, 1, &temp);

      BOARD_AddMove(&board->pseudoMoves, square, attackSquare);
    }
  }
}

void BOARD_GeneratePseudoMoves_Knight(BOARD_Board* board, uint8_t isWhite)
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
    BITBOARD_BitwiseOR(&temp, 2, &emptySquares, isWhite?(&board->black_knights):(&board->white_knights));
    BITBOARD_SetBitboardToBitboard(&movesMask, &(BITBOARD_Bitboard){{0xFFFFFFFF,0xFFFFFFFF}});
    BITBOARD_BitwiseAND(&movesMask, 2, &temp, &BITBOARD_Masks_knight[square]);
    while(BITBOARD_IsBitboardTrue(&movesMask)){
      moveSquare = BITBOARD_CountTrailingZeros(&movesMask);
      BITBOARD_SetBitboardToBitboard(&temp, &movesMask);
      BITBOARD_Subtract(&temp, &temp, &(BITBOARD_Bitboard){{1,0}});
      BITBOARD_BitwiseAND(&movesMask, 1, &temp);

      BOARD_AddMove(&board->pseudoMoves, square, moveSquare);
    }
  }
}

void BOARD_GeneratePseudoMoves_Bishop(BOARD_Board* board, uint8_t isWhite)
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

      BOARD_AddMove(&board->pseudoMoves, square, moveSquare);
    }
  }
}

void BOARD_GeneratePseudoMoves_Rook(BOARD_Board* board, uint8_t isWhite)
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

      BOARD_AddMove(&board->pseudoMoves, square, moveSquare);
    }
  }
}

void BOARD_GeneratePseudoMoves_Queen(BOARD_Board* board, uint8_t isWhite)
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

      BOARD_AddMove(&board->pseudoMoves, square, moveSquare);
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

      BOARD_AddMove(&board->pseudoMoves, square, moveSquare);
    }
  }
}

void BOARD_GeneratePseudoMoves_King(BOARD_Board* board, uint8_t isWhite)
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

    BOARD_AddMove(&board->pseudoMoves, square, moveSquare);
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
}

