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

Serial::Serial()
{
    isRunning = true;
    serialPort = -1;
    foundBoard = false;
}

int Serial::SetInterface(int fd, int speed)
{
    struct termios tty;
    memset (&tty, 0, sizeof tty);
    if (tcgetattr (fd, &tty) != 0)
    {
            //error_message ("error %d from tcgetattr", errno);
            return -1;
    }

    tty.c_iflag=0;
    tty.c_oflag=0;
    tty.c_cflag=CS8|CREAD|CLOCAL;           // 8n1, see termios.h for more information
    tty.c_lflag=0;
    tty.c_cc[VMIN]=1;
    tty.c_cc[VTIME]=5;

    cfsetospeed (&tty, speed);
    cfsetispeed (&tty, speed);

    /*
    tty.c_cflag     &=  ~PARENB;            // Make 8n1
    tty.c_cflag     &=  ~CSTOPB;
    tty.c_cflag     &=  ~CSIZE;
    tty.c_cflag     |=  CS8;

    tty.c_cflag     &=  ~CRTSCTS;           // no flow control
    tty.c_cc[VMIN]   =  0;                  // read doesn't block
    tty.c_cc[VTIME]  =  5;                  // 0.5 seconds read timeout
    tty.c_cflag     |=  CREAD | CLOCAL;     // turn on READ & ignore ctrl lines

    cfmakeraw(&tty);

    fcntl(fd, F_SETFL, FNDELAY);

    tty.c_lflag &= (~ICANON & ~ECHO);

    tcflush(fd, TCIFLUSH);
    */


    if (tcsetattr (fd, TCSANOW, &tty) != 0)
    {
            //error_message ("error %d froioctlm tcsetattr", errno);
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

bool Serial::IsConnected()
{
    return foundBoard;
}


void Serial::TestSerial(char *portname)
{
    //int fd = open (portname, O_RDWR | O_NOCTTY );
    int fd = open (portname, O_RDWR | O_NONBLOCK );
    if (fd < 0)
    {
        //error_message ("error %d opening %s: %s", errno, portname, strerror (errno));
        return;
    }

    if(SetInterface(fd, B57600) != 0) // set speed to 57600 bps
    {
        close(fd);
        return;
    }    

    unsigned char buffer[100];

    buffer[0] = 128;
    buffer[1] = 0;

    int n = write(fd, buffer, 2);

    int bytes_avail = 0;
    while(bytes_avail != 7)
    {
        sched_yield();
        ioctl(fd, FIONREAD, &bytes_avail);
    }


    /*
    fd_set         input;
    struct timeval timeout;

    FD_ZERO(&input);
    FD_SET(fd, &input);
    timeout.tv_sec  = 10;
    timeout.tv_usec = 0;

    int n = select(fd,&input,NULL,NULL,&timeout);
    */

    unsigned char buf[100];
    read(fd, buf, 7);
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
            //MessageBox.Show("Fritz found but firmware version is too old!\nFound "+version+" but this application requires 3 and above.");
            foundBoard = false;
        }        
        else
        {
            //serialPort = (String)port;
            foundBoard = true;
            //commPort = tstPort;
        }
    }
    else
    {
        foundBoard = false;
    }

    close(fd);
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

    if(SetInterface(serialPort, B57600) != 0) // set speed to 57600 bps, 8n1 (no parity)
    {
        close(serialPort);
        return -1;
    }

   foundBoard = true;
   return serialPort;
}

void Serial::Close()
{
   close(serialPort);
   foundBoard = false;
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




































