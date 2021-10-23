#ifndef GAMEPARAMETER_H
#define GAMEPARAMETER_H

#include <QObject>

class GameParameter : public QObject    //此类不实例化，只用于定义全局参数
{
    Q_OBJECT
public:
    explicit GameParameter(QObject *parent = nullptr);
    const static int totLevel = 5;  //关卡总数

    const static int column = 26;   //游戏关卡地形块的列数
    const static int row = 26;  //游戏关卡地形块的行数

    const static int tankWidth = 60;    //坦克的宽高
    const static int tankHeight = 60;

    const static int up = 0;    //坦克或子弹的不同朝向
    const static int right = 1;
    const static int down = 2;
    const static int left = 3;

    const static int friendTank = 0;    //坦克的不同敌我关系，己方、敌方、中立方
    const static int enemyTank = 1;
    const static int individualTank = 3;

    const static int myTankPosX = 9*30; //己方坦克出生点（相对游戏地图）
    const static int myTankPosY = 24*30;
    const static int friendTankPosX = 13*30;
    const static int friendTankPosY = 24*30;

    const static int bulletWidth = 30;
    const static int bulletHeight = 30;
signals:

};

#endif // GAMEPARAMETER_H
