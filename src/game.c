// Główna logika rozgrywki (pętla, obróbka ruchów)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/game.h"

// sprawdzenie, czy pole jest na planszy
int is_valid(Board *board, int row, int col)
{
    return row >= 0 && row < board->rows && col >= 0 && col < board->cols;
}

// odkrycie pola
int reveal_field(Board *board, int row, int col)
{
    if (!is_valid(board, row, col))
    {
        return 0;
    }
    if (board->grid[row][col].is_revealed)
    {
        return 0;
    }
    if (board->grid[row][col].is_mine)
    {
        return -1;
    }
    board->grid[row][col].is_revealed = 1;
    if (board->grid[row][col].mines_in_neighborhood == 0) //to powinno rekruencyjnie odkrywać sąsiednie pola az do napotkania takich z minami w sasiedztwie lub scian
    {
        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                reveal_field(board, row + i, col + j);
            }
        }
    }
    return 1;
}

// oznaczenie pola flagą
void flag_field(Board *board, int row, int col)
{
    if (!is_valid(board, row, col))
    {
        return;
    }
    if (board->grid[row][col].is_revealed)
    {
        return;
    }
    board->grid[row][col].is_flagged = !board->grid[row][col].is_flagged;
}
