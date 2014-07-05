#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QApplication>
#include <QtCore>
#include <QFileDialog>
#include <opencv2/opencv.hpp>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    evol(NULL)
{
    ui->setupUi(this);

    //QMainWindow::showMaximized();
    //connect(ui->actionStart_Evolving, SIGNAL(triggered(bool)), &controller, SLOT(startORstop(bool)));

}

MainWindow::~MainWindow()
{
    if(evol)
    {
        evol->terminate();
        delete evol;
        evol = NULL;
    }
    delete ui;
}

void MainWindow::on_actionStart_Evolving_triggered(bool checked)
{
    if(checked)
    {
        std::cout << evol << std::endl;
        if (evol)
        {
            std::cout << "delete thread.." << std::endl;
            evol->terminate();
            delete evol;
        }
        evol = new EvolveThread();
        evol->start();
    }
    else
    {
        if(evol)
        {
            evol->terminate();
            delete evol;
            evol = NULL;
        }
    }
}
