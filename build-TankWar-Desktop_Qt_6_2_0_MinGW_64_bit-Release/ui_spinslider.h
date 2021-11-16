/********************************************************************************
** Form generated from reading UI file 'spinslider.ui'
**
** Created by: Qt User Interface Compiler version 6.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPINSLIDER_H
#define UI_SPINSLIDER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SpinSlider
{
public:
    QHBoxLayout *horizontalLayout;
    QToolButton *toolBtn;
    QSlider *horizontalSlider;
    QSpinBox *spinBox;

    void setupUi(QWidget *SpinSlider)
    {
        if (SpinSlider->objectName().isEmpty())
            SpinSlider->setObjectName(QString::fromUtf8("SpinSlider"));
        SpinSlider->resize(500, 60);
        horizontalLayout = new QHBoxLayout(SpinSlider);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        toolBtn = new QToolButton(SpinSlider);
        toolBtn->setObjectName(QString::fromUtf8("toolBtn"));

        horizontalLayout->addWidget(toolBtn);

        horizontalSlider = new QSlider(SpinSlider);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(horizontalSlider);

        spinBox = new QSpinBox(SpinSlider);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));

        horizontalLayout->addWidget(spinBox);


        retranslateUi(SpinSlider);

        QMetaObject::connectSlotsByName(SpinSlider);
    } // setupUi

    void retranslateUi(QWidget *SpinSlider)
    {
        SpinSlider->setWindowTitle(QCoreApplication::translate("SpinSlider", "Form", nullptr));
        toolBtn->setText(QCoreApplication::translate("SpinSlider", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SpinSlider: public Ui_SpinSlider {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPINSLIDER_H
