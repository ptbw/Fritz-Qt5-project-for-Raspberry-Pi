#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "configwindow.h"
#include "aboutbox.h"
#include "robot.h"

#include <QMessageBox>
#include <QtSerialPort/QSerialPort>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionConfig_triggered()
{
    ConfigWindow w;
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
    Robot * robot = new Robot();
    robot->SetExpression(arg1);
    delete robot;
}

