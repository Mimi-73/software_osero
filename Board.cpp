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
    printf("   1   2   3   4   5   6   7   8\n");
    
    for(int i = 0; i < ROW; i++){
        printf(" +---+---+---+---+---+---+---+---+\n");
        printf("%d", i+1);
        
        for(int j = 0; j < COLUMN; j++){
            printf("|");
            switch (Stone[i][j])
            {
            case 0:
                printf(" ● ");
                break;

            case 1:
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
    int Row, Column, coodinate[2];
    int flag1, flag2, wflag = 1;

    while(wflag){
        printf("行を入力 : ");
        scanf("%d", &Row);
        printf("列を入力　 : ");
        scanf("%d", &Column);

        coodinate[0] = Row + 1;
        coodinate[1] = Column + 1;

        if( (0 <= Row < 8) && (0 <= Column < 8) ){
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
            //Board::UpSetStone(coodinate);
            wflag = 0;
        } else {
            printf("不正な入力です\n");
        }
    }
}

bool Board::isSandwichStone(bool player)
{

}