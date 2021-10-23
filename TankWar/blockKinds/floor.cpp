#include "floor.h"

Floor::Floor(int _posX,int _posY,QObject *parent):GameBlock(_posX,_posY,parent)
{
    iconPath = ":/Resource/img/wall/floor.png";
    canTankThrough = true;
    canBulletThrough = true;
    canDestroy = false;
    isUponTank = false;
    speed = 1;
}
