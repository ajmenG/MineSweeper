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
    srand(time(NULL));
    int mines = board->mine_count;
    while (mines > 0)
    {
        int r = rand() % board->rows;
        int c = rand() % board->cols;
        if ((r == row && c == col) ||
            (r - 1 == row && c - 1 == col) ||
            (r - 1 == row && c == col) ||
            (r - 1 == row && c + 1 == col) ||
            (r == row && c - 1 == col) ||
            (r == row && c + 1 == col) ||
            (r + 1 == row && c - 1 == col) ||
            (r + 1 == row && c == col) ||
            (r + 1 == row && c + 1 == col))
        {
            continue;
        }
        if (board->grid[r][c].is_mine)
        {
            continue;
        }
        board->grid[r][c].is_mine = 1;
        mines--;
    }
}

// obliczanie wszystkich min w sasiedztwie kazdego pola
int calculate_mines_in_neighborhood(Board *board)
{
    for (int i = 0; i < board->rows; i++)
    {
        for (int j = 0; j < board->cols; j++)
        {
            board->grid[i][j].mines_in_neighborhood = count_mines(board, i, j);
        }
    }
    return 0;
}

// zliczanie min w sasiedztwie pola
int count_mines(Board *board, int row, int col)
{
    int count = 0;
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (is_valid(board, row + i, col + j) && board->grid[row + i][col + j].is_mine)
            {
                count++;
            }
        }
    }
    return count;
}