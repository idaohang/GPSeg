#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QApplication>
#include <QtCore>
#include <QFileDialog>
#include <opencv2/opencv.hpp>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //QMainWindow::showMaximized();
    //connect(ui->actionStart_Evolving, SIGNAL(triggered(bool)), &controller, SLOT(startORstop(bool)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionStart_Evolving_triggered(bool checked)
{
    if(checked)
    {
        evol = new EvolveThread();
        evol->start();
    } else
    {
        evol->exit();
    }
}
