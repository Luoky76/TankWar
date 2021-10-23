#ifndef STEEL_H
#define STEEL_H

#include <blockKinds/gameblock.h>

class Steel : public GameBlock
{
    Q_OBJECT
public:
    Steel(int _posX,int _posY,QObject *parent = nullptr);
};

#endif // STEEL_H
