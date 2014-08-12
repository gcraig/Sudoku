#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define TRUE   1
#define FALSE  0

/*
 * brute force sudoku puzzle generator
 *
 * instead of a constrained model (perhaps leveraging
 * graphs) throw out the current random row while
 * creating a puzzle;
 *
 * this still does not guarantee a single solution;
 *
 * http://4c.ucc.ie/~hsimonis/sudoku.pdf
 *
 * c. George Craig. Public Domain.
 *
 */

typedef struct range {
	int lo;
	int hi;
};

int inRow(int **puzzle, int rowNum, int val) 
{
	int col = 8, i = 0, used = FALSE;

	if (puzzle == NULL)
		return FALSE;

    for (i=0; i<9; i++) {
		if (puzzle[rowNum][i] == val)
			used = TRUE;
	}

    return used;
}

int inCol(int **puzzle, int colNum, int val) 
{
	int row = 8, i = 0, used = FALSE;

	if (puzzle == NULL)
		return FALSE;

    for (i=0; i<9; i++) {
		if (puzzle[i][colNum] == val)
			used = TRUE;
	}

    return used;
}

int whichLS(int row, int col) {

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

int inLSq(int **puzzle, int row, int col, int val) {

	int i = 0, j = 0;
	int lsNum = -1;
	range rowRange;
	range colRange;
	
	lsNum = whichLS(row, col);

	if (lsNum == -1) {
		fprintf(stderr, "error finding which latin square");
		exit(EXIT_FAILURE); 
	}
    
    if (lsNum < 3 && lsNum > -1) {
		rowRange.lo = 0;
		rowRange.hi = 2;
        switch(lsNum) {
            case 0: 
				colRange.lo = 0;
				colRange.hi = 2;
                break;
            case 1: 
				colRange.lo = 3;
				colRange.hi = 5;
                break;
            case 2: 
				colRange.lo = 6;
				colRange.hi = 8;
                break;
        }
    }

    if (lsNum < 6 && lsNum > 2) {
		rowRange.lo = 3;
		rowRange.hi = 5;
        switch(lsNum) {
            case 0: 
				colRange.lo = 0;
				colRange.hi = 2;
                break;
            case 1: 
				colRange.lo = 3;
				colRange.hi = 5;
                break;
            case 2: 
				colRange.lo = 6;
				colRange.hi = 8;
                break;
        }
    }

    if (lsNum < 9 && lsNum > 5) {
		rowRange.lo = 6;
		rowRange.hi = 8;
        switch(lsNum) {
            case 0: 
				colRange.lo = 0;
				colRange.hi = 2;
                break;
            case 1: 
				colRange.lo = 3;
				colRange.hi = 5;
                break;
            case 2: 
				colRange.lo = 6;
				colRange.hi = 8;
                break;
        }
    }

	for (i=rowRange.lo; i<rowRange.hi; i++) 
	{
		for (j=colRange.lo; j<colRange.hi; j++) 
		{
			if (TRUE) // puzzle[i][j] == val
				return TRUE;
		}
	}

	return FALSE;
}

main() {
	printf("generating sudoku puzzle ...\n");
	_getch();
}

/*
def buildPuzzle() {

    rowRange = null
    colRange = null

    def puzzle = new Object[9][9]
    Random rnd = new Random()
    
    done = false
    ctr = 1
    
    (0..8).each{row->
      (0..8).each{col->
           
        btrack = 0
          
        while(!done) {
            x = rnd.nextInt(9) + 1
            
            if (
                    inRow(puzzle, row, x) ||
                    inCol(puzzle, col, x) || 
                    inLSq(puzzle, row, col, x)
                
                ) {
            
                done = false
                btrack++
                
                if (btrack > 1) 
                    buildPuzzle()
                
            } else {
            
                puzzle[row][col] = x
                print x + " "
                done = true       
            }
        }
        
        if (ctr % 9 == 0)
            println ""

        done = false
        ctr++
        
      } // colRange
    } // rowRange  
}
*/