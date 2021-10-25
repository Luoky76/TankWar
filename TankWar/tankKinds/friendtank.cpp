#include "friendtank.h"

FriendTank::FriendTank(int _posX,int _posY,QObject *parent)
    :Tank(_posX,_posY,parent)
{
    identity = Tank::friendTank;
    HP = 1;
    pathU = ":/Resource/img/tank/p2tankU.png";
    pathR = ":/Resource/img/tank/p2tankR.png";
    pathD = ":/Resource/img/tank/p2tankD.png";
    pathL = ":/Resource/img/tank/p2tankL.png";
}
