// Obsługa planszy (generowanie, odkrywanie pól itp.)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/board.h"

// tworzenie planszy
Board *board_create(int rows, int cols, int difficulty, int mines)
{
    Board *board = malloc(sizeof(Board));
    board->rows = rows;
    board->cols = cols;
    board->difficulty = difficulty;
    board->mine_count = mines;
    board->grid = malloc(rows * sizeof(Cell *)); // alokacja pamięci na wiersze
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
    return board;
}

// generowanie min
void generate_mines(Board *board, int row, int col)
{
}

// obliczanie min w sasiedztwie pola
int calculate_mines_in_neighborhood(Board *board, int row, int col)
{
    return 0;
}