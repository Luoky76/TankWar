#include "gamestatepusher.h"

GameStatePusher* GameStatePusher::instance = nullptr;

GameStatePusher *GameStatePusher::getInstance()
{
    if (instance == nullptr) instance = new GameStatePusher;
    return instance;
}

void GameStatePusher::setMaxEnemyCnt(int maxEnemyCnt)
{
    this->maxEnemyCnt = maxEnemyCnt;
}

void GameStatePusher::setFriend(bool hasFriend)
{
    this->hasFriend = hasFriend;
}

void GameStatePusher::startGame()
{
    surplusEnemyCnt = maxEnemyCnt;
    aliveEnemyCnt = maxEnemyCnt;
    generatorTimer->start(7000); //每7秒生成敌人
    //generatorTimer->start(700);   //每0.7秒生成敌人，用于测试
    difficulty = MapStruct::getInstance()->getDifficultyLevel();
    setEplison();
    playerLives = 3;    //给玩家3条命
    generatePlayerTank();   //创建玩家坦克
    if (hasFriend)
    {
        friendLives = 1;    //给伙伴1条命
        generateFriendTank();   //创建伙伴坦克
    }

    Artificial::getInstance()->startArtificial();
}

void GameStatePusher::endGame()
{
    qDebug()<<"GameStatePusher开始停止游戏";
    generatorTimer->stop();
    Artificial::getInstance()->stopArtificial();
    qDebug()<<"GameStatePusher成功停止游戏";
}

GameStatePusher::GameStatePusher(QObject *parent)
    : QObject{parent}
{
    generatorTimer = new QTimer(this);
    connect(generatorTimer,&QTimer::timeout,this,&GameStatePusher::generateNewEnemy);   //计时结束创建敌人
    connect(MapStruct::getInstance(),&MapStruct::basementDestroyed,this,[=](){  //收到基地被破坏信号时，判定游戏失败
        qDebug()<<"GameStatePusher判定游戏失败，即将发送gameLose信号";
        emit gameLose();
        qDebug()<<"GameStatePusher判定游戏失败，成功发送gameLose信号";
    });

    //当游戏胜利或失败时，结束游戏（停止计时）
    connect(this,&GameStatePusher::gameWin,this,&GameStatePusher::endGame);
    connect(this,&GameStatePusher::gameLose,this,&GameStatePusher::endGame);
}

GameStatePusher::~GameStatePusher()
{
    this->disconnect();
}

void GameStatePusher::generateNewEnemy()
{
    if (surplusEnemyCnt<=0) //已经生成完所有坦克
    {
        generatorTimer->stop();
        return;
    }
    --surplusEnemyCnt;
    if (surplusEnemyCnt<=0) generatorTimer->stop();

    //随机确定敌方坦克类型
    int randomNum = QRandomGenerator::global()->bounded(100);
    int enemyKind;
    if (randomNum<eplison1) enemyKind = EnemyTank::Heavy_Tank;
    else if (randomNum<eplison2) enemyKind = EnemyTank::Mid_Tank;
    else enemyKind = EnemyTank::Mini_Tank;
    EnemyTank* enemyTank = MapStruct::getInstance()->creatEnemyTank(enemyKind);
    connect(enemyTank,&EnemyTank::tankDestroyed,this,[=](){  //接收到坦克的摧毁信号后扣去存活坦克数
        --aliveEnemyCnt;
        if (aliveEnemyCnt<=0) //玩家消灭了所有敌人
        {
            emit gameWin();
        }
    });
}

void GameStatePusher::generatePlayerTank()
{
    if (playerLives<=0) //玩家失去所有生命数时发送游戏失败信号
    {
        emit gameLose();
        return;
    }
    --playerLives;
    //调用地图类的创建玩家坦克方法
    Tank* myTank = MapStruct::getInstance()->creatPlayerTank();
    //每当玩家坦克被破坏时，再次调用此函数
    connect(myTank,&Tank::tankDestroyed,this,&GameStatePusher::generatePlayerTank);
}

void GameStatePusher::generateFriendTank()
{
    if (friendLives<=0) return;
    --friendLives;
    Tank* friendTank = MapStruct::getInstance()->creatFriendTank();
    connect(friendTank,&Tank::tankDestroyed,this,&GameStatePusher::generateFriendTank);
}

void GameStatePusher::setEplison()
{
    switch (difficulty) {
    case 1:
        eplison1 = 20;
        eplison2 = 40;
        break;
    case 2:
        eplison1 = 40;
        eplison2 = 70;
        break;
    case 3:
        eplison1 = 60;
        eplison2 = 90;
        break;
    default:
        eplison1 = 30;
        eplison2 = 60;
        break;
    }
}
