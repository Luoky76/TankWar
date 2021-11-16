#ifndef MAPSTRUCT_H
#define MAPSTRUCT_H

#include "blockKinds/gameblock.h"
#include "blockKinds/base.h"
#include "bulletKind/bullet.h"
#include "tankKinds/tank.h"
#include "tankKinds/friendtank.h"
#include "tankKinds/enemytank.h"
#include "tankKinds/playertank.h"
#include "tankKinds/minitank.h"
#include "tankKinds/midtank.h"
#include "tankKinds/heavytank.h"
#include "bulletKind/bullet.h"
#include "mapdatabase.h"
#include <QObject>
#include <QList>
#include <QPoint>
#include <QRandomGenerator>
#include <QDebug>

class MapStruct : public QObject
{
    Q_OBJECT
public:
    static MapStruct* getInstance(QList< QList<GameBlock *> > *gameMap,QList<Tank *> *tanks,QList<Bullet *> *bullets,Base** base,QObject *parent = nullptr);    //单例模式
    static MapStruct* getInstance();

    QPoint getBasePos();    //获取基地位置
    QPoint getP1BornPos();  //获取玩家P1的出生点
    QPoint getP2BornPos();  //获取玩家P2的出生点
    void setP1BornPos(QPoint pos);  //设置玩家的出生点
    void setP2BornPos(QPoint pos);
    QPoint getRandomBornPos(int objWith,int objHeight);  //获取随机出生点

    int getDifficultyLevel();
    int getGameLevel();

    PlayerTank* creatPlayerTank(); //创建玩家坦克
    FriendTank* creatFriendTank(); //创建友方坦克
    EnemyTank* creatEnemyTank(int tankKind);   //创建敌方坦克

    void setDifficulty(int difficultyLevel);    //设置游戏难度
    void setGameLevel(int gameLevel);   //设置游戏关卡级别，设置后重置地图
    void resetGmp();    //根据当前关卡用游戏地图数据加载游戏地图及当前关卡的游戏地图数据
    void respondTankMove(Tank *tank,int toPosX,int toPosY);
    void respondBulletMove(Bullet *bullet,int toPosX,int toPosY);
    void newBullet(Tank *fromTank,int _forward,int _identity,int _posX,int _posY);
    void changeBlock(int row,int column,int transformBlock);  //有方块改变时调用此函数，参数为方块行列，变成的方块类型
    void clearAll();    //清除所有地图块、坦克、子弹

private:
    explicit MapStruct(QList< QList<GameBlock *> > *gameMap, QList<Tank *> *tanks, QList<Bullet *> *bullets, Base** base ,QObject *parent = nullptr);
    static MapStruct* instance;
    ~MapStruct();

    QList< QList<GameBlock *> > *gmp;    //地图上的地形块数据，为游戏界面持有的地图的引用
    QList <Tank *> *tanks;   //地图上各坦克的引用
    QList <Bullet *> *bullets;  //地图上各子弹的引用
    Base** base;    //地图上基地的引用
    QPoint basePos;   //记录基地的左上角格所对应的位置
    QPoint p1BornPos; //玩家P1的出生点
    QPoint p2BornPos; //玩家P2的出生点

    int difficultyLevel = 1;    //难度
    int gameLevel = 1;  //当前关卡等级
    QList <QList<int> > singleMp;   //当前关卡的游戏地图数据
    MapDataBase mp; //游戏地图数据（所有关卡）

    void specificCoveredBlock(QRect obj,int &row1,int &row2,int &column1,int &column2); //计算矩形所覆盖的准确行列
    void insideCoveredBlock(QRect obj,int &row1,int &row2,int &column1,int &column2);   //计算矩形所覆盖的地图内行列
    bool canTankOn(QRect pos);
    bool canTankOn(VisibleObject obj);
    bool canBulletOn(QRect pos);
    bool canBulletOn(VisibleObject obj);
    bool outofBoundary(int row,int column); //判断某行某列是否在地图内部（下标从0开始）
    void deleteTank(Tank* tank);    //坦克被破坏时调用此函数清除坦克资源

signals:
    void basementDestroyed();   //基地被破坏信号
};

#endif // MAPSTRUCT_H
