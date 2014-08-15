#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>

#define TRUE   1
#define FALSE  0

#define ROW  1
#define COL  0

/**
 * brute force sudoku puzzle generator
 *
 * instead of a constrained model (perhaps leveraging
 * graphs) throw out the current random row while
 * creating a puzzle; ಠ_ಠ 
 *
 * this still does not guarantee a single solution;
 *
 * http://4c.ucc.ie/~hsimonis/sudoku.pdf
 * http://uaasoftware.com/?page_id=27
 * http://garethrees.org/2007/06/10/zendoku-generation/
 * http://stackoverflow.com/questions/9730280/sudoku-solver-using-backtracking?rq=1
 *
 * Sudoku puzzle creation is not trivial. 
 * Using a backtrack algorithm Ie., DXL will significantly
 * add complexity to what I thought was a simple problem.
 * This exercise has been fun! I've learned a great deal from
 * thinking it was a simple incremental random number to 
 * discarding rows as I built up an aglorithm on the fly to
 * solve this problem. I finally did some real research and
 * learned the scale of this problem. I want to build a 
 * fully working generator, to easily output various puzzles
 * of varying complexity. 
 * 
 * 8/14/14 - does not compile/run correctly
 * 
 * George Craig 
 * Code released under Public Domain.
 * Please see LICENSE.
 *
 */

static int row_beg = 0;
static int row_end = 0;

static int col_beg = 0;
static int col_end = 0;

int in_row_or_col(
	int puzzle[9][9], 
	int row_col_num, 
	int val, 
	int row_or_col) {

	int i = 0, j = 0, used = FALSE;

	if (puzzle == NULL)
		return FALSE;

    for (i=0; i<9; i++) {

		if (row_or_col)
			j = (puzzle[row_col_num][i] == val);
		else
			j = (puzzle[i][row_col_num] == val);

		if (j)
			used = TRUE;
	}

    return used;
}

int in_row(int puzzle[9][9], int row_num, int val) 
{
	return in_row_or_col(*puzzle, row_num, val, ROW);
}

int in_col(int puzzle[9][9], int col_num, int val) 
{
	return in_row_or_col(*puzzle, col_num, val, COL);
}

int which_latin_sq(int row, int col) {

	/* stupidly simply lookup table, 
	 * optimiaztion later
	 */
    if ( row < 3 && col < 3 )
        return 0;
    if ( row < 3 && col < 6 )
        return 1;
    if ( row < 3 && col < 9 )
        return 2;

    if ( row < 6 && col < 3 )
        return 3; 
    if ( row < 6 && col < 6 )
        return 4; 
    if ( row < 6 && col < 9 )
        return 5; 

    if ( row < 9 && col < 3 )
        return 6; 
    if ( row < 9 && col < 6 )
        return 7; 
    if ( row < 9 && col < 9 )
        return 8; 

	return -1;
}

int in_latin_sq(int puzzle[9][9], int row, int col, int val) {

	int i = 0, j = 0;
	int ls_num = -1;
	
	/*
	range rRange = { 0, 0 };
	range cRange = { 0, 0 };
		
	range *rowRange = &rRange;
	range *colRange = &cRange;
	*/
	
	ls_num = which_latin_sq(row, col);

	if (ls_num == -1) {
		fprintf(stderr, "error finding which latin square");
		exit(EXIT_FAILURE); 
	}
   
	/**
	 * another stupid simple temp
	 * lookup table
 	 */ 
    if (ls_num < 3 && ls_num > -1) {
		row_beg = 0;
		row_end = 2;
        switch(ls_num) {
            case 0: 
				col_beg = 0;
				col_end = 2;
                break;
            case 1: 
				col_beg = 3;
				col_end = 5;
                break;
            case 2: 
				col_beg = 6;
				col_end = 8;
                break;
        }
    }

    if (ls_num < 6 && ls_num > 2) {
		row_beg = 3;
		row_end = 5;
        switch(ls_num) {
            case 0: 
				col_beg = 0;
				col_end = 2;
                break;
            case 1: 
				col_beg = 3;
				col_end = 5;
                break;
            case 2: 
				col_beg = 6;
				col_end = 8;
                break;
        }
    }

    if (ls_num < 9 && ls_num > 5) {
		row_beg = 6;
		row_end = 8;
        switch(ls_num) {
            case 0: 
				col_beg = 0;
				col_end = 2;
                break;
            case 1: 
				col_beg = 3;
				col_end = 5;
                break;
            case 2: 
				col_beg = 6;
				col_end = 8;
                break;
        }
    }
}

void print_puzzle(int puzzle[9][9]) 
{
	int i = 0, j = 0;

	for (i=0; i<9; i++) 
	{
		for (j=0; j<9; j++) 
		{
			printf("%d ", puzzle[i][j]);
		}

		printf("\n");
	}
}
	
/**
 * TODO: Add second counter, throw out rows before throwing out
 * entire puzzle
 */

int build_puzzle(int puzzle[9][9])
{
	int i = 0, j = 0, r = 0, ctr = 0; 

	srand(time(NULL));
	
restart: 

	for (i=0; i<9; i++) 
	{
		for (j=0; j<9; j++) 
		{
			//printf(".");
reguess:
			r = (rand() % 9);
			r++;
			
			if (in_row(puzzle, i, r) || in_col(puzzle, j, r) || in_latin_sq(puzzle, i, j, r))
			{
				/*
				ctr++;
				if (ctr>10000) {
					i = 0;
					j = 0;
					ctr = 0;
					printf("\n**************\n");
					printf("*** RESTART ***");
					printf("\n**************\n");
					goto restart;
				}
				*/

				goto reguess;

				// throw out guess and restart
				if (j!=0)
					--j;
				continue;
			} else {
				puzzle[i][j] = r;	
				//printf(". ");
				printf("%d ", r);
			}
			
			/*
			if (puzzle[i][j] == val
				return TRUE;
			*/
		}

		printf("\n");
		//printf("\nRow Complete ------------------------- %d\n", i);
	}
		
	printf("\n");
	print_puzzle(puzzle);

	return TRUE;
}

int main(void) {
	
	int puzzle_matrix[9][9]; 
	int *puzzle = puzzle_matrix[0];

	printf("generating sudoku puzzle ...\n");
	build_puzzle(puzzle_matrix);

	_getch();
	return EXIT_SUCCESS;
}
