#include "mapdatabase.h"
#include <QFile>
#include <QTextStream>
#include <QVector>
#include <QByteArray>
#include <QDebug>

MapDataBase::MapDataBase(QObject *parent):QObject(parent)
{
    int totLevel = GameParameter::totLevel;
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
    }
}
