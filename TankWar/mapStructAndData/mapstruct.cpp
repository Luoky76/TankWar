#include "mapstruct.h"

MapStruct* MapStruct::instance = nullptr;
MapStruct::MapStruct(QList<QList<GameBlock *> > *gameMap,QList<Tank *> *tanks,QList<Bullet *> *bullets,QObject *parent):QObject(parent)
{
    this->gmp = gameMap;
    this->tanks = tanks;
    this->bullets = bullets;
    this->p1BornPos = QPoint(9*GameBlock::blockWidth,24*GameBlock::blockHeight);
    this->p2BornPos = QPoint(13*GameBlock::blockWidth,24*GameBlock::blockHeight);
}

MapStruct *MapStruct::getInstance(QList< QList<GameBlock *> > *gameMap,QList<Tank *> *tanks,QList<Bullet *> *bullets,QObject *parent)
{
    if (instance == nullptr)
    {
        instance = new MapStruct(gameMap,tanks,bullets,parent);
    }
    return instance;
}

MapStruct *MapStruct::getInstance()
{
    return instance;
}

QPoint MapStruct::getBasePos()
{
    return basePos;
}

QPoint MapStruct::getP1BornPos()
{
    return p1BornPos;
}

QPoint MapStruct::getP2BornPos()
{
    return p2BornPos;
}

void MapStruct::setP1BornPos(QPoint pos)
{
    p1BornPos = pos;
}

void MapStruct::setP2BornPos(QPoint pos)
{
    p2BornPos = pos;
}

QPoint MapStruct::getRandomBornPos()    //可能出现在已经有坦克的位置
{
    //不存在地图时返回(-1,-1)
    if (gmp->count()<=0 || gmp->at(0).count()<=0) return QPoint(-1,-1);

    //随机生成一个位置，且该位置必位于上半地图
    int blockWidth = gmp->at(0).count();  //获取地图的长宽
    int blockHeight = gmp->count();
    int randomNum;
    int randomRow;
    int randomcolum;
    do  //随机生成位置，直到该位置允许坦克通过
    {
        bool flag = true;
        randomNum = QRandomGenerator::global()->bounded(blockHeight*blockWidth/2);
        randomRow = randomNum/blockWidth;   //随机位置所在行
        randomcolum = randomNum%blockWidth; //随机位置所在列
        flag &= gmp->at(randomRow).at(randomcolum)->getCanTankThrough();

        VisibleObject obj(randomcolum*GameBlock::blockWidth,randomRow*GameBlock::blockHeight,Tank::tankWidth,Tank::tankHeight);  //创建一个临时块，用于判断是否与现有块冲突
        for (Tank* i:(*tanks))
        {
            flag &= i->isCrashed(&obj);
        }
        if (flag) break;    //随机生成了一个可行的位置
    } while(true);
    return QPoint(randomNum/blockWidth,randomNum%blockWidth);
}

PlayerTank *MapStruct::creatPlayerTank()
{
    PlayerTank* myTank = new PlayerTank(p1BornPos.x(),p1BornPos.y(),this);
    tanks->append(myTank);
    connect(myTank,&PlayerTank::queryMove,this,&MapStruct::respondTankMove); //连接坦克的移动请求和游戏窗口的请求响应
    return myTank;
}

void MapStruct::clearAll()
{
    for (int i=0;i<gmp->count();++i) //清理旧地图的内存
    {
        for (int j=0;j<gmp->at(i).count();++j) delete gmp->at(i).at(j);
    }
    gmp->clear();
    singleMp.clear();
    for (Tank * i:*tanks) delete i;
    tanks->clear();
    for (Bullet* i:*bullets) delete i;
    bullets->clear();
    basePos.setX(-1);
    basePos.setY(-1);
}

void MapStruct::coveredBlock(QRect obj, int &row1, int &row2, int &column1, int &column2)
{
    row1 = obj.y()/GameBlock::blockHeight;
    column1 = obj.x()/GameBlock::blockWidth;
    row2 = (obj.y()+obj.height())/GameBlock::blockHeight;
    if ((obj.y()+obj.height())%GameBlock::blockHeight == 0) row2--;
    column2 = (obj.x()+obj.width())/GameBlock::blockWidth;
    if ((obj.x()+obj.width())%GameBlock::blockWidth == 0) column2--;
}

void MapStruct::setDifficulty(int difficultyLevel)
{
    this->difficultyLevel = difficultyLevel;
}

void MapStruct::setGameLevel(int gameLevel)
{
    this->gameLevel = gameLevel;
    resetGmp();
}

