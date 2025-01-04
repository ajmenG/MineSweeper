#ifndef SCOREBOARD_H
#define SCOREBOARD_H
#define MAX_SCORES 5

#include "board.h"
#include "input_output.h"

// zapisywanie wyniku do pliku
void save_score(char *nickname, int score);

void load_scores(char names[MAX_SCORES][50], int scores[MAX_SCORES], int *count);

void display_scores();

int compare_scores(const void *a, const void *b);

#endif // SCOREBOARD_H