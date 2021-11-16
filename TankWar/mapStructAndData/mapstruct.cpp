#include "mapstruct.h"
#include "playwidget.h"

MapStruct* MapStruct::instance = nullptr;
MapStruct::MapStruct(QList<QList<GameBlock *> > *gameMap,QList<Tank *> *tanks,QList<Bullet *> *bullets,Base** base,QObject *parent):QObject(parent)
{
    this->gmp = gameMap;
    this->tanks = tanks;
    this->bullets = bullets;
    this->base = base;
    this->p1BornPos = QPoint(9*GameBlock::blockWidth,24*GameBlock::blockHeight);
    this->p2BornPos = QPoint(15*GameBlock::blockWidth,24*GameBlock::blockHeight);
}

MapStruct::~MapStruct()
{
    this->disconnect();
}

MapStruct *MapStruct::getInstance(QList< QList<GameBlock *> > *gameMap,QList<Tank *> *tanks,QList<Bullet *> *bullets,Base** base,QObject *parent)
{
    instance = new MapStruct(gameMap,tanks,bullets,base,parent);
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

QPoint MapStruct::getRandomBornPos(int objWith,int objHeight)
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
        QRect pos(randomcolum*GameBlock::blockWidth,randomRow*GameBlock::blockHeight,objWith,objHeight);  //创建一个临时块，用于判断是否与现有块冲突
        flag &= canTankOn(pos);
        for (Tank* i:(*tanks))
        {
            flag &= !i->isCrashed(pos);
        }
        if (flag) break;    //随机生成了一个可行的位置
    } while(true);
    return QPoint(randomcolum*GameBlock::blockWidth,randomRow*GameBlock::blockHeight);
}

int MapStruct::getDifficultyLevel()
{
    return difficultyLevel;
}

int MapStruct::getGameLevel()
{
    return gameLevel;
}

PlayerTank *MapStruct::creatPlayerTank()
{
    QPoint bornPos = p1BornPos;
    if (!canTankOn(QRect(bornPos.x(),bornPos.y(),Tank::tankWidth,Tank::tankHeight)))
    {
        bornPos = getRandomBornPos(Tank::tankWidth,Tank::tankHeight);
    }
    PlayerTank* myTank = new PlayerTank(bornPos.x(),bornPos.y(),this);
    tanks->append(myTank);
    connect(myTank,&PlayerTank::queryMove,this,&MapStruct::respondTankMove); //连接坦克的移动请求和游戏地图的请求响应
    connect(myTank,&PlayerTank::tankDestroyed,this,[=](){
        disconnect(myTank,&PlayerTank::tankDestroyed,this,nullptr);
        deleteTank(myTank);
    }); //连接坦克的破坏信号和删除坦克的槽函数
    //连接坦克的发射子弹信号到游戏地图的生成子弹方法上
    connect(myTank,&PlayerTank::tankShot,this,&MapStruct::newBullet);

    //将游戏窗口发出的移动按键信号连接到玩家坦克的移动方法上
    connect(PlayWidget::getInstance(),&PlayWidget::pressToMove,myTank,&PlayerTank::keyPressToMove);
    //将游戏窗口发出的发射子弹按键信号连接到玩家坦克的发射子弹方法上
    connect(PlayWidget::getInstance(),&PlayWidget::pressToShoot,myTank,&PlayerTank::tryToShoot);

    return myTank;
}

FriendTank *MapStruct::creatFriendTank()
{
    QPoint bornPos = p2BornPos;
    if (!canTankOn(QRect(bornPos.x(),bornPos.y(),Tank::tankWidth,Tank::tankHeight)))
    {
        bornPos = getRandomBornPos(Tank::tankWidth,Tank::tankHeight);
    }
    FriendTank* friendTank = new FriendTank(bornPos.x(),bornPos.y(),this);
    tanks->append(friendTank);
    connect(friendTank,&FriendTank::queryMove,this,&MapStruct::respondTankMove); //连接坦克的移动请求和游戏地图的请求响应
    connect(friendTank,&FriendTank::tankDestroyed,this,[=](){
        disconnect(friendTank,&FriendTank::tankDestroyed,this,nullptr);
        deleteTank(friendTank);
    }); //连接坦克的破坏信号和删除坦克的槽函数
    //连接坦克的发射子弹信号到游戏地图的生成子弹方法上
    connect(friendTank,&FriendTank::tankShot,this,&MapStruct::newBullet);
    return friendTank;
}

