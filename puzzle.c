#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>

#define ROW  1
#define COL  0

/**
 * brute force sudoku puzzle generator
 *
 * attempt #3: start with known puzzle and swap two digits, continue
 * randomly for x amount of time; begin removing digits per latin
 * square - needs algorithm for weighting the difficulty of a puzzle
 * and whether or not it can be solvable. 
 *
 * attempt #2: instead of a constrained model (perhaps leveraging
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
 * discarding rows as I built up an algorithm on the fly to
 * solve this problem. I finally did some real research and
 * learned the scale of this problem. I want to build a 
 * fully working generator, to easily output various puzzles
 * of varying complexity. Perhaps an event-based version will
 * be better; easier to implement the backtrack/callback, graph
 * constraint.
 * 
 * 8/14/14 - does not compile/run correctly
 * 8/17/14 - compiles and generates a completed puzzle
 * 
 * George Craig 
 * Code released under Public Domain.
 * Please see LICENSE.
 */

/* 
 * I wrote a solver that uses brute force, not 'logic', based on the fact that
 * there are only 46,656 (9x6x3x6x4x2x3x2) possible patterns of one number in
 * a 9x9 puzzle. Just generate all of them, eliminate those for each number that
 * are not consistent with the positions of that number, then successively merge
 * non-conflicting patterns across numbers. Requires no look-ahead/backtracking,
 * just match/eliminate. Has 217 lines of Ruby code, and will solve 'hard' puzzles
 * in about 30 seconds on my 5 year old PC.
 * 
 * Posted by: Hal at January 2, 2009 09:07 PM
 * hal.noyes@gmail.com
 */

/**
 * attempt #3: start with a known working puzzle 
 * http://davidbau.com/archives/2006/09/04/sudoku_generator.html
 * http://www.setbb.com/phpbb/viewtopic.php?t=314&mforum=sudoku
 * 
 * - 1. randomly switch two lines(row) in a group or switch two big groups. OR
 * - 2. randomly switch all positions for two numbers, like switch all 1 and 2 
 * - Now you have a valid solution, you just need to get rid of
 *   number from it to create a sudoku.
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
    //int p[] = { 10, 20, 30, 40 };
    //int *pi = &p[0];
    //int *pi = p;
    //while (pi < &p[4])
   
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

/*
static int row_beg = 0;
static int row_end = 0;

static int col_beg = 0;
static int col_end = 0;
*/

/*
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
*/

/*
int which_latin_sq(int row, int col) {

    * stupidly simply lookup table, 
    * optimization later
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

       range rRange = { 0, 0 };
       range cRange = { 0, 0 };

       range *rowRange = &rRange;
       range *colRange = &cRange;

    ls_num = which_latin_sq(row, col);

    if (ls_num == -1) {
        fprintf(stderr, "error finding which latin square");
        exit(EXIT_FAILURE); 
    }

     * another stupid simple temp
     * lookup table
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
*/

int main(void) {

    printf("generating sudoku puzzle ...\n");

    //int *puzzle = &puzzle_matrix[0];
    //print_puzzle(puzzle);

    int *puzzle = puzzle_matrix;
    print_puzzle(puzzle);

    swap_numbers(puzzle, 1, 3);
    swap_numbers(puzzle, 9, 4);

    printf("\n\n");
    print_puzzle(puzzle);

    _getch();
    return EXIT_SUCCESS;
}
