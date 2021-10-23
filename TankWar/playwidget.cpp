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

    this->setFixedSize(1456,900);    //固定窗口大小
    this->setWindowIcon(QIcon(":/Resource/img/other/mintank.png"));    //设置图标
    this->setWindowTitle("Tanks War");  //设置标题

    //计算将游戏主界面居中放置时左上角点的坐标
    upLeftX = (this->width()-GameParameter::column*GameBlock::blockWidth)/2;
    upLeftY = (this->height()-GameParameter::row*GameBlock::blockHeight)/2;

    resetGmp();
    repaintTimer = new QTimer();
    repaintTimer->start(5);    //每5毫秒重绘地图
    connect(repaintTimer,&QTimer::timeout,[=](){
        repaint();
    });

    numOfKey = 0;
    timer = new QTimer();
    myTank = new PlayerTank(GameParameter::myTankPosX,GameParameter::myTankPosY,this);
    connect(myTank,&Tank::queryMove,this,&PlayWidget::respondTankMove); //连接坦克的移动请求和游戏窗口的请求响应
    connect(timer,&QTimer::timeout,[=](){   //计时器一到就发送当前按住的按键给自己的坦克
       myTank->keyPressToMove(currentKey);
    });
    connect(myTank,&PlayerTank::tankShot,this,&PlayWidget::newBullet);
}

