#ifndef PLAYWIDGET_H
#define PLAYWIDGET_H

#include "mapStructAndData/mapdatabase.h"
#include "blockKinds/gameblock.h"
#include "bulletKind/bullet.h"
#include "gameparameter.h"
#include "tankKinds/friendtank.h"
#include "tankKinds/enemytank.h"
#include "tankKinds/playertank.h"
#include "blockKinds/gameblock.h"
#include "bulletKind/bullet.h"
#include <QWidget>
#include <QList>
#include <QDebug>
#include <QIcon>
#include <QPainter>
#include <QKeyEvent>
#include <QTimer>

class PlayWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PlayWidget(int _playMode,int _soundLevel,int _difficultyLevel,QWidget *parent = nullptr);

private:
    void closeEvent(QCloseEvent *event) override;
    int playMode;   //单双人模式
    int soundLevel; //音量大小
    int difficultyLevel;    //难度

    int upLeftX;    //将游戏主界面居中放置时左上角点的坐标
    int upLeftY;

    int baseRow;   //基地左上角方块所在行
    int baseColumn;   //基地左上角方块所在列

    int currentKey; //用户最后一次按下的方向键
    int numOfKey;   //用户当前按住的按键数量
    PlayerTank *myTank;   //自己的坦克
    QList <Tank *> tanks; //除自己的坦克外其它所有坦克的指针
    QList <Bullet *> bullets; //所有子弹的指针

    QTimer *timer;   //计时器，在收到键盘事件后不断发出坦克移动信号，直到键盘松开
    QTimer *repaintTimer;   //重绘地图计时器;

    int gameLevel;  //当前关卡等级
    QList <QList<int> > singleMp;   //当前关卡的游戏地图数据
    MapDataBase mp; //游戏地图数据（所有关卡）
    QList <QList <GameBlock *> > gmp; //游戏地图
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void resetGmp();    //根据当前关卡用游戏地图数据加载游戏地图及当前关卡的游戏地图数据
    void respondTankMove(Tank *tank,int toPosX,int toPosY);
    void respondBulletMove(Bullet *bullet,int toPosX,int toPosY);
    void newBullet(Tank *fromTank,int _forward,int _identity,int _posX,int _posY);
    void changeGmp(int row,int column,int transformBlock);  //有方块改变时调用此函数，参数为方块行列，变成的方块类型

signals:
    void sceneClose();
};

#endif // PLAYWIDGET_H
