#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QTimer>
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

signals:

private:
    Ui::MainWindow *ui;
    EvolveThread *evol;


};

#endif // MAINWINDOW_H
