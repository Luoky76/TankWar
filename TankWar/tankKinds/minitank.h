#ifndef MINITANK_H
#define MINITANK_H

#include "enemytank.h"

class MiniTank : public EnemyTank
{
    Q_OBJECT
public:
    MiniTank(int _difficultyLevel,int _posX,int _posY,QObject *parent = nullptr);
};

#endif // MINITANK_H
