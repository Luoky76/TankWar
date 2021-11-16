#ifndef TANK_H
#define TANK_H

#include "visibleobject.h"
#include "bulletKind/bullet.h"
#include <QTimer>
#include <QObject>

class Tank : public VisibleObject
{
    Q_OBJECT
public:
    const static int tankWidth = 60;    //坦克的宽高
    const static int tankHeight = 60;
    const static int friendSign = 0;    //坦克不同敌我关系，己方、敌方、中立方
    const static int enemySign = 1;
    const static int individualSign = 2;
    const static int up = 0;    //坦克的不同朝向
    const static int right = 1;
    const static int down = 2;
    const static int left = 3;

    //参数：坦克所在X坐标（相对窗口） 坦克所在Y坐标（相对窗口） 父节点
    Tank(int _posX,int _posY,QObject *parent = nullptr);
    ~Tank();
    int getIdentity();
    int getForward();
    int getScore();
    void tankMove(int toPosX,int toPosY,double acce); //通过此函数直接控制坦克移动，acce为坦克加速比
    void tryToShoot();   //尝试发射子弹
    void resetCanShoot();   //调用后坦克可以再次发射子弹
    void blast(int damage); //子弹命中坦克时调用，扣除坦克血量，若血量低于零则坦克爆炸
    void tryToMove(int forward);    //尝试向某方向移动，成功将发送请求信号
    void paintObj(int dx, int dy, QPainter *painter);  //重写绘制函数，实现绘制坦克名

protected:
    int identity;     //敌我标记
    int forward;//坦克朝向
    int unitDis;  //坦克移动的单位距离
    int HP;     //坦克血量
    int score;  //破坏后的得分

    int from;   //用于实现动画
    int to;     //用于实现动画
    QTimer *timer;  //计时器，用于动画

    int moveTime;   //坦克移动的冷却时间（控制坦克真实速度）
    bool canMove;   //允许移动
    bool canShoot; //允许发射子弹

    QString pathU;  //上下左右朝向的图片地址
    QString pathR;
    QString pathD;
    QString pathL;

    QString tankName;   //坦克名字
    void rotate(int nexForward);    //坦克旋转
    void updateTankPixmap();    //根据坦克朝向更新坦克的图案和位置
    void bornAnimation();   //出生动画

signals:
    void queryMove(Tank *tank,int toPosX,int toPosY);   //坦克移动请求信号，参数：坦克编号，去往的坐标
    void tankDestroyed();
    void tankShot(Tank *tank,int _forward,int _identity,int _posX,int _posY);
};

#endif // TANK_H
