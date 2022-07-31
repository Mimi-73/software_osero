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
    int i, j, k, l;
    bool ok[8];
    int canPlaceStone = 0;
    bool flag[8];

    for(i = 0; i < ROW; i++){
        for(j = 0; j < COLUMN; j++){
            if(stone[i][j].getStone() != NULL){
                canStone[i][j] = false;
                break;
            }

            isRoundStone(ok, i, j);

            //上
            if(ok[0] == true){
                for(k = i + 2;k < ROW; k++){
                    if(stone[k][j].getStone() == NULL){   
                        flag[0] = false;
                        break;                  
                    } else if(stone[k][j].getStone() == player){
                        flag[0] = true;
                        break;
                    }
                }
            } else {flag[0] = false;}
            //右上
            if(ok[1] == true){
                k = i + 2;  //行
                l = j + 2;  //列
                while(k < ROW && l < COLUMN){
                    if(stone[k][l].getStone() == NULL){
                        flag[1] = false;
                        break;
                    } else if(stone[k][l].getStone() ==player){
                        flag[1] = true;
                        break;
                    }

                    k++;
                    l++;
                }   
            } else {flag[1] = false;}
            //右
            if(ok[2] == true){
                for(k = j + 2; k < COLUMN; k++){
                    if(stone[i][k].getStone() == NULL){   
                        flag[2] = false;
                        break;                  
                    } else if(stone[i][k].getStone() == player){
                        flag[2] = true;
                        break;
                    }
                }
            } else {flag[2] = false;}
            //右下
            if(ok[3] == true){
                k = i - 2;
                l = j + 2;
                while(k >= 0 && l < COLUMN){
                    if(stone[k][l].getStone() == NULL){   
                        flag[3] = false;
                        break;                  
                    } else if(stone[k][l].getStone() == player){
                        flag[3] = true;
                        break;
                    }                    
                }
            } else {flag[3] = false;}
            //下
            if(ok[4] == true){
                for(k = i - 2; k >= 0; k--){
                    if(stone[k][j].getStone() == NULL){   
                        flag[4] = false;
                        break;                  
                    } else if(stone[k][j].getStone() == player){
                        flag[4] = true;
                        break;
                    }
                }
            } else {flag[4] = false;}
            //左下
            if(ok[5] == true){
                k = i - 2;
                l = j - 2;
                while(k >= 0 && l >= 0){
                    if(stone[k][l].getStone() == NULL){   
                        flag[5] = false;
                        break;                  
                    } else if(stone[k][l].getStone() == player){
                        flag[5] = true;
                        break;
                    }
                }
            } else {flag[5] = false;}
            //左
            if(ok[6] == true){
                for(k = j - 2; k >= 0; k--){
                    if(stone[i][k].getStone() == NULL){   
                        flag[6] = false;
                        break;                  
                    } else if(stone[i][k].getStone() == player){
                        flag[6] = true;
                        break;
                    }                    
                }
            } else {flag[6] = false;}
            //左上
            if(ok[7] == true){
                k = i + 2;
                l = j - 2;
                while(k < ROW && l >= 0){
                    if(stone[k][l].getStone() == NULL){   
                        flag[7] = false;
                        break;                  
                    } else if(stone[k][l].getStone() == player){
                        flag[7] = true;
                        break;
                    }
                }
            } else {flag[7] = false;}

            for(k = 0;k < 8; k++){
                if(flag[k] == true){
                    canStone[i][j] = true;
                    canPlaceStone += 1;
                    break;
                }
            }
            if(canPlaceStone == 0){canStone[i][j]= false;}

            canPlaceStone = 0;

            if(canStone[i][j] == true){
                canPlaceStone += 1;
            }
        }
    }

    if(canPlaceStone != 0){return true;} else {return false;}
}

void Board::isRoundStone(bool *ok, int i, int j)
{
    //上
    if(i + 1 < ROW){
        if(stone[i][j].getStone() != stone[i + 1][j].getStone()){ok[0] = true;} else {ok[0] = false;}
    } else {ok[0] = false;}
    //右上
    if((i + 1 < ROW) && (j + 1 < COLUMN)){
        if(stone[i][j].getStone() != stone[i + 1][j + 1].getStone()){ok[1] = true;} else {ok[1] = false;}
    } else {ok[1] = false;}
    //右
    if(j + 1 < COLUMN){
        if(stone[i][j].getStone() != stone[i][j + 1].getStone()){ok[2] = true;} else {ok[2] = false;}
    } else {ok[2] = false;}
    //右下
    if((i - 1 >= 0) && (j + 1 < COLUMN)){
        if(stone[i][j].getStone() != stone[i - 1][j + 1].getStone()){ok[3] = true;} else {ok[3] = false;}
    } else {ok[3] = false;}
    //下
    if(i - 1 >= 0){
        if(stone[i][j].getStone() != stone[i - 1][j].getStone()){ok[4] = true;} else {ok[4] = false;}
    } else {ok[4] = false;}
    //左下
    if((i - 1 >= 0) && (j - 1 >= 0)){
        if(stone[i][j].getStone() != stone[i - 1][j - 1].getStone()){ok[5] = true;} else {ok[5] = false;}
    } else {ok[5] = false;}
    //左
    if(j - 1 >= 0){
        if(stone[i][j].getStone() != stone[i][j - 1].getStone()){ok[6] = true;} else {ok[6] = false;}
    } else {ok[6] = false;}
    //左上
    if((i + 1 < ROW) && (j - 1 >= 0)){
        if(stone[i][j].getStone() != stone[i + 1][j - 1].getStone()){ok[7] = true;} else {ok[7] = false;}
    } else {ok[7] = false;}
}