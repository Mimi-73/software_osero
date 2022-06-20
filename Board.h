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
        //盤の状態表示
        void ShowBoard();
        //石の配置
        void StonePlace(int Stone,bool player);
        //石の配置可マス存在判定
        bool CanSetStone(bool player);
        //挟石有無判定
        bool isSandwichStone(int Stone,bool player);
        //ひっくり返す石の指定
        void UpSetStone(int Stone);
        
};
#endif