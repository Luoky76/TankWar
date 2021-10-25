/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout;
    QStackedWidget *stackedWidget;
    QWidget *page_0;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QCheckBox *check_single;
    QCheckBox *check_double;
    QWidget *page_1;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(1000, 618);
        Widget->setMinimumSize(QSize(1000, 618));
        Widget->setMaximumSize(QSize(1000, 618));
        verticalLayout = new QVBoxLayout(Widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        stackedWidget = new QStackedWidget(Widget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        page_0 = new QWidget();
        page_0->setObjectName(QString::fromUtf8("page_0"));
        widget = new QWidget(page_0);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(350, 480, 321, 71));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        check_single = new QCheckBox(widget);
        check_single->setObjectName(QString::fromUtf8("check_single"));
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        check_single->setFont(font);
        check_single->setCursor(QCursor(Qt::PointingHandCursor));
        check_single->setTristate(false);

        horizontalLayout->addWidget(check_single);

        check_double = new QCheckBox(widget);
        check_double->setObjectName(QString::fromUtf8("check_double"));
        check_double->setFont(font);
        check_double->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout->addWidget(check_double);

        stackedWidget->addWidget(page_0);
        page_1 = new QWidget();
        page_1->setObjectName(QString::fromUtf8("page_1"));
        stackedWidget->addWidget(page_1);

        verticalLayout->addWidget(stackedWidget);


        retranslateUi(Widget);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
#if QT_CONFIG(tooltip)
        stackedWidget->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        check_single->setText(QCoreApplication::translate("Widget", "\345\215\225\344\272\272\346\270\270\346\210\217", nullptr));
        check_double->setText(QCoreApplication::translate("Widget", "\345\217\214\344\272\272\346\270\270\346\210\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
