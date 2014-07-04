#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QTimer>
#include "Thread/SegController.h"

namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    //typedef boost::shared_ptr<Controller> ControllerPtr;
    Controller controller;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:


signals:

private:
    Ui::MainWindow *ui;


};

#endif // MAINWINDOW_H
