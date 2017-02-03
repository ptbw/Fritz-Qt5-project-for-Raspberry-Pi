#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "configwindow.h"
#include "aboutbox.h"
#include "robot.h"
#include "speak.h"
#include "i.h"

#include <QMessageBox>
#include <QtSerialPort/QSerialPort>
#include <QProcess>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    serial = new Serial();
}

MainWindow::~MainWindow()
{
    delete serial;
    delete ui;
}

void MainWindow::on_actionConfig_triggered()
{
    ConfigWindow w;
    w.serial = serial;
    w.exec();
}

void MainWindow::on_actionAbout_triggered()
{
    AboutBox w;
    w.exec();
}

void MainWindow::on_actionSave_triggered()
{

}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_comboBox_activated(const QString &arg1)
{
    Robot * robot = new Robot(serial);
    robot->SetExpression(arg1);
    QEventLoop loop;
    QTimer::singleShot(5000, &loop, SLOT(quit()));
    loop.exec();
    delete robot;
}

void MainWindow::SpeakMessage(QString msg)
{
    Speak speak;
    Robot robot(serial);

    QStringList phons = speak.TextToPhon(msg);
    speak.TextToSpeech(msg);

    QStringListIterator iterator(phons);
    while (iterator.hasNext())
    {
        QString shape = speak.GetMouthShape(iterator.next());
        robot.SetMouth(shape);
        I::msleep(10);
    }
}

void MainWindow::on_btnHello_clicked()
{
    QString msg = "Hello  My Name is Fritz";
    SpeakMessage(msg);
}

void MainWindow::on_btnAsk_clicked()
{
    QString msg = "May I tell your fortune?";
    SpeakMessage(msg);
}

void MainWindow::on_btnFortune_clicked()
{
    // QString command = "fortune cookies.txt";
    QString command = "fortune -s";

    QProcess process;
    process.start(command);
    process.waitForFinished();
    QString output(process.readAllStandardOutput());
    SpeakMessage(output);
}

void MainWindow::on_btnOkBye_clicked()
{
    QString msg = "Ok. Goodbye";
    SpeakMessage(msg);
}

void MainWindow::on_btnThanks_clicked()
{
    QString msg = "Thankyou. Goodbye";
    SpeakMessage(msg);
}

void MainWindow::on_btnLeft_clicked()
{
    //SetState(int n_leftHorizontalEye, int n_leftVerticalEye, int n_rightHorizontalEye, int n_rightVerticalEye, int n_leftEyebrow, int n_rightEyebrow, int n_rightEyelid, int n_leftEyelid, int n_leftLip, int n_rightLip, int n_jaw, int n_neckTilt, int n_neckTwist);
    Robot robot(serial);
    robot.SetState(40, -1, 40, -1, 30, 70, 100, 100, 50, 50, 50, -1, 10);
}

void MainWindow::on_btnCentre_clicked()
{
    Robot robot(serial);
    robot.SetState(40, -1, 40, -1, 50, 50, 100, 100, 50, 50, 50, -1, 50);
}

void MainWindow::on_btnRight_clicked()
{
    Robot robot(serial);
    robot.SetState(40, -1, 40, -1, 30, 70, 100, 100, 50, 50, 50, -1, 90);
}
