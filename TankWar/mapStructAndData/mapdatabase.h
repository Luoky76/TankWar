#ifndef MAPDATABASE_H
#define MAPDATABASE_H

#include <QObject>
#include <QMap>
class MapDataBase:public QObject   //地图的初始化数据库
{
    Q_OBJECT
public:
    const static int totLevel = 5;  //关卡总数
    const static int column = 26;   //游戏关卡地形块的列数
    const static int row = 26;  //游戏关卡地形块的行数

    MapDataBase(QObject *parent = nullptr);
    QMap<int, QVector< QVector<int> > >mData;   //关卡和地图数据的映射

private:

    QVector <QVector<int> > arr;    //arr暂存单个关卡的信息
};

#endif // MAPDATABASE_H
