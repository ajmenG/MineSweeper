// Główny plik, parsuje argumenty, uruchamia grę
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include "../include/board.h"
#include "../include/game.h"
#include "../include/parse_file.h"
#include <bits/getopt_core.h>

void print_usage(const char *prog_name)
{
    printf("Usage: %s [-f x y] [-r x y]\n", prog_name);
}

int main(int argc, char *argv[])
{
    int opt;

    int rows, cols, difficulty, mines;
    printf("Podaj poziom trudności (1-3): ");
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
    }   

    if (difficulty < 1 || difficulty > 3)
    {
        printf("Niepoprawny poziom trudności\n");
        return EXIT_FAILURE;
    }

    Board *board = board_create(rows, cols, difficulty, mines);
    print_board(board);
        
    while ((opt = getopt(argc, argv, "f:r:"))){
        switch (opt)
        {
            case 'f':
                flag_field(board, 6, 6);
                print_board(board);
                break;
            case 'r':
                reveal_field(board, 8, 8);
                print_board(board);
                break;
        }
    }

    return 0;
}