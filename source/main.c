#include "main.h"
#include "bitboard_func.h"
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

  // BOARD_Board board = BOARD_SetupBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq");
  BOARD_Board board = BOARD_SetupBoard("k7/4P3/8/8/8/8/4p3/K7 w");

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

    printf("%d\n", board.bools);
    if(UTIL_GetBoolFromBools(board.bools, INDEX_WIN)==0 && UTIL_GetBoolFromBools(board.bools, INDEX_DRAW)==0){
      BOARD_DrawBoard(&board, TS, TS);
      BOARD_PlayTurn(&board, TS, TS);
    }
    else{
      if(UTIL_GetBoolFromBools(board.bools, INDEX_WIN)){
        if(UTIL_GetBoolFromBools(board.bools, INDEX_WINNER)){
          DrawText("White won by checkmate", TS, TS*2, TS/2, WHITE);
        }
        else{
          DrawText("Black won by checkmate", TS, TS*2, TS/2, WHITE);
        }
      }
      else if(UTIL_GetBoolFromBools(board.bools, INDEX_DRAW)){
        DrawText("Game is Draw by stalemate", TS, TS*2, TS/2, WHITE);
      }
      else{
        DrawText("wtf", TS, TS*2, TS/2, WHITE);
      }
    }

    SetWindowTitle(TextFormat(":) - FPS:%d", GetFPS()));

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
