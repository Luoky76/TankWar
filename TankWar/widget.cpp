#include "widget.h"
#include "ui_widget.h"
#include "mybutton.h"
#include "spinslider.h"
#include "playwidget.h"
#include "gameExecutor/gamestatepusher.h"
#include <QCheckBox>
#include <QTimer>
#include <QIcon>
#include <QPainter>
#include <QPixmap>
#include <QColor>
#include <QKeyEvent>

Widget::Widget(QWidget *parent) //开始游戏界面
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setWindowTitle("坦克大战");   //设置窗口标题
    this->setWindowIcon(QIcon(":/Resource/img/other/mintank.png")); //设置窗口图标

    ui->stackedWidget->setCurrentIndex(0);  //设置初始页面为第0页，即开始游戏主界面

    //创建开始游戏按钮
    btn_start = new MyButton(":/Resource/img/other/gameStart.png","",ui->page_0);
    btn_start->move((this->width()-btn_start->width())*0.5,(this->height()-btn_start->height())*0.4);   //居中放置按钮
    btn_start->setToolTip("开始游戏");  //设置操作提示
    //btn_start->setSound(":/Resource/music/button.wav"); //设置按钮音效
    connect(btn_start,&MyButton::clicked,this,[=](){ //按下按钮后创建并打开游戏界面
        if (playWidget!=nullptr) return;    //若已创建过游戏界面，不再重复创建 
        int playMode;   //表示单双人模式
        if (ui->check_single->checkState()==Qt::Checked) playMode = singlePlayer;
        else playMode = doublePlayer;

        //根据游戏模式，音量，难度创建游戏界面
        playWidget = PlayWidget::getInstance(playMode,soundSlider->getValue(),hardSlider->getValue(),playerName->text());

        connect(playWidget,&PlayWidget::sceneClose,this,[=](){   //游戏窗口关闭时清除内存，恢复空指针
            disconnect(playWidget,&PlayWidget::sceneClose,this,nullptr);
            //playWidget->deleteLater();
            playWidget = nullptr;
        });
        QTimer::singleShot(450,[=](){
            playWidget->show();
        });
    });

    //设置选择单双人游戏的按钮，使两个按钮互斥
    ui->check_single->setCheckState(Qt::Checked);
    connect(ui->check_single,&QCheckBox::stateChanged,[=](){
       if (ui->check_single->checkState()==Qt::Checked) ui->check_double->setCheckState(Qt::Unchecked);
       else ui->check_double->setCheckState(Qt::Checked);
    });
    connect(ui->check_double,&QCheckBox::stateChanged,[=](){
       if (ui->check_double->checkState()==Qt::Checked) ui->check_single->setCheckState(Qt::Unchecked);
       else ui->check_single->setCheckState(Qt::Checked);
    });

    //创建设置按钮
    MyButton *btn_setUp = new MyButton(":/Resource/img/other/setUp.png","",ui->page_0);
    btn_setUp->move(700,480);
    btn_setUp->setToolTip("设置");    //设置操作提示
    connect(btn_setUp,&MyButton::clicked,[=](){ //点击按钮进入设置界面
        QTimer::singleShot(450,[=](){
            ui->stackedWidget->setCurrentIndex(1);
        });
    });

    //创建音量调节条
    soundSlider = new SpinSlider(":/Resource/img/other/sound.png",":/Resource/img/other/muteSound.png",ui->page_1);
    soundSlider->move((this->width()-soundSlider->width())*0.5,250);    //水平居中放置音量条
    soundSlider->setToolTip("音量");
    soundSlider->setMaxValue(10);
    soundSlider->setMinValue(0);    //设置音量范围为0~10

    //创建难度调节条
    hardSlider = new SpinSlider(":/Resource/img/other/difficultyRed.png",":/Resource/img/other/difficultyGreen.png",ui->page_1);
    hardSlider->move((this->width()-hardSlider->width())*0.5,350);    //水平居中放置音量条
    hardSlider->setToolTip("难度");
    hardSlider->setMaxValue(3);
    hardSlider->setMinValue(1);     //设置难度范围为1~3

    //创建玩家姓名提示图片
    playerNamePix = new QLabel(ui->page_1);
    QPixmap pixmap(":/Resource/img/other/playerName.png");
    pixmap = pixmap.scaled(140,50);
    playerNamePix->resize(pixmap.width(),pixmap.height());
    playerNamePix->setPixmap(pixmap);
    playerNamePix->move((this->width()-playerNamePix->width())*0.5-175,450);

    //创建玩家姓名单行文本框
    QPalette palette;
    palette.setColor(QPalette::Text, Qt::white);
    playerName = new QLineEdit(ui->page_1);
    playerName->setFont(QFont("微软雅黑", 20, QFont::Bold));
    playerName->setPalette(palette);
    playerName->setPlaceholderText("请输入玩家姓名");
    playerName->setText("Luoky");
    playerName->setEchoMode(QLineEdit::Normal);
    playerName->resize(300, 50);
    playerName->setStyleSheet("padding: -1");
    playerName->setStyleSheet("background-color:rgba(0,0,0,0);");
    playerName->move((this->width()-playerName->width())*0.5+50,450);

    //创建返回按键
    btn_back = new MyButton(":/Resource/img/other/backBtn.png","",ui->page_1);
    btn_back->move(700,480);
    btn_back->setToolTip("返回");    //设置操作提示
    connect(btn_back,&MyButton::clicked,[=](){ //点击按钮进入设置界面
        QTimer::singleShot(450,[=](){
            ui->stackedWidget->setCurrentIndex(0);
        });
    });
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pixmap(":/Resource/img/other/background.png");
    pixmap.scaled(this->width(),this->height());
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);

    if (ui->stackedWidget->currentIndex()==0)   //为单双人游戏模式选择添加半透明底框
    {
        QPixmap pixmap2(ui->widget->width(),ui->widget->height());
        QColor color(255,255,255,100);
        pixmap2.fill(color);
        painter.drawPixmap(ui->widget->x(),ui->widget->y(),pixmap2);
    }

    if (ui->stackedWidget->currentIndex()==1)   //为设置界面画上标题
    {
        QPixmap pixmap2(":/Resource/img/other/gameSetting.png");
        painter.drawPixmap((this->width()-pixmap2.width())/2,100,pixmap2);
    }
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Return: case Qt::Key_Enter:
        if (ui->stackedWidget->currentIndex()==0) emit btn_start->clicked();
        else emit btn_back->clicked();
        break;
    default:
        break;
    }
}

Widget::~Widget()
{
    delete ui;
}
