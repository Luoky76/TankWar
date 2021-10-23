#ifndef HEAVYTANK_H
#define HEAVYTANK_H

#include "enemytank.h"

class HeavyTank : public EnemyTank
{
    Q_OBJECT
public:
    HeavyTank(int _difficultyLevel,int _posX,int _posY,QObject *parent = nullptr);
};

#endif // HEAVYTANK_H
