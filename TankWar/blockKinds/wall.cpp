#include "wall.h"

Wall::Wall(int _posX,int _posY,QObject *parent):GameBlock(_posX,_posY,parent)
{
    iconPath = ":/Resource/img/wall/wall.png";
    canTankThrough = false;
    canBulletThrough = false;
    canDestroy = true;
    speed = 0;
    isUponTank = false;
    transformBlock = floor;
    score = 100;    //破坏后奖励100分
}
