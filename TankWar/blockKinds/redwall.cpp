#include "redwall.h"

Redwall::Redwall(int _posX,int _posY,QObject *parent) : GameBlock(_posX,_posY,parent)
{
    iconPath = ":/Resource/img/wall/redwall.png";
    canTankThrough = false;
    canBulletThrough = false;
    canDestroy = true;
    speed = 0;
    isUponTank = false;
    transformBlock = wall;
}
