// Obsługa planszy (generowanie, odkrywanie pól itp.)
#include "board.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// tworzenie planszy
Board *board_create(int rows, int cols, int difficulty, int mines)
{
    srand(time(NULL));
    Board *board = malloc(sizeof(Board));
    board->rows = rows;
    board->cols = cols;
    board->difficulty = difficulty;
    board->mine_count = mines;
    board->grid = malloc(rows * sizeof(Cell *));
    for (int i = 0; i < rows; i++)
    {
        board->grid[i] = malloc(cols * sizeof(Cell));
        for (int j = 0; j < cols; j++)
        {
            board->grid[i][j].is_mine = 0;
            board->grid[i][j].is_revealed = 0;
            board->grid[i][j].is_flagged = 0;
            board->grid[i][j].mines_in_neighborhood = 0;
        }
    }
}