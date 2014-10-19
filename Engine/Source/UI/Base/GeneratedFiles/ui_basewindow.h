/********************************************************************************
** Form generated from reading UI file 'basewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BASEWINDOW_H
#define UI_BASEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BaseWindowClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *BaseWindowClass)
    {
        if (BaseWindowClass->objectName().isEmpty())
            BaseWindowClass->setObjectName(QStringLiteral("BaseWindowClass"));
        BaseWindowClass->resize(600, 400);
        menuBar = new QMenuBar(BaseWindowClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        BaseWindowClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(BaseWindowClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        BaseWindowClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(BaseWindowClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        BaseWindowClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(BaseWindowClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        BaseWindowClass->setStatusBar(statusBar);

        retranslateUi(BaseWindowClass);

        QMetaObject::connectSlotsByName(BaseWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *BaseWindowClass)
    {
        BaseWindowClass->setWindowTitle(QApplication::translate("BaseWindowClass", "BaseWindow", 0));
    } // retranslateUi

};

namespace Ui {
    class BaseWindowClass: public Ui_BaseWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BASEWINDOW_H
