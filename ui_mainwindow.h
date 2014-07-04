/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Fri Jul 4 17:34:54 2014
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen_Origin;
    QAction *actionOpen_Target;
    QAction *actionStart_Evolving;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1381, 695);
        actionOpen_Origin = new QAction(MainWindow);
        actionOpen_Origin->setObjectName(QString::fromUtf8("actionOpen_Origin"));
        actionOpen_Target = new QAction(MainWindow);
        actionOpen_Target->setObjectName(QString::fromUtf8("actionOpen_Target"));
        actionStart_Evolving = new QAction(MainWindow);
        actionStart_Evolving->setObjectName(QString::fromUtf8("actionStart_Evolving"));
        actionStart_Evolving->setCheckable(true);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        MainWindow->setCentralWidget(centralwidget);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        toolBar->setMinimumSize(QSize(0, 40));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        toolBar->addAction(actionOpen_Origin);
        toolBar->addSeparator();
        toolBar->addAction(actionOpen_Target);
        toolBar->addSeparator();
        toolBar->addAction(actionStart_Evolving);
        toolBar->addSeparator();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionOpen_Origin->setText(QApplication::translate("MainWindow", "Open Origin", 0, QApplication::UnicodeUTF8));
        actionOpen_Target->setText(QApplication::translate("MainWindow", "Open Target", 0, QApplication::UnicodeUTF8));
        actionStart_Evolving->setText(QApplication::translate("MainWindow", "Start Evolving", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
