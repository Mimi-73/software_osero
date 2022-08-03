#ifndef _BOARD_H_
#define _BOARD_H_

#include "Stone.h"

#define ROW 8  //行
#define COLUMN 8  //列

class Board{

    private:
        //属性
        //盤
        Stone stone[ROW][COLUMN];  //true:白 false:黒
        //石の有無
        bool isStone[ROW][COLUMN]; //true:石有　false:石無
        //白石の数
        int white;
        //黒石の数
        int black;
        //配置可能か 
        bool canStone[ROW][COLUMN];  //true:配置可能 false:配置不可
        //狭石端点記録
        int LineData[8][8][8][3];  //LineData[行][列][方向0~7][端点座標 0:端点有無 1:行 2:列]
    
    public:
        //操作
        Board();
        //盤の指定座標に置かれている石の色を返す
        bool getStoneOnBoard(int Row,int Column);
        //盤の指定座標に石が置かれているか否かを返す
        bool getisStone(int Row, int Column);
        //盤の状態表示
        void ShowBoard();
        //石を配置 & ひっくり返す
        void StonePlace(bool Player);
        //挟石有無判定 & 狭石端点記録
        bool isSandwichStone(bool Player);
        //周りの石の判定
        void isRoundStone(bool *SearchAngle, int row, int column, bool Player);
        //ひっくり返す関数
        void UpSetStone(int row, int column);
        
};
#endif