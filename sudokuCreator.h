#ifndef SUDOKUCREATOR_H_INCLUDED
#define SUDOKUCREATOR_H_INCLUDED

void sudokuGenerator(int** arr, int arraySize); //randomly fills an 2d array using sudoku rules
int arrayCheckerX(int** arr, int currentArraySizeY, int currentArraySizeX); //y is constant, compares given x with other numbers that come before it in 2d array
int arrayCheckerY(int** arr, int currentArraySizeY, int currentArraySizeX); //x is constant, compares given y with other numbers that come before it in 2d array
int sudokuRuleCheck(int** arr, int arraySizeY, int arraySizeX); //controls 3x9 blocks by splitting them into 3x3 blocks, checks if every block has 1-9 in them
void restarter(int* loop1, int* loop2); //restarts whole sudoku creation process
void restartLine(int* loop1); //restarts only x axis
void restartBatch(int* loop1, int* loop2); //goes back 3 y axis, also x axis is set to 0

#endif // SUDOKUCREATOR_H_INCLUDED
