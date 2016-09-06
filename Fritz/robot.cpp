#include "robot.h"

Robot::Robot()
{
    serial = new Serial();

    const int minPin = 2;
    const int maxPin = 19;

    float irValue = 1000.0f;
    float sonarValue = 1000.0f;

    cd = new CalibrationData();

    RobotState initState = new RobotState();

    leftHorizontalEye = f_leftHorizontalEye = initState.leftHorizontalEye;
    leftVerticalEye = f_leftVerticalEye = initState.leftVerticalEye;
    rightHorizontalEye = f_rightHorizontalEye = initState.rightHorizontalEye;
    rightVerticalEye = f_rightVerticalEye = initState.rightVerticalEye;
    leftEyebrow = f_leftEyebrow = initState.leftEyebrow;
    rightEyebrow = f_rightEyebrow = initState.rightEyebrow;
    rightEyelid = f_rightEyelid = initState.rightEyelid;
    leftEyelid = f_leftEyelid = initState.leftEyelid;
    leftLip = f_leftLip = initState.leftLip;
    rightLip = f_rightLip = initState.rightLip;
    jaw = f_jaw = initState.jaw;
    neckTilt = f_neckTilt = initState.neckTilt;
    neckTwist = f_neckTwist = initState.neckTwist;

}

Robot::~Robot()
{
    delete cd;
    delete serial;
}

void Robot::Reset()
{
    RobotState initState = new RobotState();

    f_leftHorizontalEye = initState.leftHorizontalEye;
    f_leftVerticalEye = initState.leftVerticalEye;
    f_rightHorizontalEye = initState.rightHorizontalEye;
    f_rightVerticalEye = initState.rightVerticalEye;
    f_leftEyebrow = initState.leftEyebrow;
    f_rightEyebrow = initState.rightEyebrow;
    f_rightEyelid = initState.rightEyelid;
    f_leftEyelid = initState.leftEyelid;
    f_leftLip = initState.leftLip;
    f_rightLip = initState.rightLip;
    f_jaw = initState.jaw;
    f_neckTilt = initState.neckTilt;
    f_neckTwist = initState.neckTwist;

    //newData.Set();
}

void Robot::SetState(float n_leftHorizontalEye, float n_leftVerticalEye, float n_rightHorizontalEye, float n_rightVerticalEye, float n_leftEyebrow, float n_rightEyebrow, float n_rightEyelid, float n_leftEyelid, float n_leftLip, float n_rightLip, float n_jaw, float n_neckTilt, float n_neckTwist)
{
    if (n_leftHorizontalEye != -1) f_leftHorizontalEye = n_leftHorizontalEye;
    if (n_leftVerticalEye != -1) f_leftVerticalEye = n_leftVerticalEye;
    if (n_rightHorizontalEye != -1) f_rightHorizontalEye = n_rightHorizontalEye;
    if (n_rightVerticalEye != -1) f_rightVerticalEye = n_rightVerticalEye;
    if (n_leftEyebrow != -1) f_leftEyebrow = n_leftEyebrow;
    if (n_rightEyebrow != -1) f_rightEyebrow = n_rightEyebrow;
    if (n_rightEyelid != -1) f_rightEyelid = n_rightEyelid;
    if (n_leftEyelid != -1) f_leftEyelid = n_leftEyelid;
    if (n_leftLip != -1) f_leftLip = n_leftLip;
    if (n_rightLip != -1) f_rightLip = n_rightLip;
    if (n_jaw != -1) f_jaw = n_jaw;
    if (n_neckTilt != -1) f_neckTilt = n_neckTilt;
    if (n_neckTwist != -1) f_neckTwist = n_neckTwist;


//    f_leftHorizontalEye = initState.leftHorizontalEye;
//    f_leftVerticalEye = initState.leftVerticalEye;
//    f_rightHorizontalEye = initState.rightHorizontalEye;
//    f_rightVerticalEye = initState.rightVerticalEye;
    serial->SendCommand(ARDUINO_SET_SERVO, cd->leftEyebrowPin, (short) f_leftEyebrow);
//    f_rightEyebrow = initState.rightEyebrow;
//    f_rightEyelid = initState.rightEyelid;
//    f_leftEyelid = initState.leftEyelid;
//    f_leftLip = initState.leftLip;
//    f_rightLip = initState.rightLip;
//    f_jaw = initState.jaw;
//    f_neckTilt = initState.neckTilt;
//    f_neckTwist = initState.neckTwist;
    //newData.Set();
}

