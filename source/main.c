#include "main.h"
#include "board.h"
#include <raylib.h>

int SCREEN_WIDTH;
int SCREEN_HEIGHT;
int TS;
Texture2D tileset;

#define DIM_W 1000
#define DIM_H 800

int main(void)
{
  // float scale = 1.2f;
  float scale = 0.8f;
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

  // BOARD_Board board = BOARD_SetupBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq");
  BOARD_Board board = BOARD_SetupBoard("k1q3b1/3Q4/8/8/8/1K6/8/8 b");
  while (!WindowShouldClose()){
    BeginDrawing();
    ClearBackground((Color){10,10,10,255});

    BOARD_DrawBoard(&board, TS/2, TS/2);
    printf("%d\n", BOARD_IsCheck(&board, 1));

    SetWindowTitle(TextFormat(":) - FPS:%d", GetFPS()));

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
