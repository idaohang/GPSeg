#ifndef SEGCONTROLLER_H
#define SEGCONTROLLER_H

#include <QObject>
#include "SegEvolver.h"
class Controller : public QObject
{
    Q_OBJECT
    QThread workerThread;
public:
    Controller();
    ~Controller();
public slots:
    void handleResults(const QString &);
    void startORstop(bool run);
signals:
    void operate(const QString &);
};

#endif
