#ifndef WORKER_H
#define WORKER_H

#include "configwindow.h"
#include "ui_configwindow.h"
#include <QThread>
#include <QObject>
#include <QDebug>
#include <QMutex>
#include <QTimer>

class Worker : public QObject
{
    Q_OBJECT    
public:
    explicit Worker(QObject *parent = 0);
    void requestWork();
    void abort();

private:
    bool _working;
    bool _abort;
    QMutex mutex;

signals:
    void workRequested();
    void valueChanged(int);
    void finished();

public slots:
    void doWork();
};

#endif // WORKER_H
