#include "boardOperators.h"
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>

#define CONSOLE GetStdHandle(STD_OUTPUT_HANDLE)
#define RESET_COLOR SetConsoleTextAttribute(CONSOLE, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

coordinates nextHighLightablePoint(boardOperators* board, coordinates* alreadyHighlightedPoint, char way, int arraySize)
{
    int i, j;
    coordinates highLightablePoint;

    if(way == 'd')
    {
        for(i = alreadyHighlightedPoint->y; i < arraySize; i++)
        {
            for(j = alreadyHighlightedPoint->x + 1; j < arraySize; j++)
            {
                if(board->accessable[i][j] == 1)
                {
                    highLightablePoint.y = i;
                    highLightablePoint.x = j;
                    highLightablePoint.isPresent = 1;
                    return highLightablePoint;
                }
            }
            alreadyHighlightedPoint->x = -1;
        }
        highLightablePoint = highLighterStartingPoint(board->accessable, 9);
    }

    else if(way == 'a')
    {
        for(i = alreadyHighlightedPoint->y; i >= 0; i--)
        {
            for(j = alreadyHighlightedPoint->x - 1; j >= 0; j--)
            {
                if(board->accessable[i][j] == 1)
                {
                    highLightablePoint.y = i;
                    highLightablePoint.x = j;
                    highLightablePoint.isPresent = 1;
                    return highLightablePoint;
                }
            }
            alreadyHighlightedPoint->y = 10;
            alreadyHighlightedPoint->x = 9;
        }
        highLightablePoint = highLighterReverseStartingPoint(board->accessable, 8);
    }
    else
        return *alreadyHighlightedPoint;

    if(highLightablePoint.isPresent == 0)
    {
        checkSolution(board, 9);
        highLightablePoint = highLighterStartingPoint(board->accessable, 9);
    }

    return highLightablePoint;
}

coordinates controls(boardOperators* board, coordinates* highLighter)
{
    char input;
    do
    {
        input = getch();
    }
    while(input != 'a' && input != 'd' && input != '1' && input != '2'
          && input != '3' && input != '4' && input != '5' && input != '6'
          && input != '7' && input != '8' && input != '9' && input != 13); // 13 = ENTER

    if(input != 'a' && input != 'd' && input != 13)
    {
        if(highLighter->isPresent == 1)
        {
        board->inputableSudoku[highLighter->y][highLighter->x] = (int) input - 48;
        board->visibility[highLighter->y][highLighter->x] = 1;
        board->colorOfNumbers[highLighter->y][highLighter->x] = 0;
        return nextHighLightablePoint(board, highLighter, 'd', 9);
        }
    }
    else if (input == 13)
    {
        checkSolution(board, 9);
        if(board->accessable[highLighter->y][highLighter->x] == 0)
        {
            return nextHighLightablePoint(board, highLighter, 'd', 9);
        }
    }
    else //Highlighter goes right or left
    {
        return nextHighLightablePoint(board, highLighter, input, 9);
    }

    return *highLighter;
}


