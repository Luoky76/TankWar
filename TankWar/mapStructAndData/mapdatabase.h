#ifndef MAPDATABASE_H
#define MAPDATABASE_H

#include "gameparameter.h"
#include <QObject>
#include <QMap>
class MapDataBase:public QObject   //地图的初始化数据库
{
    Q_OBJECT
public:
    MapDataBase(QObject *parent = nullptr);
    QMap<int, QVector< QVector<int> > >mData;   //关卡和地图数据的映射

private:

    QVector <QVector<int> > arr;    //arr暂存单个关卡的信息
};

#endif // MAPDATABASE_H
