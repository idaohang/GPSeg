#ifndef EVOLVETHREAD_H
#define EVOLVETHREAD_H

#include <QThread>

class EvolveThread : public QThread
{
public:
    EvolveThread();
	void run();
};

#endif
