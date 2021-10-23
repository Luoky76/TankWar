#include "tank.h"
#include "bulletKind/bullet.h"
#include "gameparameter.h"
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
    forward = GameParameter::up;
    canMove = false;    //等出生完成后再允许移动
    canShoot = false;    //等出生完成后再允许发射子弹，一辆坦克同时只能有一枚子弹在地图上
    objWidth = GameParameter::tankWidth;
    objHeight = GameParameter::tankHeight;
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

void Tank::Shoot()
{
    if (canShoot)
    {
        switch (forward) {   //根据坦克位置和朝向决定子弹的位置
            case GameParameter::up:
                emit tankShot(this,forward,identity,posX+(width()-GameParameter::bulletWidth)/2,posY-GameParameter::bulletHeight);
                break;
            case GameParameter::right:
                emit tankShot(this,forward,identity,posX+width(),posY+(height()-GameParameter::bulletHeight)/2);
                break;
            case GameParameter::down:
                emit tankShot(this,forward,identity,posX+(width()-GameParameter::bulletWidth)/2,posY+height());
                break;
            case GameParameter::left:
                emit tankShot(this,forward,identity,posX-GameParameter::bulletWidth,posY+(height()-GameParameter::bulletHeight)/2);
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
        case GameParameter::up: iconPath = pathU; break;
        case GameParameter::right: iconPath = pathR; break;
        case GameParameter::down: iconPath = pathD; break;
        case GameParameter::left: iconPath = pathL; break;
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
