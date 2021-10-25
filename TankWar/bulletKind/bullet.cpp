#include "bullet.h"
#include "gameparameter.h"
#include <QTimer>
#include <QDebug>
#include <QPixmap>
#include <QObject>

Bullet::Bullet(int _forward,int _identity,int _posX,int _posY,QObject *parent):VisibleObject(parent)
{
    //设置子弹的尺寸
    objWidth = bulletWidth;
    objHeight = bulletHeight;
    iconPath = ":/Resource/img/fire/friendMissile.png";
    forward = _forward;
    identity = _identity;
    posX = _posX;
    posY = _posY;
    unitDis = 10;
    damage = 1;     //子弹伤害为1
    moveTime = 30;

    timer = new QTimer();
    timer->start(moveTime);
    connect(timer,&QTimer::timeout,[=](){   //每当计时到了就发送前进请求信号
        timer->stop();  //等移动响应结束后再继续计时
        switch (forward) {
            case Bullet::up: emit queryMove(this,posX,posY-unitDis); break;
            case Bullet::right: emit queryMove(this,posX+unitDis,posY); break;
            case Bullet::down: emit queryMove(this,posX,posY+unitDis); break;
            case Bullet::left: emit queryMove(this,posX-unitDis,posY); break;
            default: break;
        }
    });
    blastTimer = new QTimer();
    connect(blastTimer,&QTimer::timeout,[=](){  //实现子弹的爆炸动画
        ++from;
        if (from<=to)
        {
            iconPath = QString(":/Resource/img/fire/%1.png").arg(from);
        }
        else
        {
            blastTimer->stop();
            emit bulletDestroyed(this);
        }
    });
}

void Bullet::bulletMove(int toPosX, int toPosY)
{
    posX = toPosX;
    posY = toPosY;
    timer->start(moveTime);
}

void Bullet::blast()
{
    from = 0;
    to = 9;
    blastTimer->start(30);
}

void Bullet::setMoveTime(int newMoveTime)
{
    moveTime = newMoveTime;
    timer->start(moveTime);
}

void Bullet::setIcon(QString newIconPath)
{
    iconPath = newIconPath;
}
