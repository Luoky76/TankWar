#include "playwidget.h"
#include "gameparameter.h"
#include "tankKinds/friendtank.h"
#include "tankKinds/enemytank.h"
#include "tankKinds/heavytank.h"
#include "blockKinds/gameblock.h"
#include "bulletKind/bullet.h"
#include <QDebug>
#include <QIcon>
#include <QVector>
#include <QPainter>
#include <QKeyEvent>
#include <QTimer>

PlayWidget::PlayWidget(int _playMode, int _soundLevel, int _difficultyLevel, QWidget *parent)
    :QWidget(parent)
{
    playMode = _playMode;   //设定属性
    soundLevel = _soundLevel;
    difficultyLevel = _difficultyLevel;
    gameLevel = 3;  //从第一关开始打
    MapStruct::getInstance(&gmp,&tanks,&bullets,this)->setGameLevel(gameLevel);
    MapStruct::getInstance()->setDifficulty(difficultyLevel);

    this->setFixedSize(1456,900);    //固定窗口大小
    this->setWindowIcon(QIcon(":/Resource/img/other/mintank.png"));    //设置图标
    this->setWindowTitle("Tanks War");  //设置标题

    //计算将游戏主界面居中放置时左上角点的坐标
    upLeftX = (this->width()-GameParameter::column*GameBlock::blockWidth)/2;
    upLeftY = (this->height()-GameParameter::row*GameBlock::blockHeight)/2;

    repaintTimer = new QTimer();
    repaintTimer->start(5);    //每5毫秒重绘地图
    connect(repaintTimer,&QTimer::timeout,[=](){
        repaint();
    });

    numOfKey = 0;
    timer = new QTimer();

    //创建玩家的坦克
    PlayerTank* myTank = MapStruct::getInstance()->creatPlayerTank();
    connect(timer,&QTimer::timeout,[=](){   //计时器一到就发送当前按住的按键给自己的坦克
       myTank->keyPressToMove(currentKey);
    });
    connect(this,&PlayWidget::pressToShoot,myTank,&PlayerTank::shoot);
    connect(myTank,&PlayerTank::tankShot,MapStruct::getInstance(),&MapStruct::newBullet);
}

void PlayWidget::closeEvent(QCloseEvent *)
{
    repaintTimer->stop();
    emit sceneClose();
}

void PlayWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this); //创建画图工具
    //绘制地图块
    for (int i=0;i<gmp.count();++i)
    {
        for (int j=0;j<gmp[i].count();++j)
        {
            if (!gmp[i][j]->getIsUponTank())    //在坦克底下的先绘制，在坦克上方的先用地板的图片代替
            {
                gmp[i][j]->paintObj(upLeftX,upLeftY,&painter);
            }
            else gmp[i][j]->paintObj(upLeftX,upLeftY,QString(":/Resource/img/wall/floor.png"),&painter);
        }
    }

    //绘制坦克
    for (Tank* i:tanks)
    {
        i->paintObj(upLeftX,upLeftY,&painter);
    }

    //绘制子弹
    for (Bullet* i:bullets)
    {
        i->paintObj(upLeftX,upLeftY,&painter);
    }

    //绘制浮空地图块和基地
    for (int i=0;i<gmp.count();++i)
    {
        for (int j=0;j<gmp[i].count();++j)
        {
            if (gmp[i][j]->getIsUponTank())
            {
                gmp[i][j]->paintObj(upLeftX,upLeftY,&painter);
            }
        }
    }
}

void PlayWidget::keyPressEvent(QKeyEvent *event)
{
    if (!event->isAutoRepeat()) //如果不是键盘按住后自动发出的键盘信号
    {
        //如果按的是方向键，则将按键信息传给玩家坦克
        if (event->key() == Qt::Key_Up || event->key() == Qt::Key_Right || event->key() == Qt::Key_Down || event->key() == Qt::Key_Left
                || event->key() == Qt::Key_W || event->key() == Qt::Key_D || event->key() == Qt::Key_S || event->key() == Qt::Key_A)
        {
            ++numOfKey;
            currentKey = event->key();
            timer->start(5);    //第一次按下方向键时开始计时来给出坦克移动所需的时钟脉冲
        }
    }

    if (event->key() == Qt::Key_0 || event->key() == Qt::Key_Space)
    {
        emit pressToShoot();
    }
}

void PlayWidget::keyReleaseEvent(QKeyEvent *event)
{
    if (!event->isAutoRepeat())
    {
        //如果松开的是方向键
        if (event->key() == Qt::Key_Up || event->key() == Qt::Key_Right || event->key() == Qt::Key_Down || event->key() == Qt::Key_Left
                || event->key() == Qt::Key_W || event->key() == Qt::Key_D || event->key() == Qt::Key_S || event->key() == Qt::Key_A)
        {
            --numOfKey;
            if (numOfKey == 0) timer->stop();   //所有方向键都松开后停止时钟脉冲
        }
    }
}
