// Main game logic (game loop, move processing)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/game.h"

int revealed = 0;

/**
 * Checks if coordinates are within board boundaries
 * @param board Pointer to the game board
 * @param row Row coordinate
 * @param col Column coordinate
 * @return 1 if coordinates are valid, 0 otherwise
 */
int is_valid(Board *board, int row, int col)
{
    return row >= 0 && row < board->rows && col >= 0 && col < board->cols;
}

/**
 * Reveals a cell at specified coordinates
 * @param board Pointer to the game board
 * @param row Row coordinate
 * @param col Column coordinate
 * @return 1 if cell was revealed, 0 otherwise
 */
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

/**
 * Places or toggles a flag at specified coordinates
 * @param board Pointer to the game board
 * @param row Row coordinate
 * @param col Column coordinate
 */
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

/**
 * Removes a flag from specified coordinates
 * @param board Pointer to the game board
 * @param row Row coordinate
 * @param col Column coordinate
 */
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

/**
 * Reveals all mines on the board (game over)
 * @param board Pointer to the game board
 */
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

/**
 * Counts the number of revealed cells on the board
 * @param board Pointer to the game board
 * @return Number of revealed cells
 */
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

/**
 * Calculates player's score based on revealed cells and difficulty
 * @param board Pointer to the game board
 * @param difficulty Game difficulty level
 * @return Player's score
 */
int score(Board *board, int difficulty)
{
    return difficulty * count_revealed(board);
}

/**
 * Checks if a cell can be revealed
 * @param board Pointer to the game board
 * @param row Row coordinate
 * @param col Column coordinate
 * @return 1 if cell can be revealed, 0 otherwise
 */
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

/**
 * Checks if a cell can be flagged
 * @param board Pointer to the game board
 * @param row Row coordinate
 * @param col Column coordinate
 * @return 1 if cell can be flagged, 0 otherwise
 */
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

/**
 * Checks if a flag can be removed from a cell
 * @param board Pointer to the game board
 * @param row Row coordinate
 * @param col Column coordinate
 * @return 1 if flag can be removed, 0 otherwise
 */
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
