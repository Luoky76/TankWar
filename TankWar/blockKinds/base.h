#ifndef BASE_H
#define BASE_H

#include <blockKinds/gameblock.h>

class Base : public GameBlock
{
    Q_OBJECT
public:
    Base(int _posX,int _posY,QObject *parent = nullptr);
};

#endif // BASE_H
