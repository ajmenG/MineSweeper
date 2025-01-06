// Zapisywanie i wczytywanie najlepszych wyników
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/scoreboard.h"

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
void load_scores(ScoreEntry scores[MAX_SCORES], int *count)
{
    FILE *file = fopen("bin/scoreboard.txt", "r");
    if (file == NULL)
    {
        perror("Nie można otworzyć pliku do odczytu");
        return;
    }

    *count = 0;
    while (*count < MAX_SCORES && fscanf(file, "%49s %d", scores[*count].name, &scores[*count].score) == 2)
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
    int score_a = ((ScoreEntry *)a)->score;
    int score_b = ((ScoreEntry *)b)->score;
    return score_b - score_a; // sortowanie malejąco
}

void sort_scores(ScoreEntry scores[MAX_SCORES], int count)
{
    qsort(scores, count, sizeof(ScoreEntry), compare_scores);
}

// wyświetlanie 5 najlepszych wyników
void display_scores()
{
    ScoreEntry scores[MAX_SCORES] = {0};
    int count = 0;

    load_scores(scores, &count);

    // sortowanie wyników
    sort_scores(scores, count);

    printf("Najlepsze wyniki:\n");
    for (int i = 0; i < 5; i++)
    {
        printf("%d. %s %d\n", i + 1, scores[i].name, scores[i].score);
    }
}