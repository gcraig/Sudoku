#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * brute force sudoku puzzle generator
 *
 * george craig 
 * code released into the public domain.
 * please see LICENSE
 */

int puzzle_matrix[] = {

    1, 2, 3, 4, 5, 6, 7, 8, 9,
    4, 5, 6, 7, 8, 9, 1, 2, 3,
    7, 8, 9, 1, 2, 3, 4, 5, 6,
    2, 3, 4, 5, 6, 7, 8, 9, 1,
    5, 6, 7, 8, 9, 1, 2, 3, 4,
    8, 9, 1, 2, 3, 4, 5, 6, 7,
    3, 4, 5, 6, 7, 8, 9, 1, 2,
    6, 7, 8, 9, 1, 2, 3, 4, 5,
    9, 1, 2, 3, 4, 5, 6, 7, 8 

}; 

/**
 * swap two numbers throughout the given puzzle
 * matrix; returning the number of swaps
 *
 * TODO: unit test, remove magic number
 */

int swap_numbers(int *puzzle, int num1, int num2) 
{
    int num_swaps = 0;

    while (puzzle < &puzzle_matrix[81])
    {
        if (*puzzle == num1)
        {
            num_swaps++;
            *puzzle = num2;
        }
        else if (*puzzle == num2)
        {
            num_swaps++;
            *puzzle = num1;
        }
        puzzle++;
    }

    return num_swaps;
}

int print_puzzle(int *puzzle)
{
    int i = 0;

    while(puzzle < &puzzle_matrix[81])
    {   
        i++;
        printf("%i ", *puzzle++);
        if ((i % 9) == 0)
            printf("\n");
    }

    return 0;
}

int build_puzzle(int* puzzle)
{
    int num_itr = 0, i = 0, x = 0, y = 0;
    puts("generating sudoku puzzle ...");
    
    srand(time(NULL));
    num_itr = (rand() % 1000000);
    printf("number iterations: %d\n", num_itr);

    for (i = 0; i<num_itr; i++) 
    {
        x = (rand() % 9);
        y = (rand() % 9);
        x++;
        y++;
        /* printf("x = %d, y = %d\n", x, y); */
        swap_numbers(puzzle, x, y);
    }

    puts();
    print_puzzle(puzzle);
    return 0;
}

int main(void) 
{
    int *puzzle = puzzle_matrix;
    build_puzzle(puzzle);
    return EXIT_SUCCESS;
}
