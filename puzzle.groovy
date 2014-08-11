
/*
 * brute force sudoku puzzle generator
 *
 */

/* define puzzle matrix */
def puzzle = new Object[9][9]
Random rnd = new Random()

def inRow(puzzle, rowNum, val) {
    def col = 0..8  
    def used = false
    col.each {i->
        if (puzzle[rowNum][i] == val)
            used = true
    }
    return used
}

def inCol(puzzle, colNum, val) {
    def row = 0..8  
    def used = false
    row.each {i->
        if (puzzle[i][colNum] == val)
            used = true
    }
    return used
}

/* Latin Square */
def inLSq(puzzle, lsNum, val) {

    rowRange = null
    colRange = null
    
    if (lsNum < 3 && lsNum > -1) {
        rowRange = 0..2
        switch(lsNum) 
            0: colRange = 0..2
                break
            1: colRange = 3..5
                break
            2: colRange = 6..8
                break
    }

    if (lsNum < 6 && lsNum > 2) {
        rowRange = 3..5
        switch(lsNum) {
            3: colRange = 0..2
                break
            4: colRange = 3..5
                break
            5: colRange = 6..8
                break
        }
    }

    if (lsNum < 9 && lsNum > 5) {
        rowRange = 6..8
        switch(lsNum) {
            6: colRange = 0..2
                break
            7: colRange = 3..5
                break
            8: colRange = 6..8
                break
        }
    }

    (rowRange).each{i->
      (colRange).each{j->
        if (puzzle[i][j] == val)
            return true
      }
    }

    return false
}

def buildPuzzle() {

    set = false
    
    (rowRange).each{i->
      (colRange).each{j->
      
        while(!set) {
            x = rnd.nextInt(9) + 1
            if (inRow(puzzle, i, x) ||
                inCol(puzzle, j, x) ||
                inLSq(puzzle, 0, x))
                {
                    set = false
                } else {
                    set = true
                    puzzle[i][j] = x
                }
        }
      
       
      } // colRange
    } // rowRange
    
}

buildPuzzle()

//println inRow(puzzle, 0, null)
//println inCol(puzzle, 0, 0)
//println inLatinSquare(puzzle, 0, 0)