void color(int colorInfo, int isItHighlighted)
{
        switch(colorInfo)
        {
    case 0:
        SetConsoleTextAttribute(CONSOLE, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
        if(isItHighlighted)
            SetConsoleTextAttribute(CONSOLE, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
        break;
    case 1:
        if(isItHighlighted)
            SetConsoleTextAttribute(CONSOLE, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
        break;
    case 2:
        SetConsoleTextAttribute(CONSOLE, FOREGROUND_INTENSITY | FOREGROUND_RED);
        if(isItHighlighted)
            SetConsoleTextAttribute(CONSOLE, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_INTENSITY);
        break;
    case 3:
        SetConsoleTextAttribute(CONSOLE, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
        if(isItHighlighted)
            SetConsoleTextAttribute(CONSOLE, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        break;
        }
}

void sudokuPrinter(boardOperators* board, coordinates* highLighter, int arraySize)
{
    int i, j;

    for (i = 0; i < arraySize; i++)
    {
        if (i == 0)
            puts("=========================================");
            else if(i % 3 == 0)
        {
            puts("||===========||===========||===========||");
        }
        else
            puts("||-----------||-----------||-----------||");

        for(j = 0; j < arraySize; j++)
        {
            if(j % 3 == 0)
                printf("|| ");
            else
            printf("| ");
            if(board->visibility[i][j] == 1)
            {
                if(highLighter->isPresent == 1 && highLighter->x == j && highLighter->y == i)
                {
                    color(board->colorOfNumbers[i][j], 1);
                }
                else
                {
                    color(board->colorOfNumbers[i][j], 0);
                }
                printf("%d", board->inputableSudoku[i][j]);
            }
            else
            {
                if(highLighter->isPresent == 1 && highLighter->x == j && highLighter->y == i)
                {
                     color(board->colorOfNumbers[i][j], 1);
                }
                else
                {
                    color(board->colorOfNumbers[i][j], 0);
                }
                printf(" ");
            }
            RESET_COLOR;
            printf(" ");
        }
        printf("|| \n");
    }
    puts("=========================================");
}

coordinates highLighterStartingPoint(int** arr, int arraySize)
{
    coordinates firstOne;
    int i, j;
    for (i = 0; i < arraySize; i++)
        for(j = 0; j < arraySize; j++)
        {
            if(arr[i][j] == 1)
            {
                firstOne.x = j;
                firstOne.y = i;
                firstOne.isPresent = 1;
                return firstOne;
            }
        }
        firstOne.x = 0;
        firstOne.y = 10;
        firstOne.isPresent = 0;
        return firstOne;
}

coordinates highLighterReverseStartingPoint(int** arr, int arraySize)
{
    coordinates lastOne;
    int i, j;
    for (i = arraySize; i >= 0; i--)
        for(j = arraySize; j >= 0; j--)
        {
            if(arr[i][j] == 1)
            {
                lastOne.x = j;
                lastOne.y = i;
                lastOne.isPresent = 1;
                return lastOne;
            }
        }
        lastOne.x = 0;
        lastOne.y = 10;
        lastOne.isPresent = 0;
        return lastOne;
}


void checkSolution(boardOperators* board, int arraySize)
{
    int i, j, win;
    for(i = 0; i < arraySize; i++)
    {
        for(j = 0; j < arraySize; j++)
        {
            if(board->realSudoku[i][j] == board->inputableSudoku[i][j] && board->accessable[i][j] == 1 && board->visibility[i][j] == 1)
            {
                board->colorOfNumbers[i][j] = 3;
                board->accessable[i][j] = 0;
            }
            else if(board->accessable[i][j] == 1 && board->visibility[i][j] == 1)
            {
                board->colorOfNumbers[i][j] = 2;
            }
        }
    }
    win = countSolvedNumbers(board, 9);
    if(win == 81)
    {
        won();
    }
}

int countSolvedNumbers(boardOperators* board, int arraySize)
{
    int i, j, filledTileNumber = 0;
    for(i = 0; i < arraySize; i++)
        for(j = 0; j < arraySize; j++)
        {
            if(board->accessable[i][j] == 0)
                filledTileNumber++;
        }
    return filledTileNumber;
}

void won()
{
    system("cls");

    printf("                 ,----..                                             ,----..            ,--.\n");
    printf("                /   /   \\                                   .---.   /   /   \\         ,--.'|\n");
    printf("        ,---,  /   .     :          ,--,                   /. ./|  /   .     :    ,--,:  : |\n");
    printf("       /_ ./| .   /   ;.  \\       ,'_ /|               .--'.  ' ; .   /   ;.  \\,`--.'`|  ' : \n");
    printf(" ,---, |  ' :.   ;   /  ` ;  .--. |  | :              /__./ \\ : |.   ;   /  ` ;|   :  :  | |\n");
    printf("/___/ \\.  : |;   |  ; \\ ; |,'_ /| :  . |          .--'.  '   \\' .;   |  ; \\ ; |:   |   \\ | :\n");
    printf(" .  \\  \\ ,' '|   :  | ; | '|  ' | |  . .         /___/ \\ |    ' '|   :  | ; | '|   : '  '; |\n");
    printf("  \\  ;  `  ,'.   |  ' ' ' :|  | ' |  | |         ;   \\  \\;      :.   |  ' ' ' :'   ' ;.    ;\n");
    printf("   \\  \\    ' '   ;  \\; /  |:  | | :  ' ;          \\   ;  `      |'   ;  \\; /  ||   | | \\   |\n");
    printf("    '  \\   |  \\   \\  ',  / |  ; ' |  | '           .   \\    .\\  ; \\   \\  ',  / '   : |  ; .'\n");
    printf("     \\  ;  ;   ;   :    /  :  | : ;  ; |            \\   \\   ' \\ |  ;   :    /  |   | '`--' \n");
    printf("      :  \\  \\   \\   \\ .'   '  :  `--'   \\            :   '  |--\"    \\   \\ .'   '   : |     \n");
    printf("       \\  ' ;    `---`     :  ,      .-./             \\   \\ ;        `---`     ;   |.'      \n");
    printf("        `--`                `--`----'                  '---\"                   '---'        \n");


    Sleep(10000);
    exit(1);
}



int askForDifficulty()
{
    int difficulty;

    do
    {
    printf("%s", "Select a difficulty from 0 to 4..: ");
    scanf("%d", &difficulty);

    if(difficulty < 0 || difficulty > 4)
        puts("Invalid difficulty!");

    }while(difficulty < 0 || difficulty > 4);

    return difficulty;
}

void setVisibility(int difficulty, boardOperators* board, int arraySize)
{
    int i, j;
    for(i = 0; i < arraySize; i++)
    {
        for(j = 0; j < arraySize; j++)
        {
            if ((rand() % 8) + 1 > difficulty)
                board->visibility[i][j] = 1;
            else
                board->visibility[i][j] = 0;
        }
    }
}
