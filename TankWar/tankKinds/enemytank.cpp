#include "enemytank.h"
#include "namebox.h"
#include <tankKinds/heavytank.h>
#include <tankKinds/midtank.h>
#include <tankKinds/minitank.h>

EnemyTank::EnemyTank(int _difficultyLevel,int _posX,int _posY,QObject *parent)
    :Tank(_posX,_posY,parent)
{
    identity = Tank::enemySign;
    moveTime/=_difficultyLevel;  //敌方坦克的移动速度统一先加快难度倍
    tankName = NameBox::getInstance()->getRandomName();
}

EnemyTank *EnemyTank::enemyTankCreator(int tankKind, int _difficultyLevel, int _posX, int _posY, QObject *parent)
{
    switch (tankKind)
    {
        case Heavy_Tank:return (EnemyTank *) new HeavyTank(_difficultyLevel,_posX,_posY,parent); break;
        case Mid_Tank:return (EnemyTank *) new MidTank(_difficultyLevel,_posX,_posY,parent); break;
        case Mini_Tank:return (EnemyTank *) new MiniTank(_difficultyLevel,_posX,_posY,parent); break;
        default: return nullptr; break;
    }
}
