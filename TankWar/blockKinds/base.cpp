#include "base.h"

Base::Base(int _posX,int _posY,QObject *parent):VisibleObject(_posX,_posY,60,60,parent)
{
    iconPath = ":/Resource/img/wall/base.png";
    blastTimer = new QTimer(this);
}

void Base::blast()
{
    from = 0;
    to = 9;
    blastTimer->start(30);
    connect(blastTimer,&QTimer::timeout,this,[=](){  //实现子弹的爆炸动画
        ++from;
        if (from<=to)
        {
            iconPath = QString(":/Resource/img/fire/%1.png").arg(from);
        }
        else
        {
            blastTimer->stop();
            disconnect(blastTimer,&QTimer::timeout,this,nullptr);
            emit baseDestroyed();
        }
    });
}
