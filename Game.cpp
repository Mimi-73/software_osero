#include "Game.h"
#include "Board.h"
#include <stdio.h>

//コンストラクタ
Game::Game(){
    player=true; //先手:true 後手:false
    flag=false; //trueになったときゲーム終了
    pass=false; //前回のターンでパスが行われていればtrueになる
}

//ゲーム全体の流れをここに書き込む
void Game::play(){


}

bool Game::Pass(){
    //狭石有無判定で、挟める石がなければターン続行不可としてpass=trueとした上で返り値trueを返す
    if(!board.isSandwichStone(player)){
        pass=true;
        return true;
    }else{
        pass=false;
        return false;
    }
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