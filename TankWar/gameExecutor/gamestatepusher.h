#ifndef GAMESTATEPUSHER_H
#define GAMESTATEPUSHER_H

#include "mapStructAndData/mapstruct.h"
#include "tankKinds/enemytank.h"
#include "gameExecutor/artificial.h"
#include <QObject>
#include <QTimer>
#include <QRandomGenerator>

class GameStatePusher : public QObject
{
    Q_OBJECT
public:
    static GameStatePusher* getInstance();
    void setMaxEnemyCnt(int maxEnemyCnt);
    void setFriend(bool hasFriend);  //设置是否有伙伴坦克
    void startGame();  //开始推进游戏

private:
    explicit GameStatePusher(QObject *parent = nullptr);
    ~GameStatePusher();
    int maxEnemyCnt = 20;    //最大敌人数，默认20
    int surplusEnemyCnt;    //待生成敌人数
    int aliveEnemyCnt;  //存活敌人数（包括尚未生成的敌人）
    int difficulty; //游戏难度
    int eplison1;   //学习率，由难度控制，影响重型坦克生成概率
    int eplison2;   //影响中型坦克生成概率
    int playerLives;    //玩家的生命条数
    int friendLives;    //同伴的生命条数
    bool hasFriend = false;     //是否有伙伴坦克

    static GameStatePusher* instance;
    void generateNewEnemy();    //生成一个敌人
    void generatePlayerTank();  //生成玩家坦克
    void generateFriendTank();  //生成伙伴坦克
    void setEplison();  //通过难度确定学习率
    void endGame();    //当游戏胜利或失败时自动停止推进游戏
    QTimer *generatorTimer;  //生成敌人的计时器

signals:
    void gameWin(); //游戏胜利信号
    void gameLose();//游戏失败信号
};

#endif // GAMESTATEPUSHER_H
