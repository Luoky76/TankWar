#ifndef ARTIFICIAL_H
#define ARTIFICIAL_H

#include "tankKinds/enemytank.h"
#include "tankKinds/friendtank.h"
#include "mapStructAndData/mapstruct.h"
#include <QObject>
#include <QRandomGenerator>
#include <QTimer>
#include <QRect>

class Artificial : public QObject
{
    Q_OBJECT
public:
    static Artificial* getInstance(QList <Tank *> *tanks,QObject *parent = nullptr);
    static Artificial* getInstance();
    void startArtificial();
    void stopArtificial();

private:
    static Artificial* instance;
    explicit Artificial(QList <Tank *> *tanks,QObject *parent = nullptr);
    ~Artificial();
    int eplisonToBase;    //敌方坦克移动时，向基地行动的概率，受难度影响
    int eplisonStay;      //坦克静止的概率
    int eplisonForward;   //坦克直接前进的概率
    QList <Tank *> *tanks;  //地图类坦克的引用
    void emitEnemyCommand();
    void emitFriendCommand();
    void setEplison();
    bool canFriendShoot(Tank* tank);  //判断友方坦克能否射击
    QTimer* timer;  //发送命令计时器

signals:

};

#endif // ARTIFICIAL_H
