#ifndef SPINSLIDER_H
#define SPINSLIDER_H

#include <QWidget>

namespace Ui {
class SpinSlider;
}

class SpinSlider : public QWidget
{
    Q_OBJECT

public:
    explicit SpinSlider(QString normalPath,QString minPath = "",QWidget *parent = nullptr);
    ~SpinSlider();
    void setValue(int x);
    int getValue();
    void setMaxValue(int x);
    void setMinValue(int x);

private:
    Ui::SpinSlider *ui;
    QString minIconPath;    //值为最小值时的图标路径
    QString normalIconPath;    //值不为最小值时的图标路径
    int maxValue = 10;      //拖条的最大值
    int minValue = 0;
    void updateIcon();      //根据value更新图标

signals:
    void valueChanged();    //值发生改变时发出信号
};

#endif // SPINSLIDER_H
