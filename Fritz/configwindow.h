#ifndef CONFIGWINDOW_H
#define CONFIGWINDOW_H

#include <QDialog>
#include <QtSerialPort/QSerialPort>
#include <QMap>
#include <QPixmap>

#include "worker.h"
#include "serial.h"
#include "keyenterreceiver.h"

class Worker;

namespace Ui {
class ConfigWindow;
class CalibrationData;
}

class CalibrationData
{
public:
    int leftHorizontalEyeTrim;
    int leftHorizontalEyeMax;
    int leftHorizontalEyeMin;
    int leftHorizontalEyePin;
    bool leftHorizontalEyeEnabled;

    int leftVerticalEyeTrim;
    int leftVerticalEyeMax;
    int leftVerticalEyeMin;
    int leftVerticalEyePin;
    bool leftVerticalEyeEnabled;

    int rightHorizontalEyeTrim;
    int rightHorizontalEyeMax;
    int rightHorizontalEyeMin;
    int rightHorizontalEyePin;
    bool rightHorizontalEyeEnabled;

    int rightVerticalEyeTrim;
    int rightVerticalEyeMax;
    int rightVerticalEyeMin;
    int rightVerticalEyePin;
    bool rightVerticalEyeEnabled;

    int leftEyebrowTrim;
    int leftEyebrowMax;
    int leftEyebrowMin;
    int leftEyebrowPin;
    bool leftEyebrowEnabled;

    int rightEyebrowTrim;
    int rightEyebrowMax;
    int rightEyebrowMin;
    int rightEyebrowPin;
    bool rightEyebrowEnabled;

    int rightEyelidTrim;
    int rightEyelidMax;
    int rightEyelidMin;
    int rightEyelidPin;
    bool rightEyelidEnabled;

    int leftEyelidTrim;
    int leftEyelidMax;
    int leftexplicitEyelidMin;
    int leftEyelidPin;
    bool leftEyelidEnabled;

    int neckTiltTrim;
    int neckTiltMax;
    int neckTiltMin;
    int neckTiltPin;
    bool neckTiltEnabled;

    int neckTwistTrim;
    int neckTwistMax;
    int neckTwistMin;
    int neckTwistPin;
    bool neckexplicitTwistEnabled;

    int leftLipTrim;
    int leftLipMax;
    int leftLipMin;
    int leftLipPin;
    bool leftLipEnabled;

    int rightLipTrim;
    int rightLipMax;
    int rightLipMin;
    int rightLipPin;
    bool rightLipEnabled;

    int jawTrim;
    int jawMax;
    int jawMin;
    int jawPin;
    bool jawEnabled;

    int sonarTriggerPin;
    int sonarEchoPin;
    bool sonarEnabled;

    int irPin;
    bool irEnabled;

    explicit CalibrationData();
};

class RobotState
{
public:
    float leftHorizontalEye;
    float leftVerticalEye;
    float rightHorizontalEye;
    float rightVerticalEye;
    float leftEyebrow;
    float rightEyebrow;
    float rightEyelid;
    float leftEyelid;
    float leftLip;
    float rightLip;
    float jaw;
    float neckTilt;
    float neckTwist;
    long position;
    long triggerPosition;

    RobotState()
    {
        leftHorizontalEye = 0.5f;
        leftVerticalEye = 0.5f;
        rightHorizontalEye = 0.5f;
        rightVerticalEye = 0.5f;
        leftEyebrow = 0.5f;
        rightEyebrow = 0.5f;
        rightEyelid = 0.5f;
        leftEyelid = 0.5f;
        leftLip = 0.5f;
        rightLip = 0.5f;
        jaw = 0.5f;
        neckTilt = 0.5f;
        neckTwist = 0.5f;
        position = 0;
        triggerPosition = 0;
    }

    RobotState(bool empty)
    {
        leftHorizontalEye = -1;
        rightHorizontalEye = -1;
        leftVerticalEye = -1;
        rightVerticalEye = -1;
        leftEyebrow = -1;
        rightEyebrow = -1;
        leftEyelid = -1;
        rightEyelid = -1;
        leftLip = -1;
        rightLip = -1;
        jaw = -1;
        neckTilt = -1;
        neckTwist = -1;
    }

    RobotState(const RobotState & r)
    {
        leftHorizontalEye = r.leftHorizontalEye;
        rightHorizontalEye = r.rightHorizontalEye;
        leftVerticalEye = r.leftVerticalEye;
        rightVerticalEye = r.rightVerticalEye;
        leftEyebrow = r.leftEyebrow;
        rightEyebrow = r.rightEyebrow;
        leftEyelid = r.leftEyelid;
        rightEyelid = r.rightEyelid;
        leftLip = r.leftLip;
        rightLip = r.rightLip;
        jaw = r.jaw;
        neckTilt = r.neckTilt;
        neckTwist = r.neckTwist;
        position = r.position;
    }

};

class ConfigWindow : public QDialog
{
    Q_OBJECT
public:
    explicit ConfigWindow(QWidget *parent = 0);
        ~ConfigWindow();

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

    Serial *serial;

signals:

public slots:

private slots:
    void ActivateTest(const int i);
    void DeactivateTest();


    void on_btnCancelSave_accepted();

    void on_btnCancelSave_rejected();

    int GetVersion();

    //int GetVersion(QByteArray buf);

    void on_pushButton_clicked();

    void on_btnRunTests_clicked();

    void on_btnTestSpeech_clicked();

    void on_btnTestSpeech_2_clicked();

    void on_btnTestSpeech_3_clicked();

    void on_btnTestSpeech_4_clicked();

    void on_btnTestSpeech_5_clicked();

    void on_btnTestSonar_clicked();

    void SpeakMessage(QString msg);

private:
    void SetServo(int pin, float value, int max, int min, int trim, bool inverted = false);
    void SetServo(int pin, int value);
    void fetchImage(QString filename);

    Ui::ConfigWindow *ui;

    Worker *worker;

    QThread *thread;

    QWidget *main;

    keyEnterReceiver* key;

    CalibrationData * cd;

    RobotState * ss;

    int currentValue[32];
    bool currentDirection[32];
    bool currentActive[32];

    int indexToPin[17];
    int pinToIndex[20];

    int tickCount;
    int speed;

    QMap<QString, QPixmap> imageMap;

};

#endif // CONFIGWINDOW_H


