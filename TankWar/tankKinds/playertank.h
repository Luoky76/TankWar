#ifndef PLAYERTANK_H
#define PLAYERTANK_H

#include <tankKinds/tank.h>

class PlayerTank : public Tank
{
    Q_OBJECT
public:
    PlayerTank(int _posX,int _posY,QObject *parent = nullptr);
    void keyPressToMove(int key);   //接收按下的方向键
};

#endif // PLAYERTANK_H
