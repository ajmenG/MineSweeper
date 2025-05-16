#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

#include "board.h"

// Displays the current game board state
void print_board(Board *board);

// Gets the next move from the user
int get_user_move(Board *board, int *row, int *col, char *action);

// Displays game rules and possible moves
void rules();

#endif // INPUT_OUTPUT_H