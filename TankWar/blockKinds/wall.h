#ifndef WALL_H
#define WALL_H

#include <blockKinds/gameblock.h>

class Wall : public GameBlock
{
    Q_OBJECT
public:
    Wall(int _posX,int _posY,QObject *parent = nullptr);
};

#endif // WALL_H
