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
    while(!flag){
        if(!Pass()){
            board.ShowBoard();
            showPlayer();
            board.StonePlace(player);
        }

        ChangePlayer();
    }

    ShowWinner();
}

bool Game::Pass()
{
    //狭石有無判定で、挟める石がなければターン続行不可としてpass=trueとした上で返り値trueを返す
    if(!board.isSandwichStone(player)){
        printf("パスしました\n");
        if(pass){flag = true;}
        pass=true;
        return true;
    }else{
        pass=false;
        return false;
    }
} 

void Game::ChangePlayer(){
    player = !player;
}

void Game::ShowWinner(){
    int i, j;
    int white = 0, black = 0;

    for(i = 0; i < 8; i++){
        for(j = 0; j < 8; j++){
            if(board.getisStone(i, j) == true){
                if(board.getStoneOnBoard(i, j)){white += 1;} else {black += 1;}
            }
        }
    }

    if(white > black){
        printf("白の勝ちです\n");
    } else if(white < black){
        printf("黒の勝ちです\n");
    } else {
        printf("引き分けです\n");
    }
}

void Game::showPlayer()
{
    if(player){
        printf("白の番です\n");
    } else {
        printf("黒の番です\n");
    }
}