
/*
 * brute force sudoku puzzle generator
 *
 */

/* define puzzle matrix */
def puzzle = new Object[9][9]
Random random = new Random()

/* initialize each cell */
(0..<puzzle.size()).each{i->
  (0..<puzzle[i].size()).each{j->
    assert puzzle[i][j] == null
    puzzle[i][j] = 0
  }
}

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

def inLatinSquare(puzzle, lsNum, val) {
    return false
}

/* check if in row */
println inRow(puzzle, 0, 0)

/* check if in col */
println inCol(puzzle, 0, 0)

println inLatinSquare(puzzle, 0, 0)