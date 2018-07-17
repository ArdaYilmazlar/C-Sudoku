#include <stdio.h>
#include <stdlib.h>
#include "sudokuCreator.h"


void sudokuGenerator(int** arr, int arraySize)
{
    int i, j, loopcounter = 0, batchloopcounter = 0;
    for(i = 0; i < arraySize; i++)
    {
        for (j = 0; j < arraySize; j++)
        {
          if(i > 0 && j > 0 &&  i % 3 == 0 && j % 3 == 0)
            {
                if (sudokuRuleCheck(arr, i, j) == 0)
                {
                    restartBatch(&i, &j);
                    batchloopcounter++;

                    if(batchloopcounter > 100)
                    {
                        restarter(&i, &j);
                        batchloopcounter = 0;
                    }
                }
            }
                loopcounter = 0;
            do{
                arr[i][j] = (rand() % 9) + 1;
                loopcounter++;
                if(loopcounter > 15)
                {
                    restartLine(&j);
                }
            }while(arrayCheckerX(arr, i, j) != 1 || arrayCheckerY(arr, i, j) != 1);
        }
    }
}

int arrayCheckerX(int** arr, int currentArraySizeY, int currentArraySizeX)
{
    int i;
    for(i = 0; i < currentArraySizeX; i++)
    {
        if(arr[currentArraySizeY][currentArraySizeX] == arr[currentArraySizeY][i])
        {
            return 0;
        }
    }
    return 1;
}

int arrayCheckerY(int** arr, int currentArraySizeY, int currentArraySizeX)
{
    int i;
    for(i = 0; i < currentArraySizeY; i++)
    {
        if(arr[currentArraySizeY][currentArraySizeX] == arr[i][currentArraySizeX])
        {
            return 0;
        }
    }
    return 1;
}

int sudokuRuleCheck(int** arr, int arraySizeY, int arraySizeX)
{
    int check[9] = {0};

    int i, j;

    for (i = arraySizeY - 3; i < arraySizeY; i++)
    {
        for (j = arraySizeX - 3; j < arraySizeX; j++)
        {
            check[(arr[i][j]) - 1] = 1;
        }
    }


    for(i = 0; i < 9; i++)
    {
        if(check[i] == 0)
            return 0;
    }
    return 1;
}

void restarter(int* loop1, int* loop2)
{
    *loop1 = 0;
    *loop2 = 0;
}

void restartLine(int* loop1)
{
    *loop1 = 0;
}

void restartBatch(int* loop1, int* loop2)
{
    *loop1 -= 3;
    *loop2 = 0;
}
