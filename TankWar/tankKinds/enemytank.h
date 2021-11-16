#ifndef ENEMYTANK_H
#define ENEMYTANK_H

#include <tankKinds/tank.h>

class EnemyTank : public Tank
{
    Q_OBJECT
public:
    const static int Heavy_Tank = 0;    //不同种类的坦克
    const static int Mid_Tank = 1;
    const static int Mini_Tank = 2;
    static EnemyTank *enemyTankCreator(int tankKind,int _difficultyLevel,int _posX,int _posY,QObject *parent);

protected:
    EnemyTank(int _difficultyLevel,int _posX,int _posY,QObject *parent = nullptr);
};

#endif // ENEMYTANK_H