EnemyTank *MapStruct::creatEnemyTank(int tankKind)
{
    QPoint point = getRandomBornPos(Tank::tankWidth,Tank::tankHeight);
    EnemyTank* enemyTank = EnemyTank::enemyTankCreator(tankKind,difficultyLevel,point.x(),point.y(),this);
    tanks->append(enemyTank);

    connect(enemyTank,&EnemyTank::queryMove,this,&MapStruct::respondTankMove); //连接坦克的移动请求和游戏地图的请求响应
    connect(enemyTank,&EnemyTank::tankDestroyed,this,[=](){
        disconnect(enemyTank,&EnemyTank::tankDestroyed,this,nullptr);
        deleteTank(enemyTank);
    }); //连接坦克的破坏信号和删除坦克的槽函数
    //连接坦克的发射子弹信号到游戏地图的生成子弹方法上
    connect(enemyTank,&EnemyTank::tankShot,this,&MapStruct::newBullet);
    return enemyTank;
}

void MapStruct::clearAll()
{
    for (int i=0;i<gmp->count();++i) //清理旧地图的内存
    {
        for (int j=0;j<gmp->at(i).count();++j)
        {
            delete gmp->at(i).at(j);
        }
    }
    gmp->clear();
    singleMp.clear();
    delete (*base); //清除基地内存
    *base = nullptr;
    for (Tank* i:*tanks) delete i;
    tanks->clear();
    for (Bullet* i:*bullets) delete i;
    bullets->clear();
    basePos.setX(-1);
    basePos.setY(-1);
}

void MapStruct::specificCoveredBlock(QRect obj, int &row1, int &row2, int &column1, int &column2)
{
    row1 = (obj.y()+GameBlock::blockHeight*100)/GameBlock::blockHeight-100;
    column1 = (obj.x()+GameBlock::blockWidth*100)/GameBlock::blockWidth-100;
    row2 = (obj.y()+obj.height())/GameBlock::blockHeight;
    if ((obj.y()+obj.height())%GameBlock::blockHeight == 0) row2--;
    column2 = (obj.x()+obj.width())/GameBlock::blockWidth;
    if ((obj.x()+obj.width())%GameBlock::blockWidth == 0) column2--;
}

void MapStruct::insideCoveredBlock(QRect obj, int &row1, int &row2, int &column1, int &column2)
{
    specificCoveredBlock(obj,row1,row2,column1,column2);
    if (row1 < 0) row1 = 0;
    if (row2 < 0) row2 = 0;
    if (column1 < 0) column1 = 0;
    if (column2 < 0) column2 = 0;
    if (row1 >= MapDataBase::row) row1 = MapDataBase::row-1;
    if (row2 >= MapDataBase::row) row2 = MapDataBase::row-1;
    if (column1 >= MapDataBase::column) column1 = MapDataBase::column-1;
    if (column2 >= MapDataBase::column) column2 = MapDataBase::column-1;
}

bool MapStruct::canTankOn(QRect pos)
{
    int row1,row2,column1,column2;
    specificCoveredBlock(pos,row1,row2,column1,column2);
    //超出边界了
    if (outofBoundary(row1,column1) || outofBoundary(row2,column2)) return false;

    for (int i=row1;i<=row2;++i)
    {
        for (int j=column1;j<=column2;++j)
        {
            if (!gmp->at(i).at(j)->getCanTankThrough()) return false;
        }
    }

    //碰到基地了
    if ((*base)!=nullptr && (*base)->isCrashed(pos)) return false;

    return true;
}

bool MapStruct::canTankOn(VisibleObject obj)
{
    return canTankOn(QRect(obj.getPosX(),obj.getPosY(),obj.width(),obj.height()));
}

bool MapStruct::canBulletOn(QRect pos)
{
    int row1,row2,column1,column2;
    specificCoveredBlock(pos,row1,row2,column1,column2);
    //超出边界了
    if (outofBoundary(row1,column1) || outofBoundary(row2,column2)) return false;

    for (int i=row1;i<=row2;++i)
    {
        for (int j=column1;j<=column2;++j)
        {
            if (!gmp->at(i).at(j)->getCanBulletThrough()) return false;
        }
    }

    //碰到基地了
    if ((*base)!=nullptr && (*base)->isCrashed(pos)) return false;

    return true;
}

