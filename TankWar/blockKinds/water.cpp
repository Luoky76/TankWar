#include "water.h"

Water::Water(int _posX,int _posY,QObject *parent):GameBlock(_posX,_posY,parent)
{
    iconPath = ":/Resource/img/wall/water.png";
    canTankThrough = true;
    canBulletThrough = true;
    canDestroy = false;
    isUponTank = false;
    speed = 2;
}
