// Główna logika rozgrywki (pętla, obróbka ruchów)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/game.h"

int revealed = 0;

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
    if (board->grid[row][col].is_revealed && board->rows * board->cols - revealed == board->mine_count)
    {
        run = 0;
        fail = 0;
    }
    if (board->grid[row][col].is_mine)
    {
        reveal_all_mines(board);
    }
    board->grid[row][col].is_revealed = 1;
    if (board->grid[row][col].mines_in_neighborhood == 0)
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
void flag_field(Board *board, int row, int col) // Dodano tę linijkę
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

// usuwanie flagi
void remove_flag(Board *board, int row, int col)
{
    if (!is_valid(board, row, col))
    {
        return;
    }
    if (board->grid[row][col].is_revealed)
    {
        return;
    }
    board->grid[row][col].is_flagged = 0;
}

// przegrana
void reveal_all_mines(Board *board)
{
    for (int i = 0; i < board->rows; i++)
    {
        for (int j = 0; j < board->cols; j++)
        {
            if (board->grid[i][j].is_mine)
            {
                board->grid[i][j].is_revealed = 1;
            }
        }
    }
    run = 0;
    fail = 1;
}

// ile odkrytych pól
int count_revealed(Board *board)
{
    revealed = 0;
    for (int i = 0; i < board->rows; i++)
    {
        for (int j = 0; j < board->cols; j++)
        {
            if (board->grid[i][j].is_revealed)
            {
                revealed++;
            }
        }
    }
    return revealed;
}

// wynik
int score(Board *board, int difficulty)
{
    return difficulty * count_revealed(board);
}

int check_reveal(Board *board, int row, int col)
{
    if (!is_valid(board, row, col))
    {
        return 0;
    }
    if (board->grid[row][col].is_revealed)
    {
        return 0;
    }
    return 1;
}

int check_flag(Board *board, int row, int col)
{
    if (!is_valid(board, row, col))
    {
        return 0;
    }
    if (board->grid[row][col].is_flagged)
    {
        return 0;
    }
    return 1;
}

int check_remove_flag(Board *board, int row, int col)
{
    if (!is_valid(board, row, col))
    {
        return 0;
    }
    if (board->grid[row][col].is_revealed)
    {
        return 0;
    }
    if (!board->grid[row][col].is_flagged)
    {
        return 0;
    }
    return 1;
}
