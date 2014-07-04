#include "../SegController.h"
#include <iostream>

Controller::Controller()
{
    SegEvolver *worker = new SegEvolver();
    std::cout << "Controller Constructor" << std::endl;
    worker->moveToThread(&workerThread);
    std::cout << "Controller Constructor" << std::endl;
    connect(&workerThread, SIGNAL(finished()), worker, SLOT(deleteLater()));
    std::cout << "Controller Constructor" << std::endl;
    connect(this, SIGNAL(operate(QString)), worker, SLOT(doWork(QString)));
    std::cout << "Controller Constructor" << std::endl;
    connect(worker, SIGNAL(resultReady(QString)), this, SLOT(handleResults(QString)));
    std::cout << "Controller Constructor" << std::endl;
    //workerThread.start();
    std::cout << "Controller Constructor" << std::endl;
}

Controller::~Controller()
{
    workerThread.quit();
    workerThread.wait();
}

void Controller::handleResults(const QString &)
{

}

void Controller::startORstop(bool run)
{
    if(run)
    {
        std::cout << "start" << std::endl;
        emit operate("run");
    }
}
