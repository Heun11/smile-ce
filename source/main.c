#include "main.h"
#include "bitboard_func.h"
#include "board.h"
#include "engine.h"
#include "util.h"
#include <stdint.h>
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
  // BOARD_Board board = BOARD_SetupBoard("8/4P3/8/1k6/4B3/6N1/4n3/R3K2R w KQ");
  // BOARD_Board board = BOARD_SetupBoard("r3k2r/r3P3/6n1/4b3/1K6/8/4p3/8 b kq");
  // BOARD_Board board = BOARD_SetupBoard("2R5/1k6/8/8/8/8/K7/8 w ");
  // BOARD_Board board = BOARD_SetupBoard("7R/k7/8/8/8/8/K7/8 w ");

  uint8_t playerColor = 1;

  while (!WindowShouldClose()){
    BeginDrawing();
    ClearBackground((Color){10,10,10,255});

    if(UTIL_GetBoolFromBools(board.board.bools, INDEX_GAME_END)==0){
      BOARD_DrawBoard(&board, TS, TS, &board.board.bools);
      if(UTIL_GetBoolFromBools(board.board.bools, INDEX_ON_TURN)==playerColor){
        BOARD_PlayTurn(&board, TS, TS);
      }
      else{
        ENGINE_PlayTurn(&board);
        // BOARD_PlayTurn(&board, TS, TS);
      }
    }
    else{
      BOARD_DrawBoard(&board, TS, TS, &board.board.bools);
      if(UTIL_GetBoolFromBools(board.board.bools, INDEX_DRAW)){
        DrawText("Game ended in Draw", TS, TS*0.1, TS/2, WHITE);
      }
      else{
        if(UTIL_GetBoolFromBools(board.board.bools, INDEX_WIN)){
          DrawText("White won by checkmate", TS, TS*0.1, TS/2, WHITE);
        }
        else{
          DrawText("Black won by checkmate", TS, TS*0.1, TS/2, WHITE);
        }
      } 
    }

    SetWindowTitle(TextFormat(":) - FPS:%d", GetFPS()));

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
