#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "input_output.h"

extern int run;

extern int fail;

// sprawdzenie, czy pole jest na planszy
int is_valid(Board *board, int row, int col);

// odkrycie pola
int reveal_field(Board *board, int row, int col);

// oznaczenie pola flagą
void flag_field(Board *board, int row, int col);

// odkrywanie wszystkich min
void reveal_all_mines(Board *board);

#endif // GAME_H