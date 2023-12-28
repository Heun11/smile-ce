#include "board.h"
#include "main.h"
#include <ctype.h>
#include <raylib.h>
#include <stdio.h>

#define BOARD_PIECEWC(piece, color) ((color>0)?toupper(piece):tolower(piece))

BOARD_Board BOARD_SetupBoard(char* fen)
{
  BOARD_Board board;

  board.win = 0;
  board.selectedPiece.x = -1;
  board.selectedPiece.y = -1;
  
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
        if(symbol=='K'){
          board.kingPosW.x = file;
          board.kingPosW.y = rank;
        }
        if(symbol=='k'){
          board.kingPosB.x = file;
          board.kingPosB.y = rank;
        }
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

  // printing board
  printf("Show Board:\n\n");
  for(int i=0;i<8;i++){
    for(int j=0;j<8;j++){
      printf("%c ", board.board[i][j]);
    }
    printf("\n");
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

  for(int i=0;i<8;i++){
    DrawText(TextFormat("%c", (char)(i+0x61)), offx+i*TS, SCREEN_HEIGHT-TS/2, TS/3, (Color){ 150, 150, 150, 255 });
    DrawText(TextFormat("%d", (i+0x1)), offx-TS/3, SCREEN_HEIGHT-TS*(i+1), TS/3, (Color){ 150, 150, 150, 255 });
  }
}

int BOARD_IsCheck(BOARD_Board* board, int color)
{
  int x, y;
  if(color>0){
    x = board->kingPosW.x;
    y = board->kingPosW.y;
  }
  else{
    x = board->kingPosB.x;
    y = board->kingPosB.y;
  }

  // pawn
  if(color>0){
    // white
    if(x>0 && y>0 && board->board[y-1][x-1]=='p'){
      return 1;
    }
    if(x<7 && y>0 && board->board[y-1][x+1]=='p'){
      return 1;
    }
  }
  else{
    // black
    if(x>0 && y<7 && board->board[y+1][x-1]=='P'){
      return 1;
    }
    if(x<7 && y<7 && board->board[y+1][x+1]=='P'){
      return 1;
    }
  }

  // rook & queen (horizontal & vertical)
  int fromEdgeX = 7-x;
  int fromEdgeY = 7-y;
  int result = 0;

  // horizontal
  for(int i=fromEdgeX-7;(i+x)<8;i++){
    if(i==0 && result==1){
      break;
    }
    if(board->board[y][x+i]==BOARD_PIECEWC('r', color*-1) || board->board[y][x+i]==BOARD_PIECEWC('q', color*-1)){
      result = 1;
    }
    if(board->board[y][x+i]!=' ' && board->board[y][x+i]!=BOARD_PIECEWC('r',color*-1) 
    && board->board[y][x+i]!=BOARD_PIECEWC('q',color*-1) && i!=0){
      result = 0;
      if(i>0){
        break;
      }
    }
  }

  if(result>0){return 1;};

  // vertical
  for(int i=fromEdgeY-7;(i+y)<8;i++){
    if(i==0 && result==1){
      break;
    }
    if(board->board[y+i][x]==BOARD_PIECEWC('r', color*-1) || board->board[y+i][x]==BOARD_PIECEWC('q', color*-1)){
      result = 1;
    }
    if(board->board[y+i][x]!=' ' && board->board[y+i][x]!=BOARD_PIECEWC('r',color*-1) 
    && board->board[y+i][x]!=BOARD_PIECEWC('q',color*-1) && i!=0){
      result = 0;
      if(i>0){
        break;
      }
    }
  }
  
  if(result>0){return 1;};

  // bishop & queen (diagonal)
  // start topleft
  int startX = 0, startY = 0;

  if(x>y){
    startX = x-y;
  }
  else{
    startY = y-x;
  }

  for(int i=0;(startX+i)<8 && (startY+i)<8;i++){
    if(board->board[startY+i][startX+i]==BOARD_PIECEWC('k', color) && result==1){
      break;
    }
    if(board->board[startY+i][startX+i]==BOARD_PIECEWC('b', color*-1) || board->board[startY+i][startX+i]==BOARD_PIECEWC('q', color*-1)){
      result = 1;
    }
    if(board->board[startY+i][startX+i]!=' ' && board->board[startY+i][startX+i]!=BOARD_PIECEWC('b',color*-1) 
    && board->board[startY+i][startX+i]!=BOARD_PIECEWC('q',color*-1) && i!=0){
      result = 0;
      if(startX+i>x && startY+i>y){
        break;
      }
    }
  }
  
  if(result>0){return 1;};
  
  // start bottomleft
  startX = 0, startY = 7;

  if(x>fromEdgeY){
    startX = x-fromEdgeY;
  }
  else{
    startY = abs((fromEdgeY-x)-7);
  }

  for(int i=0;(startX+i)<8 && (startY-i)>=0;i++){
    if(board->board[startY-i][startX+i]==BOARD_PIECEWC('k', color) && result==1){
      break;
    }
    if(board->board[startY-i][startX+i]==BOARD_PIECEWC('b', color*-1) || board->board[startY-i][startX+i]==BOARD_PIECEWC('q', color*-1)){
      result = 1;
    }
    if(board->board[startY-i][startX+i]!=' ' && board->board[startY-i][startX+i]!=BOARD_PIECEWC('b',color*-1) 
    && board->board[startY-i][startX+i]!=BOARD_PIECEWC('q',color*-1) && i!=0){
      result = 0;
      if(startX+i>x && startY-i>y){
        break;
      }
    }
  }
  
  if(result>0){return 1;};

  // knight
  int xMoves[8] = {-2, -2, -1, -1, +1, +1, +2, +2};
  int yMoves[8] = {-1, +1, -2, +2, -2, +2, +1, -1};
  for(int i=0;i<8;i++){
    if(x+xMoves[i]>=0 && x+xMoves[i]<=7 && y+yMoves[i]>=0 && y+yMoves[i]<=7){
      if(board->board[y+yMoves[i]][x+xMoves[i]]==BOARD_PIECEWC('n', color*-1)){
        return 1;
      }
    }
  }

  // king check
  for(int i=-1;i<=1;i++){
    for(int j=-1;j<=1;j++){
      if(x+i>=0 && x+i<8 && y+i>=0 && y+i<8 && board->board[y+j][x+i]==BOARD_PIECEWC('k', color*-1)){
        return 1;
      }
    }
  }

  return 0;
}

BOARD_Moves BOARD_GenerateMoves(BOARD_Board* board)
{
  BOARD_Moves moves = {0, NULL};
  if(board->selectedPiece.x<0 || board->selectedPiece.y<0){
    return moves;
  }

  return moves;
}

void BOARD_MakeMove(BOARD_Board* board, int ox, int oy)
{
  if(board->selectedPiece.x<0 || board->selectedPiece.y<0){
    int mx = GetMouseX();
    int my = GetMouseY();

    int px = (mx-ox)/TS;
    int py = (my-oy)/TS;

    printf("%d %d\n", px, py);
  }
}
