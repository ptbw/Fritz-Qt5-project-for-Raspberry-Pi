#include "string.h"
#include "strings.h"
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sched.h>
#include "serial.h"

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

Serial::Serial()
{

    foundBoard = false;

    arduino_is_available = true;
    arduino_port_name = "/dev/ttyUSB0";

    arduino = new QSerialPort;

}

bool Serial::IsConnected()
{
    return foundBoard;
}


int Serial::TestSerial()
{
    int version = -1;

    if(!arduino_is_available){
       return -1;
    }

    // open and configure the serialport
    arduino->setPortName(arduino_port_name);
    arduino->open(QSerialPort::ReadWrite);
    arduino->setBaudRate(QSerialPort::Baud57600);
    arduino->setDataBits(QSerialPort::Data8);
    arduino->setParity(QSerialPort::NoParity);
    arduino->setStopBits(QSerialPort::OneStop);
    arduino->setFlowControl(QSerialPort::NoFlowControl);

    QByteArray sendData;
    QByteArray requestData;

    sendData[0] = 128;
    sendData[1] = 0;

    if(arduino->isWritable())
    {
        arduino->write(sendData);
        if (arduino->waitForReadyRead(10000))
        {
            // read request
            requestData = arduino->readAll();
            while (arduino->waitForReadyRead(10))
                requestData += arduino->readAll();

            //QMessageBox::information(this, "Information", requestData.toUpper());
            version = GetVersion(requestData);
        }
    }

    arduino->close();
    return version;
}

int Serial::Open(char * portname)
{
    foundBoard = true;

    serialPort = open (portname, O_RDWR | O_NOCTTY );
    if (serialPort < 0)
    {
        //error_message ("error %d opening %s: %s", errno, portname, strerror (errno));
        serialPort = -1;
        return serialPort;
    }


   foundBoard = true;
   return serialPort;
}

void Serial::Close()
{
   close(serialPort);
   foundBoard = false;
}

int Serial::GetVersion(QByteArray buf)
{

    char b1 = buf[0];
    char b2 = buf[1];
    char b3 = buf[2];
    char b4 = buf[3];
    char v1 = buf[4];
    char v2 = buf[5];
    char v3 = buf[6];

    int version = ((v1-'0')*100)+((v2-'0')*10)+(v3-'0');

    if ((b1 == 'A') && (b2 == 'R') && (b3 == 'D') && (b4 == 'U'))
    {
        if (version < 4)
        {
            foundBoard = false;
        }
        else
        {
            foundBoard = true;
        }
    }
    else
    {
        foundBoard = false;
        version = -2;
    }
    return version;
}


bool Serial::SendPacket(unsigned char buffer[], int pl)
{
    if(foundBoard && serialPort != -1)
    {
        if ((buffer[0] & 127) >= 32)
        write(serialPort, buffer, pl);
        Read(buffer, 0, 3);

        int len;
        if ((buffer[0] & 127) >= 32)
            len = (buffer[1] | (buffer[2]<<7));
        else
            len = buffer[1];

        if (len > 0)
            Read(buffer, 3, len);

        return true;
    }

    //error_message ("Port not open");
    return false;
}


void Serial::Read(unsigned char buffer[], int offset, int len)
{
    if(foundBoard && serialPort != -1)
    {
        while (true)
        {
            int l = read(serialPort,&buffer[offset], len);
            offset+=l;
            len-=l;
            if (len <= 0) return;
        }
    }

    //error_message ("Port not open");
    return;
}




































