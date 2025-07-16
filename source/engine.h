#ifndef ENGINE_H
#define ENGINE_H

// pawn 1
// knight & bishop 3
// rook 5
// queen 9

#define ENGINE_DEPTH 2

#include "board.h"
#include <stdint.h>

int8_t ENGINE_EvaluatePosition(BOARD_BoardState *board);

void ENGINE_PlayTurn(BOARD_Board *board);

#endif
