#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <math.h>

#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

// Support for Wii controller
#include <bluetooth/bluetooth.h>
#include <cwiid.h>

extern "C" int lk_init(void);
extern "C" unsigned char exp_motors(unsigned char module_id_lower_two_bits, unsigned char motor_in, unsigned char direction_in, unsigned char speed_in , unsigned int* buffer_in);

//Laika board
#include <laika/laika.h>

using namespace std;

#define LOW_GEAR 	0
#define MED_GEAR 	1
#define HIGH_GEAR 	2

#define COLOUR_RED    1
#define COLOUR_GREEN  2
#define COLOUR_BLUE   4

// Variables used in call backs and accessed in the main thread. Made volatile so they are not cached
static volatile int leftCount = 0;
static volatile int rightCount = 0;
static volatile bool inMenu = true;
static volatile int gear = MED_GEAR;
static volatile bool running = true;

unsigned int lk_buffer[LK_BUFFER_SIZE];

int minSpeed = 130;
int maxSpeed = 255;

cwiid_wiimote_t * wiimote = 0;

void setLed(int l)
{

}

void flashLED( int colour, int times, int duration )
{
    printf(" %d, %d, %d\n",colour,time,duration);
}

// Set the left motor speed independently of the right
void SetLeftMotor(int speed)
{
    static int prev_speed = 0;

    if(prev_speed == speed)
        return;

    unsigned int ret;
    if( speed < 0 )
    {
        unsigned int uspeed = min(speed * -1, 255);
        ret = exp_motors(MODULE_ONE, EXP_MOTOR_1, EXP_MOTOR_REVERSE, uspeed, lk_buffer);
    }
    else if(speed > 0)
    {
        unsigned int uspeed = min(speed, 255);
        ret = exp_motors(MODULE_ONE, EXP_MOTOR_1, EXP_MOTOR_FORWARD, uspeed, lk_buffer);
    }
    else
    {
        ret = exp_motors(MODULE_ONE, EXP_MOTOR_1, EXP_MOTOR_STOP, 0, lk_buffer);
    }
    printf("Return %d\n",ret);

}

// Set the right motor speed independently of the left
void SetRightMotor(int speed)
{
    static int prev_speed = 0;

    if(prev_speed == speed)
        return;

    unsigned int ret;
    if( speed < 0 )
    {
        unsigned int uspeed = min(speed * -1, 255);
        ret = exp_motors(MODULE_ONE, EXP_MOTOR_2, EXP_MOTOR_REVERSE, uspeed, lk_buffer);
    }
    else if( speed > 0 )
    {
        unsigned int uspeed = min(speed, 255);
        ret = exp_motors(MODULE_ONE, EXP_MOTOR_2, EXP_MOTOR_FORWARD, uspeed, lk_buffer);
    }
    else
    {
        ret = exp_motors(MODULE_ONE, EXP_MOTOR_2, EXP_MOTOR_STOP, 0, lk_buffer);
    }
    printf("Return %d\n",ret);
}

void Stop()
{
    SetRightMotor(0);
    SetLeftMotor(0);
}


int pairWiiMote(cwiid_mesg_callback_t *callback ) // wiimote handle
{

    bdaddr_t bdaddr = {{0, 0, 0, 0, 0, 0}};   // BDADDR_ANY - bluetooth device address

    // First pair with the Wiimote
    printf("Put Wiimote in discoverable mode now (press 1+2)...\n");
    if (!(wiimote = cwiid_open(&bdaddr, 0))) {
        fprintf(stderr, "Unable to connect to wiimote\nReturn to main menu\n");
        flashLED( COLOUR_RED, 5, 250 );
        return -1;
    }

    // Buzz the Wiimote to confirm pairing
    cwiid_set_rumble(wiimote, 1);
    sleep(1);
    cwiid_set_rumble(wiimote, 0);

    // Set a call back for messages from the Wiimote
    if (cwiid_set_mesg_callback(wiimote, callback))
    {
        fprintf(stderr, "Unable to set message callback\n");
        flashLED( COLOUR_RED, 5, 250 );
        return -2;
    }

    // Set the reporting mode from the Wimote
    if (cwiid_set_rpt_mode(wiimote, CWIID_RPT_EXT | CWIID_RPT_BTN ))
    {
        fprintf(stderr, "Error setting report mode\n");
        flashLED( COLOUR_RED, 5, 250 );
        return -3;
    }

    // Finally enable messages from the Wiimote
    if (cwiid_enable(wiimote, CWIID_FLAG_MESG_IFC))
    {
        fprintf(stderr, "Error enabling messages\n");
        flashLED( COLOUR_RED, 5, 250 );
        return -4;
    }

    flashLED(COLOUR_GREEN, 2, 500 );
    return 0;
}

