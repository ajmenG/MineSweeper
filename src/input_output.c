// Funkcje czytające/wyświetlające w terminalu
#include <stdio.h>
#include "../include/input_output.h"

// wyświetlanie planszy
void print_board(Board *board)
{
    printf("  ");
    for (int i = 0; i < board->cols; i++)
    {
        printf("%d ", i);
    }
    printf("\n");
    for (int i = 0; i < board->rows; i++)
    {
        printf("%d ", i);
        for (int j = 0; j < board->cols; j++)
        {
            if (board->grid[i][j].is_revealed)
            {
                if (board->grid[i][j].is_mine)
                {
                    printf("X ");
                }
                else
                {
                    printf("%d ", board->grid[i][j].mines_in_neighborhood);
                }
            }
            else if (board->grid[i][j].is_flagged)
            {
                printf("F ");
            }
            else
            {
                printf(". ");
            }
        }
        printf("\n");
    }
}
