#include "playertank.h"
#include <QDebug>

PlayerTank::PlayerTank(int _posX,int _posY,QObject *parent)
    :Tank(_posX,_posY,parent)
{
    identity = Tank::friendSign;
    HP = 1;
    pathU = ":/Resource/img/tank/p1tankU.png";
    pathR = ":/Resource/img/tank/p1tankR.png";
    pathD = ":/Resource/img/tank/p1tankD.png";
    pathL = ":/Resource/img/tank/p1tankL.png";
    tankName = "P1";
}

void PlayerTank::keyPressToMove(int key)
{
    int newForward;   //坦克的新朝向
    switch (key) {
    case Qt::Key_W:
    case Qt::Key_Up: newForward = Tank::up; break;    //w或↑
    case Qt::Key_D:
    case Qt::Key_Right: newForward = Tank::right; break;  //d或→
    case Qt::Key_S:
    case Qt::Key_Down: newForward = Tank::down; break;    //s或↓
    case Qt::Key_A:
    case Qt::Key_Left: newForward = Tank::left; break;    //a或←
    default: newForward = Tank::up; break;
    }
    tryToMove(newForward);
}
