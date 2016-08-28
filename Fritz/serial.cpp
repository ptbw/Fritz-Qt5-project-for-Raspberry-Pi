#include "string.h"
#include "strings.h"
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include "serial.h"

Serial::Serial()
{
}

int Serial::SetInterface(int fd, int speed, int parity)
{
    struct termios tty;
    memset (&tty, 0, sizeof tty);
    if (tcgetattr (fd, &tty) != 0)
    {
            //error_message ("error %d from tcgetattr", errno);
            return -1;
    }

    cfsetospeed (&tty, speed);
    cfsetispeed (&tty, speed);

    /* Setting other Port Stuff */
    tty.c_cflag     &=  ~PARENB;            // Make 8n1
    tty.c_cflag     &=  ~CSTOPB;
    tty.c_cflag     &=  ~CSIZE;
    tty.c_cflag     |=  CS8;

    tty.c_cflag     &=  ~CRTSCTS;           // no flow control
    tty.c_cc[VMIN]   =  0;                  // read doesn't block
    tty.c_cc[VTIME]  =  1;                  // 0.5 seconds read timeout
    tty.c_cflag     |=  CREAD | CLOCAL;     // turn on READ & ignore ctrl lines

    cfmakeraw(&tty);
    tcflush(fd, TCIFLUSH);

    if (tcsetattr (fd, TCSANOW, &tty) != 0)
    {
            //error_message ("error %d from tcsetattr", errno);
            return -1;
    }
    return 0;

}

void Serial::SetBlocking (int fd, int should_block)
{
    struct termios tty;
    memset (&tty, 0, sizeof tty);
    if (tcgetattr (fd, &tty) != 0)
    {
            //error_message ("error %d from tggetattr", errno);
            return;
    }

    tty.c_cc[VMIN]  = should_block ? 1 : 0;
    tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

    if (tcsetattr (fd, TCSANOW, &tty) != 0)
    {
            //error_message ("error %d setting term attributes", errno);
            return;
     }
}



void Serial::TestSerial()
{
    char *portname = "/dev/ttyUSB0";

    int fd = open (portname, O_RDWR | O_NOCTTY );
    if (fd < 0)
    {
        //error_message ("error %d opening %s: %s", errno, portname, strerror (errno));
        return;
    }

    if(SetInterface(fd, B57600, 0) != 0) // set speed to 57600 bps, 8n1 (no parity)
    {
        return;
    }

    //SetBlocking(fd, 0);          // set no blocking

    unsigned char buffer[100];

    buffer[0] = 128;
    buffer[1] = 0;

    write(fd, buffer, 2);
    usleep ((7 + 25) * 100);

    read(fd, buffer, 7);
    char b1 = buffer[0];
    char b2 = buffer[1];
    char b3 = buffer[2];
    char b4 = buffer[3];
    char v1 = buffer[4];
    char v2 = buffer[5];
    char v3 = buffer[6];

    int version = ((v1-'0')*100)+((v2-'0')*10)+(v3-'0');

    if ((b1 == 'A') && (b2 == 'R') && (b3 == 'D') && (b4 == 'U'))
    {
        if (version < 4)
        {
            //MessageBox.Show("Fritz found but firmware version is too old!\nFound "+version+" but this application requires 3 and above.");
        }
        else
        {
            //serialPort = (String)port;
            //foundBoard = true;
            //commPort = tstPort;
        }
    }
    else
    {

    }
    close(fd);

}
