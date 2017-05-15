/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created: Fri Dec 26 15:22:00 2014
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>
#include "qwt_plot.h"

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QLabel *label;
    QwtPlot *qwtPlot;
    QLabel *RRI;
    QLCDNumber *RRI_LCD;
    QLabel *label_2;
    QLCDNumber *HR_LCD;
    QLabel *label_3;
    QLCDNumber *ration_LCD;
    QwtPlot *psdPlot;
    QPushButton *pushButton_1;
    QPushButton *pushButton_2;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(1138, 552);
        Widget->setMinimumSize(QSize(650, 550));
        Widget->setMaximumSize(QSize(1280, 720));
        label = new QLabel(Widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(5, 5, 640, 480));
        label->setMinimumSize(QSize(640, 480));
        label->setMaximumSize(QSize(1280, 720));
        qwtPlot = new QwtPlot(Widget);
        qwtPlot->setObjectName(QString::fromUtf8("qwtPlot"));
        qwtPlot->setGeometry(QRect(640, 20, 471, 221));
        RRI = new QLabel(Widget);
        RRI->setObjectName(QString::fromUtf8("RRI"));
        RRI->setGeometry(QRect(60, 500, 51, 31));
        QFont font;
        font.setPointSize(18);
        RRI->setFont(font);
        RRI->setMouseTracking(false);
        RRI->setTextFormat(Qt::AutoText);
        RRI->setScaledContents(false);
        RRI->setMargin(0);
        RRI->setIndent(0);
        RRI_LCD = new QLCDNumber(Widget);
        RRI_LCD->setObjectName(QString::fromUtf8("RRI_LCD"));
        RRI_LCD->setGeometry(QRect(110, 500, 71, 31));
        label_2 = new QLabel(Widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(260, 510, 41, 21));
        label_2->setFont(font);
        label_2->setMouseTracking(false);
        label_2->setTextFormat(Qt::AutoText);
        HR_LCD = new QLCDNumber(Widget);
        HR_LCD->setObjectName(QString::fromUtf8("HR_LCD"));
        HR_LCD->setGeometry(QRect(300, 500, 71, 31));
        label_3 = new QLabel(Widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(450, 510, 71, 21));
        label_3->setFont(font);
        label_3->setTextFormat(Qt::AutoText);
        ration_LCD = new QLCDNumber(Widget);
        ration_LCD->setObjectName(QString::fromUtf8("ration_LCD"));
        ration_LCD->setGeometry(QRect(530, 500, 71, 31));
        psdPlot = new QwtPlot(Widget);
        psdPlot->setObjectName(QString::fromUtf8("psdPlot"));
        psdPlot->setGeometry(QRect(640, 270, 471, 221));
        pushButton_1 = new QPushButton(Widget);
        pushButton_1->setObjectName(QString::fromUtf8("pushButton_1"));
        pushButton_1->setGeometry(QRect(760, 500, 81, 41));
        pushButton_2 = new QPushButton(Widget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(940, 500, 91, 41));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "zed_camera_AVI", 0, QApplication::UnicodeUTF8));
        label->setText(QString());
        RRI->setText(QApplication::translate("Widget", "RRI", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Widget", "HR", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Widget", "LF/HF", 0, QApplication::UnicodeUTF8));
        pushButton_1->setText(QApplication::translate("Widget", "Start", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("Widget", "Close", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
