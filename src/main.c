// Main file - parses command line arguments and runs the game
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include "../include/board.h"
#include "../include/game.h"
#include "../include/parse_file.h"
#include "../include/input_output.h"
#include "../include/scoreboard.h"
#include "../include/tests.h"
#include <bits/getopt_core.h>
#include <getopt.h>
#include <game.h>

extern int revealed;

// Flag indicating if the game is running
int run = 1;

// Flag indicating if the game has been failed
int fail = 0;

// Function prototypes
int interactive_mode();
void file_mode(char *filename);
void test_mode();
void print_usage(char *name);

/**
 * Main function - parses command line arguments and runs the appropriate mode
 * @param argc Number of command line arguments
 * @param argv Array of command line arguments
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int main(int argc, char *argv[])
{
    int opt;
    char *filename = NULL;
    int flag_found = 0;

    while ((opt = getopt(argc, argv, "f:t")) != -1)
    {
        switch (opt)
        {
        case 'f':
            filename = optarg;
            printf("Filename: %s\n", filename);
            file_mode(filename);
            flag_found = 1;
            break;
        case 't':
            test_mode();
            flag_found = 1;
            break;
        default:
            print_usage(argv[0]);
            return EXIT_FAILURE;
        }
    }

    if (!flag_found)
    {
        if (interactive_mode() == -1)
        {
            return EXIT_FAILURE;
        }
    }

    return 0;
}

/**
 * Interactive mode - runs the game in interactive mode
 * @return 0 on success, -1 on failure
 */
int interactive_mode()
{
    rules();

    int rows, cols, difficulty, mines;
    printf("Select difficulty level (1-3) or 4 (custom): ");
    scanf("%d", &difficulty);

    switch (difficulty)
    {
    case 1:
        rows = 9;
        cols = 9;
        mines = 10;
        break;
    case 2:
        rows = 16;
        cols = 16;
        mines = 40;
        break;
    case 3:
        rows = 16;
        cols = 30;
        mines = 99;
        break;
    case 4:
        printf("Enter number of rows: ");
        scanf("%d", &rows);
        printf("Enter number of columns: ");
        scanf("%d", &cols);
        printf("Enter number of mines: ");
        scanf("%d", &mines);
        break;
    }

    if (mines >= rows * cols)
    {
        printf("Too many mines\n");
        return -1;
    }

    if (difficulty < 1 || difficulty > 4)
    {
        printf("Invalid difficulty level\n");
        return -1;
    }

    Board *board = board_create(rows, cols, difficulty, mines);
    print_board(board);

    int move_counter = 0;

    while (run)
    {
        char command;
        int x, y;

        printf("Enter command: ");
        if (scanf(" %c", &command) != 1) // Check if command was read
        {
            printf("Invalid command\n");
            while (getchar() != '\n')
                ; // Clear input buffer
            continue;
        }

        if (command == 'x') // Check 'x' command before reading coordinates
        {
            fail = 1;
            run = 0;
            break;
        }

        if (command == 'f' || command == 'd' || command == 'r')
        {
            if (scanf("%d %d", &x, &y) != 2) // Check if two coordinates were read
            {
                printf("Missing coordinates\n");
                while (getchar() != '\n')
                    ; // Clear input buffer
                continue;
            }

            if (x < 1 || x > rows || y < 1 || y > cols)
            {
                printf("Invalid coordinates\n");
                continue;
            }

            if (move_counter == 0)
            {
                generate_mines(board, x - 1, y - 1);
                calculate_mines_in_neighborhood(board);
            }
            move_counter++;
        }
        else
        {
            printf("Invalid command\n");
            continue;
        }

        switch (command)
        {
        case 'f':
            flag_field(board, x - 1, y - 1);
            break;
        case 'd':
            remove_flag(board, x - 1, y - 1);
            break;
        case 'r':
            reveal_field(board, x - 1, y - 1);
            break;
        }

        printf("\n");
        print_board(board);
        if (count_revealed(board) == board->rows * board->cols - board->mine_count)
        {
            run = 0;
        }
        printf("Current score: %d\n", score(board, difficulty));
    }

    if (fail)
    {
        printf("Game over! You lost!\n");
    }
    else
    {
        printf("Congratulations! You won!\n");
    }

    printf("Your final score: %d\n\n", score(board, difficulty));

    char answer;
    char nickname[20];
    printf("Do you want to save your score? (y/n): ");
    scanf(" %c", &answer);
    switch (answer)
    {
    case 'y':
        printf("Enter your nickname: ");
        scanf("%s", nickname);
        save_score(nickname, score(board, difficulty));
        printf("Thank you for playing!\n\n");
        break;
    case 'n':
        printf("Thank you for playing!\n\n");
        break;
    default:
        printf("Invalid command\n");
        break;
    }

    display_scores();

    return 0;
}

/**
 * File mode - runs the game from a file
 * @param filename Name of the file to read
 */
void file_mode(char *filename)
{
    read_file(filename, fail);
    return;
}

/**
 * Test mode - runs all tests
 */
void test_mode()
{
    int tests_passed = 0;
    int tests_failed = 0;

    printf("Running tests...\n");
    if (test_board_create())
    {
        printf("test_board_create: PASSED\n");
        tests_passed++;
    }
    else
    {
        printf("test_board_create: FAILED\n");
        tests_failed++;
    }

    if (test_generate_mines())
    {
        printf("test_generate_mines: PASSED\n");
        tests_passed++;
    }
    else
    {
        printf("test_generate_mines: FAILED\n");
        tests_failed++;
    }

    if (test_calculate_mines_in_neighborhood())
    {
        printf("test_calculate_mines_in_neighborhood: PASSED\n");
        tests_passed++;
    }
    else
    {
        printf("test_calculate_mines_in_neighborhood: FAILED\n");
        tests_failed++;
    }

    if (test_count_mines())
    {
        printf("test_count_mines: PASSED\n");
        tests_passed++;
    }
    else
    {
        printf("test_count_mines: FAILED\n");
        tests_failed++;
    }

    if (test_flag_field())
    {
        printf("test_flag_field: PASSED\n");
        tests_passed++;
    }
    else
    {
        printf("test_flag_field: FAILED\n");
        tests_failed++;
    }

    if (test_remove_flag())
    {
        printf("test_remove_flag: PASSED\n");
        tests_passed++;
    }
    else
    {
        printf("test_remove_flag: FAILED\n");
        tests_failed++;
    }

    if (test_reveal_field())
    {
        printf("test_reveal_field: PASSED\n");
        tests_passed++;
    }
    else
    {
        printf("test_reveal_field: FAILED\n");
        tests_failed++;
    }

    if (test_count_revealed())
    {
        printf("test_count_revealed: PASSED\n");
        tests_passed++;
    }
    else
    {
        printf("test_count_revealed: FAILED\n");
        tests_failed++;
    }

    printf("Tests passed: %d\n", tests_passed);
    printf("Tests failed: %d\n", tests_failed);

    return;
}

/**
 * Prints usage information
 * @param name Name of the program
 */
void print_usage(char *name)
{
    printf("Usage: %s [-f filename]\n", name);
    printf("or:\n");
    printf("Usage: %s [-t]\n", name);
    printf("Run game in interactive mode: %s\n", name);
    printf("Run game from file: %s -f filename\n", name);
    printf("Run tests: %s -t\n", name);
    return;
}