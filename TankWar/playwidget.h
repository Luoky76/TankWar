#ifndef PLAYWIDGET_H
#define PLAYWIDGET_H

#include "mapStructAndData/mapdatabase.h"
#include "mapStructAndData/mapstruct.h"
#include "blockKinds/gameblock.h"
#include "bulletKind/bullet.h"
#include "tankKinds/tank.h"
#include "gameparameter.h"
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
    int gameLevel;  //当前关卡等级

    int upLeftX;    //将游戏主界面居中放置时左上角点的坐标
    int upLeftY;

    int currentKey; //用户最后一次按下的方向键
    int numOfKey;   //用户当前按住的按键数量

    QList <Tank *> tanks; //除自己的坦克外其它所有坦克的指针
    QList <Bullet *> bullets; //所有子弹的指针

    QTimer *timer;   //计时器，在收到键盘事件后不断发出坦克移动信号，直到键盘松开
    QTimer *repaintTimer;   //重绘地图计时器;

    QList <QList <GameBlock *> > gmp; //游戏地图
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

signals:
    void pressToShoot();    //玩家按下了发射按键
    void sceneClose();
};

#endif // PLAYWIDGET_H
