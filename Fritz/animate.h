#ifndef ANIMATE_H
#define ANIMATE_H

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "serial.h"
#include <QThread>
#include <QObject>
#include <QDebug>
#include <QMutex>
#include <QTimer>
#include <QTime>

class Animate : public QObject
{
    Q_OBJECT
public:
    explicit Animate(Serial *serial);
    void requestWork();
    void abort();    
    void SpeakMessage(QString msg);

private:
    bool _working;
    bool _abort;
    Serial *_serial;
    QMutex mutex;

    QStringList text;

signals:
    void workRequested();
    void animate();
    void finished();
    void done();

public slots:
    void doWork();
    void doWorkOld();
};


#endif // ANIMATE_H
