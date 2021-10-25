#include "tank.h"
#include "bulletKind/bullet.h"
#include <QRandomGenerator>
#include <QTimer>
#include <QKeyEvent>
#include <QDebug>

Tank::Tank(int _posX,int _posY,QObject *parent):VisibleObject(parent)
{
    posX = _posX;
    posY = _posY;
    unitDis = 10; //设置坦克移动的单位距离
    moveTime = 30;  //设置坦克移动的基础冷却时间
    forward = Tank::up;
    canMove = false;    //等出生完成后再允许移动
    canShoot = false;    //等出生完成后再允许发射子弹，一辆坦克同时只能有一枚子弹在地图上
    objWidth = tankWidth;
    objHeight = tankHeight;
    bornAnimation();
}

void Tank::tankMove(int toPosX,int toPosY,double acce)   //无条件移动坦克
{
    posX = toPosX;
    posY = toPosY;
    updateTankPixmap(); //移动后更新图标位置
    canMove = false;
    QTimer::singleShot(moveTime/acce,[=](){canMove = true;});
}

void Tank::shoot()
{
    if (canShoot)
    {
        switch (forward) {   //根据坦克位置和朝向决定子弹的位置
            case Tank::up:
                emit tankShot(this,forward,identity,posX+(width()-Bullet::bulletWidth)/2,posY-Bullet::bulletHeight);
                break;
            case Tank::right:
                emit tankShot(this,forward,identity,posX+width(),posY+(height()-Bullet::bulletHeight)/2);
                break;
            case Tank::down:
                emit tankShot(this,forward,identity,posX+(width()-Bullet::bulletWidth)/2,posY+height());
                break;
            case Tank::left:
                emit tankShot(this,forward,identity,posX-Bullet::bulletWidth,posY+(height()-Bullet::bulletHeight)/2);
                break;
            default:
                break;
        }
        canShoot = false;
    }
}

void Tank::bornAnimation()
{
    from = 0;
    to = 4;
    timer = new QTimer();
    timer->start(200);
    connect(timer,&QTimer::timeout,[=](){
        from++;
        if (from>to)
        {
            timer->stop();
            updateTankPixmap();
            canMove = true; //出生完成，允许移动
            canShoot = true;//出生完成，允许开炮
        }
        else iconPath = QString(":/Resource/img/other/born%1.png").arg(from);
    });
}

void Tank::updateTankPixmap()
{
    switch (forward) {
        case Tank::up: iconPath = pathU; break;
        case Tank::right: iconPath = pathR; break;
        case Tank::down: iconPath = pathD; break;
        case Tank::left: iconPath = pathL; break;
        default: break;
    }
}

int Tank::getIdentity()
{
    return identity;
}

int Tank::getForward()
{
    return forward;
}

void Tank::resetCanShoot()
{
    canShoot = true;
}
