#ifndef REDWALL_H
#define REDWALL_H

#include "gameblock.h"

class Redwall : public GameBlock
{
    Q_OBJECT
public:
    explicit Redwall(int _posX,int _posY,QObject *parent = nullptr);
};

#endif // REDWALL_H
