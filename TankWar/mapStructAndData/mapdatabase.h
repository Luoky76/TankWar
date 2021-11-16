#ifndef MAPDATABASE_H
#define MAPDATABASE_H

#include "blockKinds/gameblock.h"
#include <QObject>
#include <QMap>
#include <QPoint>
#include <QDebug>
class MapDataBase:public QObject   //地图的初始化数据库
{
    Q_OBJECT
public:
    const static int totLevel = 5;  //关卡总数（下标从1开始）
    const static int column = 26;   //游戏关卡地形块的列数
    const static int row = 26;  //游戏关卡地形块的行数
    MapDataBase(QObject *parent = nullptr);
    QList< QList<int> > getMapData(int gameLevel);  //获取单个关卡的数据
    QPoint getBasePos(int gameLevel);   //获取基地左上角所在行列（x为列，y为行）
    int getBaseRow(int gameLevel);  //获取基地左上角所在行
    int getBaseColumn(int gameLevel);   //获取基地左上角所在列

private:
    QMap<int, QList< QList<int> > >mData;   //关卡和地图数据的映射
    QMap<int, QPoint> baseData; //关卡和基地位置的映射
    void findBase(int gameLevel);
};

#endif // MAPDATABASE_H
