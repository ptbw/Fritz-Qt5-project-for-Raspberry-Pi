#ifndef SERIAL_H
#define SERIAL_H

#include "string.h"
#include <QtSerialPort/QSerialPort>


class Serial
{

private:

    int sendQueueTop;
    int sendQueueBottom;
    bool isRunning;

    int serialPort;

    bool foundBoard;

public:

    Serial();

    int TestSerial();

    bool IsConnected();

    int Open(char * portName);

    void Close();

    bool SendPacket(unsigned char buffer[], int len);

    void Read(unsigned char buffer[], int offset, int len);

    int GetVersion(QByteArray requestData);

    QSerialPort *arduino;

    QString arduino_port_name;
    bool arduino_is_available;

};

#endif // SERIAL_H
