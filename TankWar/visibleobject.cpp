#include "visibleobject.h"

VisibleObject::VisibleObject(QObject *parent) : QObject(parent)
{

}

VisibleObject::VisibleObject(int posX, int posY, int objWidth, int objHeight, QObject *parent) : QObject(parent)
{
    this->posX = posX;
    this->posY = posY;
    this->objWidth = objWidth;
    this->objHeight = objHeight;
}

int VisibleObject::width()
{
    return objWidth;
}

int VisibleObject::height()
{
    return objHeight;
}

int VisibleObject::getPosX()
{
    return posX;
}

int VisibleObject::getPosY()
{
    return posY;
}

QString VisibleObject::getIconPath()
{
    return iconPath;
}

bool VisibleObject::isCrashed(VisibleObject* obj2)
{
    if (this->getPosX()+this->width()<=obj2->getPosX()) return false;
    if (obj2->getPosX()+obj2->width()<=this->getPosX()) return false;
    if (this->getPosY()+this->height()<=obj2->getPosY()) return false;
    if (obj2->getPosY()+obj2->height()<=this->getPosY()) return false;
    return true;
}

void VisibleObject::paintObj(int dx, int dy, QPainter *painter)
{
    QPixmap pixmap(iconPath);
    pixmap = pixmap.scaled(objWidth,objHeight);
    painter->drawPixmap(dx+posX,dy+posY,pixmap);
}

void VisibleObject::paintObj(int dx, int dy, QString iconPath, QPainter *painter)
{
    QPixmap pixmap(iconPath);
    pixmap = pixmap.scaled(objWidth,objHeight);
    painter->drawPixmap(dx+posX,dy+posY,pixmap);
}
