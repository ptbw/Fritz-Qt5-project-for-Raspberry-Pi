#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "animate.h"
#include "serial.h"

class Animate;

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

    void SpeakMessage(QString msg);

private slots:

    void on_actionAbout_triggered();

    //void on_SpeakPhrase(int i);

    void on_Stop();

    void on_actionConfig_triggered();

    void on_actionSave_triggered();

    void on_actionQuit_triggered();

    void on_comboBox_activated(const QString &arg1);

    void on_btnLeft_clicked();

    void on_btnHello_clicked();

    void on_btnAsk_clicked();

    void on_btnFortune_clicked();

    void on_btnOkBye_clicked();

    void on_btnThanks_clicked();

    void on_btnCentre_clicked();

    void on_btnRight_clicked();

    void on_btnAnimate_clicked();


private:
    Ui::MainWindow *ui;

    Serial *serial;

    Animate *animate;

    QThread *thread;

    bool animationRunning;

};

#endif // MAINWINDOW_H
