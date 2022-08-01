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
        //配置可能な石の判定 0:false 1:true
        int canStone[ROW][COLUMN];
    
    public:
        //操作
        Board();
        bool getStoneOnBoard(int Row,int Column);
        bool getisStone(int Row, int Column);
        //盤の状態表示  南
        void ShowBoard();
        //石の配置  //南
        void StonePlace(bool player);
        //挟石有無判定  //原
        bool isSandwichStone(bool player);
        //周りの石の判定
        void isRoundStone(bool *ok, int row, int column, bool player);
        //ひっくり返す石の座標を調べる関数
        void SearchPoint(int Row, int Column, bool player);
        //ひっくり返す関数
        void UpSetStone(int sPoint[2], int ePoint[2]);
        
};
#endif