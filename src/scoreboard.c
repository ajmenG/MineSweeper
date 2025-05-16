// Score management (saving, loading, and displaying high scores)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/scoreboard.h"

/**
 * Saves a player's score to the scoreboard file
 * @param nickname Player's nickname
 * @param score Player's score
 */
void save_score(char *nickname, int score)
{
    FILE *file = fopen("bin/scoreboard.txt", "a");
    if (file == NULL)
    {
        perror("Cannot open file for writing");
        return;
    }

    if (fprintf(file, "%s %d\n", nickname, score) < 0)
    {
        perror("Cannot write to file");
    }

    if (fclose(file) != 0)
    {
        perror("Cannot close file");
    }
}

/**
 * Loads scores from the scoreboard file into an array
 * @param scores Array to store the loaded scores
 * @param count Pointer to store the number of loaded scores
 */
void load_scores(ScoreEntry scores[MAX_SCORES], int *count)
{
    FILE *file = fopen("bin/scoreboard.txt", "r");
    if (file == NULL)
    {
        perror("Cannot open file for reading");
        return;
    }

    *count = 0;
    while (*count < MAX_SCORES && fscanf(file, "%49s %d", scores[*count].name, &scores[*count].score) == 2)
    {
        (*count)++;
    }

    if (fclose(file) != 0)
    {
        perror("Cannot close file");
    }
}

/**
 * Comparison function for sorting scores in descending order
 * @param a First score entry to compare
 * @param b Second score entry to compare
 * @return Difference between scores (for descending sort)
 */
int compare_scores(const void *a, const void *b)
{
    int score_a = ((ScoreEntry *)a)->score;
    int score_b = ((ScoreEntry *)b)->score;
    return score_b - score_a; // Sort in descending order
}

/**
 * Sorts scores in descending order
 * @param scores Array of score entries to sort
 * @param count Number of scores in the array
 */
void sort_scores(ScoreEntry scores[MAX_SCORES], int count)
{
    qsort(scores, count, sizeof(ScoreEntry), compare_scores);
}

/**
 * Displays the top 5 scores
 */
void display_scores()
{
    ScoreEntry scores[MAX_SCORES] = {0};
    int count = 0;

    load_scores(scores, &count);

    // Sort the scores
    sort_scores(scores, count);

    printf("Top Scores:\n");
    for (int i = 0; i < 5 && i < count; i++)
    {
        printf("%d. %s %d\n", i + 1, scores[i].name, scores[i].score);
    }
}