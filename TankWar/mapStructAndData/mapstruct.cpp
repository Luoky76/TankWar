#include "mapstruct.h"

MapStruct::MapStruct(QList<QList<GameBlock *> > *gameMap, QList<Tank *> *tanks, QObject *parent):QObject(parent)
{
    this->gameMap = gameMap;
    this->tanks = tanks;
}

QPoint MapStruct::getBasePos()
{
    return basePos;
}

QPoint MapStruct::getP1BornPos()
{
    return p1BornPos;
}

QPoint MapStruct::getP2BornPos()
{
    return p2BornPos;
}

void MapStruct::setP1BornPos(QPoint pos)
{
    p1BornPos = pos;
}

void MapStruct::setP2BornPos(QPoint pos)
{
    p2BornPos = pos;
}

QPoint MapStruct::getRandomBornPos()    //可能出现在已经有坦克的位置
{
    //不存在地图时返回(-1,-1)
    if (gameMap->count()<=0 || gameMap->at(0).count()<=0) return QPoint(-1,-1);

    //随机生成一个位置，且该位置必位于上半地图
    int blockWidth = gameMap->at(0).count();  //获取地图的长宽
    int blockHeight = gameMap->count();
    int randomNum;
    int randomRow;
    int randomcolum;
    do  //随机生成位置，直到该位置允许坦克通过
    {
        bool flag = true;
        randomNum = QRandomGenerator::global()->bounded(blockHeight*blockWidth/2);
        randomRow = randomNum/blockWidth;   //随机位置所在行
        randomcolum = randomNum%blockWidth; //随机位置所在列
        flag &= gameMap->at(randomRow).at(randomcolum)->getCanTankThrough();

        VisibleObject obj(randomcolum*GameBlock::blockWidth,randomRow*GameBlock::blockHeight,GameParameter::tankWidth,GameParameter::tankHeight);  //创建一个临时块，用于判断是否与现有块冲突
        for (Tank* i:(*tanks))
        {
            flag &= i->isCrashed(&obj);
        }
        if (flag) break;    //随机生成了一个可行的位置
    } while(true);
    return QPoint(randomNum/blockWidth,randomNum%blockWidth);
}
