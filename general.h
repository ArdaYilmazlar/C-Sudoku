#ifndef GENERAL_H_INCLUDED
#define GENERAL_H_INCLUDED

void nullCheck(void* ptr, char* errorMessage);
void fill2DIntArrayWith(int filler, size_t size_y, size_t size_x, int** arr);
int** create2DIntArray(size_t y, size_t x);
void reverseBool(int** array1, int arraySize); //turns 1's to 0's and vice versa
void arrayCopier(int** array1, int** array2, int arraySize); //copies 2d array1 into 2d array2

#endif // GENERAL_H_INCLUDED
