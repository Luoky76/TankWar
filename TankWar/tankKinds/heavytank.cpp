#include "heavytank.h"
#include <QRandomGenerator>

HeavyTank::HeavyTank(int _difficultyLevel,int _posX,int _posY,QObject *parent)
    :EnemyTank(_difficultyLevel,_posX,_posY,parent)
{
    HP = 3;
    moveTime *= 2;  //重型坦克移动速度慢
    score = 300;    //破坏后奖励300分
    //从4中不同颜色的重型装甲车中随机生成
    int ran = QRandomGenerator::global()->bounded(3,7);
    pathU = QString(":/Resource/img/tank/enemy%1U.png").arg(ran);
    pathR = QString(":/Resource/img/tank/enemy%1R.png").arg(ran);
    pathD = QString(":/Resource/img/tank/enemy%1D.png").arg(ran);
    pathL = QString(":/Resource/img/tank/enemy%1L.png").arg(ran);
}
