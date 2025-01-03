// Zapisywanie i wczytywanie najlepszych wyników
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/scoreboard.h"

// zapisywanie wyniku do pliku
void save_score(char *nickname, int score)
{
    FILE *file = fopen("scoreboard.txt", "a");

    fclose(file);
}