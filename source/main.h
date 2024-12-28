#ifndef MAIN_H
#define MAIN_H

#include"raylib.h"
#include"stdio.h"
#include"stdlib.h"

#define TILE_REAL 16

#define TILE_REAL_W 32
#define TILE_REAL_H 42

#define FANCY_BOARD 1

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern int TS;
extern Texture2D tileset;

// include source
#include "board.h"

#endif
