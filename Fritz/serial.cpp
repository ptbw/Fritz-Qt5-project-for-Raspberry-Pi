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
#include <QDebug>

Serial::Serial()
    : QObject()
{

    foundBoard = false;

    arduino_is_available = true;
    arduino_port_name = "/dev/ttyACM0";

    arduino = new QSerialPort;

    Open();
}

Serial::~Serial()
{
    Close();
}

bool Serial::IsConnected()
{
    return foundBoard;
}

int Serial::TestSerialOld()
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
        if (!arduino->waitForBytesWritten(waitTimeOut))
            return version;

        if (arduino->waitForReadyRead(waitTimeOut))
        {
            // read request
            requestData = arduino->readAll();
            while (arduino->waitForReadyRead(100))
                requestData += arduino->readAll();

            //QMessageBox::information(this, "Information", requestData.toUpper());
            version = GetVersion(requestData);
        }
    }

    return version;
}

int Serial::Open()
{
    // open and configure the serialport
    arduino->setPortName(arduino_port_name);
    if( !arduino->open(QSerialPort::ReadWrite) )
    {
      qDebug()<<"Unable to open serial port";
    }
    I::sleep(2);
    arduino->setBaudRate(QSerialPort::Baud57600);
    arduino->setDataBits(QSerialPort::Data8);
    arduino->setParity(QSerialPort::NoParity);
    arduino->setStopBits(QSerialPort::OneStop);
    arduino->setFlowControl(QSerialPort::NoFlowControl);

    if(arduino->isWritable())
        arduino_is_available = true;

    sonarValue = 9999.0;
    version = -1;

    connect(arduino, &QSerialPort::readyRead, this, &Serial::handleReadyRead);
    //connect(arduino, &QSerialPort::serialPortError, this, &Serial::handleError);
    //connect(arduino, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),this, &Serial::handleError);
    //connect(&m_timer, &QTimer::timeout, this, &SerialPortReader::handleTimeout);

    TestSerial();

   return 0;
}

void Serial::Close()
{    
   if(arduino->isOpen())
   {
       arduino->close();
   }
   arduino_is_available = false;
   foundBoard = false;
}

double Serial::GetSonar()
{
    return sonarValue;
}

int Serial::GetVersion()
{
    return version;
}

int Serial::TestSerial()
{
    version = -1;

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
       arduino->waitForBytesWritten(waitTimeOut);
    }

    return version;
}

bool Serial::SendPacket(QByteArray buffer, int slen, int rlen)
{
    unsigned int command;
    int length;

    QByteArray sendData;
    int idx = 0;
    int crc;
    //int high;
    // Before CRC
    // 131 - Command
    //   2 - pin?
    // 102 - lsb position
    //  11
    //   0
    //   0
    //   0
    // 106 - msb position

    command = crc = buffer[0];    // Command
    length = slen - 2;
    if( length < 0 )
        length = 0;

    sendData[idx++] = command;
    sendData[idx++] = (quint8) (length & 127);
    crc ^= (quint8) (length & 127);

    if((command & 127) >= 32)
    {
        sendData[idx++] = (quint8) (length >> 7);
        crc ^= (quint8) (length >> 7);
    }

    for(int i = 1; i < slen; i++)
    {
        sendData[idx++] = buffer[i];
        crc ^= buffer[i];
    }

    sendData[9] = crc;

    // After CRC
    // 131 - Command
    //   6 - CRC
    //   2 - pin
    // 102 - lsb position
    //  11
    //   0
    //   0
    //   0
    // 106

    if(arduino->isWritable())
    {
        arduino->write(sendData,9);
        arduino->waitForBytesWritten(waitTimeOut);
        //qWarning() << "Send: " << QString(sendData.toHex()) << endl;
        return true;
    }
    qWarning() << "Failed to write" << endl;
    return false;
}

void Serial::handleReadyRead()
{
    I::msleep(10);
    QByteArray requestData = arduino->readAll();
    while(arduino->bytesAvailable())
    {
        I::msleep(2);
        requestData = requestData + arduino->readAll();
    }


    //qWarning() << "Rec:  " << QString(requestData.toHex()) << endl;

    while(true)
    {
        if(((uchar)requestData[0] & 127) == 'A')
        {
            version = GetVersion(requestData);
            qWarning() << "Version: " << version << endl;
            requestData.remove(0,7);
        }
        else if(((uchar)requestData[0] & 127) == ARDUINO_GET_SONAR)
        {
          int x = ((int)requestData[3] | (requestData[4] << 7));
          // convert distance to cm
          double dist = (float)((float)x / 29.10f);
          if( dist > 0 )
              sonarValue = dist;

          //qWarning() << "Rec:  " << QString(requestData.toHex()) << endl;
          //qWarning() << "Sonar: " << sonarValue << endl;
          requestData.remove(0,9);
        }
        else if(((uchar)requestData[0] & 127) == ARDUINO_SET_SERVO)
        {
          requestData.remove(0,9);
        }
        else
          requestData.remove(0,9);

        if(requestData.length()<9)
            break;
     }
}

