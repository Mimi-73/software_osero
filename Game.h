#ifndef _GAME_H_
#define _GAME_H_

#include "Board.h"

class Game{

    private:
        //盤
        Board board;
    
    public:
        //属性
        //現在のプレイヤー
        bool player;
        //ゲーム終了フラグ
        bool flag;

    public:
        //操作
        //実行する
        Game();
        
    private:
        //パス判定
        bool pass;
        //プレイヤー交代
        void ChangePlayer(bool player);
        //勝者を表示する
        void ShowWinner();

};
#endif