#ifndef _BOARD_H_
#define _BOARD_H_

#include "Stone.h"

#define ROW 8  //行
#define COLUMN 8  //列

class Board{

    private:
        //属性
        //盤
        int Stone[ROW][COLUMN];  //0:黒 1:白 2:空
        //白石の数
        int white;
        //黒石の数
        int black;
        //配置可能な石の判定 0:false 1:true
        int canStone[ROW][COLUMN];
    
    public:
        //操作
        Board();
        //盤の状態表示  南
        void ShowBoard();
        //石の配置  //南
        void StonePlace(bool player);
        //挟石有無判定  //原
        bool isSandwichStone(bool player);
        //ひっくり返す石の指定　　原
        void UpSetStone(int coodinate[2]);
        
};
#endif