#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "configwindow.h"
#include "aboutbox.h"
#include "serial.h"

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
    char * portname = "/dev/ttyUSB0";
    port->TestSerial(portname);
    delete port;
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}
