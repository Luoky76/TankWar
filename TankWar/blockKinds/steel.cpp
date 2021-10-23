#include "steel.h"

Steel::Steel(int _posX,int _posY,QObject *parent):GameBlock(_posX,_posY,parent)
{
    iconPath = ":/Resource/img/wall/steel.png";
    canTankThrough = false;
    canBulletThrough = false;
    canDestroy = false;
    isUponTank = false;
    speed = 0;
}
