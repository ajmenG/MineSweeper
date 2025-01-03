#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

#include "board.h"

// wyświetlanie planszy
void print_board(Board *board);

// ruch gracza
int get_user_move(Board *board, int *row, int *col, char *action);

#endif // INPUT_OUTPUT_H