#ifndef WIDGET_H
#define WIDGET_H
#include "mybutton.h"
#include "playwidget.h"
#include "spinslider.h"
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    static const int singlePlayer = 0;  //定义参数含义，0表示单人游戏
    static const int doublePlayer = 1;  //1表示双人游戏

private:
    Ui::Widget *ui;
    MyButton *btn_start = nullptr;    //开始游戏按钮
    MyButton *btn_back = nullptr;     //返回按钮
    SpinSlider *soundSlider;          //音量拖条
    SpinSlider *hardSlider;           //难度拖条
    PlayWidget *playWidget = nullptr; //按下开始后跳转的游戏界面
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
};
#endif // WIDGET_H
