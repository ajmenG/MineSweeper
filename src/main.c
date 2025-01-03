// Główny plik, parsuje argumenty, uruchamia grę
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include "../include/board.h"
#include "../include/parse_file.h"
#include <bits/getopt_core.h>

void print_usage(const char *prog_name)
{
    printf("Usage: %s [-f x y] [-r x y]\n", prog_name);
}

int main(int argc, char *argv[])
{

    if (argc == 1)
    {
        int rows, cols, difficulty, mines;
        printf("Podaj liczbę wierszy: ");
        scanf("%d", &rows);
        printf("Podaj liczbę kolumn: ");
        scanf("%d", &cols);
        printf("Podaj poziom trudności (1-3): ");

        scanf("%d", &difficulty);
        if (difficulty < 1 || difficulty > 3)
        {
            printf("Niepoprawny poziom trudności\n");
            return EXIT_FAILURE;
        }

        mines = rows * cols * difficulty / 10;
        Board *board = board_create(rows, cols, difficulty, mines);
        print_board(board);
    }

    return 0;
}