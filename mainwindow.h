#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QTimer>
#include <QtXml>
#include <QStandardItemModel>
#include "Thread/SegController.h"
#include "Thread/EvolveThread.h"
namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    //typedef boost::shared_ptr<Controller> ControllerPtr;
    //Controller controller;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionStart_Evolving_triggered(bool checked);
    void on_actionOpen_Origin_triggered();
    void on_actionOpen_Target_triggered();

    // set the GP Log Directory
    void on_setGPLogDir(QString dirname);

public slots:
    void tableview_individuals_clicked(QModelIndex index);
    void tableview_generations_clicked(QModelIndex index);

signals:
    void openOriginFile(QString filename);
    void openTargetFile(QString filename);

private:
    Ui::MainWindow *ui;

    // Evolving Thread
    EvolveThread *_evol;

    // GP Log File Directory
    QString _strLogDir;

    // Models of Table View
    // individuals' view model
    QStandardItemModel * _modelIndividuals;
    // generations' view model
    QStandardItemModel * _modelGenerations;
};

#endif // MAINWINDOW_H