void Serial::handleError(QSerialPort::SerialPortError serialPortError)
{
    arduino->flush();
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

bool Serial::SendPacketOld(QByteArray buffer, int slen, int rlen)
{
    unsigned int command;
    int length;

    QByteArray sendData;
    int idx = 0;
    int crc;
    //int high;
    // Before CRC
    // 131 - Command
    //   2 - pin?
    // 102 - lsb position
    //  11
    //   0
    //   0
    //   0
    // 106 - msb position

    command = crc = buffer[0];    // Command
    length = slen - 2;
    if( length < 0 )
        length = 0;

    sendData[idx++] = command;
    sendData[idx++] = (quint8) (length & 127);
    crc ^= (quint8) (length & 127);

    if((command & 127) >= 32)
    {
        sendData[idx++] = (quint8) (length >> 7);
        crc ^= (quint8) (length >> 7);
    }

    for(int i = 1; i < slen; i++)
    {
        sendData[idx++] = buffer[i];
        crc ^= buffer[i];
    }

    sendData[9] = crc;

    // After CRC
    // 131 - Command
    //   6 - CRC
    //   2 - pin
    // 102 - lsb position
    //  11
    //   0
    //   0
    //   0
    // 106

    QByteArray requestData;
    if(arduino->isWritable())
    {
        arduino->write(sendData,9);
        if (!arduino->waitForBytesWritten(waitTimeOut))
            return false;

        if (arduino->waitForReadyRead(waitTimeOut))
        {
            // read request
            requestData = arduino->readAll();
            //while (arduino->waitForReadyRead(100))
                //requestData += arduino->readAll();

            if(((uchar)requestData[0] & 127) == ARDUINO_GET_SONAR)
            {
              int x = ((int)requestData[3] | (requestData[4] << 7));
              // convert distance to cm
              sonarValue = (float)((float)x / 29.10f);
            }
        }
        return true;
    }
    return false;
}

void Serial::ReadOld(QByteArray requestData)
{
    if (arduino->waitForReadyRead(waitTimeOut))
    {
        // read request
        requestData = arduino->readAll();
        while (arduino->waitForReadyRead(100))
            requestData += arduino->readAll();

        if(((uchar)requestData[0] & 127) == ARDUINO_GET_SONAR)
        {
          int x = ((int)requestData[3] | (requestData[4] << 7));
          // convert distance to cm
          sonarValue = (float)((float)x / 29.10f);
        }
    }
}

void Serial::DoTest( Qt::CheckState state, int min, int max, int pin, int val)
{
    //range min - max maps to 0 - 100 so val maps to min + val * ( range / 100 )
    float range = max - min;
    int pos = (int)min + ( val * range/100);

    if(state == Qt::Checked)
    {
        SetServo(pin, pos);
    }
}

void Serial::SetSonar(int sonarOutPin, int sonarInPin)
{
   SendCommand(ARDUINO_GET_SONAR, sonarOutPin, (short) sonarInPin);
}

void Serial::SetServo(int pin, int value)
{
   SendCommand(ARDUINO_SET_SERVO, pin, (short)value + 1500);
}

void Serial::SendCommand(int cmd)
{
  QByteArray buffer;
  buffer.resize(3);

  buffer[0] = (quint8)(128 | cmd);

  SendPacket(buffer, 1, 1);
}

void Serial::SendCommand(int cmd, int pin)
{
  QByteArray buffer;
  buffer.resize(3);

  buffer[0] = (quint8)(128 | cmd);
  buffer[1] = (quint8)(pin & 127);
  buffer[2] = (quint8)((buffer[0] ^ buffer[1] ^ 1) & 127);

  SendPacket(buffer, 3, 2);
}

void Serial::SendCommand(int cmd, int pin, int value)
{
  QByteArray buffer;

  buffer.resize(8);
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

  buffer.resize(5);
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

  buffer.resize(4);
  buffer[0] = (quint8)(128 | cmd);
  buffer[1] = (quint8)(pin & 127);
  buffer[2] = (quint8)(value & 127);
  buffer[3] = (quint8)((buffer[0] ^ buffer[1] ^ buffer[2] ^ 2) & 127);

 SendPacket(buffer, 4, 2);
}

void Serial::SendCommand(int cmd, QList<int> dat)
{
  QByteArray buffer;

  buffer.resize(4096);
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

  buffer.resize(4096);
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


