void Robot::SetExpression(QString name)
{
//    if (name == "Afraid")
//        SetState(0.5f/*leftHorizontalEye*/, 0.7f/*leftVerticalEye*/, 0.5f/*rightHorizontalEye*/, 0.7f/*rightVerticalEye*/, 1.0f-0.1836375f/*leftEyebrow*/, 0.7860668f/*rightEyebrow*/, 0.0625f/*rightEyelid*/, 0.0625f/*leftEyelid*/, 0.1142002f/*leftLip*/, 0.8580002f/*rightLip*/, 0.225f/*jaw*/, 0.5f/*neckTilt*/, -1.0f/*neckTwist*/);
//    else if (name == "Awkward")
//        SetState(0.5119048f/*leftHorizontalEye*/, 0.4880952f/*leftVerticalEye*/, 0.5119048f/*rightHorizontalEye*/, 0.4880952f/*rightVerticalEye*/, 1f/*leftEyebrow*/, 1f/*rightEyebrow*/, 0.452381f/*rightEyelid*/, 0.452381f/*leftEyelid*/, 1f/*leftLip*/, 0f/*rightLip*/, 0.675f/*jaw*/, 0.5f/*neckTilt*/, -1.0f/*neckTwist*/);
//    else if (name == "Angry")
//        SetState(0.5f/*leftHorizontalEye*/, 0.5f/*leftVerticalEye*/, 0.5f/*rightHorizontalEye*/, 0.5f/*rightVerticalEye*/, 1.0f - 0.9075357f/*leftEyebrow*/, 0.09246436f/*rightEyebrow*/, 0.4047619f/*rightEyelid*/, 0.4047619f/*leftEyelid*/, 0.2235353f/*leftLip*/, 0.7764647f/*rightLip*/, 0f/*jaw*/, 0.33f/*neckTilt*/, -1.0f/*neckTwist*/);
//    else if (name == "Disappointed")
//        SetState(0.4761905f/*leftHorizontalEye*/, 0.7857143f/*leftVerticalEye*/, 0.4761905f/*rightHorizontalEye*/, 0.7857143f/*rightVerticalEye*/, 1.0f - 0.5687325f/*leftEyebrow*/, 0.4312675f/*rightEyebrow*/, 0.07142857f/*rightEyelid*/, 0.07142857f/*leftEyelid*/, 0.312833f/*leftLip*/, 0.687167f/*rightLip*/, 0f/*jaw*/, 0.17f/*neckTilt*/, -1.0f/*neckTwist*/);
//    else if (name == "Happy")
//        SetState(0.625f/*leftHorizontalEye*/, 0.5625f/*leftVerticalEye*/, 0.5f/*rightHorizontalEye*/, 0.5625f/*rightVerticalEye*/, 1.0f - 0.2499876f/*leftEyebrow*/, 0.6599966f/*rightEyebrow*/, 0.4047619f/*rightEyelid*/, 0.4047619f/*leftEyelid*/, 0.75f/*leftLip*/, 0.25f/*rightLip*/, 1f/*jaw*/, 0.5f/*neckTilt*/, -1.0f/*neckTwist*/);
//    else if (name == "Neutral")
//        SetState(0.5f/*leftHorizontalEye*/, 0.5f/*leftVerticalEye*/, 0.5f/*rightHorizontalEye*/, 0.5f/*rightVerticalEye*/, 0.5f/*leftEyebrow*/, 0.5f/*rightEyebrow*/, 0.5f/*rightEyelid*/, 0.5f/*leftEyelid*/, 0.5f/*leftLip*/, 0.5f/*rightLip*/, 0.0f/*jaw*/, 0.5f/*neckTilt*/, 0.5f/*neckTwist*/);
//    else if (name == "Sad")
//        SetState(0.5595238f/*leftHorizontalEye*/, 0.6428571f/*leftVerticalEye*/, 0.5595238f/*rightHorizontalEye*/, 0.6428571f/*rightVerticalEye*/, 1.0f - 0.09873044f/*leftEyebrow*/, 0.9012696f/*rightEyebrow*/, 0.5714286f/*rightEyelid*/, 0.5714286f/*leftEyelid*/, 0f/*leftLip*/, 0.9494985f/*rightLip*/, 0.25f/*jaw*/, 0.5f/*neckTilt*/, -1.0f/*neckTwist*/);
//    else if (name == "Sinister")
//        SetState(0.5f/*leftHorizontalEye*/, 0.4404762f/*leftVerticalEye*/, 0.5f/*rightHorizontalEye*/, 0.4404762f/*rightVerticalEye*/, 1.0f - 0.9320638f/*leftEyebrow*/, 0.06793616f/*rightEyebrow*/, 0.0625f/*rightEyelid*/, 0.0625f/*leftEyelid*/, 0.7014102f/*leftLip*/, 0.2985898f/*rightLip*/, 0.675f/*jaw*/, 0.5f/*neckTilt*/, -1.0f/*neckTwist*/);
//    else if (name == "Sleepy")
//        SetState(0.5f/*leftHorizontalEye*/, 0.5595238f/*leftVerticalEye*/, 0.5119048f/*rightHorizontalEye*/, 0.5952381f/*rightVerticalEye*/, 1.0f - 0.4f/*leftEyebrow*/, 0.6f/*rightEyebrow*/, 0.8f/*rightEyelid*/, 0.8f/*leftEyelid*/, 0.25f/*leftLip*/, 0.75f/*rightLip*/, 0.2f/*jaw*/, 0.3f/*neckTilt*/, -1.0f/*neckTwist*/);
//    else if (name == "Smile")
//        SetState(0.625f/*leftHorizontalEye*/, 0.5625f/*leftVerticalEye*/, 0.5f/*rightHorizontalEye*/, 0.5625f/*rightVerticalEye*/, 1.0f - 0.419993f/*leftEyebrow*/, 0.580007f/*rightEyebrow*/, 0.07142857f/*rightEyelid*/, 0.07142857f/*leftEyelid*/, 1f/*leftLip*/, 0f/*rightLip*/, 0f/*jaw*/, 0.5f/*neckTilt*/, -1.0f/*neckTwist*/);
//    else if (name == "Sneaky")
//        SetState(0.6190476f/*leftHorizontalEye*/, 0.297619f/*leftVerticalEye*/, 0.6190476f/*rightHorizontalEye*/, 0.297619f/*rightVerticalEye*/, 1.0f - 0.4217965f/*leftEyebrow*/, 0.5137788f/*rightEyebrow*/, 0.2619048f/*rightEyelid*/, 0.2619048f/*leftEyelid*/, 0f/*leftLip*/, 0f/*rightLip*/, 0.925f/*jaw*/, 0.5f/*neckTilt*/, -1.0f/*neckTwist*/);
//    else if (name == "Sulk")
//        SetState(0.3690476f/*leftHorizontalEye*/, 0.6071429f/*leftVerticalEye*/, 0.3690476f/*rightHorizontalEye*/, 0.6071429f/*rightVerticalEye*/, 1.0f - 0.6799673f/*leftEyebrow*/, 0.3200327f/*rightEyebrow*/, 0.7619048f/*rightEyelid*/, 0.7619048f/*leftEyelid*/, 0.1740483f/*leftLip*/, 0.3668751f/*rightLip*/, 0f/*jaw*/, 0.5f/*neckTilt*/, -1.0f/*neckTwist*/);
//    else if (name == "Surprised")
//        SetState(0.5f/*leftHorizontalEye*/, 0.4761905f/*leftVerticalEye*/, 0.5f/*rightHorizontalEye*/, 0.4761905f/*rightVerticalEye*/, 1f/*leftEyebrow*/, 1f/*rightEyebrow*/, 0.1428571f/*rightEyelid*/, 0.1428571f/*leftEyelid*/, 0.25f/*leftLip*/, 0.7147767f/*rightLip*/, 1f/*jaw*/, 0.5f/*neckTilt*/, -1.0f/*neckTwist*/);
//    else if (name == "Yelling")
//        SetState(0.5f/*leftHorizontalEye*/, 0.5f/*leftVerticalEye*/, 0.5f/*rightHorizontalEye*/, 0.5f/*rightVerticalEye*/, 1.0f - 0.9075357f/*leftEyebrow*/, 0.09246436f/*rightEyebrow*/, 0.4047619f/*rightEyelid*/, 0.4047619f/*leftEyelid*/, 0.2235353f/*leftLip*/, 0.7764647f/*rightLip*/, 1f/*jaw*/, 0.33f/*neckTilt*/, -1.0f/*neckTwist*/);
//    else if (name == "Worried")
//        SetState(0.5119048f/*leftHorizontalEye*/, 0.3690476f/*leftVerticalEye*/, 0.5119048f/*rightHorizontalEye*/, 0.3690476f/*rightVerticalEye*/, 1.0f - 0.1930289f/*leftEyebrow*/, 0.8069711f/*rightEyebrow*/, 0.07142857f/*rightEyelid*/, 0.07142857f/*leftEyelid*/, 0.1828069f/*leftLip*/, 0.8171931f/*rightLip*/, 0.5f/*jaw*/, 0.67f/*neckTilt*/, -1.0f/*neckTwist*/);

    if (name == "Afraid")
        SetState(0.5 /*leftHorizontalEye*/, 0.7 /*leftVerticalEye*/, 0.5 /*rightHorizontalEye*/, 0.7 /*rightVerticalEye*/, 1.0f-0.1836375 /*leftEyebrow*/, 0.7860668 /*rightEyebrow*/, 0.0625 /*rightEyelid*/, 0.0625 /*leftEyelid*/, 0.1142002 /*leftLip*/, 0.8580002 /*rightLip*/, 0.225 /*jaw*/, 0.5 /*neckTilt*/, -1.0 /*neckTwist*/);
    else if (name == "Awkward")
        SetState(0.5119048 /*leftHorizontalEye*/, 0.4880952 /*leftVerticalEye*/, 0.5119048 /*rightHorizontalEye*/, 0.4880952 /*rightVerticalEye*/, 1 /*leftEyebrow*/, 1 /*rightEyebrow*/, 0.452381 /*rightEyelid*/, 0.452381 /*leftEyelid*/, 1 /*leftLip*/, 0 /*rightLip*/, 0.675 /*jaw*/, 0.5 /*neckTilt*/, -1.0 /*neckTwist*/);
    else if (name == "Angry")
        SetState(0.5 /*leftHorizontalEye*/, 0.5 /*leftVerticalEye*/, 0.5 /*rightHorizontalEye*/, 0.5 /*rightVerticalEye*/, 1.0f - 0.9075357 /*leftEyebrow*/, 0.09246436 /*rightEyebrow*/, 0.4047619 /*rightEyelid*/, 0.4047619 /*leftEyelid*/, 0.2235353 /*leftLip*/, 0.7764647 /*rightLip*/, 0 /*jaw*/, 0.33 /*neckTilt*/, -1.0 /*neckTwist*/);
    else if (name == "Disappointed")
        SetState(0.4761905 /*leftHorizontalEye*/, 0.7857143 /*leftVerticalEye*/, 0.4761905 /*rightHorizontalEye*/, 0.7857143 /*rightVerticalEye*/, 1.0f - 0.5687325 /*leftEyebrow*/, 0.4312675 /*rightEyebrow*/, 0.07142857 /*rightEyelid*/, 0.07142857 /*leftEyelid*/, 0.312833 /*leftLip*/, 0.687167 /*rightLip*/, 0 /*jaw*/, 0.17 /*neckTilt*/, -1.0 /*neckTwist*/);
    else if (name == "Happy")
        SetState(0.625 /*leftHorizontalEye*/, 0.5625 /*leftVerticalEye*/, 0.5 /*rightHorizontalEye*/, 0.5625 /*rightVerticalEye*/, 1.0f - 0.2499876 /*leftEyebrow*/, 0.6599966 /*rightEyebrow*/, 0.4047619 /*rightEyelid*/, 0.4047619 /*leftEyelid*/, 0.75 /*leftLip*/, 0.25 /*rightLip*/, 1 /*jaw*/, 0.5 /*neckTilt*/, -1.0 /*neckTwist*/);
    else if (name == "Neutral")
        SetState(0.5 /*leftHorizontalEye*/, 0.5 /*leftVerticalEye*/, 0.5 /*rightHorizontalEye*/, 0.5 /*rightVerticalEye*/, 0.5 /*leftEyebrow*/, 0.5 /*rightEyebrow*/, 0.5 /*rightEyelid*/, 0.5 /*leftEyelid*/, 0.5 /*leftLip*/, 0.5 /*rightLip*/, 0.0 /*jaw*/, 0.5 /*neckTilt*/, 0.5 /*neckTwist*/);
    else if (name == "Sad")
        SetState(0.5595238 /*leftHorizontalEye*/, 0.6428571 /*leftVerticalEye*/, 0.5595238 /*rightHorizontalEye*/, 0.6428571 /*rightVerticalEye*/, 1.0f - 0.09873044 /*leftEyebrow*/, 0.9012696 /*rightEyebrow*/, 0.5714286 /*rightEyelid*/, 0.5714286 /*leftEyelid*/, 0 /*leftLip*/, 0.9494985 /*rightLip*/, 0.25 /*jaw*/, 0.5 /*neckTilt*/, -1.0 /*neckTwist*/);
    else if (name == "Sinister")
        SetState(0.5 /*leftHorizontalEye*/, 0.4404762 /*leftVerticalEye*/, 0.5 /*rightHorizontalEye*/, 0.4404762 /*rightVerticalEye*/, 1.0f - 0.9320638 /*leftEyebrow*/, 0.06793616 /*rightEyebrow*/, 0.0625 /*rightEyelid*/, 0.0625 /*leftEyelid*/, 0.7014102 /*leftLip*/, 0.2985898 /*rightLip*/, 0.675 /*jaw*/, 0.5 /*neckTilt*/, -1.0 /*neckTwist*/);
    else if (name == "Sleepy")
        SetState(0.5 /*leftHorizontalEye*/, 0.5595238 /*leftVerticalEye*/, 0.5119048 /*rightHorizontalEye*/, 0.5952381 /*rightVerticalEye*/, 1.0f - 0.4 /*leftEyebrow*/, 0.6 /*rightEyebrow*/, 0.8 /*rightEyelid*/, 0.8 /*leftEyelid*/, 0.25 /*leftLip*/, 0.75 /*rightLip*/, 0.2 /*jaw*/, 0.3 /*neckTilt*/, -1.0 /*neckTwist*/);
    else if (name == "Smile")
        SetState(0.625 /*leftHorizontalEye*/, 0.5625 /*leftVerticalEye*/, 0.5 /*rightHorizontalEye*/, 0.5625 /*rightVerticalEye*/, 1.0f - 0.419993 /*leftEyebrow*/, 0.580007 /*rightEyebrow*/, 0.07142857 /*rightEyelid*/, 0.07142857 /*leftEyelid*/, 1 /*leftLip*/, 0 /*rightLip*/, 0 /*jaw*/, 0.5 /*neckTilt*/, -1.0 /*neckTwist*/);
    else if (name == "Sneaky")
        SetState(0.6190476 /*leftHorizontalEye*/, 0.297619 /*leftVerticalEye*/, 0.6190476 /*rightHorizontalEye*/, 0.297619 /*rightVerticalEye*/, 1.0f - 0.4217965 /*leftEyebrow*/, 0.5137788 /*rightEyebrow*/, 0.2619048 /*rightEyelid*/, 0.2619048 /*leftEyelid*/, 0 /*leftLip*/, 0 /*rightLip*/, 0.925 /*jaw*/, 0.5 /*neckTilt*/, -1.0 /*neckTwist*/);
    else if (name == "Sulk")
        SetState(0.3690476 /*leftHorizontalEye*/, 0.6071429 /*leftVerticalEye*/, 0.3690476 /*rightHorizontalEye*/, 0.6071429 /*rightVerticalEye*/, 1.0f - 0.6799673 /*leftEyebrow*/, 0.3200327 /*rightEyebrow*/, 0.7619048 /*rightEyelid*/, 0.7619048 /*leftEyelid*/, 0.1740483 /*leftLip*/, 0.3668751 /*rightLip*/, 0 /*jaw*/, 0.5 /*neckTilt*/, -1.0 /*neckTwist*/);
    else if (name == "Surprised")
        SetState(0.5 /*leftHorizontalEye*/, 0.4761905 /*leftVerticalEye*/, 0.5 /*rightHorizontalEye*/, 0.4761905 /*rightVerticalEye*/, 1 /*leftEyebrow*/, 1 /*rightEyebrow*/, 0.1428571 /*rightEyelid*/, 0.1428571 /*leftEyelid*/, 0.25 /*leftLip*/, 0.7147767 /*rightLip*/, 1 /*jaw*/, 0.5 /*neckTilt*/, -1.0 /*neckTwist*/);
    else if (name == "Yelling")
        SetState(0.5 /*leftHorizontalEye*/, 0.5 /*leftVerticalEye*/, 0.5 /*rightHorizontalEye*/, 0.5 /*rightVerticalEye*/, 1.0f - 0.9075357 /*leftEyebrow*/, 0.09246436 /*rightEyebrow*/, 0.4047619 /*rightEyelid*/, 0.4047619 /*leftEyelid*/, 0.2235353 /*leftLip*/, 0.7764647 /*rightLip*/, 1 /*jaw*/, 0.33 /*neckTilt*/, -1.0 /*neckTwist*/);
    else if (name == "Worried")
        SetState(0.5119048 /*leftHorizontalEye*/, 0.3690476 /*leftVerticalEye*/, 0.5119048 /*rightHorizontalEye*/, 0.3690476 /*rightVerticalEye*/, 1.0f - 0.1930289 /*leftEyebrow*/, 0.8069711 /*rightEyebrow*/, 0.07142857 /*rightEyelid*/, 0.07142857 /*leftEyelid*/, 0.1828069 /*leftLip*/, 0.8171931 /*rightLip*/, 0.5 /*jaw*/, 0.67 /*neckTilt*/, -1.0 /*neckTwist*/);


    //EditState(GetFinalState());
}
