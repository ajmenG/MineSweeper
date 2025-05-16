// File input handler (for -f mode)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/parse_file.h"
#include "../include/board.h"
#include "../include/game.h"

/**
 * Reads game configuration and commands from an input file
 * @param filename Path to the input file
 * @param fail Flag indicating if the game is in failed state
 */
void read_file(char *filename, int fail)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Failed to open file\n");
        exit(EXIT_FAILURE);
    }

    // Create board with specified dimensions, difficulty, and mine count
    int rows, cols, difficulty, mines;
    fscanf(file, " %d %d %d %d", &rows, &cols, &difficulty, &mines);
    Board *board = board_create(rows, cols, difficulty, mines);

    // Read mine positions from the file
    for (int i = 0; i < board->rows; i++)
    {
        for (int j = 0; j < board->cols; j++)
        {
            int tmp;
            fscanf(file, "%d", &tmp);

            if (tmp == 1)
            {
                board->grid[i][j].is_mine = 1;
            }
            else
            {
                board->grid[i][j].is_mine = 0;
            }
        }
    }

    calculate_mines_in_neighborhood(board);

    // Process commands from the file
    char command;
    int x, y;
    int valid_commands = 0;

    while (fscanf(file, " %c %d %d", &command, &x, &y) != EOF)
    {
        switch (command)
        {
        case 'f':
            if (check_flag(board, x - 1, y - 1) == 1 && fail == 0)
            {
                valid_commands++;
            }
            flag_field(board, x - 1, y - 1);
            break;
        case 'd':
            if (check_remove_flag(board, x - 1, y - 1) == 1 && fail == 0)
            {
                valid_commands++;
            }
            remove_flag(board, x - 1, y - 1);
            break;
        case 'r':
            if (check_reveal(board, x - 1, y - 1) == 1 && fail == 0)
            {
                valid_commands++;
            }
            reveal_field(board, x - 1, y - 1);
            break;
        }
    }

    printf("Valid commands executed: %d\n", valid_commands);
    printf("Player's score: %d\n", score(board, difficulty));
    printf("Player won: %s\n",
           score(board, difficulty) == board->rows * board->cols - board->mine_count ? "Yes" : "No");

    fclose(file);
    printf("File successfully processed\n");
    return;
}