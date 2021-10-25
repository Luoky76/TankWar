#include "gameblock.h"
#include "blockKinds/base.h"
#include "blockKinds/floor.h"
#include "blockKinds/grass.h"
#include "blockKinds/steel.h"
#include "blockKinds/wall.h"
#include "blockKinds/water.h"
#include "blockKinds/redwall.h"

GameBlock::GameBlock(int _posX,int _posY,QObject *parent):VisibleObject(parent)
{
    posX = _posX;
    posY = _posY;
    objWidth = blockWidth;
    objHeight = blockHeight;

    blastTimer = new QTimer(this);
    connect(blastTimer,&QTimer::timeout,[=](){  //实现子弹的爆炸动画
        ++from;
        if (from<=to)
        {
            iconPath = QString(":/Resource/img/fire/%1.png").arg(from);
        }
        else
        {
            blastTimer->stop();
            emit newBlock(this);
        }
    });
}

GameBlock *GameBlock::gameBlockCreator(int blockKind,int _posX,int _posY,QObject *parent)
{
    switch (blockKind) {   //逐个创建地图块
        case floor:
            return (GameBlock *) new Floor(_posX,_posY,parent); break;
        case wall:
            return (GameBlock *) new Wall(_posX,_posY,parent); break;
        case water:
            return (GameBlock *) new Water(_posX,_posY,parent); break;
        case steel:
            return (GameBlock *) new Steel(_posX,_posY,parent); break;
        case grass:
            return (GameBlock *) new Grass(_posX,_posY,parent); break;
        case base:
            return (GameBlock *) new Base(_posX,_posY,parent); break;
        case redwall:
            return (GameBlock *) new Redwall(_posX,_posY,parent); break;
        default:
            qDebug()<<"地图中含有未知的方块";
            return nullptr;
            break;
    }
}

void GameBlock::blast()
{
    from = 0;
    to = 9;
    canBulletThrough = true;    //引爆过程中允许子弹通过
    blastTimer->start(30);
}

bool GameBlock::getCanTankThrough()
{
    return canTankThrough;
}

bool GameBlock::getCanBulletThrough()
{
    return canBulletThrough;
}

bool GameBlock::getCanDestroy()
{
    return canDestroy;
}

double GameBlock::getSpeed()
{
    return speed;
}

int GameBlock::getIsUponTank()
{
    return isUponTank;
}

int GameBlock::getTransformBlock()
{
    return transformBlock;
}
