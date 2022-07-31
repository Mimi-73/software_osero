#include "Stone.h"
#include <stdio.h>

Stone::Stone(){
  StoneColor=true; //初期値はtrue=白にしておく
}

void Stone::setStone(bool color){
  StoneColor=color;
}

bool Stone::getStone(){
  return StoneColor;
}

void Stone::UpSet(){
  StoneColor=!StoneColor;
}