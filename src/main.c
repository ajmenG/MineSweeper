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

extern int revealed;

void print_usage(const char *prog_name)
{
    printf("Usage: %s [-f x y] [-r x y]\n", prog_name);
}

int run = 1;

int fail = 0;

int main(int argc, char *argv[])
{
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

    int licznik = 0;
    while (run)
    {
        licznik++;
        char command;
        int x, y;

        printf("Podaj komendę: ");

        scanf(" %c %d %d", &command, &x, &y);
        if (licznik == 1)
        {
            generate_mines(board, x - 1, y - 1);
            calculate_mines_in_neighborhood(board);
        }
        switch (command)
        {
        case 'f':
            flag_field(board, x - 1, y - 1);
            printf("\n");
            print_board(board);
            break;
        case 'r':
            reveal_field(board, x - 1, y - 1);
            printf("\n");
            print_board(board);
            break;
        case 'x': // dodalem x zeby zakonczyc gre
            fail = 1;
            run = 0;
            break;
        default:
            printf("Niepoprawna komenda\n");
            // run = 0; - to zakancza gre jak ktos popsuje to nie moze tak byc
            break;
        }
    }

    if (fail)
    {
        printf("Przegrałeś\n");
    }
    else
    {
        printf("Wygrałeś\n");
    }

    printf("Twój wynik to: %d\n", difficulty * revealed);

    return 0;
}