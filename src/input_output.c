// Terminal I/O functions for the game
#include <stdio.h>
#include "../include/input_output.h"

/**
 * Displays the current state of the game board
 * @param board Pointer to the game board
 */
void print_board(Board *board)
{
    printf("   ");
    for (int i = 0; i < board->cols; i++)
    {
        printf("%2d ", i + 1);
    }
    printf("\n");
    for (int i = 0; i < board->rows; i++)
    {
        printf("%2d ", i + 1);
        for (int j = 0; j < board->cols; j++)
        {
            if (board->grid[i][j].is_revealed)
            {
                if (board->grid[i][j].is_mine)
                {
                    printf(" X ");
                }
                else if (board->grid[i][j].mines_in_neighborhood > 0)
                {
                    printf("%2d ", board->grid[i][j].mines_in_neighborhood);
                }
                else
                {
                    printf("   ");
                }
            }
            else if (board->grid[i][j].is_flagged)
            {
                printf(" F ");
            }
            else
            {
                printf(" . ");
            }
        }
        printf("\n");
    }
}

/**
 * Displays game rules and possible commands
 */
void rules()
{
    printf("Game Rules:\n");
    printf("1. The goal is to uncover all cells without mines.\n");
    printf("2. The board contains mines, with the number depending on difficulty.\n");
    printf("3. You win when you uncover all cells without mines.\n");
    printf("4. You lose if you uncover a cell with a mine.\n");
    printf("5. You can mark cells with flags to indicate potential mines.\n");
    printf("6. You win if you correctly flag all mines.\n");
    printf("7. You lose if you flag a cell without a mine.\n");
    printf("8. To reveal a cell, type 'r' followed by coordinates (e.g., r 10 8).\n");
    printf("9. To place a flag, type 'f' followed by coordinates (e.g., f 10 8).\n");
    printf("10. To remove a flag, type 'd' followed by coordinates (e.g., d 4 7).\n");
    printf("11. To exit the game at any time, type 'x'.\n\n");
}