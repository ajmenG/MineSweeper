#ifndef PARSE_FILE_H
#define PARSE_FILE_H

#include "board.h"
#include "input_output.h"

// Reads board dimensions, difficulty settings, board layout and moves from file
void read_file(char *filename, int fail);

#endif // PARSE_FILE_H