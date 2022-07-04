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
    printf("   a   b   c   d   e   f   g   h\n");
    
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
        printf("行(英文字)を入力 : ");
        scanf(%c, inRow);
        printf("列(数字)を入力　 : ");
        scanf(%c, inColumn);

        Column = (int)inColumn - 1;

        switch(cinRow){
            case "a":
                Row = 0;
                break;
            case "b":
                Row = 1;
                break;
            case "c":
                Row = 2;
                break;
            case "d":
                Row = 3;
                break;
            case "e":
                Row = 4;
                break;
            case "f":
                Row = 5;
                break;
            case "g";
                Row = 6;
                break;
            case "h":
                Row = 7;
                break;
            default:
                Row = 8;
                break;
        }

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
            Board::UpSetStone(coodinate);
            wflag = 0;
        } else {
            printf("不正な入力です\n");
        }
    }
}