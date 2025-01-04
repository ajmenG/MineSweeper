// Zapisywanie i wczytywanie najlepszych wyników
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/scoreboard.h"

#define MAX_SCORES 5

// zapisywanie wyniku do pliku
void save_score(char *nickname, int score)
{
    FILE *file = fopen("bin/scoreboard.txt", "a");
    if (file == NULL)
    {
        perror("Nie można otworzyć pliku do zapisu");
        return;
    }

    if (fprintf(file, "%s %d\n", nickname, score) < 0)
    {
        perror("Nie można zapisać do pliku");
    }

    if (fclose(file) != 0)
    {
        perror("Nie można zamknąć pliku");
    }
}

// wczytywanie najlepszych wyników z pliku
void load_scores(char names[MAX_SCORES][50], int scores[MAX_SCORES], int *count)
{
    FILE *file = fopen("bin/scoreboard.txt", "r");
    if (file == NULL)
    {
        perror("Nie można otworzyć pliku do odczytu");
        return;
    }

    *count = 0;
    while (*count < MAX_SCORES && fscanf(file, "%49s %d", names[*count], &scores[*count]) == 2)
    {
        (*count)++;
    }

    if (fclose(file) != 0)
    {
        perror("Nie można zamknąć pliku");
    }
}

// funkcja porównująca wyniki do sortowania
int compare_scores(const void *a, const void *b)
{
    int score_a = *(const int *)a;
    int score_b = *(const int *)b;
    return score_b - score_a; // sortowanie malejąco
}

// wyświetlanie 5 najlepszych wyników
void display_scores()
{
    char names[MAX_SCORES][50] = {0};
    int scores[MAX_SCORES] = {0};
    int count = 0;

    load_scores(names, scores, &count);

    // sortowanie wyników
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            if (scores[j] < scores[j + 1])
            {
                int temp_score = scores[j];
                scores[j] = scores[j + 1];
                scores[j + 1] = temp_score;

                char temp_name[50];
                strcpy(temp_name, names[j]);
                strcpy(names[j], names[j + 1]);
                strcpy(names[j + 1], temp_name);
            }
        }
    }

    printf("Najlepsze wyniki:\n");
    for (int i = 0; i < count; i++)
    {
        printf("%d. %s %d\n", i + 1, names[i], scores[i]);
    }
}