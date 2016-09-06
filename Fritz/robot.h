#ifndef ROBOT_H
#define ROBOT_H

#include "serial.h"
#include "configwindow.h"

class Robot
{
private:
    // send packets

    Serial * serial;

    static const int minPin = 2;
    static const int maxPin = 19;

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


    float f_leftHorizontalEye;
    float f_leftVerticalEye;
    float f_rightHorizontalEye;
    float f_rightVerticalEye;
    float f_leftEyebrow;
    float f_rightEyebrow;
    float f_rightEyelid;
    float f_leftEyelid;
    float f_leftLip;
    float f_rightLip;
    float f_jaw;
    float f_neckTilt;
    float f_neckTwist;

    float leftHorizontalEye;
    float leftVerticalEye;
    float rightHorizontalEye;
    float rightVerticalEye;
    float leftLip;
    float rightLip;
    float jaw;
    float neckTilt;
    float neckTwist;
    float leftEyebrow;
    float rightEyebrow;
    float leftEyelid;
    float rightEyelid;
    float irValue;
    float sonarValue;

    CalibrationData * cd;


public:
    Robot();
    ~Robot();

    void Reset();
    void SetState(float n_leftHorizontalEye, float n_leftVerticalEye, float n_rightHorizontalEye, float n_rightVerticalEye, float n_leftEyebrow, float n_rightEyebrow, float n_rightEyelid, float n_leftEyelid, float n_leftLip, float n_rightLip, float n_jaw, float n_neckTilt, float n_neckTwist);
    void SetExpression(QString name);
};

#endif // ROBOT_H
