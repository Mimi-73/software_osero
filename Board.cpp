#include <stdio.h>
#include <cstdlib>
#include "Board.h"
#include "Stone.h"

using namespace std;

Board::Board()
{
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COLUMN; j++)
        {
            isStone[i][j] = false;

            for (int k = 0; k < 8; k++)
            {
                LineData[i][j][k][0] = 0;
                LineData[i][j][k][1] = 0;
                LineData[i][j][k][2] = 0;
            }
        }
    }

    stone[3][3].setStone(true);
    stone[4][4].setStone(true);
    stone[3][4].setStone(false);
    stone[4][3].setStone(false);

    isStone[3][3] = isStone[4][4] = isStone[3][4] = isStone[4][3] = true;
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

    for (int i = 0; i < ROW; i++)
    {
        printf(" +---+---+---+---+---+---+---+---+\n");
        printf("%d", i + 1);

        for (int j = 0; j < COLUMN; j++)
        {
            printf("|");
            if (isStone[i][j] == false)
            {
                printf("   ");
            }
            else if (stone[i][j].getStone())
            {
                printf(" ○ "); //白
            }
            else if (!stone[i][j].getStone())
            {
                printf(" ● "); //黒
            }
        }

        printf("|\n");
    }

    printf(" +---+---+---+---+---+---+---+---+\n");
}

void Board::StonePlace(bool Player)
{
    char cinRow, cinColumn;
    int Row = 0, Column = 0;

    while (true)
    {
        printf("行を入力 : ");
        scanf(" %c", &cinRow);
        printf("列を入力 : ");
        scanf(" %c", &cinColumn);

        Row = int(cinRow) - 48; // char->int
        Column = int(cinColumn) - 48;

        if (((Row >= 1 && Row <= 8) && (Column >= 1 && Column <= 8)) && canStone[Row][Column]) //入力座標が盤内 && 入力座標が配置可能な位置として記録されている
        {
            isStone[Row - 1][Column - 1] = true;
            stone[Row - 1][Column - 1].setStone(Player);
            SearchPoint(Row - 1, Column - 1, Player); // Search->UpSetでひっくり返す
            printf("(%d,%d)に配置\n", Row, Column);
            break;
        }
        else
        {
            printf("不正な入力です\n");
        }
    }
}

