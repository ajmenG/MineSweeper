// Unit tests for the Minesweeper game
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/board.h"
#include "../include/game.h"
#include "../include/parse_file.h"
#include "../include/input_output.h"
#include "../include/scoreboard.h"
#include "../include/tests.h"

/**
 * Tests the board_create function by verifying board properties
 * @return 1 if test passed, 0 if failed
 */
int test_board_create()
{
    Board *board = board_create(10, 10, 1, 10);
    if (board == NULL)
    {
        return 0;
    }
    if (board->rows != 10 || board->cols != 10 || board->difficulty != 1 || board->mine_count != 10)
    {
        return 0;
    }
    return 1;
}

/**
 * Tests the mine generation functionality by verifying correct mine count
 * @return 1 if test passed, 0 if failed
 */
int test_generate_mines()
{
    Board *board = board_create(10, 10, 1, 10);
    generate_mines(board, 0, 0);
    int mine_count = 0;
    for (int i = 0; i < board->rows; i++)
    {
        for (int j = 0; j < board->cols; j++)
        {
            if (board->grid[i][j].is_mine == 1)
            {
                mine_count++;
            }
        }
    }
    if (mine_count != 10)
    {
        return 0;
    }
    return 1;
}

/**
 * Tests the neighborhood mine calculation functionality
 * Verifies that cells in the 3x3 area around the first click have no mines
 * @return 1 if test passed, 0 if failed
 */
int test_calculate_mines_in_neighborhood()
{
    Board *board = board_create(10, 10, 1, 10);
    generate_mines(board, 0, 0);
    calculate_mines_in_neighborhood(board);
    if (board->grid[0][0].mines_in_neighborhood != 0)
    {
        return 0;
    }
    return 1;
}

/**
 * Tests the mine counting function for a specific cell
 * @return 1 if test passed, 0 if failed
 */
int test_count_mines()
{
    Board *board = board_create(10, 10, 1, 10);
    generate_mines(board, 0, 0);
    if (count_mines(board, 0, 0) != 0)
    {
        return 0;
    }
    return 1;
}

/**
 * Tests the flag placement functionality
 * @return 1 if test passed, 0 if failed
 */
int test_flag_field()
{
    Board *board = board_create(10, 10, 1, 10);
    flag_field(board, 0, 0);
    if (board->grid[0][0].is_flagged != 1)
    {
        return 0;
    }
    return 1;
}

/**
 * Tests the flag removal functionality
 * @return 1 if test passed, 0 if failed
 */
int test_remove_flag()
{
    Board *board = board_create(10, 10, 1, 10);
    flag_field(board, 0, 0);
    remove_flag(board, 0, 0);
    if (board->grid[0][0].is_flagged != 0)
    {
        return 0;
    }
    return 1;
}

/**
 * Tests the cell revelation functionality
 * @return 1 if test passed, 0 if failed
 */
int test_reveal_field()
{
    Board *board = board_create(10, 10, 1, 10);
    reveal_field(board, 0, 0);
    if (board->grid[0][0].is_revealed != 1)
    {
        return 0;
    }
    return 1;
}

/**
 * Tests the revealed cells counting functionality
 * @return 1 if test passed, 0 if failed
 */
int test_count_revealed()
{
    Board *board = board_create(10, 10, 1, 10);
    if (count_revealed(board) != 0)
    {
        return 0;
    }
    return 1;
}
