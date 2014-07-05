#ifndef EVOLVETHREAD_H
#define EVOLVETHREAD_H

#include <QThread>
#include <QString>

class EvolveThread : public QThread
{
Q_OBJECT
public:
    EvolveThread();
    void run();
public slots:
    void setTargetFilename(QString target);
    void setOriginFilename(QString origin);
private:
    QString _strTargetFile;
    QString _strOriginFile;
};

#endif
