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

Tank::~Tank()
{
    timer->stop();
    timer->deleteLater();
    this->disconnect();
}

void Tank::tankMove(int toPosX,int toPosY,double acce)   //无条件移动坦克
{
    posX = toPosX;
    posY = toPosY;
    updateTankPixmap(); //移动后更新图标位置
    canMove = false;
    //移动后必须等待移动冷却结束才能再次移动
    QTimer::singleShot(moveTime/acce,[=](){canMove = true;});
}

void Tank::tryToShoot()
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
    connect(timer,&QTimer::timeout,this,[=](){
        from++;
        if (from>to)
        {
            timer->stop();
            updateTankPixmap();
            canMove = true; //出生完成，允许移动
            canShoot = true;//出生完成，允许开炮
            disconnect(timer,&QTimer::timeout,this,nullptr);    //解除连接
        }
        else iconPath = QString(":/Resource/img/other/born%1.png").arg(from);
    });
}

void Tank::updateTankPixmap()
{
    if (timer->isActive()) return;  //如果当前正在动画（出生，爆炸），则不更新icon
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

int Tank::getScore()
{
    return score;
}

void Tank::resetCanShoot()
{
    canShoot = true;
}

void Tank::blast(int damage)
{
    if (timer->isActive()) return;  //若还在出生动画阶段，则坦克处于无敌状态
    HP-=damage;
    if (HP<=0)
    {
        canMove = false;    //坦克即将爆炸，强制停止移动和发射子弹
        canShoot = false;
        from = 0;
        to = 11;
        timer->start(30);
        connect(timer,&QTimer::timeout,this,[=](){
            from++;
            if (from>to)
            {
                timer->stop();
                canMove = true; //出生完成，允许移动
                canShoot = true;//出生完成，允许开炮
                disconnect(timer,&QTimer::timeout,this,nullptr);    //解除连接
                emit tankDestroyed();   //发送坦克被破坏的信号
            }
            else iconPath = QString(":/Resource/img/fire/blast%1.png").arg(from);
        });
    }
}

void Tank::tryToMove(int forward)
{
    if (forward == this->forward && canMove)   //实现坦克必须先转向再前进
    {
        switch (forward) {
            case Tank::up: emit queryMove(this,posX,posY-unitDis); break;
            case Tank::right: emit queryMove(this,posX+unitDis,posY); break;
            case Tank::down: emit queryMove(this,posX,posY+unitDis); break;
            case Tank::left: emit queryMove(this,posX-unitDis,posY); break;
            default: break;
        }
    }
    else this->forward = forward;
    updateTankPixmap();
}

void Tank::paintObj(int dx, int dy, QPainter *painter)
{
    QPixmap pixmap;
    if (!pixmap.load(iconPath)) return;
    pixmap = pixmap.scaled(objWidth,objHeight);
    painter->drawPixmap(dx+posX,dy+posY,pixmap);
    QFont font("宋体",16,QFont::Bold,true);
    painter->setFont(font);
    painter->setPen(Qt::blue);
    painter->drawText(QRect(dx+posX,dy+posY,this->width(),this->height()),Qt::AlignCenter,tankName);
}
