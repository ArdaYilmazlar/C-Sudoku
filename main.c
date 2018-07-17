#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include "sudokuCreator.h"
#include "general.h"
#include "boardOperators.h"


//Miscellaneous


/*
COLOR OF NUMBERS
0 = Yellow
1 = White
2 = Red
3 = Green
*/



int main()
{
    srand(time(NULL));

    coordinates* highLighter = malloc(sizeof(coordinates));
    nullCheck(highLighter, "Cannot allocate memory for highlighter!");

    boardOperators board;

    board.accessable = create2DIntArray(9, 9);
    board.colorOfNumbers = create2DIntArray(9, 9);
    board.visibility = create2DIntArray(9, 9);
    board.inputableSudoku = create2DIntArray(10, 9);
    board.realSudoku = create2DIntArray(9, 9);


    fill2DIntArrayWith(0, 9, 9, board.accessable);
    fill2DIntArrayWith(0, 9, 9, board.colorOfNumbers);
    fill2DIntArrayWith(0, 9, 9, board.visibility);


    int difficulty = askForDifficulty();

    setVisibility(difficulty, &board, 9);
    sudokuGenerator(board.realSudoku, 9);
    arrayCopier(board.realSudoku, board.inputableSudoku, 9);
    arrayCopier(board.visibility, board.colorOfNumbers, 9);
    arrayCopier(board.visibility, board.accessable, 9);
    reverseBool(board.accessable, 9);

    *highLighter = highLighterStartingPoint(board.accessable, 9);

    while(difficulty)
    {
        system("cls");
        sudokuPrinter(&board, highLighter, 9);
        *highLighter = controls(&board, highLighter);
    }

    sudokuPrinter(&board, highLighter, 9);
    return 0;
}



