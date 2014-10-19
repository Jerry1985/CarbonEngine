/********************************************************************************
** Form generated from reading UI file 'qtproject.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTPROJECT_H
#define UI_QTPROJECT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QTProjectClass
{
public:
    QWidget *centralWidget;

    void setupUi(QMainWindow *QTProjectClass)
    {
        if (QTProjectClass->objectName().isEmpty())
            QTProjectClass->setObjectName(QString::fromUtf8("QTProjectClass"));
        QTProjectClass->resize(600, 400);
        centralWidget = new QWidget(QTProjectClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QTProjectClass->setCentralWidget(centralWidget);

        retranslateUi(QTProjectClass);

        QMetaObject::connectSlotsByName(QTProjectClass);
    } // setupUi

    void retranslateUi(QMainWindow *QTProjectClass)
    {
        QTProjectClass->setWindowTitle(QApplication::translate("QTProjectClass", "Carbon", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QTProjectClass: public Ui_QTProjectClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTPROJECT_H
