#ifndef _GAME_H_
#define _GAME_H_

#include "Board.h"

class Game{  //ほわい

    private:
        //盤
        Board board;
    
    public:
        
        //現在のプレイヤー
        bool player;
        //ゲーム終了フラグ
        bool flag;
        //前回のターンでパスが行われていればtrueになる
        bool pass;

    public:
        //コンストラクタ
        Game();
        //実行する
        void play();

    private:
        //パス判定
        bool Pass();
        //プレイヤー交代
        void ChangePlayer(bool player);
        //勝者を表示する
        void ShowWinner();

};
#endif