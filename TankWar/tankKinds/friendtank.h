#ifndef FRIENDTANK_H
#define FRIENDTANK_H

#include <tankKinds/tank.h>

class FriendTank : public Tank
{
    Q_OBJECT
public:
    FriendTank(int _posX,int _posY,QObject *parent = nullptr);
};

#endif // FRIENDTANK_H
