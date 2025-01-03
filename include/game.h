#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "input_output.h"

// sprawdzenie, czy pole jest na planszy
int is_valid(Board *board, int row, int col);

// odkrycie pola
int reveal_field(Board *board, int row, int col);

// oznaczenie pola flagą
void flag_field(Board *board, int row, int col);

#endif // GAME_H