#include "main.h"
#include "board.h"
#include "util.h"
#include <stdio.h>

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

  TS = SCREEN_HEIGHT*0.1;
  #if FANCY_BOARD
  tileset = LoadTexture("resources/chess-fancy.png");
  #else
  tileset = LoadTexture("resources/chess.png");
  #endif

  BOARD_Board board = BOARD_SetupBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq");
  // BOARD_Board board = BOARD_SetupBoard("1q5k/8/4N3/8/KQ5q/8/8/8 w");
  uint8_t result = 0;

  // debugging
  // printf("isCheck = %d\n", BOARD_IsCheck(&board.board, 1));
  // BOARD_GeneratePseudoMoves(&board);
  // printf("pseudo legal moves:\n");
  // BOARD_PrintMoves(&board.pseudoMoves);
  // BOARD_FilterLegalMoves(&board);
  // printf("legal moves:\n");
  // BOARD_PrintMoves(&board.legalMoves);
  
  while (!WindowShouldClose()){
    BeginDrawing();
    ClearBackground((Color){10,10,10,255});

    // result = BOARD_IsGameEnd(&board, board.onTurn);
    if(result==0){
      BOARD_DrawBoard(&board, TS, TS);
      BOARD_PlayTurn(&board, TS, TS);
    }
    else{
      if(result==1){
        if(UTIL_GetBoolFromBools(board.bools, 5)){
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
