#ifndef _BOARD_H_
#define _BOARD_H_

#include "Stone.h"

class Board{

    private:
        //属性
        //盤
        int Stone[8][8];
        //白石の数
        int white;
        //黒石の数
        int black;
    
    public:
        //操作
        Board();
        //盤の状態表示  //南
        void ShowBoard();
        //石の配置  //南
        void StonePlace(bool player);
        //石の配置可マス存在判定
        bool CanSetStone(bool player);
        //挟石有無判定  //原
        bool isSandwichStone(bool player);
        //ひっくり返す石の指定　　原
        void UpSetStone(int Stone);
        
};
#endif