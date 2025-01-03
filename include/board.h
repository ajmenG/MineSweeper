#ifndef BOARD_H
#define BOARD_H

// pojedyncza komórka planszy
typedef struct
{
    // czy komórka jest miną
    int is_mine;
    // czy komórka jest odkryta
    int is_revealed;
    // czy komórka jest oznaczona
    int is_flagged;
    // liczba min w sąsiedztwie 3x3 od pola
    int mines_in_neighborhood;
} Cell;

// plansza
typedef struct
{
    // liczba wierszy
    int rows;
    // liczba kolumn
    int cols;
    // poziom trudności
    int difficulty;
    // plansza
    Cell **grid;
    // liczba min
    int mine_count;

} Board;

// tworzenie planszy
Board *board_create(int rows, int cols, int difficulty, int mines);

// generowanie min
void generate_mines(Board *board, int row, int col);

// obliczanie min w sasiedztwie pola
int calculate_mines_in_neighborhood(Board *board, int row, int col);

#endif // BOARD_H