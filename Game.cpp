#include "Game.h"
#include <stdio.h>

//コンストラクタ
Game::Game(){
    player=true; //先手:true 後手:false
    flag=false; //trueになったときゲーム終了
    pass=false; //trueの時pass
}

//ゲーム全体の流れをここに書き込む
void Game::play(){


}

void Game::ChangePlayer(bool player){
    //bool を反転する
    player = !player;
}

void Game::ShowWinner(){
    //現在のプレイヤーを勝者として表示する
    if(player==true) printf("勝者は PLAYER1 です");
    else printf("勝者は PLAYER2 です");
}