bool Board::isSandwichStone(bool player)
{
    // LineDataの初期化
    for (int i = 0; i < ROW; i++){
        for (int j = 0; j < COLUMN; j++){
            for (int k = 0; k < 8; k++){
                LineData[i][j][k][0] = 0;
                LineData[i][j][k][1] = 0;
                LineData[i][j][k][2] = 0;
            }
        }
    }

    bool SearchAngle[8];   //調査する方向
    int canPlaceStone = 0; //石の配置が可能な場所の数
    int searchRow = 0, searchColumn = 0;

    for (int i = 0; i < ROW; i++){ //行ループ
        for (int j = 0; j < COLUMN; j++){  //列ループ
            canStone[i][j] = false; //初期化

            if (isStone[i][j] == true)
            { //指定座標に既に石がある
                printf("(%d,%d)には石があるよ\n", i + 1, j + 1);
            }
            else
            {
                isRoundStone(SearchAngle, i, j, player);

                for (int k = 0; k < 8; k++)
                { //各方向について調査
                    if (SearchAngle[k])
                    { // k=0:上 1:右上 2:右 3:右下 4:下 5:左下 6:左 7:左上

                        //座標シフト
                        bool firstLoop = true; // 1回目のループならtrue
                        if (k == 7 || k == 0 || k == 1){ //上方向への座標シフト
                            if (firstLoop){ searchRow = i + 2; firstLoop = false; }
                            else{ searchRow++; }
                        }
                        if (k == 3 || k == 4 || k == 5){ //下方向への座標シフト
                            if (firstLoop){ searchRow = i - 2; firstLoop = false; }
                            else{ searchRow--;}
                        }
                        if (k == 1 || k == 2 || k == 3){ //右方向への座標シフト
                            if (firstLoop){ searchColumn = j + 2; firstLoop = false; }
                            else{ searchColumn++; }
                        }
                        if (k == 5 || k == 6 || k == 7){ //左方向への座標シフト
                            if (firstLoop){ searchColumn = j - 2; firstLoop = false; }
                            else{ searchColumn--; }
                        }

                        if (searchRow < 0 || searchRow >= ROW)break; //盤外の行ならbreak
                        if (searchColumn < 0 || searchColumn >= COLUMN)break; //盤外の列ならbreak

                        if (isStone[searchRow][searchColumn] == false){ //石がない
                            break; //その方向についての調査終了

                        }else if (isStone[searchRow][searchColumn] && stone[searchRow][searchColumn].getStone() == player){ //石がある && それが自分の色
                            canStone[i][j] = true;               //(i,j)には石が置けるものとして記録
                            LineData[i][j][k][0] = 1;            //端点ありと記録
                            LineData[i][j][k][1] = searchRow;    //端点の行を記録
                            LineData[i][j][k][2] = searchColumn; //端点の列を記録
                            break;                               //その方向についての調査終了
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

    if (canPlaceStone == 0){
        return true; //置ける場所がないのでパス
    }else{
        return false;
    }
}

void Board::isRoundStone(bool *SearchAngle, int i, int j, bool player)
{
    //上
    if (i + 1 < ROW)
    {
        if ((isStone[i + 1][j] == true) && (stone[i + 1][j].getStone() != player))
        {
            SearchAngle[0] = true;
        }
        else
        {
            SearchAngle[0] = false;
        }
    }
    else
    {
        SearchAngle[0] = false;
    }
    //右上
    if ((i + 1 < ROW) && (j + 1 < COLUMN))
    {
        if ((isStone[i + 1][j + 1] == true) && (stone[i + 1][j + 1].getStone() != player))
        {
            SearchAngle[1] = true;
        }
        else
        {
            SearchAngle[1] = false;
        }
    }
    else
    {
        SearchAngle[1] = false;
    }
    //右
    if (j + 1 < COLUMN)
    {
        if ((isStone[i][j + 1] == true) && (stone[i][j + 1].getStone() != player))
        {
            SearchAngle[2] = true;
        }
        else
        {
            SearchAngle[2] = false;
        }
    }
    else
    {
        SearchAngle[2] = false;
    }
    //右下
    if ((i - 1 >= 0) && (j + 1 < COLUMN))
    {
        if ((isStone[i - 1][j + 1] == true) && (stone[i - 1][j + 1].getStone() != player))
        {
            SearchAngle[3] = true;
        }
        else
        {
            SearchAngle[3] = false;
        }
    }
    else
    {
        SearchAngle[3] = false;
    }
    //下
    if (i - 1 >= 0)
    {
        if ((isStone[i - 1][j] == true) && (stone[i - 1][j].getStone() != player))
        {
            SearchAngle[4] = true;
        }
        else
        {
            SearchAngle[4] = false;
        }
    }
    else
    {
        SearchAngle[4] = false;
    }
    //左下
    if ((i - 1 >= 0) && (j - 1 >= 0))
    {
        if ((isStone[i - 1][j - 1] == true) && (stone[i - 1][j - 1].getStone() != player))
        {
            SearchAngle[5] = true;
        }
        else
        {
            SearchAngle[5] = false;
        }
    }
    else
    {
        SearchAngle[5] = false;
    }
    //左
    if (j - 1 >= 0)
    {
        if ((isStone[i][j - 1] == true) && (stone[i][j - 1].getStone() != player))
        {
            SearchAngle[6] = true;
        }
        else
        {
            SearchAngle[6] = false;
        }
    }
    else
    {
        SearchAngle[6] = false;
    }
    //左上
    if ((i + 1 < ROW) && (j - 1 >= 0))
    {
        if ((isStone[i + 1][j - 1] == true) && (stone[i + 1][j - 1].getStone() != player))
        {
            SearchAngle[7] = true;
        }
        else
        {
            SearchAngle[7] = false;
        }
    }
    else
    {
        SearchAngle[7] = false;
    }
}

void Board::SearchPoint(int Row, int Column, bool player)
{
    int i, j, k, l, count = 0;
    bool SearchAngle[8];
    int EnZahyou[8][2];
    int StZahyou[2]; // 0:行 1:列

    isRoundStone(SearchAngle, Row, Column, player);
    StZahyou[0] = Row;
    StZahyou[1] = Column;

    //上
    if (SearchAngle[0] == true)
    {
        for (k = i + 2; k < ROW; k++)
        {
            if (isStone[k][j])
            {
                if (stone[k][j].getStone() == player)
                {
                    EnZahyou[0][0] = k;
                    EnZahyou[0][1] = j;
                    Board::UpSetStone(StZahyou, EnZahyou[0]);
                    break;
                }
            }
            else
            {
                break;
            }
        }

        /*if(isStone[k][j] && stone[k][j].getStone() == player){

        }*/
        printf("c\n"); //こっちは表示されない
    }
    //右上
    if (SearchAngle[1] == true)
    {
        k = i + 2; //行
        l = j + 2; //列
        while (k < ROW && l < COLUMN)
        {
            printf("%d %d\n", Row, Column);
            if (isStone[k][l])
            {
                if (stone[k][l].getStone() == player)
                {
                    EnZahyou[1][0] = k;
                    EnZahyou[1][1] = l;
                    Board::UpSetStone(StZahyou, EnZahyou[1]);
                    break;
                }
            }
            k++;
            l++;
        }
    }
    //右
    if (SearchAngle[2] == true)
    {
        for (k = j + 2; k < COLUMN; k++)
        {
            if (isStone[i][k])
            {
                if (stone[i][k].getStone() == player)
                {
                    EnZahyou[2][0] = i;
                    EnZahyou[2][1] = k;
                    Board::UpSetStone(StZahyou, EnZahyou[2]);
                    break;
                }
            }
        }
    }
    //右下
    if (SearchAngle[3] == true)
    {
        k = i - 2;
        l = j + 2;
        while (k >= 0 && l < COLUMN)
        {
            if (isStone[k][l])
            {
                if (stone[k][l].getStone() == player)
                {
                    EnZahyou[3][0] = k;
                    EnZahyou[3][1] = l;
                    Board::UpSetStone(StZahyou, EnZahyou[3]);
                    break;
                }
            }
            k--;
            l++;
        }
    }
    //下
    if (SearchAngle[4] == true)
    {
        for (k = i - 2; k >= 0; k--)
        {
            if (isStone[k][j])
            {
                if (stone[k][j].getStone() == player)
                {
                    EnZahyou[4][0] = k;
                    EnZahyou[4][1] = j;
                    Board::UpSetStone(StZahyou, EnZahyou[4]);
                    break;
                }
            }
        }
    }
    //左下
    if (SearchAngle[5] == true)
    {
        k = i - 2;
        l = j - 2;
        while (k >= 0 && l >= 0)
        {
            if (isStone[k][l])
            {
                if (stone[k][l].getStone() == player)
                {
                    EnZahyou[2][0] = k;
                    EnZahyou[2][1] = l;
                    Board::UpSetStone(StZahyou, EnZahyou[5]);
                    break;
                }
            }
            k--;
            l--;
        }
    }
    //左
    if (SearchAngle[6] == true)
    {
        for (k = j - 2; k >= 0; k--)
        {
            if (isStone[i][k])
            {
                if (stone[i][k].getStone() == player)
                {
                    EnZahyou[2][0] = i;
                    EnZahyou[2][1] = k;
                    Board::UpSetStone(StZahyou, EnZahyou[6]);
                    break;
                }
            }
        }
    }
    //左上
    if (SearchAngle[7] == true)
    {
        k = i + 2;
        l = j - 2;
        while (k < ROW && l >= 0)
        {
            if (isStone[k][l])
            {
                if (stone[k][l].getStone() == player)
                {
                    EnZahyou[2][0] = k;
                    EnZahyou[2][1] = l;
                    Board::UpSetStone(StZahyou, EnZahyou[7]);
                    break;
                }
            }
            k++;
            l--;
        }
    }
}

void Board::UpSetStone(int sPoint[2], int ePoint[2])
{
    int i = 0, j = 0, k = 1, loop = 0;
    int def_a = 0, def_b = 0;

    def_a = sPoint[0] - ePoint[0];
    def_b = sPoint[1] - ePoint[1];

    if (def_a == 0)
    {
        loop = abs(def_b);
    }
    else
    {
        loop = abs(def_a);
    }

    if (def_a < 0)
    {
        i = sPoint[0];
    }
    else
    {
        i = ePoint[0];
    }

    if (def_b < 0)
    {
        j = sPoint[1];
    }
    else
    {
        j = ePoint[1];
    }

    while (k < loop)
    {
        stone[i][j].UpSet();
        if (def_a != 0)
            i++;
        if (def_b != 0)
            j++;
        k++;
    }
}