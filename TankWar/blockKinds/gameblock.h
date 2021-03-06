#ifndef GAMEBLOCK_H
#define GAMEBLOCK_H
#include "visibleobject.h"
#include <QTimer>
#include <QDebug>
class GameBlock:public VisibleObject
{
    Q_OBJECT
public:
    //用数字指代不同地形块的类型
    const static int floor = 1;
    const static int wall = 2;
    const static int steel = 3;
    const static int grass = 4;
    const static int water = 5;
    const static int redwall = 6;

    const static int blockWidth = 30;   //地图块的默认宽高，单位像素
    const static int blockHeight = 30;

    static GameBlock *gameBlockCreator(int blockKind,int _posX,int _posY,QObject *parent);  //地形块创建工厂

    bool getCanTankThrough();
    bool getCanBulletThrough();
    bool getCanDestroy();
    double getSpeed();
    int getIsUponTank();
    int getTransformBlock();
    int getScore();
    void blast();   //无条件引爆方块并发出毁灭请求
    ~GameBlock();

protected:
    bool canTankThrough;    //坦克能否通过
    bool canBulletThrough;  //子弹能否通过
    bool canDestroy;    //能否被破坏
    bool isUponTank;    //能否覆盖坦克
    double speed;   //坦克在上面行驶的速度倍数
    int transformBlock;//破坏后变成的新方块
    int score;  //破坏后的得分

    QTimer *blastTimer; //计时器，用于爆炸动画
    int from;   //记录爆炸图片的起始编号-1
    int to;     //终止编号
    GameBlock(int _posX,int _posY,QObject *parent = nullptr);

signals:
    void newBlock(GameBlock *gameBlock);   //当方块引爆后发送此信号
};

#endif // GAMEBLOCK_H
