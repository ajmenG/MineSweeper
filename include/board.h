#ifndef BOARD_H
#define BOARD_H

// Individual cell of the board
typedef struct
{
    // Indicates if the cell contains a mine
    int is_mine;
    // Indicates if the cell has been revealed by the player
    int is_revealed;
    // Indicates if the cell has been flagged by the player
    int is_flagged;
    // Number of mines in the 3x3 neighborhood around this cell
    int mines_in_neighborhood;
} Cell;

// Game board structure
typedef struct
{
    // Number of rows on the board
    int rows;
    // Number of columns on the board
    int cols;
    // Difficulty level of the game
    int difficulty;
    // 2D grid of cells
    Cell **grid;
    // Total number of mines on the board
    int mine_count;

} Board;

// Creates a new game board with specified dimensions and mine count
Board *board_create(int rows, int cols, int difficulty, int mines);

// Randomly distributes mines across the board, avoiding the specified cell
void generate_mines(Board *board, int row, int col);

// Calculates the number of neighboring mines for each cell on the board
int calculate_mines_in_neighborhood(Board *board);

// Counts the number of mines in the 3x3 neighborhood of a specific cell
int count_mines(Board *board, int row, int col);

#endif // BOARD_H