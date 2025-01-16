// Główny plik, parsuje argumenty, uruchamia grę
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

int run = 1;

int fail = 0;

int interactive_mode();

void file_mode();

void test_mode();

void print_usage(char *name);

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
            printf("Nazwa pliku: %s\n", filename);
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

int interactive_mode()
{
    rules();

    int rows, cols, difficulty, mines;
    printf("Podaj poziom trudności (1-3) lub 4 (własny): ");
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
        printf("Podaj liczbę wierszy: ");
        scanf("%d", &rows);
        printf("Podaj liczbę kolumn: ");
        scanf("%d", &cols);
        printf("Podaj liczbę min: ");
        scanf("%d", &mines);
        break;
    }

    if (mines >= rows * cols)
    {
        printf("Za dużo min\n");
        return -1;
    }

    if (difficulty < 1 || difficulty > 4)
    {
        printf("Niepoprawny poziom trudności\n");
        return -1;
    }

    Board *board = board_create(rows, cols, difficulty, mines);
    print_board(board);

    int licznik = 0;

    while (run)
    {
        char command;
        int x, y;

        printf("Podaj komendę: ");
        if (scanf(" %c", &command) != 1) // Sprawdzenie, czy wczytano komendę
        {
            printf("Niepoprawna komenda\n");
            while (getchar() != '\n')
                ; // Wyczyść bufor wejściowy
            continue;
        }

        if (command == 'x') // Sprawdzenie komendy 'x' przed wczytaniem współrzędnych
        {
            fail = 1;
            run = 0;
            break;
        }

        if (command == 'f' || command == 'd' || command == 'r')
        {
            if (scanf("%d %d", &x, &y) != 2) // Sprawdzenie, czy wczytano dwie współrzędne
            {
                printf("Brak współrzędnych\n");
                while (getchar() != '\n')
                    ; // Wyczyść bufor wejściowy
                continue;
            }

            if (x < 1 || x > rows || y < 1 || y > cols)
            {
                printf("Niepoprawne współrzędne\n");
                continue;
            }

            if (licznik == 0)
            {
                generate_mines(board, x - 1, y - 1);
                calculate_mines_in_neighborhood(board);
            }
            licznik++;
        }
        else
        {
            printf("Niepoprawna komenda\n");
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
        printf("Aktualny wynik: %d\n", score(board, difficulty));
    }

    if (fail)
    {
        printf("Przegrałeś!!!!!\n");
    }
    else
    {
        printf("Wygrałeś!!!, gratulacje\n");
    }

    printf("Twój wynik to: %d\n\n", score(board, difficulty));

    char odp;
    char nickname[20];
    printf("Czy chcesz zapisać wynik? (t/n): ");
    scanf(" %c", &odp);
    switch (odp)
    {
    case 't':
        printf("Podaj nick: ");
        scanf("%s", nickname);
        save_score(nickname, score(board, difficulty));
        printf("Dziękujemy za grę\n\n");
        break;
    case 'n':
        printf("Dziękujemy za grę\n\n");
        break;
    default:
        printf("Niepoprawna komenda\n");
        break;
    }

    display_scores();

    return 0;
}

void file_mode(char *filename)
{
    read_file(filename, fail);
    return;
}

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
void print_usage(char *name)
{
    printf("Użycie: %s [-f filename]\n", name);
    printf("lub:");
    printf("Użycie: %s [-t]\n", name);
    printf("Uruchomienie gry w trybie interaktywnym: %s\n", name);
    printf("Uruchomienie gry z pliku: %s -f filename\n", name);
    printf("Uruchomienie testów: %s -t\n", name);
    return;
}