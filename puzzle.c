#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* brute force sudoku puzzle generator
 *
 * (1) no verification that the puzzle generated has only one solution
 * (2) -Wall -std=c11 -pedantic -O3
 *
 * george craig 
 * csr development, co.
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
numbers to remove 
#define EASY       18 
#define MEDIUM     36
#define HARD       54
*/

#define DIFFICULTY 18 /* TODO: command line option */

#define JSW_RANDOM
#ifdef JSW_RANDOM
	/* include prototypes of custom random generator */
	unsigned long jsw_rand (void);
	void jsw_seed (unsigned long s);
#endif

/* swap two numbers throughout the given puzzle
 * matrix; returning the number of swaps
 *
 * TODO: unit test, remove magic number
 */
static int swap_numbers(int *puzzle, int num1, int num2) 
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

/* print in a 9x9 grid, the sudoku puzzle
 * as stored as a int[] array of 81 ints.
 * beware of pointer arithmetic 
 */
static void print_grid(int array[])
{
    int i = 0;
	int *p = array;

    while(p < &array[81])
    {   
        i++;

		/* a completed puzzle will contain values 1-9
		 * so this function serves to also print an
		 * unsolved puzzle; if a number is 0 we are
		 * hiding it's value
		 */
		
		if(*p==0) {
			printf("_ ");
			p++;
		} else
			printf("%i ", *p++);

        if ((i % 9) == 0)
            printf("\n");
    }
}

static void pick_values(int* matrix) 
{
    /* number of removed cells per latin square
     * based on difficulty
     */
    int nr = DIFFICULTY / 9;
    for (int i=0; i<9; i++) {
        for (int j=0; j<nr; j++) {
        }
    }
}

/* remove random values from printed grid 
 * for solving by us apes
 */
static void remove_values(int* matrix)
{
	puts("remove values...");

	/* number of removed numbers */
	int nr = DIFFICULTY;
	int r;

    // for each latin square, distribute evenly the number of cells
    // to hide
	for (int j=0; j<81; j++)
	{

        /* obtain random list of cells to hide */
        /* } */

    // for 0 to 81, assign blanks to cells to present puzzle

		puzzle_matrix[j] = puzzle_solution[j];

		if (nr>0)
		{
			/* TODO: This has to change, the distribution
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

	print_grid(puzzle_matrix);
}

/* randomly swap out values, by num_itr,
 * number of iterations, of known solved puzzle;
 * should result in a new (completed) random puzzle
 */
static int build_puzzle(int* puzzle, int* matrix)
{
    int num_itr = 0, x = 0, y = 0;
    puts("generating sudoku puzzle ...");

	/* There is a stdlib call "rand"; this function is tuned primarily for speed
	 * and distribution, not for unpredictability. Almost all built-in random 
	 * functions for various languages and frameworks use this function by 
	 * default. There are also "cryptographic" random number generators that are
	 * much less predictable, but run much slower. These should be used in any sort
	 * of security-related application. - tylerl
	 * http://stackoverflow.com/questions/822323/how-to-generate-a-random-number-in-c
	 */

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

    print_grid(puzzle_solution);
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
