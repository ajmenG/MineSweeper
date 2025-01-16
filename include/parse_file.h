#ifndef PARSE_FILE_H
#define PARSE_FILE_H

#include "board.h"
#include "input_output.h"

// funkcja do wczytania rozmiarow planszy, trudnosci, planszy oraz ruchow z pliku
void read_file(char *filename, int fail);

#endif // PARSE_FILE_H