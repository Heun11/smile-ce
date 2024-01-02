#include "main.h"

int SCREEN_WIDTH;
int SCREEN_HEIGHT;
int TS;
Texture2D tileset;

#define DIM_W 1000
#define DIM_H 800

int main(void)
{
  float scale = 1.2f;
  // float scale = 0.8f;
  SCREEN_WIDTH = DIM_W*scale;
  SCREEN_HEIGHT = DIM_H*scale;
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, ":)");
  // int display = GetCurrentMonitor();
  // SCREEN_WIDTH = GetMonitorWidth(display);
  // SCREEN_HEIGHT = GetMonitorHeight(display);
  // SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
  // ToggleFullscreen();

  SetTargetFPS(60);

  TS = SCREEN_HEIGHT/9;
  tileset = LoadTexture("resources/chess.png");

  BOARD_Board board = BOARD_SetupBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq");
  // BOARD_Board board = BOARD_SetupBoard("k7/7R/8/8/8/8/8/2R3K1 w");
  int result;

  while (!WindowShouldClose()){
    BeginDrawing();
    ClearBackground((Color){10,10,10,255});

    result = BOARD_IsGameEnd(&board, board.onTurn);
    if(result==0){
      BOARD_DrawBoard(&board, TS/2, TS/2);
      BOARD_MakeMove(&board, TS/2, TS/2);
    }
    else{
      if(result==1){
        if(board.onTurn==1){
          DrawText("Black won by checkmate", TS, TS*2, TS/2, WHITE);
        }
        else{
          DrawText("White won by checkmate", TS, TS*2, TS/2, WHITE);
        }
      }
      else{
        DrawText("Game is Draw by stalemate", TS, TS*2, TS/2, WHITE);
      }
    }

    SetWindowTitle(TextFormat(":) - FPS:%d", GetFPS()));

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
