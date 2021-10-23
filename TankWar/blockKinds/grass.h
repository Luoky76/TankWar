#ifndef GRASS_H
#define GRASS_H

#include <blockKinds/gameblock.h>

class Grass : public GameBlock
{
    Q_OBJECT
public:
    Grass(int _posX,int _posY,QObject *parent = nullptr);
};

#endif // GRASS_H
