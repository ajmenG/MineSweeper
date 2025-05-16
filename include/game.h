#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "input_output.h"

extern int run;

extern int fail;

// Validates if coordinates are within the board boundaries
int is_valid(Board *board, int row, int col);

// Reveals a cell at the specified coordinates
int reveal_field(Board *board, int row, int col);

// Places a flag at the specified coordinates
void flag_field(Board *board, int row, int col);

// Reveals all mines on the board (typically at game end)
void reveal_all_mines(Board *board);

// Counts the total number of revealed cells
int count_revealed(Board *board);

// Removes a flag from the specified coordinates
void remove_flag(Board *board, int row, int col);

// Calculates the player's score based on game state and difficulty
int score(Board *board, int difficulty);

// Checks if a cell at the specified coordinates can be revealed
int check_reveal(Board *board, int row, int col);

// Checks if a cell at the specified coordinates can be flagged
int check_flag(Board *board, int row, int col);

// Checks if a flag can be removed from the specified coordinates
int check_remove_flag(Board *board, int row, int col);

#endif // GAME_H