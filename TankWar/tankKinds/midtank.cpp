#include "midtank.h"

MidTank::MidTank(int _difficultyLevel,int _posX,int _posY,QObject *parent)
    :EnemyTank(_difficultyLevel,_posX,_posY,parent)
{
    HP = 2;
    score = 200;    //破坏后奖励200分
    pathU = ":/Resource/img/tank/enemy1U.png";
    pathR = ":/Resource/img/tank/enemy1R.png";
    pathD = ":/Resource/img/tank/enemy1D.png";
    pathL = ":/Resource/img/tank/enemy1L.png";
}
