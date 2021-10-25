#ifndef MAPSTRUCT_H
#define MAPSTRUCT_H

#include "blockKinds/gameblock.h"
#include "bulletKind/bullet.h"
#include "tankKinds/tank.h"
#include "tankKinds/friendtank.h"
#include "tankKinds/enemytank.h"
#include "tankKinds/playertank.h"
#include "bulletKind/bullet.h"
#include "mapdatabase.h"
#include <QObject>
#include <QList>
#include <QPoint>
#include <QRandomGenerator>
#include <QTimer>
#include <QDebug>

class MapStruct : public QObject
{
    Q_OBJECT
public:
    static MapStruct* getInstance(QList< QList<GameBlock *> > *gameMap,QList<Tank *> *tanks,QList<Bullet *> *bullets,QObject *parent = nullptr);    //单例模式
    static MapStruct* getInstance();

    QPoint getBasePos();    //获取基地位置
    QPoint getP1BornPos();  //获取玩家P1的出生点
    QPoint getP2BornPos();  //获取玩家P2的出生点
    void setP1BornPos(QPoint pos);  //设置玩家的出生点
    void setP2BornPos(QPoint pos);
    QPoint getRandomBornPos();  //获取随机出生点

    PlayerTank* creatPlayerTank(); //创建玩家坦克
    void setDifficulty(int difficultyLevel);    //设置游戏难度
    void setGameLevel(int gameLevel);   //设置游戏关卡级别，设置后重置地图
    void resetGmp();    //根据当前关卡用游戏地图数据加载游戏地图及当前关卡的游戏地图数据
    void respondTankMove(Tank *tank,int toPosX,int toPosY);
    void respondBulletMove(Bullet *bullet,int toPosX,int toPosY);
    void newBullet(Tank *fromTank,int _forward,int _identity,int _posX,int _posY);
    void changeBlock(int row,int column,int transformBlock);  //有方块改变时调用此函数，参数为方块行列，变成的方块类型

private:
    explicit MapStruct(QList< QList<GameBlock *> > *gameMap,QList<Tank *> *tanks,QList<Bullet *> *bullets,QObject *parent = nullptr);
    static MapStruct* instance;

    QList< QList<GameBlock *> > *gmp;    //地图上的地形块数据，为游戏界面持有的地图的引用
    QList <Tank *> *tanks;   //地图上各坦克的引用
    QList <Bullet *> *bullets;  //地图上各子弹的引用
    QPoint basePos;   //记录基地的左上角格所对应的位置
    QPoint p1BornPos; //玩家P1的出生点
    QPoint p2BornPos; //玩家P2的出生点

    int difficultyLevel = 1;    //难度
    int gameLevel = 1;  //当前关卡等级
    QList <QList<int> > singleMp;   //当前关卡的游戏地图数据
    MapDataBase mp; //游戏地图数据（所有关卡）

    void clearAll();    //清除所有地图块、坦克、子弹
    void coveredBlock(QRect obj,int &row1,int &row2,int &column1,int &column2); //计算可见物件所覆盖的行列

signals:

};

#endif // MAPSTRUCT_H
