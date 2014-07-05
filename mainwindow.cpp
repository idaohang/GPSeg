#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QApplication>
#include <QtCore>
#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include <opencv2/opencv.hpp>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(new QGraphicsScene(this)),
    evol(new EvolveThread())
{
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);
    connect(this, SIGNAL(openOriginFile(QString)), evol, SLOT(setOriginFilename(QString)));
    connect(this, SIGNAL(openTargetFile(QString)), evol, SLOT(setTargetFilename(QString)));
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
        QGraphicsPixmapItem * pix = scene->addPixmap(QPixmap(filename));
        pix->setFlag(QGraphicsItem::ItemIsMovable);
        pix->setScale(0.3);
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
        QGraphicsPixmapItem * pix = scene->addPixmap(QPixmap(filename));
        pix->setFlag(QGraphicsItem::ItemIsMovable);
        pix->setScale(0.3);
        emit openTargetFile(filename);
    }
}
