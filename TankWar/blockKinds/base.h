#ifndef BASE_H
#define BASE_H

#include "visibleobject.h"
#include <QTimer>

class Base : public VisibleObject
{
    Q_OBJECT
public:
    Base(int _posX,int _posY,QObject *parent = nullptr);
    void blast();   //引爆基地，爆炸结束后发送基地毁坏信号

private:
    QTimer *blastTimer; //计时器，用于爆炸动画
    int from;   //记录爆炸图片的起始编号-1
    int to;     //终止编号

signals:
    void baseDestroyed();   //基地毁坏信号
};

#endif // BASE_H
