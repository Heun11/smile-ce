#ifndef ENGINE_H
#define ENGINE_H

// pawn 1
// knight & bishop 3
// rook 5
// queen 9

#define ENGINE_DEPTH 2

#include "board.h"
#include <stdint.h>

void ENGINE_PlayTurn(BOARD_Board *board);

#endif
