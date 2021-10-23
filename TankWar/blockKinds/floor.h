#ifndef FLOOR_H
#define FLOOR_H

#include <blockKinds/gameblock.h>

class Floor : public GameBlock
{
    Q_OBJECT
public:
    Floor(int _posX,int _posY,QObject *parent = nullptr);
};

#endif // FLOOR_H
