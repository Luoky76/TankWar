#ifndef VISIBLEOBJECT_H
#define VISIBLEOBJECT_H

#include <QObject>
#include <QPainter>
#include <QPixmap>

class VisibleObject : public QObject    //可见物件类
{
    Q_OBJECT
public:
    explicit VisibleObject(QObject *parent = nullptr);
    explicit VisibleObject(int posX,int posY,int objWidth,int objHeight,QObject *parent = nullptr);
    int width();
    int height();
    int getPosX();
    int getPosY();
    QString getIconPath();
    bool isCrashed(VisibleObject* obj2); //判断两个物件是否相交
    void paintObj(int dx,int dy,QPainter *painter);   //绘制该物件，dx dy 为开始绘制的左上角位置
    void paintObj(int dx,int dy,QString iconPath,QPainter *painter);

protected:
    int objWidth;   //物件宽高
    int objHeight;
    int posX;   //物件位置
    int posY;
    QString iconPath;   //物件的图片路径

signals:

};

#endif // VISIBLEOBJECT_H
