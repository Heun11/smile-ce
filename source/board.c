#include "board.h"
#include "main.h"
#include <stdio.h>

#define BOARD_PIECEWC(piece, color) ((color>0)?toupper(piece):tolower(piece))
#define BOARD_GETC(piece) ((isupper(piece))?1:-1)

BOARD_Board BOARD_SetupBoard(char* fen)
{
  BOARD_Board board;

  board.win = 0;
  board.selectedPiece = (BOARD_Vec2){-1,-1};
  board.enPassant = (BOARD_Vec2){-1,-1};
  board.promotion = 'q';
  
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

      if(j==board->selectedPiece.x && i==board->selectedPiece.y){
        DrawRectangle(offx+j*TS, offy+i*TS, TS, TS, (Color){ 20, 20, 200, 125 });
      }

      switch (board->board[i][j]){
        case ' ':
          x = -1, y = -1;
          break;
        case 'P':
          x = 0, y = 0;
          break;
        case 'p':
          x = 0, y = 1;
          break;
        case 'R':
          x = 1, y = 0;
          break;
        case 'r':
          x = 1, y = 1;
          break;
        case 'N':
          x = 2, y = 0;
          break;
        case 'n':
          x = 2, y = 1;
          break;
        case 'B':
          x = 3, y = 0;
          break;
        case 'b':
          x = 3, y = 1;
          break;
        case 'Q':
          x = 4, y = 0;
          break;
        case 'q':
          x = 4, y = 1;
          break;
        case 'K':
          x = 5, y = 0;
          break;
        case 'k':
          x = 5, y = 1;
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

  int i;
  switch (board->promotion){
    case 'q':
      i=0;
      break;
    case 'b':
      i=1;
      break;
    case 'n':
      i=2;
      break;
    case 'r':
      i=3;
      break;
  }
  DrawRectangle(SCREEN_WIDTH-(int)(TS*1.5), offy+TS*i, TS, TS, (Color){ 170, 50, 160, 125 });

  DrawTexturePro(tileset, (Rectangle){4*TILE_SIZE_REAL, 0, TILE_SIZE_REAL, TILE_SIZE_REAL}, 
    (Rectangle){SCREEN_WIDTH-(int)(TS*1.5), offy+TS*0, TS, TS}, (Vector2){0,0}, 0, RAYWHITE);
  DrawTexturePro(tileset, (Rectangle){3*TILE_SIZE_REAL, 0, TILE_SIZE_REAL, TILE_SIZE_REAL}, 
    (Rectangle){SCREEN_WIDTH-(int)(TS*1.5), offy+TS*1, TS, TS}, (Vector2){0,0}, 0, RAYWHITE);
  DrawTexturePro(tileset, (Rectangle){2*TILE_SIZE_REAL, 0, TILE_SIZE_REAL, TILE_SIZE_REAL}, 
    (Rectangle){SCREEN_WIDTH-(int)(TS*1.5), offy+TS*2, TS, TS}, (Vector2){0,0}, 0, RAYWHITE);
  DrawTexturePro(tileset, (Rectangle){1*TILE_SIZE_REAL, 0, TILE_SIZE_REAL, TILE_SIZE_REAL}, 
    (Rectangle){SCREEN_WIDTH-(int)(TS*1.5), offy+TS*3, TS, TS}, (Vector2){0,0}, 0, RAYWHITE);
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
      if(i>0){
        break;
      }
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

  // // vertical
  for(int i=fromEdgeY-7;(i+y)<8;i++){
    if(i==0 && result==1){
      break;
    }
    if(board->board[y+i][x]==BOARD_PIECEWC('r', color*-1) || board->board[y+i][x]==BOARD_PIECEWC('q', color*-1)){
      result = 1;
      if(i>0){
        break;
      }
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
      if(startX+i>x && startY+i>y){
        break;
      }
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
      if(startX+i>x && startY-i<y){
        break;
      }
    }
    if(board->board[startY-i][startX+i]!=' ' && board->board[startY-i][startX+i]!=BOARD_PIECEWC('b',color*-1) 
    && board->board[startY-i][startX+i]!=BOARD_PIECEWC('q',color*-1) && i!=0){
      result = 0;
      if(startX+i>x && startY-i<y){
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

void BOARD_AppendMove(BOARD_Board* board, BOARD_Moves* moves, int nx, int ny)
{
  int x = board->selectedPiece.x;
  int y = board->selectedPiece.y;
  char p = board->board[y][x];
  int color = board->onTurn;
  
  int prev = board->board[ny][nx];
  
  board->board[ny][nx] = p;
  board->board[y][x] = ' ';
  if(board->board[ny][nx]=='k'){
    board->kingPosB = (BOARD_Vec2){nx, ny};
  }
  if(board->board[ny][nx]=='K'){
    board->kingPosW = (BOARD_Vec2){nx, ny};
  }
  if(BOARD_IsCheck(board, color)==0){
    moves->len++;
    moves->moves[moves->len-1] = (BOARD_Vec2){nx, ny};
  }
  if(board->board[ny][nx]=='k'){
    board->kingPosB = (BOARD_Vec2){x, y};
  }
  if(board->board[ny][nx]=='K'){
    board->kingPosW = (BOARD_Vec2){x, y};
  }
  board->board[ny][nx] = prev;
  board->board[y][x] = p;
}

BOARD_Moves BOARD_GenerateMoves(BOARD_Board* board)
{
  BOARD_Moves moves = {0, NULL};
  if(board->selectedPiece.x<0 || board->selectedPiece.y<0){
    return moves;
  }

  moves.moves = (BOARD_Vec2*)malloc(sizeof(BOARD_Vec2)*30);

  int x = board->selectedPiece.x;
  int y = board->selectedPiece.y;
  char p = board->board[y][x];
  int color = board->onTurn;
  int r=0, l=0, u=0, d=0;

  // pawn movement
  if(p==BOARD_PIECEWC('p', color)){
    if(y-1*color>=0 && y-1*color<8 && board->board[y-1*color][x]==' '){
      BOARD_AppendMove(board, &moves, x, y-1*color);
      if((float)y-(2.5f*(float)color)==3.5f && board->board[y-2*color][x]==' '){
        BOARD_AppendMove(board, &moves, x, y-2*color);
      }
    }
    if(y-1*color>=0 && y-1*color<8 && x+1<8 && BOARD_GETC(board->board[y-1*color][x+1])==color*-1 && !(board->board[y-1*color][x+1]==' ')){
      BOARD_AppendMove(board, &moves, x+1, y-1*color);
    }
    if(y-1*color>=0 && y-1*color<8 && x-1>=0 && BOARD_GETC(board->board[y-1*color][x-1])==color*-1 && !(board->board[y-1*color][x-1]==' ')){
      BOARD_AppendMove(board, &moves, x-1, y-1*color);
    }

    if(x-1>=0 && x+1<8 && y-1*color>=0 && y-1*color<8 && (x-1==board->enPassant.x || x+1==board->enPassant.x) && y-1*color==board->enPassant.y){
      BOARD_AppendMove(board, &moves, board->enPassant.x, y-1*color);
    }
  }
  // rook movement
  r=1, l=1, u=1, d=1;
  if(p==BOARD_PIECEWC('r', color) || p==BOARD_PIECEWC('q', color)){
    for(int i=1;i<8;i++){
      if(x+i<8 && r){
        if(board->board[y][x+i]==' '){
          BOARD_AppendMove(board, &moves, x+i, y);
        }
        else if(BOARD_GETC(board->board[y][x+i])==color){
          r = 0;
        }
        else if(BOARD_GETC(board->board[y][x+i])==color*-1){
          BOARD_AppendMove(board, &moves, x+i, y);
          r = 0;
        }
      }
      if(x-i>=0 && l){
        if(board->board[y][x-i]==' '){
          BOARD_AppendMove(board, &moves, x-i, y);
        }
        else if(BOARD_GETC(board->board[y][x-i])==color){
          l = 0;
        }
        else if(BOARD_GETC(board->board[y][x-i])==color*-1){
          BOARD_AppendMove(board, &moves, x-i, y);
          l = 0;
        }
      }

      if(y+i<8 && d){
        if(board->board[y+i][x]==' '){
          BOARD_AppendMove(board, &moves, x, y+i);
        }
        else if(BOARD_GETC(board->board[y+i][x])==color){
          d = 0;
        }
        else if(BOARD_GETC(board->board[y+i][x])==color*-1){
          BOARD_AppendMove(board, &moves, x, y+i);
          d = 0;
        }
      }
      if(y-i>=0 && u){
        if(board->board[y-i][x]==' '){
          BOARD_AppendMove(board, &moves, x, y-i);
        }
        else if(BOARD_GETC(board->board[y-i][x])==color){
          u = 0;
        }
        else if(BOARD_GETC(board->board[y-i][x])==color*-1){
          BOARD_AppendMove(board, &moves, x, y-i);
          u = 0;
        }
      }
    }
  }
  // bishop movement
  r=1, l=1, u=1, d=1;
  if(p==BOARD_PIECEWC('b', color) || p==BOARD_PIECEWC('q', color)){
    for(int i=1;i<8;i++){
      if(x+i<8 && y+i<8 && r){
        if(board->board[y+i][x+i]==' '){
          BOARD_AppendMove(board, &moves, x+i, y+i);
        }
        else if(BOARD_GETC(board->board[y+i][x+i])==color){
          r = 0;
        }
        else if(BOARD_GETC(board->board[y+i][x+i])==color*-1){
          BOARD_AppendMove(board, &moves, x+i, y+i);
          r = 0;
        }
      }
      if(x-i>=0 && y+i<8 && l){
        if(board->board[y+i][x-i]==' '){
          BOARD_AppendMove(board, &moves, x-i, y+i);
        }
        else if(BOARD_GETC(board->board[y+i][x-i])==color){
          l = 0;
        }
        else if(BOARD_GETC(board->board[y+i][x-i])==color*-1){
          BOARD_AppendMove(board, &moves, x-i, y+i);
          l = 0;
        }
      }

      if(x+i<8 && y-i>=0 && u){
        if(board->board[y-i][x+i]==' '){
          BOARD_AppendMove(board, &moves, x+i, y-i);
        }
        else if(BOARD_GETC(board->board[y-i][x+i])==color){
          u = 0;
        }
        else if(BOARD_GETC(board->board[y-i][x+i])==color*-1){
          BOARD_AppendMove(board, &moves, x+i, y-i);
          u = 0;
        }
      }
      if(x-i>=0 && y-i>=0 && d){
        if(board->board[y-i][x-i]==' '){
          BOARD_AppendMove(board, &moves, x-i, y-i);
        }
        else if(BOARD_GETC(board->board[y-i][x-i])==color){
          d = 0;
        }
        else if(BOARD_GETC(board->board[y-i][x-i])==color*-1){
          BOARD_AppendMove(board, &moves, x-i, y-i);
          d = 0;
        }
      }
    }
  }
  // knight movement
  if(p==BOARD_PIECEWC('n', color)){
    int xMoves[8] = {-2, -2, -1, -1, +1, +1, +2, +2};
    int yMoves[8] = {-1, +1, -2, +2, -2, +2, +1, -1};
    for(int i=0;i<8;i++){
      if(y+yMoves[i]<8 && y+yMoves[i]>=0 && x+xMoves[i]<8 && x+xMoves[i]>=0 
      && (board->board[y+yMoves[i]][x+xMoves[i]]==' ' || !(BOARD_GETC(board->board[y+yMoves[i]][x+xMoves[i]])==color))){
        BOARD_AppendMove(board, &moves, x+xMoves[i], y+yMoves[i]);
      }
    }
  }
  // king movement
  if(p==BOARD_PIECEWC('k', color)){
    for(int i=-1;i<=1;i++){
      for(int j=-1;j<=1;j++){
        if(i==0 && j==0){
          continue;
        }
        if(y+i<8 && y+i>=0 && x+j<8 && x+j>=0 
        && (board->board[y+i][x+j]==' ' || !(BOARD_GETC(board->board[y+i][x+j])==color))){
          BOARD_AppendMove(board, &moves, x+j, y+i);
        }
      }  
    }
  }

  return moves;
}

void BOARD_MakeMove(BOARD_Board* board, int ox, int oy)
{
  int mx = GetMouseX();
  int my = GetMouseY();

  int px = (mx-ox)/TS;
  int py = (my-oy)/TS;

  if(IsMouseButtonPressed(0)){
    if(board->selectedPiece.x<0 || board->selectedPiece.y<0){
      if(px>=0 && px<8 && py>=0 && py<8 && board->board[py][px]!=' ' && BOARD_GETC(board->board[py][px])==board->onTurn){
        board->selectedPiece = (BOARD_Vec2){px, py};
      }
      else{
        if(mx>=SCREEN_WIDTH-(int)(TS*1.5) && mx<=SCREEN_WIDTH-(int)(TS*1.5)+TS){
          if(my>=oy+TS*0 && my<=oy+TS*1){
            board->promotion = 'q';
          }
          if(my>=oy+TS*1 && my<=oy+TS*2){
            board->promotion = 'b';
          }
          if(my>=oy+TS*2 && my<=oy+TS*3){
            board->promotion = 'n';
          }
          if(my>=oy+TS*3 && my<=oy+TS*4){
            board->promotion = 'r';
          }
        }
      }
    }
    else{
      // printf("%d %d\n", px, py);
      if(px<0 || px>=8 || py<0 || py>=8){
        board->selectedPiece = (BOARD_Vec2){-1, -1};

        if(mx>=SCREEN_WIDTH-(int)(TS*1.5) && mx<=SCREEN_WIDTH-(int)(TS*1.5)+TS){
          if(my>=oy+TS*0 && my<=oy+TS*1){
            board->promotion = 'q';
          }
          if(my>=oy+TS*1 && my<=oy+TS*2){
            board->promotion = 'b';
          }
          if(my>=oy+TS*2 && my<=oy+TS*3){
            board->promotion = 'n';
          }
          if(my>=oy+TS*3 && my<=oy+TS*4){
            board->promotion = 'r';
          }
        }
      }
      else{
        int moved = 0;
        BOARD_Moves moves = BOARD_GenerateMoves(board);
        for(int i=0;i<moves.len;i++){
          if(px==moves.moves[i].x && py==moves.moves[i].y){
            moved = 1;
            printf("make move\n");
            
            board->board[py][px] = board->board[board->selectedPiece.y][board->selectedPiece.x];
            board->board[board->selectedPiece.y][board->selectedPiece.x] = ' ';

            if(board->board[py][px]=='k'){
              board->kingPosB = (BOARD_Vec2){px, py};
            }
            if(board->board[py][px]=='K'){
              board->kingPosW = (BOARD_Vec2){px, py};
            }

            if(board->board[py][px]=='p' || board->board[py][px]=='P'){
              if(abs(board->selectedPiece.y-py)==2){
                board->enPassant = (BOARD_Vec2){px, board->selectedPiece.y-1*BOARD_GETC(board->board[py][px])};
                board->enPassantColor = BOARD_GETC(board->board[py][px]);
                // printf("mozny en passant %d %d\n", board->enPassant.x, board->enPassant.y);
              }
              else if(board->enPassantColor!=board->onTurn){
                if(py==board->enPassant.y && px==board->enPassant.x){
                  board->board[board->enPassant.y+1*BOARD_GETC(board->board[py][px])][board->enPassant.x] = ' ';
                }
              }
              if(py==0 || py==7){
                board->board[py][px] = BOARD_PIECEWC(board->promotion, BOARD_GETC(board->board[py][px]));
              }
            }
            if(board->enPassantColor!=board->onTurn){
              board->enPassant = (BOARD_Vec2){-1,-1};
            }

            board->selectedPiece = (BOARD_Vec2){-1,-1};

            board->onTurn *= -1;
          }
        }
        if(!moved && board->board[py][px]!=' '){
          if(board->board[py][px]!=' ' && BOARD_GETC(board->board[py][px])==board->onTurn){
            board->selectedPiece = (BOARD_Vec2){px, py};
          }
          else{
            board->selectedPiece = (BOARD_Vec2){-1, -1};
          }
        }
        free(moves.moves);   
      }
    }
  }

  if(board->selectedPiece.x>=0 && board->selectedPiece.y>=0){
    BOARD_Moves moves = BOARD_GenerateMoves(board);
    for(int i=0;i<moves.len;i++){
      DrawRectangle(ox+moves.moves[i].x*TS, oy+moves.moves[i].y*TS, TS, TS, (Color){ 200, 100, 100, 155 });
    }
    free(moves.moves);
  }
}