void PlayWidget::newBullet(Tank *fromTank, int _forward, int _identity, int _posX, int _posY)
{
    Bullet *bullet = new Bullet(_forward,_identity,_posX,_posY,this);
    bullets.append(bullet);

    connect(bullet,&Bullet::bulletDestroyed,[=](){
        for (int i = 0;i<bullets.count();++i)   //从子弹表中把这枚子弹删除
        {
            if (bullets[i] == bullet)
            {
                bullets.erase(bullets.begin()+i);
                break;
            }
        }
        delete bullet;
        fromTank->resetCanShoot();
    });
    connect(bullet,&Bullet::queryMove,this,&PlayWidget::respondBulletMove);
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

    //绘制玩家的坦克
    myTank->paintObj(upLeftX,upLeftY,&painter);

    //绘制其它坦克
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
        myTank->Shoot();
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

void PlayWidget::resetGmp()
{
    for (int i=0;i<gmp.count();++i) //清理旧地图的内存
    {
        for (int j=0;j<gmp[i].count();++j) delete gmp[i][j];
    }
    gmp.clear();
    singleMp.clear();
    singleMp = mp.mData[gameLevel]; //根据关卡调出地图数据
    baseRow = -1;  //重新查找基地坐标
    baseColumn = -1;
    GameBlock* base = nullptr;    //用于暂存基地指针
    QVector <GameBlock *> v;  //v为单行地图
    int currentX = 0;  //用于暂时记录当前方块的位置
    int currentY = 0;
    for (int i=0;i<GameParameter::row;++i)
    {
        v.clear();
        GameBlock *gameBlock;
        for (int j=0;j<GameParameter::column;++j)
        {
            //创建地图块，同时对基地进行特殊处理，只保留一个基地块
            if (singleMp[i][j]!=GameBlock::base)
            {
                gameBlock = GameBlock::gameBlockCreator(singleMp[i][j],currentX,currentY,this);
            }
            else
            {
                if (base==nullptr)
                {
                    gameBlock = GameBlock::gameBlockCreator(singleMp[i][j],currentX,currentY,this);
                    baseRow = i;
                    baseColumn = j;
                    base = gameBlock;
                }
                else gameBlock = base;
            }
            v.push_back(gameBlock);

            connect(gameBlock,&GameBlock::newBlock,[=](GameBlock *block){   //接收地图块改变的信号
                changeGmp(i,j,block->getTransformBlock());
            });
            currentX += GameBlock::blockWidth;
        }
        currentX = 0;
        currentY += GameBlock::blockHeight;
        gmp.push_back(v);
    }
}

void PlayWidget::changeGmp(int row, int column, int transformBlock)
{
    int posX = gmp[row][column]->getPosX();
    int posY = gmp[row][column]->getPosY();
    delete gmp[row][column];
    gmp[row][column] = GameBlock::gameBlockCreator(transformBlock,posX,posY,this);

    //对基地特殊处理
    if (transformBlock==GameBlock::base)
    {
        gmp[row][column+1] = gmp[row][column];
        gmp[row+1][column] = gmp[row][column];
        gmp[row+1][column+1] = gmp[row][column];
    }

    connect(gmp[row][column],&GameBlock::newBlock,[=](GameBlock *block){   //接收地图块改变的信号
        changeGmp(row,column,block->getTransformBlock());
    });
}

void PlayWidget::respondTankMove(Tank *tank, int toPosX, int toPosY)
{
    if (toPosX+tank->width()>GameParameter::column*GameBlock::blockWidth || toPosX<0) return;   //超出边界
    if (toPosY+tank->height()>GameParameter::row*GameBlock::blockHeight || toPosY<0) return;

    //计算坦克四个角所在方块
    int row1,row2,column1,column2;
    row1 = toPosY/GameBlock::blockHeight;
    column1 = toPosX/GameBlock::blockWidth;
    row2 = (toPosY+tank->height())/GameBlock::blockHeight;
    if ((toPosY+tank->height())%GameBlock::blockHeight == 0) row2--;
    column2 = (toPosX+tank->width())/GameBlock::blockWidth;
    if ((toPosX+tank->width())%GameBlock::blockWidth == 0) column2--;

    //坦克所在方块只要有一个不可通行就无法移动坦克
    for (int i=row1;i<=row2;++i)
    {
        for (int j=column1;j<=column2;++j)
        {
            if (!gmp[i][j]->getCanTankThrough()) return;
        }
    }

    //acce为坦克加速比，坦克加速比为所在方块中最慢的方块
    double acce = gmp[row1][column1]->getSpeed();
    for (int i=row1;i<=row2;++i)
    {
        for (int j=column1;j<=column2;++j)
        {
            acce = qMin(acce,gmp[i][j]->getSpeed());
        }
    }

    tank->tankMove(toPosX,toPosY,acce);
}

void PlayWidget::respondBulletMove(Bullet *bullet, int toPosX, int toPosY)
{
    //qDebug()<<toPosX<<" "<<toPosY;

    bool alive = true; //表示子弹是否还存留
    //判断是否超出边界
    if (toPosX+bullet->width()>GameParameter::column*GameBlock::blockWidth || toPosX<0) alive = false;
    if (toPosY+bullet->height()>GameParameter::row*GameBlock::blockHeight || toPosY<0) alive = false;
    if (!alive) {bullet->blast(); return;}

    //计算子弹四个角所在方块
    int row1,row2,column1,column2;
    row1 = toPosY/GameBlock::blockHeight;
    column1 = toPosX/GameBlock::blockWidth;
    row2 = (toPosY+bullet->height())/GameBlock::blockHeight;
    if ((toPosY+bullet->height())%GameBlock::blockHeight == 0) row2--;
    column2 = (toPosX+bullet->width())/GameBlock::blockWidth;
    if ((toPosX+bullet->width())%GameBlock::blockWidth == 0) column2--;

    //所在方块只要有一个不可通行就引爆子弹
    for (int i=row1;i<=row2;++i)
    {
        for (int j=column1;j<=column2;++j)
        {
            if (!gmp[i][j]->getCanBulletThrough())
            {
                alive = false;
                break;
            }
        }
        if (!alive) break;
    }

    //引爆所在方块中可破坏的方块
    for (int i=row1;i<=row2;++i)
    {
        for (int j=column1;j<=column2;++j)
        {
            if (gmp[i][j]->getCanDestroy())
            {
                gmp[i][j]->blast();
            }
        }
    }

    if (alive) bullet->bulletMove(toPosX,toPosY);
    else bullet->blast();
}
