#ifndef SERIAL_H
#define SERIAL_H

#include "string.h"

class Serial
{
public:
    Serial();

    int SetInterface(int fd, int speed, int parity);

    void SetBlocking(int fd, int should_block);

    void TestSerial();
};

#endif // SERIAL_H
