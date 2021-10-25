#ifndef BULLET_H
#define BULLET_H

#include "visibleobject.h"
#include <QTimer>
#include <QObject>

class Bullet : public VisibleObject
{
    Q_OBJECT
public:
    const static int bulletWidth = 30;  //子弹的默认宽高
    const static int bulletHeight = 30;
    const static int up = 0;    //子弹的不同朝向
    const static int right = 1;
    const static int down = 2;
    const static int left = 3;

    Bullet(int _forward,int _identity,int _posX,int _posY,QObject *parent = nullptr);
    void bulletMove(int toPosX,int toPosY);  //无条件移动子弹
    void blast();   //无条件引爆子弹
    void setMoveTime(int newMoveTime);
    void setIcon(QString newIconPath);

protected:
    int identity;     //敌我标记
    int forward;    //子弹朝向
    int unitDis;  //子弹前进的单位距离
    int damage; //子弹能造成的伤害
    int moveTime;   //子弹前进的时间间隔
    QTimer *timer;  //计时器，用于发出子弹前进所需时钟脉冲
    QTimer *blastTimer; //计时器，用于子弹爆炸动画
    int from;   //记录爆炸图片的起始编号-1
    int to;     //终止编号

signals:
    void queryMove(Bullet *bullet,int toPosX,int toPosY);   //子弹前进请求
    void bulletDestroyed(Bullet *bullet);  //请求毁灭，接收到此信号后应清理子弹内存
};

#endif // BULLET_H
