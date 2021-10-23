#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>
#include <QDebug>
#include <QPropertyAnimation>
#include <QTimer>
#include <QSoundEffect>

class MyButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyButton(QString normalImg,QString pressImg = "",QWidget *parent = nullptr);
    void setSound(QString soundPath);

private:
    QString normalImgPath;
    QString pressImgPath;
    QString soundPath = nullptr;  //音效文件路径
    QSoundEffect *soundEffect;  //音效播放控件
    void onPlaySound(); //播放音效
    void zoomDown(int dy = 10);
    void zoomUp(int dy = 10);
    void zoom();
    void enterEvent(QEnterEvent *ev) override;
    void leaveEvent(QEvent *ev) override;

signals:
    void mouseEntered();
    void mouseLeft();
};

#endif // MYBUTTON_H
