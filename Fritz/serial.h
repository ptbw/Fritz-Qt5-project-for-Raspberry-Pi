#ifndef SERIAL_H
#define SERIAL_H

#include "string.h"
#include <QtSerialPort/QSerialPort>
#include <QObject>


class Serial : public QObject
{

private:

    //QString arduino_port_name;
    static const int ARDUINO_GET_ID = 0; // returns ARDU
    static const int ARDUINO_RESET = 1; //
    static const int ARDUINO_SET_OBJECT = 2; //
    static const int ARDUINO_SET_SERVO = 3; //
    static const int ARDUINO_HEARTBEAT = 4;
    static const int ARDUINO_RELEASE_SERVO = 5;
    static const int ARDUINO_GET_IR = 6;
    static const int ARDUINO_GET_SONAR = 7;

    static const int ARDUINO_LOAD_CONFIG = 32;
    static const int ARDUINO_SAVE_CONFIG = 33;
    static const int ARDUINO_SAVE_SEQUENCE = 34;

    int sendQueueTop;
    int sendQueueBottom;
    bool isRunning;

    int serialPort;

    bool foundBoard;

    double sonarValue;

    int version;

    static const int waitTimeOut = 50;

public:

    Serial();
    ~Serial();

    bool IsConnected();

    int Open();

    void Close();

    void DoTest(Qt::CheckState state, int min, int max, int pin, int val);

    int TestSerialOld();
    bool SendPacketOld(QByteArray data, int slen, int rlen);
    void ReadOld(QByteArray data);

    int TestSerial();
    bool SendPacket(QByteArray data, int slen, int rlen);
    void handleReadyRead();
    void handleError(QSerialPort::SerialPortError serialPortError);

    int GetVersion(QByteArray data);

    int GetVersion();

    double GetSonar();

    void SetSonar(int outPin, int inPin);

    void SetServo(int pin, float value, int max, int min, int trim, bool inverted = false);

    void SetServo(int pin, int value);

    void SendCommand(int cmd);

    void SendCommand(int cmd, int pin);

    void SendCommand(int cmd, int pin, int value);

    void SendCommand(int cmd, int pin, short value);

    void SendCommand(int cmd, int pin, quint8 value);

    void SendCommand(int cmd, QList<int> dat);

    void SendCommand(int cmd, QByteArray dat);

    QSerialPort *arduino;

    QString arduino_port_name;
    bool arduino_is_available;



};

#endif // SERIAL_H
