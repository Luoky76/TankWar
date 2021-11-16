#include "artificial.h"

Artificial* Artificial::instance = nullptr;

Artificial::Artificial(QList <Tank *> *tanks,QObject *parent)
    : QObject{parent}
{
    this->tanks = tanks;
    setEplison();
    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&Artificial::emitEnemyCommand);
    connect(timer,&QTimer::timeout,this,&Artificial::emitFriendCommand);
}

Artificial::~Artificial()
{
    this->disconnect();
}

Artificial *Artificial::getInstance(QList<Tank *> *tanks, QObject *parent)
{
    instance = new Artificial(tanks,parent);
    return instance;
}

Artificial *Artificial::getInstance()
{
    return instance;
}

void Artificial::startArtificial()
{
    timer->start(100);  //每100毫秒向全体人机操控的坦克发出命令
}

void Artificial::stopArtificial()
{
    qDebug()<<"Artificial即将关闭人机";
    timer->stop();
    qDebug()<<"Artificial成功关闭人机";
}

void Artificial::emitEnemyCommand()
{
    for (Tank* i:(*tanks))
    {
        if (i->inherits("EnemyTank"))
        {
            QPoint basePos = MapStruct::getInstance()->getBasePos();
            int randNum = QRandomGenerator::global()->bounded(101);
            if (randNum < eplisonStay) continue;    //坦克静止不动

            randNum = QRandomGenerator::global()->bounded(101);
            if (randNum < eplisonForward)   //坦克向前进
            {
                i->tryToMove(i->getForward());
                i->tryToShoot();
                continue;
            }

            randNum = QRandomGenerator::global()->bounded(101);
            if (randNum < eplisonToBase)    //向基地行动
            {
                randNum = QRandomGenerator::global()->bounded(2);
                if (randNum < 1)
                {
                    if (basePos.x() < i->getPosX())
                    {
                        i->tryToMove(Tank::left);
                    }
                    else i->tryToMove(Tank::right);
                }
                else
                {
                    if (basePos.y() < i->getPosY())
                    {
                        i->tryToMove(Tank::up);
                    }
                    else i->tryToMove(Tank::down);
                }
            }
            else    //不向基地行动
            {
                randNum = QRandomGenerator::global()->bounded(2);
                if (randNum < 1)
                {
                    if (basePos.x() < i->getPosX())
                    {
                        i->tryToMove(Tank::right);
                    }
                    else i->tryToMove(Tank::left);
                }
                else
                {
                    if (basePos.y() < i->getPosY())
                    {
                        i->tryToMove(Tank::down);
                    }
                    else i->tryToMove(Tank::up);
                }
            }
            i->tryToShoot();
        }
    }
}

void Artificial::emitFriendCommand()
{
    for (Tank* i:(*tanks))
    {
        if (i->inherits("FriendTank"))
        {
            int randNum = QRandomGenerator::global()->bounded(101);
            if (randNum < eplisonForward)   //坦克向前进
            {
                i->tryToMove(i->getForward());
                continue;
            }

            randNum = QRandomGenerator::global()->bounded(4);
            switch (randNum) {
            case 0:
                i->tryToMove(Tank::up);
                break;
            case 1:
                i->tryToMove(Tank::right);
                break;
            case 2:
                i->tryToMove(Tank::down);
                break;
            case 3:
                i->tryToMove(Tank::left);
                break;
            default:
                break;
            }
            i->tryToShoot();
        }
    }
}

void Artificial::setEplison()
{
    int difficulty = MapStruct::getInstance()->getDifficultyLevel();
    switch (difficulty) {
    case 1:
        eplisonToBase = 50;
        break;
    case 2:
        eplisonToBase = 65;
        break;
    case 3:
        eplisonToBase = 80;
        break;
    default:
        break;
    }
    eplisonStay = 50;
    eplisonForward = 80;
}
