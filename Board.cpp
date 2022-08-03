#include <stdio.h>
#include <cstdlib>
#include <string>
#include "Board.h"
#include "Stone.h"

using namespace std;

Board::Board()
{
    for (int i = 0; i < ROW; i++){
        for (int j = 0; j < COLUMN; j++){
            isStone[i][j] = false;

            for (int k = 0; k < 8; k++){
                LineData[i][j][k][0] = 0;
                LineData[i][j][k][1] = 0;
                LineData[i][j][k][2] = 0;
            }
        }
    }

    stone[3][3].setStone(true);
    stone[4][4].setStone(false);
    stone[4][3].setStone(false);
    stone[3][4].setStone(true);
    isStone[3][3] = isStone[4][4] = isStone[4][3] = isStone[3][4] = true;
}

bool Board::getStoneOnBoard(int Row, int Column)
{
    return stone[Row][Column].getStone();
}

bool Board::getisStone(int Row, int Column)
{
    return isStone[Row][Column];
}
void Board::ShowBoard()
{
    printf("   1   2   3   4   5   6   7   8\n");

    for (int i = 0; i < ROW; i++){
        printf(" +---+---+---+---+---+---+---+---+\n");
        printf("%d", i + 1);

        for (int j = 0; j < COLUMN; j++){
            printf("|");
            if (isStone[i][j] == false){
                printf("   ");
            }else if (stone[i][j].getStone()){
                printf(" ● "); //白
            }else if (!stone[i][j].getStone()){
                printf(" ○ "); //黒
            }
        }

        printf("|\n");
    }

    printf(" +---+---+---+---+---+---+---+---+\n");
}

void Board::StonePlace(bool Player)
{       
    char *cinRow=0, *cinColumn=0;
    int Row = 0, Column = 0;

    while (true){
        printf("行を入力 : ");
        scanf(" %s", cinRow);
        printf("列を入力 : ");
        scanf("%*c %s", cinColumn);

        Row = atoi(cinRow); // string->int
        Column = atoi(cinColumn);

        if ((Row >= 1 && Row <= 8) && (Column >= 1 && Column <= 8)){ //入力座標が盤内
            if(canStone[Row-1][Column-1]){  //入力座標が配置可能な位置として記録されている
                isStone[Row - 1][Column - 1] = true;
                stone[Row - 1][Column - 1].setStone(Player);
                UpSetStone(Row - 1, Column - 1); // ひっくり返す
                break;
            }else{
                scanf("%*c");
                printf("不正な入力です\n");
            }
        }else{
            scanf("%*c");
            printf("不正な入力です\n");
        }
    }
}

bool Board::isSandwichStone(bool Player)
{
    bool SearchAngle[8];   //調査する方向
    int canPlaceStone = 0; //石の配置が可能な場所の数
    

    //各変数の初期化
    for (int i = 0; i < ROW; i++){
        SearchAngle[i]=false;
        for (int j = 0; j < COLUMN; j++){
            canStone[i][j] = false;
            for (int k = 0; k < 8; k++){
                LineData[i][j][k][0] = 0;
                LineData[i][j][k][1] = 0;
                LineData[i][j][k][2] = 0;
            }
        }
    }

    for (int i = 0; i < ROW; i++){ //行ループ
        for (int j = 0; j < COLUMN; j++){  //列ループ
            if (isStone[i][j] == true){ //指定座標に既に石がある
            
            }else{
                isRoundStone(SearchAngle, i, j, Player);

                for (int k = 0; k < 8; k++){ //各方向について調査
                    if (SearchAngle[k]){ // k=0:上 1:右上 2:右 3:右下 4:下 5:左下 6:左 7:左上
                        int searchRow = i, searchColumn = j;

                        bool firstLoop[4] = {true,true,true,true}; // 1回目のループならtrue
                        while(true){
                            //座標シフト
                            if (k == 7 || k == 0 || k == 1){ //上方向への座標シフト
                                if (firstLoop[0]){ searchRow -= 2; firstLoop[0] = false; }
                                else{ searchRow--; }
                            }
                            if (k == 3 || k == 4 || k == 5){ //下方向への座標シフト
                                if (firstLoop[1]){ searchRow += 2; firstLoop[1] = false; }
                                else{ searchRow++;}
                            }
                            if (k == 1 || k == 2 || k == 3){ //右方向への座標シフト
                                if (firstLoop[2]){ searchColumn += 2; firstLoop[2] = false; }
                                else{ searchColumn++; }
                            }
                            if (k == 5 || k == 6 || k == 7){ //左方向への座標シフト
                                if (firstLoop[3]){ searchColumn -= 2; firstLoop[3] = false; }
                                else{ searchColumn--; }
                            }

                            if (searchRow < 0 || searchRow > ROW){  //盤外の行ならbreak
                                break;

                            }else if (searchColumn < 0 || searchColumn > COLUMN){  //盤外の列ならbreak
                                break;

                            }else if (isStone[searchRow][searchColumn] == false){ //石が無いならbreak
                                break;

                            }else if (isStone[searchRow][searchColumn] && stone[searchRow][searchColumn].getStone() == Player){ //石がある && それが自分の色
                                canStone[i][j] = true;               //(i,j)には石が置けるものとして記録
                                LineData[i][j][k][0] = 1;            //端点ありと記録
                                LineData[i][j][k][1] = searchRow;    //端点の行を記録
                                LineData[i][j][k][2] = searchColumn; //端点の列を記録
                                break;                               //その方向についての調査終了
                            }
                        }
                    }
                } //方向ループfin
                
            }
            if (canStone[i][j]){
                canPlaceStone++;
                printf("(%d,%d)  ", i + 1, j + 1);
            }
        } //列ループfin
    }     //行ループfin

    printf("設置可能：%d箇所\n", canPlaceStone);

    if (canPlaceStone == 0){ return true; }  //置ける場所がないのでパス
    else{ return false; }
}

