#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QApplication>
#include <QtCore>
#include <QFileDialog>
#include <QLabel>
#include <opencv2/opencv.hpp>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    evol(new EvolveThread())
{
    ui->setupUi(this);

    connect(this, SIGNAL(openOriginFile(QString)), evol, SLOT(setOriginFilename(QString)));
    connect(this, SIGNAL(openTargetFile(QString)), evol, SLOT(setTargetFilename(QString)));
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
        evol->start();
    }
    else
    {
        evol->terminate();

    }
}


void MainWindow::on_actionOpen_Origin_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open Origin File");
    if (filename == "")
        return;
    else
    {
        ui->label_origin->setPixmap(QPixmap(filename).scaled(ui->label_origin->width(),ui->label_origin->height(),Qt::KeepAspectRatio));
        emit openOriginFile(filename);
    }

}

void MainWindow::on_actionOpen_Target_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open Evolving Targe File");
    if (filename == "")
        return;
    else
    {
        ui->label_target->setPixmap(QPixmap(filename).scaled(ui->label_target->width(),ui->label_target->height(),Qt::KeepAspectRatio));
        emit openTargetFile(filename);
    }
}
