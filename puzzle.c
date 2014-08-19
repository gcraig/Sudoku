#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>

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

int build_puzzle(int* puzzle)
{
    printf("generating sudoku puzzle ...\n");

    //int *puzzle = &puzzle_matrix[0];
    //int *puzzle = puzzle_matrix;
    int num_itr = 0, i = 0, x = 0, y = 0;

    srand(time(NULL));
    num_itr = (rand() % 1000);
    printf("number iterations: %d\n", num_itr);

    for (i = 0; i<num_itr; i++) 
    {
        x = (rand() % 9);
        y = (rand() % 9);
        x++;
        y++;
        //printf("x = %d, y = %d\n", x, y);
        swap_numbers(puzzle, x, y);
    }

    printf("\n");
    print_puzzle(puzzle);
    return 0;
}

int main(void) 
{
    int *puzzle = puzzle_matrix;
    build_puzzle(puzzle);
    return EXIT_SUCCESS;
}
