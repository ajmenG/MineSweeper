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

// zliczanie odkrytych pól
int count_revealed(Board *board);

// usuwanie flagi
void remove_flag(Board *board, int row, int col);

// wynik gracza
int score(Board *board, int difficulty);

// sprawdzenie, czy pole można odkryć
int check_reveal(Board *board, int row, int col);

// sprawdzenie, czy pole można oznaczyć flagą
int check_flag(Board *board, int row, int col);

// sprawdzenie, czy pole można usunąć flagę
int check_remove_flag(Board *board, int row, int col);

#endif // GAME_H