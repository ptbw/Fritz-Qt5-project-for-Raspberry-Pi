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
#include "i.h"

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QList>

Serial::Serial()
{

    foundBoard = false;

    arduino_is_available = true;
    arduino_port_name = "/dev/ttyUSB0";

    arduino = new QSerialPort;

    Open();


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


    QByteArray sendData;
    QByteArray requestData;

    sendData[0] = 128;
    sendData[1] = 0;

    if(arduino->isWritable())
    {
        arduino->write(sendData);
        I::sleep(2);
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

    return version;
}

int Serial::Open()
{
    if(!arduino_is_available){
       return -1;
    }

    if(arduino->isOpen())
    {
        arduino->close();
    }

    // open and configure the serialport
    arduino->setPortName(arduino_port_name);
    arduino->open(QSerialPort::ReadWrite);
    arduino->setBaudRate(QSerialPort::Baud57600);
    arduino->setDataBits(QSerialPort::Data8);
    arduino->setParity(QSerialPort::NoParity);
    arduino->setStopBits(QSerialPort::OneStop);
    arduino->setFlowControl(QSerialPort::NoFlowControl);

    if(arduino->isWritable())
        arduino_is_available = true;

   return 0;
}

void Serial::Close()
{
   if(arduino->isOpen())
   {
       arduino->close();
   }
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

bool Serial::SendPacket(QByteArray sendData, int slen, int rlen)
{
    QByteArray requestData;
    if(arduino->isWritable())
    {
        arduino->write(sendData);
        I::msleep(10);
        if (arduino->waitForReadyRead(10))
        {
            // read request
            requestData = arduino->readAll();
            while (arduino->waitForReadyRead(10))
                requestData += arduino->readAll();
        }
        return true;
    }
    return false;
}

void Serial::Read(QByteArray requestData)
{
    if(arduino->isWritable())
    {
        if (arduino->waitForReadyRead(1000))
        {
            // read request
            requestData = arduino->readAll();
            while (arduino->waitForReadyRead(10))
                requestData += arduino->readAll();
        }
    }
}

void Serial::SendCommand(int cmd)
{
  QByteArray buffer;

  buffer[0] = (quint8)(128 | cmd);

  SendPacket(buffer, 1, 1);
}

void Serial::SendCommand(int cmd, int pin)
{
  QByteArray buffer;

  buffer[0] = (quint8)(128 | cmd);
  buffer[1] = (quint8)(pin & 127);
  buffer[2] = (quint8)((buffer[0] ^ buffer[1] ^ 1) & 127);

  SendPacket(buffer, 3, 2);
}

void Serial::SendCommand(int cmd, int pin, int value)
{
  QByteArray buffer;

  buffer[0] = (quint8)(128 | cmd);
  buffer[1] = (quint8)(pin & 127);
  buffer[2] = (quint8)(value & 127);
  buffer[3] = (quint8)((value >> 7) & 127);
  buffer[4] = (quint8)((value >> 14) & 127);
  buffer[5] = (quint8)((value >> 21) & 127);
  buffer[6] = (quint8)((value >> 28) & 127);
  buffer[7] = (quint8)((buffer[0] ^ buffer[1] ^ buffer[2] ^ buffer[3] ^ buffer[4] ^ buffer[5] ^ buffer[6] ^ 6) & 127);

  SendPacket(buffer, 8, 2);
}

void Serial::SendCommand(int cmd, int pin, short value)
{
  QByteArray buffer;

  buffer[0] = (quint8)(128 | cmd);
  buffer[1] = (quint8)(pin & 127);
  buffer[2] = (quint8)(value & 127);
  buffer[3] = (quint8)((value >> 7) & 127);
  buffer[4] = (quint8)((buffer[0] ^ buffer[1] ^ buffer[2] ^ buffer[3] ^ 3) & 127);

  SendPacket(buffer, 5, 2);
}

void Serial::SendCommand(int cmd, int pin, quint8 value)
{
  QByteArray buffer;

  buffer[0] = (quint8)(128 | cmd);
  buffer[1] = (quint8)(pin & 127);
  buffer[2] = (quint8)(value & 127);
  buffer[3] = (quint8)((buffer[0] ^ buffer[1] ^ buffer[2] ^ 2) & 127);

 SendPacket(buffer, 4, 2);
}

void Serial::SendCommand(int cmd, QList<int> dat)
{
  QByteArray buffer;

  buffer[0] = (quint8)(128 | cmd);

  int i, j;
  for (j = 1, i = 0; (i < dat.size()); i++)
  {
    buffer[j++] = (quint8)(dat[i] & 127);
    buffer[j++] = (quint8)((dat[i] >> 7) & 127);
  }

  int crc = buffer[0];
  crc ^= (j - 1) & 127;
  crc ^= (j - 1) >> 7;
  for (i = 1; i < j; i++) crc ^= buffer[i];

  buffer[j++] = (quint8)(crc & 127);

  SendPacket(buffer, j, 1);
}

void Serial::SendCommand(int cmd, QByteArray dat)
{
  QByteArray buffer;

  buffer[0] = (quint8)(128 | cmd);

  int i, j;
  for (j = 1, i = 0; (i < dat.size()); i++)
      buffer[j++] = (quint8)dat[i];

  int crc = buffer[0];
  crc ^= (j - 1) & 127;
  crc ^= (j - 1) >> 7;
  for (i = 1; i < j; i++) crc ^= buffer[i];

  buffer[j++] = (quint8)(crc & 127);

  SendPacket(buffer, j, 1);
}


































