#ifndef SERIAL_H
#define SERIAL_H

#include "string.h"

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

    int SetInterface(int fd, int speed);

    void SetBlocking(int fd, int should_block);

    void TestSerial(char * portName);

    bool IsConnected();

    int Open(char * portName);

    void Close();

    bool SendPacket(unsigned char buffer[], int len);

    void Read(unsigned char buffer[], int offset, int len);

};

#endif // SERIAL_H
