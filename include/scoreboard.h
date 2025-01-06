#ifndef SCOREBOARD_H
#define SCOREBOARD_H
#define MAX_SCORES 100

#include "board.h"
#include "input_output.h"

typedef struct {
    char name[50];
    int score;
} ScoreEntry;

// zapisywanie wyniku do pliku
void save_score(char *nickname, int score);

void load_scores(ScoreEntry scores[MAX_SCORES], int *count);

void display_scores();

int compare_scores(const void *a, const void *b);

#endif // SCOREBOARD_H