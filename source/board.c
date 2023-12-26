#include "board.h"
#include "main.h"
#include <raylib.h>

BOARD_Board BOARD_SetupBoard(char* fen)
{
  BOARD_Board board;
  
  for(int i=0;i<8;i++){
    for(int j=0;j<8;j++){
      board.board[i][j] = ' ';
    }
  }

  // helping vars
  int file = 0, rank = 0;
  char symbol;
  int setup_info = 0;
  
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
        board.board[rank][file] = symbol;
        file++;
      }
    }
  }

  // set fen info
  for(int i=setup_info;i<strlen(fen);i++){
    symbol = fen[i];
    if(symbol=='w'){
      board.onTurn = 1;
    }
    if(symbol=='b'){
      board.onTurn = -1;
    }
    if(symbol=='K'){
      board.canCastleWK = 1;
    }
    if(symbol=='Q'){
      board.canCastleWQ = 1;
    }
    if(symbol=='k'){
      board.canCastleBK = 1;
    }
    if(symbol=='q'){
      board.canCastleBQ = 1;
    }
  }

  return board;
}

void BOARD_DrawBoard(BOARD_Board* board, int offx, int offy)
{
  int x=-1, y=-1;
  for(int i=0;i<8;i++){
    for(int j=0;j<8;j++){
      if((i+j)%2==0){
        DrawRectangle(offx+j*TS, offy+i*TS, TS, TS, (Color){ 200, 200, 200, 255 });
      }
      else{
        DrawRectangle(offx+j*TS, offy+i*TS, TS, TS, (Color){ 80, 80, 80, 255 });
      }

      switch (board->board[i][j]){
        case ' ':
          x = -1;
          y = -1;
          break;
        case 'P':
          x = 0;
          y = 0;
          break;
        case 'p':
          x = 0;
          y = 1;
          break;
        case 'R':
          x = 1;
          y = 0;
          break;
        case 'r':
          x = 1;
          y = 1;
          break;
        case 'N':
          x = 2;
          y = 0;
          break;
        case 'n':
          x = 2;
          y = 1;
          break;
        case 'B':
          x = 3;
          y = 0;
          break;
        case 'b':
          x = 3;
          y = 1;
          break;
        case 'Q':
          x = 4;
          y = 0;
          break;
        case 'q':
          x = 4;
          y = 1;
          break;
        case 'K':
          x = 5;
          y = 0;
          break;
        case 'k':
          x = 5;
          y = 1;
          break;
      }
      if(x>-1 && y>-1){
        DrawTexturePro(tileset, (Rectangle){x*TILE_SIZE_REAL, y*TILE_SIZE_REAL, TILE_SIZE_REAL, TILE_SIZE_REAL}, 
          (Rectangle){offx+TS*j, offy+TS*i, TS, TS}, (Vector2){0,0}, 0, RAYWHITE);
      }
    }
  }
}

