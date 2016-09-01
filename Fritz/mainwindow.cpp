#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "configwindow.h"
#include "aboutbox.h"
#include "serial.h"

#include <QMessageBox>

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
    Serial * port = new Serial();
    port->arduino_port_name = "/dev/ttyUSB0";
    int result = port->TestSerial();

    if(result == -1)
        QMessageBox::warning(this, "Port error","Couldn't find the Arduino!");
    else if(result == -2)
        QMessageBox::warning(this, "Port error","Fritz not found");
    else if(result < 4 )
        QMessageBox::warning(this, "Port error","Fritz found but firmware version is too old!");
    else
        QMessageBox::information(this, "Serial Port","Fritz found");


    delete port;
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}
