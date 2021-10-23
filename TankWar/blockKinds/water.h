#ifndef WATER_H
#define WATER_H

#include <blockKinds/gameblock.h>

class Water : public GameBlock
{
    Q_OBJECT
public:
    Water(int _posX,int _posY,QObject *parent = nullptr);
};

#endif // WATER_H
