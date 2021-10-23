#include "base.h"

Base::Base(int _posX,int _posY,QObject *parent):GameBlock(_posX,_posY,parent)
{
    iconPath = ":/Resource/img/wall/base.png";
    objWidth = baseWidth;
    objHeight = baseHeight;
    canTankThrough = false;
    canBulletThrough = false;
    canDestroy = true;
    isUponTank = true;
    transformBlock = base;
    speed = 0;
}
