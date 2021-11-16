#include "playwidget.h"
#include "widget.h"
#include "gameExecutor/gamestatepusher.h"

PlayWidget* PlayWidget::instance = nullptr;

PlayWidget::PlayWidget(int _playMode, int _soundLevel, int _difficultyLevel, QWidget *parent)
    :QWidget(parent)
{

    playMode = _playMode;   //设定属性
    soundLevel = _soundLevel;
    difficultyLevel = _difficultyLevel;
    gameLevel = 1;  //从第一关开始打

    this->setFixedSize(1456,900);    //固定窗口大小
    this->setWindowIcon(QIcon(":/Resource/img/other/mintank.png"));    //设置图标
    this->setWindowTitle("Tanks War");  //设置标题

    //计算将游戏主界面居中放置时左上角点的坐标
    upLeftX = (this->width()-MapDataBase::column*GameBlock::blockWidth)/2;
    upLeftY = (this->height()-MapDataBase::row*GameBlock::blockHeight)/2;

    repaintTimer = new QTimer();
    repaintTimer->start(5);    //每5毫秒重绘地图
    connect(repaintTimer,&QTimer::timeout,[=](){
        repaint();
    });

    numOfKey = 0;
    timer = new QTimer();
    connect(timer,&QTimer::timeout,this,[=](){  //每当计时结束发送移动按键的信号
        emit pressToMove(currentKey);
    });

    QTimer::singleShot(500,[=](){
        MapStruct::getInstance(&gmp,&tanks,&bullets,&base,this);
        Artificial::getInstance(&tanks,this);
        startGame();
    });   //延迟0.5秒后开始游戏
}

PlayWidget *PlayWidget::getInstance(int _playMode, int _soundLevel, int _difficultyLevel, QWidget *parent)
{
    instance = new PlayWidget(_playMode,_soundLevel,_difficultyLevel,parent);
    return instance;
}

PlayWidget *PlayWidget::getInstance()
{
    return instance;
}

void PlayWidget::startGame()
{
    MapStruct::getInstance()->setGameLevel(gameLevel);
    MapStruct::getInstance()->setDifficulty(difficultyLevel);
    GameStatePusher::getInstance()->setMaxEnemyCnt(19+gameLevel);   //每关多一个敌人
    //GameStatePusher::getInstance()->setMaxEnemyCnt(1+gameLevel);
    //设置是否有伙伴坦克
    if (this->playMode==Widget::doublePlayer)
    {
        GameStatePusher::getInstance()->setFriend(true);
    }
    else
    {
        GameStatePusher::getInstance()->setFriend(false);
    }
    GameStatePusher::getInstance()->startGame();

    connect(GameStatePusher::getInstance(),&GameStatePusher::gameWin,this,[=](){ //游戏胜利时进入下一关
        ++gameLevel;
        qDebug()<<"current gameLevel is "<<gameLevel;
        if (gameLevel>MapDataBase::totLevel) gameLevel = 1;
        disconnect(GameStatePusher::getInstance(),&GameStatePusher::gameWin,this,nullptr);
        startGame();
    });

    connect(GameStatePusher::getInstance(),&GameStatePusher::gameLose,this,[=](){ //游戏失败时，待定
        qDebug()<<"PlayWidget收到了来自GameStatePusher的游戏失败信号，准备结束游戏";  
        disconnect(GameStatePusher::getInstance(),&GameStatePusher::gameLose,this,nullptr);
        endGame();
        qDebug()<<"PlayWidget响应了来自GameStatePusher的游戏失败信号，结束游戏成功";
    });
}

PlayWidget::~PlayWidget()
{
    instance = nullptr;
    timer->stop();
    timer->deleteLater();
    repaintTimer->stop();
    repaintTimer->deleteLater();
    this->disconnect();
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

    //绘制浮空地图块
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

    //绘制基地
    if (base!=nullptr)
    {
        base->paintObj(upLeftX,upLeftY,&painter);
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

void PlayWidget::endGame()
{
    //断开与按键信号连接的槽，不再允许玩家对坦克操作
    disconnect(this,&PlayWidget::pressToShoot,0,0);
    disconnect(this,&PlayWidget::pressToMove,0,0);
    //repaintTimer->stop();   //停止重绘
    QMessageBox::information(this, "提示","   游戏结束   ");
    this->close();
}
