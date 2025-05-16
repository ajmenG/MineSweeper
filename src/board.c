// Board management (generation, cell revealing, etc.)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/board.h"
#include "../include/game.h"

/**
 * Creates a new game board with specified dimensions
 * @param rows Number of rows
 * @param cols Number of columns
 * @param difficulty Game difficulty level
 * @param mines Number of mines
 * @return Pointer to the created board
 */
Board *board_create(int rows, int cols, int difficulty, int mines)
{
    Board *board = malloc(sizeof(Board));
    board->rows = rows;
    board->cols = cols;
    board->difficulty = difficulty;
    board->mine_count = mines;
    board->grid = malloc(rows * sizeof(Cell *)); // Allocate memory for rows
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

/**
 * Randomly distributes mines on the board
 * @param board Pointer to the game board
 * @param row Row coordinate of first click (to avoid placing mine there)
 * @param col Column coordinate of first click (to avoid placing mine there)
 */
void generate_mines(Board *board, int row, int col)
{
    srand(time(NULL));
    int mines = board->mine_count;
    while (mines > 0)
    {
        int r = rand() % board->rows;
        int c = rand() % board->cols;
        // Avoid placing mines in 3x3 area around first click
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

/**
 * Calculates the number of neighboring mines for each cell
 * @param board Pointer to the game board
 * @return 0 on success
 */
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

/**
 * Counts the number of mines in the 3x3 neighborhood of a cell
 * @param board Pointer to the game board
 * @param row Row coordinate of the cell
 * @param col Column coordinate of the cell
 * @return Number of mines in the neighborhood
 */
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