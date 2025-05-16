#ifndef TESTS_H
#define TESTS_H

#include "board.h"
#include "game.h"
#include "parse_file.h"
#include "input_output.h"
#include "scoreboard.h"

// Board testing functions
int test_board_create();

int test_generate_mines();

int test_calculate_mines_in_neighborhood();

int test_count_mines();

int test_flag_field();

int test_remove_flag();

int test_reveal_field();

int test_count_revealed();

#endif // TESTS_H