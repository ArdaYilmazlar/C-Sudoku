#include <stdio.h>
#include <stdlib.h>
#include "general.h"

int** create2DIntArray(size_t y, size_t x)
{
    int i;
    int** array;

    array = (int**) malloc(y * sizeof(int*));
    nullCheck(array, "Cannot allocate memory");

    for(i = 0; i < y; i++)
    {
        array[i] = (int*) malloc(x * sizeof(int));
        nullCheck(array, "Cannot allocate memory");
    }
    return array;
}

void fill2DIntArrayWith(int filler, size_t size_y, size_t size_x, int** arr)
{
    int i, j;

    for(i = 0; i < size_y; i++)
    {
        for(j = 0; j < size_x; j++)
        {
            arr[i][j] = filler;
        }
    }
}

void nullCheck(void* ptr, char* errorMessage)
{
    if(ptr == NULL)
    {
        printf("\n%s\n", errorMessage);
        exit(1);
    }
}

void arrayCopier(int** array1, int** array2, int arraySize)
{
    int i, j;
    for(i = 0; i < arraySize; i++)
    {
        for(j = 0; j < arraySize; j++)
        {
            array2[i][j] = array1[i][j];
        }
    }
}

void reverseBool(int** array1, int arraySize)
{
    int i, j;
    for(i = 0; i < arraySize; i++)
    {
        for(j = 0; j < arraySize; j++)
        {
            if(array1[i][j] == 0)
                array1[i][j] = 1;
            else
                array1[i][j] = 0;
        }
    }
}

