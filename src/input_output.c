// Funkcje czytające/wyświetlające w terminalu
#include <stdio.h>
#include "../include/input_output.h"

// wyświetlanie planszy
void print_board(Board *board)
{
    printf("   ");
    for (int i = 0; i < board->cols; i++)
    {
        printf("%2d ", i + 1);
    }
    printf("\n");
    for (int i = 0; i < board->rows; i++)
    {
        printf("%2d ", i + 1);
        for (int j = 0; j < board->cols; j++)
        {
            if (board->grid[i][j].is_revealed)
            {
                if (board->grid[i][j].is_mine)
                {
                    printf(" X ");
                }
                else if (board->grid[i][j].mines_in_neighborhood > 0)
                {
                    printf("%2d ", board->grid[i][j].mines_in_neighborhood);
                }
                else
                {
                    printf("   ");
                }
            }
            else if (board->grid[i][j].is_flagged)
            {
                printf(" F ");
            }
            else
            {
                printf(" . ");
            }
        }
        printf("\n");
    }
}

//zasady gry i mozliwe ruchy
void rules()
{
    printf("Zasady gry:\n");
    printf("1. Gra polega na odkrywaniu pól planszy.\n");
    printf("2. Na planszy znajdują się miny, których liczba zależy od poziomu trudności.\n");
    printf("3. Gracz wygrywa, gdy odkryje wszystkie pola bez min.\n");
    printf("4. Gracz przegrywa, gdy odkryje pole z miną.\n");
    printf("5. Gracz może oznaczać pola flagą.\n");
    printf("6. Gracz wygrywa, gdy oznaczy wszystkie miny.\n");
    printf("7. Gracz przegrywa, gdy oznaczy pole bez miny.\n");
    printf("8. Gracz może odkryć pole wpisując  'r' oraz współrzędne. (np. r 10 8)\n");
    printf("9. Gracz może oznaczyć pole flagą wpisując 'f' oraz współrzędne. (np. f 10 8)\n");
    printf("10. Gracz może usunąć flagę wpisując 'd' oraz współrzędne. (np. d 4 7)\n");
    printf("11. Gracz może zakończyć grę w dowolnym momencie wpisując 'x'.\n\n");
}