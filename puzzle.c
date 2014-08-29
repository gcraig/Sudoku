#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * brute force sudoku puzzle generator
 *
 * (1) no guarantee that the puzzle generated has only one solution
 * (2) -Wall -std=c11 -pedantic -O3
 *
 * george craig 
 * code released into the public domain.
 * please see LICENSE
 */

int puzzle_solution[] = {

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

int puzzle_matrix[81];

/*
const int EASY       = 18; numbers to remove
const int MEDIUM     = 36;
const int HARD       = 54;
const int DIFFICULTY = EASY; TODO: command line option
*/

#define EASY       18 /* numbers to remove */
#define MEDIUM     36
#define HARD       54
#define DIFFICULTY 18 /* TODO: command line option */
#define JSW_RANDOM

#ifdef JSW_RANDOM
/* include prototypes of custom random generator */
unsigned long jsw_rand (void);
void jsw_seed (unsigned long s);
#endif

/**
 * swap two numbers throughout the given puzzle
 * matrix; returning the number of swaps
 *
 * TODO: unit test, remove magic number
 */

 /*
  * There is a stdlib call "rand"; this function is tuned primarily for speed
  * and distribution, not for unpredictability. Almost all built-in random 
  * functions for various languages and frameworks use this function by 
  * default. There are also "cryptographic" random number generators that are
  * much less predictable, but run much slower. These should be used in any sort
  * of security-related application. - tylerl
  * http://stackoverflow.com/questions/822323/how-to-generate-a-random-number-in-c
  */

int swap_numbers(int *puzzle, int num1, int num2) 
{
    int num_swaps = 0;

    while (puzzle < &puzzle_solution[81])
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

    while(puzzle < &puzzle_solution[81])
    {   
        i++;
        printf("%i ", *puzzle++);
        if ((i % 9) == 0)
            printf("\n");
    }

    return 0;
}

int print_matrix(int *matrix)
{
    int i = 0;

    while(matrix < &puzzle_matrix[81])
    {   
        i++;
        printf("%i ", *matrix++);
        if ((i % 9) == 0)
            printf("\n");
    }

    return 0;
}

void remove_values(int* matrix)
{
	puts("remove values...");

	/* number of removed numbers */
	int nr = DIFFICULTY;
	int r;

	for (int j=0; j<81; j++)
	{

		puzzle_matrix[j] = puzzle_solution[j];

		if (nr>0)
		{
			/*
			 * TODO: This has to change, the distribution
			 * of removed values has to be spread across all
			 * latin squares, as it stands now, it will tend
			 * to only remove values from the beginning sequence
			 * of values. ie. the first few rows and first 3
			 * latin squares. Amateur.
			 */
#ifdef JSW_RANDOM
			r = jsw_rand() % 2;
#else
			r = rand() % 2;
#endif
			/* printf("%d\n", r); */
			if (r)
			{
				puzzle_matrix[j] = 0;
				--nr;
			}
		}
		
	}

	print_matrix(matrix);
}

int build_puzzle(int* puzzle, int* matrix)
{
    int num_itr = 0, x = 0, y = 0;
    puts("generating sudoku puzzle ...");

#ifdef JSW_RANDOM
	puts("using jsw_srand()");
    jsw_seed(time(NULL));
	num_itr = (jsw_rand() % 1000000);
#else
	puts("using srand()");
	srand(time(NULL));
	num_itr = (rand() % 1000000);
#endif
    
    printf("number iterations: %d\n", num_itr);

    for (int i = 0; i<num_itr; i++) 
    {
#ifdef JSW_RANDOM
        x = (jsw_rand() % 9);
        y = (jsw_rand() % 9);
#else
        x = (rand() % 9);
        y = (rand() % 9);
#endif
        x++;
        y++;
        /* printf("x = %d, y = %d\n", x, y); */
        swap_numbers(puzzle, x, y);
    }

    puts("\n");
    print_puzzle(puzzle);
	remove_values(matrix);
    return 0;
}

int main(void) 
{
    int *puzzle = puzzle_solution;
	int *matrix = puzzle_matrix;
    build_puzzle(puzzle, matrix);
    return EXIT_SUCCESS;
}
