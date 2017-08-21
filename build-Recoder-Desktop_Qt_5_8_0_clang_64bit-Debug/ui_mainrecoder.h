/********************************************************************************
** Form generated from reading UI file 'mainrecoder.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINRECODER_H
#define UI_MAINRECODER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainRecoder
{
public:
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainRecoder)
    {
        if (MainRecoder->objectName().isEmpty())
            MainRecoder->setObjectName(QStringLiteral("MainRecoder"));
        MainRecoder->resize(259, 206);
        centralWidget = new QWidget(MainRecoder);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        MainRecoder->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainRecoder);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 259, 22));
        MainRecoder->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainRecoder);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainRecoder->setStatusBar(statusBar);

        retranslateUi(MainRecoder);

        QMetaObject::connectSlotsByName(MainRecoder);
    } // setupUi

    void retranslateUi(QMainWindow *MainRecoder)
    {
        MainRecoder->setWindowTitle(QApplication::translate("MainRecoder", "MainRecoder", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainRecoder: public Ui_MainRecoder {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINRECODER_H
