#include "i.h"
#include "worker.h"

Worker::Worker(QObject *parent) :
    QObject(parent)
{
    _working = false;
    _abort = false;
}

void Worker::doWork()
{
    for (int i = 0; i < 100; i ++) {

            mutex.lock();
            bool abort = _abort;
            mutex.unlock();

            if (abort) {
                break;
            }

            QEventLoop loop;
            QTimer::singleShot(100, &loop, SLOT(quit()));
            loop.exec();

            //emit valueChanged(QString::number(i));
            emit valueChanged(i);
     }

    mutex.lock();
    _working = false;
    mutex.unlock();

    emit finished();
}

void Worker::requestWork()
{
    mutex.lock();
    _working = true;
    _abort = false;
    mutex.unlock();

    emit workRequested();
}

void Worker::abort()
{
    if (_working) {
        _abort = true;
        qDebug()<<"Request worker aborting in Thread "<<thread()->currentThreadId();
    }
}
