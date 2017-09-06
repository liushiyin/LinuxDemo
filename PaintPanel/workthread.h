#ifndef WORKTHREAD_H
#define WORKTHREAD_H
#include<QThread>

class WorkerThread : public QThread
{
    Q_OBJECT
    void run() Q_DECL_OVERRIDE {
        QString result;

        emit resultReady(result);
    }
signals:
    void resultReady(const QString &s);

};

#endif // WORKTHREAD_H
