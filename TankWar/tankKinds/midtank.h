#ifndef MIDTANK_H
#define MIDTANK_H

#include "enemytank.h"

class MidTank : public EnemyTank
{
    Q_OBJECT
public:
    MidTank(int _difficultyLevel,int _posX,int _posY,QObject *parent = nullptr);
};

#endif // MIDTANK_H
