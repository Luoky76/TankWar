#include "playertank.h"
#include <QDebug>

PlayerTank::PlayerTank(int _posX,int _posY,QObject *parent)
    :Tank(_posX,_posY,parent)
{
    identity = GameParameter::friendTank;
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
        case Qt::Key_Up: forward = GameParameter::up; break;    //w或↑
        case Qt::Key_D:
        case Qt::Key_Right: forward = GameParameter::right; break;  //d或→
        case Qt::Key_S:
        case Qt::Key_Down: forward = GameParameter::down; break;    //s或↓
        case Qt::Key_A:
        case Qt::Key_Left: forward = GameParameter::left; break;    //a或←
        default: break;
    }
    if (forward == preForward && canMove)   //实现坦克必须先转向再前进
    {
        switch (forward) {
            case GameParameter::up: emit queryMove(this,posX,posY-unitDis); break;
            case GameParameter::right: emit queryMove(this,posX+unitDis,posY); break;
            case GameParameter::down: emit queryMove(this,posX,posY+unitDis); break;
            case GameParameter::left: emit queryMove(this,posX-unitDis,posY); break;
            default: break;
        }
    }
    updateTankPixmap();
}
