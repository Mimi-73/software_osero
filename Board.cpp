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

bool isSandwichStone(int Stone,bool player){
    
}