void MapStruct::resetGmp()
{
    clearAll();
    singleMp = mp.mData[gameLevel]; //根据关卡调出地图数据
    GameBlock* base = nullptr;    //用于暂存基地指针
    QVector <GameBlock *> v;  //v为单行地图
    int currentX = 0;  //用于暂时记录当前方块的位置
    int currentY = 0;
    for (int i=0;i<MapDataBase::row;++i)
    {
        v.clear();
        GameBlock *gameBlock;
        for (int j=0;j<MapDataBase::column;++j)
        {
            //创建地图块，同时对基地进行特殊处理，只保留一个基地块
            if (singleMp[i][j]!=GameBlock::base)
            {
                gameBlock = GameBlock::gameBlockCreator(singleMp[i][j],currentX,currentY,this);
            }
            else
            {
                if (base==nullptr)
                {
                    gameBlock = GameBlock::gameBlockCreator(singleMp[i][j],currentX,currentY,this);
                    basePos.setX(i);
                    basePos.setY(j);
                    base = gameBlock;
                }
                else gameBlock = base;
            }
            v.push_back(gameBlock);

            connect(gameBlock,&GameBlock::newBlock,[=](GameBlock *block){   //接收地图块改变的信号
                changeBlock(i,j,block->getTransformBlock());
            });
            currentX += GameBlock::blockWidth;
        }
        currentX = 0;
        currentY += GameBlock::blockHeight;
        gmp->push_back(v);
    }
}

void MapStruct::respondTankMove(Tank *tank, int toPosX, int toPosY)
{
    if (toPosX+tank->width()>MapDataBase::column*GameBlock::blockWidth || toPosX<0) return;   //超出边界
    if (toPosY+tank->height()>MapDataBase::row*GameBlock::blockHeight || toPosY<0) return;

    //计算坦克四个角所在方块
    int row1,row2,column1,column2;
    coveredBlock(QRect(toPosX,toPosY,tank->width(),tank->height()),row1,row2,column1,column2);

    //坦克所在方块只要有一个不可通行就无法移动坦克
    for (int i=row1;i<=row2;++i)
    {
        for (int j=column1;j<=column2;++j)
        {
            if (!gmp->at(i).at(j)->getCanTankThrough()) return;
        }
    }

    //acce为坦克加速比，坦克加速比为所在方块中最慢的方块
    double acce = gmp->at(row1).at(column1)->getSpeed();
    for (int i=row1;i<=row2;++i)
    {
        for (int j=column1;j<=column2;++j)
        {
            acce = qMin(acce,gmp->at(i).at(j)->getSpeed());
        }
    }

    tank->tankMove(toPosX,toPosY,acce);
}

void MapStruct::respondBulletMove(Bullet *bullet, int toPosX, int toPosY)
{
    //qDebug()<<toPosX<<" "<<toPosY;

    bool alive = true; //表示子弹是否还存留
    //判断是否超出边界
    if (toPosX+bullet->width()>MapDataBase::column*GameBlock::blockWidth || toPosX<0) alive = false;
    if (toPosY+bullet->height()>MapDataBase::row*GameBlock::blockHeight || toPosY<0) alive = false;
    if (!alive) {bullet->blast(); return;}

    //计算子弹四个角所在方块
    int row1,row2,column1,column2;
    coveredBlock(QRect(toPosX,toPosY,bullet->width(),bullet->height()),row1,row2,column1,column2);

    //所在方块只要有一个不可通行就引爆子弹
    for (int i=row1;i<=row2;++i)
    {
        for (int j=column1;j<=column2;++j)
        {
            if (!gmp->at(i).at(j)->getCanBulletThrough())
            {
                alive = false;
                break;
            }
        }
        if (!alive) break;
    }

    //引爆所在方块中可破坏的方块
    for (int i=row1;i<=row2;++i)
    {
        for (int j=column1;j<=column2;++j)
        {
            if (gmp->at(i).at(j)->getCanDestroy())
            {
                gmp->at(i).at(j)->blast();
            }
        }
    }

    if (alive) bullet->bulletMove(toPosX,toPosY);
    else bullet->blast();
}

void MapStruct::newBullet(Tank *fromTank, int _forward, int _identity, int _posX, int _posY)
{
    Bullet *bullet = new Bullet(_forward,_identity,_posX,_posY,this);
    bullets->append(bullet);

    connect(bullet,&Bullet::bulletDestroyed,[=](){
        for (int i = 0;i<bullets->count();++i)   //从子弹表中把这枚子弹删除
        {
            if (bullets->at(i) == bullet)
            {
                bullets->erase(bullets->begin()+i);
                break;
            }
        }
        delete bullet;
        fromTank->resetCanShoot();
    });
    connect(bullet,&Bullet::queryMove,this,&MapStruct::respondBulletMove);
}

void MapStruct::changeBlock(int row, int column, int transformBlock)
{
    GameBlock *block = gmp->at(row).at(column);
    int posX = block->getPosX();
    int posY = block->getPosY();
    delete block;
    block = GameBlock::gameBlockCreator(transformBlock,posX,posY,this);
    gmp->operator [](row).replace(column,block);

    //对基地特殊处理
    if (transformBlock==GameBlock::base)
    {
        gmp->operator [](row).replace(column+1,block);
        gmp->operator [](row+1).replace(column,block);
        gmp->operator [](row+1).replace(column+1,block);
    }

    connect(gmp->at(row).at(column),&GameBlock::newBlock,[=](GameBlock *block){   //接收地图块改变的信号
        changeBlock(row,column,block->getTransformBlock());
    });
}
