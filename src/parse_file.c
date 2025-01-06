// Obsługa trybu wczytywania z pliku (flaga -f)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/parse_file.h"

// funkcja do parsowania pliku wejściowego i zapisania danych do struktury planszy
void read_file(char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Nie udało się otworzyć pliku\n");
        exit(EXIT_FAILURE);
    }

    // tworzenie planszy o podanych rozmiarach, trudności oraz liczbie min
    int rows, cols, difficulty, mines;
    fscanf(file, " %d %d %d %d", &rows, &cols, &difficulty, &mines);
    Board *board = board_create(rows, cols, difficulty, mines);

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

    char command;
    int x, y;
    while (fscanf(file, " %c %d %d", &command, &x, &y) != EOF)
    {
        switch (command)
        {
        case 'f':
            // flag_field(board, x - 1, y - 1);
            break;
        case 'd':
            // remove_flag(board, x - 1, y - 1);
            break;
        case 'r':
            // reveal_field(board, x - 1, y - 1);
            break;
        }
    }
    fclose(file);
    printf("Udało się wczytać plik\n");
    return;
}