#include "grass.h"

Grass::Grass(int _posX,int _posY,QObject *parent):GameBlock(_posX,_posY,parent)
{
    iconPath = ":/Resource/img/wall/grass.png";
    canTankThrough = true;
    canBulletThrough = true;
    canDestroy = false;
    isUponTank = true;
    speed = 1;
}
