#ifndef SEGEVOLVER_H
#define SEGEVOLVER_H

#include <QObject>
#include <QThread>

class SegEvolver : public QObject
{
    Q_OBJECT
    QThread workerThread;

public slots:
    void doWork(const QString &result);

signals:
    void resultReady(const QString &result);

};

#endif
