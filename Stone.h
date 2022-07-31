#ifndef _STONE_H_
#define _STONE_H_
class Stone{  //白
    private:
        //属性
        //石の色
        bool StoneColor;
    public:
        //操作
        Stone();
        //settor
        void setStone(bool Color);
        //gettor
        bool getStone();
        //ひっくり返す
        void UpSet();

};
#endif