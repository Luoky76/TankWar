#include "playertank.h"
#include <QDebug>

PlayerTank::PlayerTank(int _posX,int _posY,QObject *parent)
    :Tank(_posX,_posY,parent)
{
    identity = Tank::friendTank;
    HP = 1;
    pathU = ":/Resource/img/tank/p1tankU.png";
    pathR = ":/Resource/img/tank/p1tankR.png";
    pathD = ":/Resource/img/tank/p1tankD.png";
    pathL = ":/Resource/img/tank/p1tankL.png";
}

void PlayerTank::keyPressToMove(int key)
{
    int preForward = forward;   //记录旋转之前坦克的朝向
    switch (key) {
        case Qt::Key_W:
        case Qt::Key_Up: forward = Tank::up; break;    //w或↑
        case Qt::Key_D:
        case Qt::Key_Right: forward = Tank::right; break;  //d或→
        case Qt::Key_S:
        case Qt::Key_Down: forward = Tank::down; break;    //s或↓
        case Qt::Key_A:
        case Qt::Key_Left: forward = Tank::left; break;    //a或←
        default: break;
    }
    if (forward == preForward && canMove)   //实现坦克必须先转向再前进
    {
        switch (forward) {
            case Tank::up: emit queryMove(this,posX,posY-unitDis); break;
            case Tank::right: emit queryMove(this,posX+unitDis,posY); break;
            case Tank::down: emit queryMove(this,posX,posY+unitDis); break;
            case Tank::left: emit queryMove(this,posX-unitDis,posY); break;
            default: break;
        }
    }
    updateTankPixmap();
}
