#include "spinslider.h"
#include "ui_spinslider.h"
#include <QDebug>
#include <QIcon>

SpinSlider::SpinSlider(QString normalPath,QString minPath,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SpinSlider)
{
    ui->setupUi(this);

    //保存图标路径
    normalIconPath = normalPath;
    if (minPath=="") minIconPath = normalPath;
    else minIconPath = minPath;

    //判断是否能正常加载图片
    QPixmap pixmap;
    bool ret = pixmap.load(normalIconPath);
    if (!ret)
    {
        qDebug()<<normalIconPath<<"加载图片失败 in SpinSlider";
    }

    ui->toolBtn->setIconSize(QSize(70,50));
    ui->toolBtn->setIcon(QIcon(pixmap));    //设置初始图片

    //QSpinBox值的改变使Slider的位置改变，图标也可能改变，同时对外发出值改变信号
    connect(ui->spinBox,(void (QSpinBox::*) (int))&QSpinBox::valueChanged,[=](int x){
        ui->horizontalSlider->setValue(x);
        updateIcon();
        emit valueChanged();
    });
    //Slider的位置改变使QSpinBox值的改变，图标也可能改变，同时对外发出值改变信号
    connect(ui->horizontalSlider,(void (QSlider::*) (int))&QAbstractSlider::valueChanged,[=](int x){
        ui->spinBox->setValue(x);
        updateIcon();
        emit valueChanged();
    });

    //当点击图标时设置数值为最小值/最大值
    connect(ui->toolBtn,&QToolButton::clicked,[=](){
        if (getValue()==minValue) setValue(maxValue);
        else setValue(minValue);
    });

    //设置拖条初始的最大值和最小值
    ui->spinBox->setMaximum(maxValue);
    ui->horizontalSlider->setMaximum(maxValue);
    ui->spinBox->setMinimum(minValue);
    ui->horizontalSlider->setMinimum(minValue);

    //设置拖条的起始值
    ui->spinBox->setValue((maxValue+minValue)/2);
}

SpinSlider::~SpinSlider()
{
    delete ui;
}

int SpinSlider::getValue()
{
    return ui->spinBox->value();
}

void SpinSlider::setValue(int x)
{
    if (x<=maxValue) ui->spinBox->setValue(x);
    else qDebug()<<QString("in SpinSlider 值太大了，请设置在%1内").arg(maxValue);
}

void SpinSlider::setMaxValue(int x)
{
    if (x>0) maxValue=x;
    else qDebug()<<"in SpinSlider 最大值请设为正数";
    ui->spinBox->setMaximum(maxValue);
    ui->horizontalSlider->setMaximum(maxValue);
    ui->spinBox->setValue((maxValue+minValue)/2);   //同时更新当前的值
    updateIcon();
}

void SpinSlider::setMinValue(int x)
{
    if (x>=0) minValue=x;
    else qDebug()<<"in SpinSlider 最小值请设为非负数";
    ui->spinBox->setMinimum(minValue);
    ui->horizontalSlider->setMinimum(minValue);
    ui->spinBox->setValue((maxValue+minValue)/2);   //同时更新当前的值
    updateIcon();
}
void SpinSlider::updateIcon()   //根据当前是否处于最小值来更新图标
{
    if (getValue()==minValue) ui->toolBtn->setIcon(QIcon(QPixmap(minIconPath)));
    else ui->toolBtn->setIcon(QIcon(QPixmap(normalIconPath)));
}
