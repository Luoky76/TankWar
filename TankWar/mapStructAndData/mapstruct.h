#ifndef MAPSTRUCT_H
#define MAPSTRUCT_H

#include "blockKinds/gameblock.h"
#include "tankKinds/tank.h"
#include <QObject>
#include <QList>
#include <QPoint>
#include <QRandomGenerator>

class MapStruct : public QObject
{
    Q_OBJECT
public:
    explicit MapStruct(QList< QList<GameBlock *> > *gameMap,QList <Tank *> *tanks,QObject *parent = nullptr);
    QPoint getBasePos();    //获取基地位置
    QPoint getP1BornPos();  //获取玩家P1的出生点
    QPoint getP2BornPos();  //获取玩家P2的出生点
    void setP1BornPos(QPoint pos);  //设置玩家的出生点
    void setP2BornPos(QPoint pos);
    QPoint getRandomBornPos();  //获取随机出生点

    void init(int gameLevel);   //根据关卡重建地图


private:
    QList< QList<GameBlock *> > *gameMap;    //地图上的地形块数据，为游戏界面持有的地图的引用
    QList <Tank *> *tanks;   //地图上各坦克的引用
    QPoint basePos;   //记录基地的左上角格所对应的位置
    QPoint p1BornPos; //玩家P1的出生点
    QPoint p2BornPos; //玩家P2的出生点

signals:

};

#endif // MAPSTRUCT_H
