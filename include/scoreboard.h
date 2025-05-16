#ifndef SCOREBOARD_H
#define SCOREBOARD_H
#define MAX_SCORES 100

#include "board.h"
#include "input_output.h"

typedef struct
{
    char name[50];
    int score;
} ScoreEntry;

// Saves player score to a file
void save_score(char *nickname, int score);

// Loads scores from file into the provided array
void load_scores(ScoreEntry scores[MAX_SCORES], int *count);

// Displays the leaderboard with top scores
void display_scores();

// Comparison function for sorting scores
int compare_scores(const void *a, const void *b);

#endif // SCOREBOARD_H