#include "minitank.h"

MiniTank::MiniTank(int _difficultyLevel,int _posX,int _posY,QObject *parent)
    :EnemyTank(_difficultyLevel,_posX,_posY,parent)
{
    moveTime /= 2;  //轻型坦克移动速度快
    HP = 1;
    score = 100;    //破坏后奖励100分
    pathU = ":/Resource/img/tank/enemy2U.png";
    pathR = ":/Resource/img/tank/enemy2R.png";
    pathD = ":/Resource/img/tank/enemy2D.png";
    pathL = ":/Resource/img/tank/enemy2L.png";
}
