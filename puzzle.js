/*
 * brute force sudoku puzzle generator
 *
 * george craig 
 * code released into the public domain.
 * please see LICENSE
 */

var puzzle_matrix = [

    1, 2, 3, 4, 5, 6, 7, 8, 9,
    4, 5, 6, 7, 8, 9, 1, 2, 3,
    7, 8, 9, 1, 2, 3, 4, 5, 6,
    2, 3, 4, 5, 6, 7, 8, 9, 1,
    5, 6, 7, 8, 9, 1, 2, 3, 4,
    8, 9, 1, 2, 3, 4, 5, 6, 7,
    3, 4, 5, 6, 7, 8, 9, 1, 2,
    6, 7, 8, 9, 1, 2, 3, 4, 5,
    9, 1, 2, 3, 4, 5, 6, 7, 8 

]; 

function swap_numbers(num1, num2) 
{
    var i;

    for	(i = 0; i < puzzle_matrix.length; i++) 
    {
        if (puzzle_matrix[i] == num1)
        {
            puzzle_matrix[i] = num2;
        } else if (puzzle_matrix[i] == num2)
        {
            puzzle_matrix[i] = num1;
        } 
    }
}

function print_puzzle()
{
    var i = 0;
    var s = '';
    
    for	(i = 0; i < puzzle_matrix.length; i++) 
    {
        if (((i % 9) == 0) && i > 0) {
            s += '\n';
        }
        s += (puzzle_matrix[i]) + ' ';
    }
    
    print(s);
}

function build_puzzle()
{
    var num_itr = 0, i = 0, x = 0, y = 0;
    print('generating sudoku puzzle ...');

    num_itr = Math.floor((Math.random() * 1000000) + 1);
    print('number of iterations ' + num_itr);
    print('\n');
    for (i = 0; i<num_itr; i++) {
        x = Math.floor((Math.random() * 9) + 1);
        y = Math.floor((Math.random() * 9) + 1);
        swap_numbers(x, y);
    }

    print_puzzle();
}

build_puzzle();