bool MapStruct::canBulletOn(VisibleObject obj)
{
    return canBulletOn(QRect(obj.getPosX(),obj.getPosY(),obj.width(),obj.height()));
}

bool MapStruct::outofBoundary(int row, int column)
{
    return row<0 || row>=MapDataBase::row || column<0 || column>=MapDataBase::column;
}

void MapStruct::deleteTank(Tank *tank)
{
    for (int i = 0;i<tanks->count();++i)   //从坦克表中把这辆坦克删除
    {
        if (tanks->at(i) == tank)
        {
            tanks->removeAt(i);
            break;
        }
    }
    QTimer::singleShot(30,[=](){delete tank;}); //一小段时间后再清除坦克内存，防止其它地方收不到坦克的信号
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
    singleMp = mp.getMapData(gameLevel); //根据关卡调出地图数据
    QVector <GameBlock *> v;  //v为单行地图
    int currentX = 0;  //用于暂时记录当前方块的位置
    int currentY = 0;
    for (int i=0;i<MapDataBase::row;++i)
    {
        v.clear();
        GameBlock *gameBlock;
        for (int j=0;j<MapDataBase::column;++j)
        {
            //创建地图块
            gameBlock = GameBlock::gameBlockCreator(singleMp[i][j],currentX,currentY,this);
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

    //创建基地
    basePos.setX(mp.getBaseColumn(gameLevel)*GameBlock::blockWidth);
    basePos.setY(mp.getBaseRow(gameLevel)*GameBlock::blockHeight);
    (*base) = new Base(basePos.x(),basePos.y(),this);
    connect((*base),&Base::baseDestroyed,this,[=](){
        basePos.setX(-1);
        basePos.setY(-1);
        qDebug()<<"MapStruct即将删除基地";
        (*base)->deleteLater();
        qDebug()<<"MapStruct成功删除基地";
        *base = nullptr;
        qDebug()<<"MapStruct即将发送基地被破坏信号";
        emit basementDestroyed();
        qDebug()<<"MapStruct成功发送基地被破坏信号";
    });
}

void MapStruct::respondTankMove(Tank *tank, int toPosX, int toPosY)
{
    QRect targetRect(toPosX,toPosY,tank->width(),tank->height());   //目标位置矩形

    //坦克目标位置只要有一个不可通行方块就无法移动坦克
    if (!canTankOn(targetRect)) return;

    //坦克目标位置已有其他坦克则无法移动坦克
    for (Tank* i:*tanks)
    {
        if (i!=tank && i->isCrashed(targetRect)) return;
    }

    //计算坦克四个角所在方块
    int row1,row2,column1,column2;
    insideCoveredBlock(targetRect,row1,row2,column1,column2);

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
    bool alive = true; //表示子弹是否还存留

    QRect targetRect(toPosX,toPosY,bullet->width(),bullet->height());   //目标位置矩形

    //所在方块只要有一个不可通行就引爆子弹
    alive &= canBulletOn(targetRect);

    //若命中不同敌我属性的坦克则引爆子弹及该坦克
    for (Tank* i:*tanks)
    {
        if (i->isCrashed(targetRect) && (bullet->getIdentity()!=i->getIdentity() || bullet->getIdentity()==Bullet::individualSign || i->getIdentity()==Tank::individualSign))
        {
            alive = false;
            i->blast(bullet->getDamage());
        }
    }

    //若非友方子弹命中基地则引爆子弹及基地
    if ((*base)!=nullptr && (*base)->isCrashed(targetRect) && bullet->getIdentity()!=Bullet::friendSign)
    {
        qDebug()<<"有敌方子弹命中了基地";
        alive = false;
        (*base)->blast();
    }

    //计算子弹四个角所在方块
    int row1,row2,column1,column2;
    insideCoveredBlock(targetRect,row1,row2,column1,column2);

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

    //两子弹碰撞时引爆两子弹
    for (Bullet* i:*bullets)
    {
        if (i!=bullet && i->isCrashed(targetRect) && (bullet->getIdentity()!=i->getIdentity() || bullet->getIdentity()==Bullet::individualSign || i->getIdentity()==Bullet::individualSign))
        {
            alive = false;
            i->blast();
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
                bullets->removeAt(i);
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
    connect(gmp->at(row).at(column),&GameBlock::newBlock,[=](GameBlock *block){   //接收地图块改变的信号
        changeBlock(row,column,block->getTransformBlock());
    });
}
