#include "mapdatabase.h"
#include <QFile>
#include <QTextStream>
#include <QVector>
#include <QByteArray>
#include <QDebug>

MapDataBase::MapDataBase(QObject *parent):QObject(parent)
{
    QList <QList<int> > arr;    //arr暂存单个关卡的信息
    int totLevel = MapDataBase::totLevel;
    QVector <int> v;    //用于读入单行数据
    for (int i=1;i<=totLevel;++i)
    {
        arr.clear();
        QString filePath = QString(":/Resource/dataBase/level%1.txt").arg(i);   //文件路径
        QFile file(filePath);
        if (file.open(QFileDevice::ReadOnly))
        {
            while (!file.atEnd())
            {
                int x;
                v.clear();
                QString qstr = file.readLine(); //从文件读入一行
                qstr =qstr.trimmed();   //删除行首、行末的空白字符
                QByteArray byteArray = qstr.toUtf8();   //QString转QByteArray
                QTextStream in(byteArray);  //读入流，逐个读入QByteArray中的数
                while (!in.atEnd())
                {
                    in>>x;
                    v.push_back(x);
                }
                arr.push_back(v);
            }
        }
        file.close();
        mData.insert(i,arr);
        findBase(i);
    }
}

QList< QList<int> > MapDataBase::getMapData(int gameLevel)
{
    if (gameLevel>totLevel || gameLevel<1)
    {
        qDebug()<<"the max game level is "<<totLevel;
    }
    return mData[gameLevel];
}

QPoint MapDataBase::getBasePos(int gameLevel)
{
    if (gameLevel>totLevel || gameLevel<1)
    {
        qDebug()<<"the max game level is "<<totLevel;
    }
    return baseData[gameLevel];
}

int MapDataBase::getBaseRow(int gameLevel)
{
    if (gameLevel>totLevel || gameLevel<1)
    {
        qDebug()<<"the max game level is "<<totLevel;
    }
    return baseData[gameLevel].y();
}

int MapDataBase::getBaseColumn(int gameLevel)
{
    if (gameLevel>totLevel || gameLevel<1)
    {
        qDebug()<<"the max game level is "<<totLevel;
    }
    return baseData[gameLevel].x();
}

void MapDataBase::findBase(int gameLevel)
{
    QList <QList<int> > arr;    //arr暂存单个关卡的信息
    arr = mData[gameLevel];
    bool find = false;
    for (int i=0;i<arr.count();++i)
    {
        for (int j=0;j<arr[i].count();++j)
        {
            if (arr[i][j]==0)   //0代表基地
            {
                if (!find)
                {
                    QPoint basePos(j,i);
                    baseData.insert(gameLevel,basePos);
                    find = true;
                }
                //将基地变为地面
                mData[gameLevel][i][j] = GameBlock::floor;
            }
        }
    }
}
