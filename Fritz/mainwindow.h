#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "serial.h"
#include <QMainWindow>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    int leftHorizontalEyeMin;
    int leftHorizontalEyeMax;
    int leftVerticalEyeMin;
    int leftVerticalEyeMax;
    int rightHorizontalEyeMin;
    int rightHorizontalEyeMax;
    int rightVerticalEyeMin;
    int rightVerticalEyeMax;
    int leftLipMin;
    int leftLipMax;
    int rightLipMin;
    int rightLipMax;
    int jawMin;
    int jawMax;
    int neckTiltMin;
    int neckTiltMax;
    int neckTwistMin;
    int neckTwistMax;
    int leftEyebrowMin;
    int leftEyebrowMax;
    int rightEyebrowMin;
    int rightEyebrowMax;
    int leftEyelidMin;
    int leftEyelidMax;
    int rightEyelidMin;
    int rightEyelidMax;

private slots:void on_actionAbout_triggered();

    void on_actionConfig_triggered();

    void on_actionSave_triggered();

    void on_actionQuit_triggered();


    void on_comboBox_activated(const QString &arg1);

private:
    Ui::MainWindow *ui;

    Serial *serial;

};

#endif // MAINWINDOW_H