void Board::isRoundStone(bool *SearchAngle, int row, int column, bool Player)
{
    for(int direction=0;direction<8;direction++){  //8方向
        
        int searchRow=row;
        int searchColumn=column;
        if(direction==7 || direction==0 || direction==1)searchRow=row-1;  //上方向への座標シフト
        if(direction==3 || direction==4 || direction==5)searchRow=row+1;  //下方向への座標シフト
        if(direction==1 || direction==2 || direction==3)searchColumn=column+1;  //右方向への座標シフト
        if(direction==5 || direction==6 || direction==7)searchColumn=column-1;  //左方向への座標シフト

        if((searchRow<0 || searchRow>=ROW) || (searchColumn<0 && searchColumn>=COLUMN)){  //盤外座標参照のときfalse
            SearchAngle[direction]=false;
        }else{
            if(isStone[searchRow][searchColumn]==false){  //石が存在しないときfalse
                SearchAngle[direction]=false;
            }else if(isStone[searchRow][searchColumn]==true && stone[searchRow][searchColumn].getStone()==Player){  //石が存在しそれが自分の色である場合もfalse
                SearchAngle[direction]=false;
            }else if(isStone[searchRow][searchColumn]==true && stone[searchRow][searchColumn].getStone()!=Player){  //石が存在しそれが自分の色でない場合はtrue
                SearchAngle[direction]=true;
            }
        }
    }
}

void Board::UpSetStone(int row, int column)
{
    int Pos[2]={0,0};  //端点{row,collunm}

    for(int direction=0;direction<8;direction++){
        int def[2]={0,0};  //2点間の差{row,colunm}
        int loop=0;  //loop数(=ひっくり返す石の数)
        int UpSetRow=row,UpSetColumn=column;

        if(LineData[row][column][direction][0]){  //その方向に端点がある
            Pos[0]=LineData[row][column][direction][1];  //row
            Pos[1]=LineData[row][column][direction][2];  //column

            def[0]=Pos[0]-row;
            def[1]=Pos[1]-column;

            if(def[0]==0){ loop=abs(def[1])-1; }  //ひっくり返す石の数は2点間の距離から1を引いた数に等しい
            else{ loop=abs(def[0])-1; }

            for(int i=0;i<loop;i++){
                if(def[0]<0){UpSetRow--;}  //行間の差が負、つまりPos[0]の方が上にあるので上にシフトさせる
                else if(def[0]>0){UpSetRow++;}  //下シフト
                if(def[1]<0){UpSetColumn--;}  //列間の差が負、つまりPos[1]の方が左にあるので左にシフトさせる
                else if(def[1]>0){UpSetColumn++;}  //右シフト

                stone[UpSetRow][UpSetColumn].UpSet();
            }
        }
    }
}