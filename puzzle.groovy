
/*
 * brute force sudoku puzzle generator
 *
 */

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

def whichLS(row, col) {

    if ( row < 3 && col < 3 )
        return 0
    if ( row < 3 && col < 6 )
        return 1 
    if ( row < 3 && col < 9 )
        return 2 

    if ( row < 6 && col < 3 )
        return 3 
    if ( row < 6 && col < 6 )
        return 4 
    if ( row < 6 && col < 9 )
        return 5 

    if ( row < 9 && col < 3 )
        return 6 
    if ( row < 9 && col < 6 )
        return 7 
    if ( row < 9 && col < 9 )
        return 8 
}
        
/* Latin Square */
def inLSq(puzzle, row, col, val) {

    lsNum = whichLS(row, col)
              
    rowRange = null
    colRange = null
    
    if (lsNum < 3 && lsNum > -1) {
        rowRange = 0..2
        switch(lsNum) {
            case 0: colRange = 0..2
                break
            case 1: colRange = 3..5
                break
            case 2: colRange = 6..8
                break
        }
    }

    if (lsNum < 6 && lsNum > 2) {
        rowRange = 3..5
        switch(lsNum) {
            case 3: colRange = 0..2
                break
            case 4: colRange = 3..5
                break
            case 5: colRange = 6..8
                break
        }
    }

    if (lsNum < 9 && lsNum > 5) {
        rowRange = 6..8
        switch(lsNum) {
            case 6: colRange = 0..2
                break
            case 7: colRange = 3..5
                break
            case 8: colRange = 6..8
                break
        }
    }

    (rowRange).each{i->
      (colRange).each{j->
        if (puzzle[i][j] == val)
            print j
            return true
      }
    }

    return false
}

def buildPuzzle() {

    rowRange = null
    colRange = null

    def puzzle = new Object[9][9]
    Random rnd = new Random()
    
    done = false
    
    (0..8).each{row->
      (0..8).each{col->
      
        while(!done) {
            x = rnd.nextInt(9) + 1
            if (inRow(puzzle, row, x) ||
                inCol(puzzle, col, x) ||
                inLSq(puzzle, row, col, x))
                {
                    done = false
                } else {
                    done = true
                    puzzle[row][col] = x
                    //print x + " "
                }
        }
        
        if (col % 9 == 0)
            //println ""

        done = false
       
      } // colRange
    } // rowRange
  
}

buildPuzzle()

//println inRow(puzzle, 0, null)
//println inCol(puzzle, 0, 0)
//println inLatinSquare(puzzle, 0, 0)