void unPairWiiMote()
{
    if(wiimote == 0)
        return;

    // Disable our Wii functions
    if(cwiid_disable(wiimote, CWIID_FLAG_MESG_IFC))
    {
        fprintf(stderr, "Error disabling messages\n");
    }

    // Finally shutdown the Wii controller
    if (cwiid_close(wiimote))
    {
        fprintf(stderr, "Error on wiimote disconnect\n");
    }
    wiimote = 0;
}

void cwiid_callback(cwiid_wiimote_t *wiimote, int mesg_count,
                    union cwiid_mesg mesg[], struct timespec *timestamp)
{
    int i;
    int leftStick;
    int rightStick;

    int leftRatio = 6;
    int rightRatio = 12;

    int leftSpeed = 0;
    int rightSpeed = 0;


    for (i=0; i < mesg_count; i++)
    {
        switch (mesg[i].type) {
        case CWIID_MESG_NUNCHUK:
        case CWIID_MESG_ACC:
        case CWIID_MESG_IR:
            break;
        case CWIID_MESG_CLASSIC:
            printf("button: %4X\n",mesg[i].classic_mesg.buttons);
            // Wii classic controller uses two proportional sticks and many buttons
            if( mesg[i].classic_mesg.buttons == 0x0001 )
            {
                // Use UP on the dpad to change gear up
                gear++;
                if( gear > HIGH_GEAR )
                    gear = HIGH_GEAR;

                if( gear == HIGH_GEAR )
                {
                    // Flash three times
                    flashLED(COLOUR_BLUE, 3, 100);
                }
                else if( gear == MED_GEAR )
                {
                    // Flash twice
                    flashLED(COLOUR_BLUE, 2, 100);
                }
                else  if( gear == LOW_GEAR )
                {
                    // Flash once
                    flashLED(COLOUR_BLUE, 1, 100);
                }
            }
            else if( mesg[i].classic_mesg.buttons == 0x4000 )
            {
                // Use DOWN on the dpad to change gear down
                gear--;
                if( gear < LOW_GEAR )
                    gear = LOW_GEAR;

                if( gear == HIGH_GEAR )
                {
                    // Flash three times
                    flashLED(COLOUR_BLUE, 3, 100);
                }
                else if( gear == MED_GEAR )
                {
                    // Flash twice
                    flashLED(COLOUR_BLUE, 2, 100);
                }
                else  if( gear == LOW_GEAR )
                {
                    // Flash once
                    flashLED(COLOUR_BLUE, 1, 100);
                }
            }
            else if( mesg[i].classic_mesg.buttons == 0x800 )
            {
                // Use HOME stop and return to main menu
                printf("Stop and return to main menu\n");
                running = false;
            }


            // Left stick Up = 63, Down = 0, Centre = 32
            // Right stick Up = 31, Down = 0, Centre = 16
            // Proportional joy sticks for turning, forward and reverse
            leftStick = mesg[i].classic_mesg.l_stick[CWIID_Y];
            rightStick = mesg[i].classic_mesg.r_stick[CWIID_Y];

            if( gear == LOW_GEAR )
            {
                leftRatio = 4;
                rightRatio = 8;
            }
            else if( gear == MED_GEAR )
            {
                leftRatio = 5;
                rightRatio = 10;
            }
            else
            {
                leftRatio = 6;
                rightRatio = 12;
            }

            leftSpeed = (int)((leftStick-32)*leftRatio);
            rightSpeed = (int)((rightStick-16)*rightRatio);

            printf(" LeftSpeed %d, RightSpeed %d \n", leftSpeed, rightSpeed);

            // For safety
            if( leftSpeed == 0 && rightSpeed == 0 )
            {
                Stop();
            }
            else
            {
                SetLeftMotor( leftSpeed );
                SetRightMotor( rightSpeed );
            }
            break;
        case CWIID_MESG_BALANCE:
        case CWIID_MESG_MOTIONPLUS:
        case CWIID_MESG_ERROR:
        case CWIID_MESG_UNKNOWN:
        default:
            printf("Unknown Report");
            break;
        }
    }
}

void setBusyCursor(bool set)
{
    if(set)
    {
        QApplication::setOverrideCursor(Qt::WaitCursor);
        QApplication::processEvents();
    }
    else
    {
        QApplication::setOverrideCursor(Qt::ArrowCursor);
        QApplication::processEvents();
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setStyleSheet("MainWindow {background-image: url(:/KeyPadBackground.png);}");
    ui->btnPair->setCheckable(true);
    //Init Laika board
    lk_init();
}

MainWindow::~MainWindow()
{
    unPairWiiMote();
    delete ui;
}

void MainWindow::on_btnPair_clicked()
{
    if(IsPaired)
    {
        unPairWiiMote();
        IsPaired = false;
    }
    else
    {
        setBusyCursor(true);
        if( pairWiiMote(cwiid_callback) != 0 )
        {
            IsPaired = false;
        }
        else
        {
            IsPaired = true;
        }
    }
    ui->btnPair->setChecked(IsPaired);
    setBusyCursor(false);

}


void MainWindow::on_btnForward_clicked()
{

}
