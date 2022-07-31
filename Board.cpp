#include <stdio.h>
#include "Board.h"
#include "Stone.h"

using namespace std;


Board::Board()
{
    for(int i = 0; i < ROW; i++){
        for(int j = 0; j < COLUMN; j++){
            stone[i][j].setStone(NULL);
        }
    }
    
    stone[3][3].setStone(true);
    stone[4][4].setStone(true);
    stone[3][4].setStone(false);
    stone[4][3].setStone(false);
}

void Board::ShowBoard()
{
    printf("   1   2   3   4   5   6   7   8\n");
    
    for(int i = 0; i < ROW; i++){
        printf(" +---+---+---+---+---+---+---+---+\n");
        printf("%d", i+1);
        
        for(int j = 0; j < COLUMN; j++){
            printf("|");
            switch (stone[i][j].getStone())
            {
            case false:
                printf(" ● ");
                break;

            case true:
                printf(" ○ ");
            
            default:
                printf("   ");
                break;
            }
        }

        printf("|\n");
    }
}

void Board::StonePlace(bool Player)
{
    char cinRow, cinColumn;
    int Row, Column;
    int flag1, flag2, wflag = 1;

    while(wflag){
        printf("行を入力 : ");
        scanf("%d", &Row);
        printf("列を入力　 : ");
        scanf("%d", &Column);

        if( (1 <= Row <= 8) && (1 <= Column <= 8) ){
            flag1 = 1;
        } else {
            flag1 = 0;
        }

        if(canStone[Row][Column] == 1){
            flag2 = 1;
        } else {
            flag2 = 0;
        }

        if( (flag1 == 1) && (flag2 == 1) ){
            stone[Row - 1][Column - 1].UpSet();
            wflag = 0;
        } else {
            printf("不正な入力です\n");
        }
    }
}

bool Board::isSandwichStone(bool player)
{
}