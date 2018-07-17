#ifndef BOARDOPERATORS_H_INCLUDED
#define BOARDOPERATORS_H_INCLUDED

typedef struct
{
    int x;
    int y;
    int isPresent;
}coordinates;

typedef struct
{
    int** realSudoku;
    int** visibility;
    int** inputableSudoku;
    int** colorOfNumbers;
    int** accessable;
}boardOperators;

void sudokuPrinter(boardOperators* board, coordinates* highLighter, int arraySize);
coordinates highLighterStartingPoint(int** arr, int arraySize); //finds first 0 in a 2d array and returns its ((y,x),1) as coordinates (1 being "isVisible")
coordinates nextHighLightablePoint(boardOperators* board, coordinates* alreadyHighlightedPoint, char way, int arraySize);
coordinates highLighterReverseStartingPoint(int** arr, int arraySize);
coordinates controls(boardOperators* board, coordinates* highLighter);
void color(int colorInfo, int isItHighlighted);
void checkSolution(boardOperators* board, int arraySize);
int countSolvedNumbers(boardOperators* board, int arraySize);
int askForDifficulty(); //gets difficulty from user, used to seed setVisibility
void setVisibility(int difficulty, boardOperators* board, int arraySize); //fills a 2d array with 1's and 0's based on difficulty (1 = visible, 0 invisible)
void won();

#endif // BOARDOPERATORS_H_INCLUDED
