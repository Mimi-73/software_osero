#include <stdio.h>
#include "Board.h"
#include "Stone.h"

using namespace std;

Board::Board()
{
    for(int i = 0; i < ROW; i++){
        for(int j = 0; j < COLUMN; j++){
            Stone[i][j] = 2;
        }
    }

    Stone[3][3] = Stone[4][4] = 1;
    Stone[3][4] = Stone[4][3] = 0;

    white = black = 2;
}

void Board::ShowBoard()
{
    printf("   a  b  c  d  e  f  g  h\n");
    
    for(int i = 0; i < ROW; i++){
        printf(" +--+--+--+--+--+--+--+--+\n");
        printf("%d", i+1);
        
        for(int j = 0; j < COLUMN; j++){
            printf("|");
            switch (Stone[i][j])
            {
            case 0:
                printf("●");
                break;

            case 1:
                printf("〇");
            
            default:
                printf("　");
                break;
            }
        }

        printf("|\n");
    }
}