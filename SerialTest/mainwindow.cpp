#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QtCore/QtGlobal>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    arduino_is_available = true;
    arduino_port_name = "/dev/ttyUSB0";
    arduino = new QSerialPort;

    /*
    qDebug() << "Number of available ports: " << QSerialPortInfo::availablePorts().length();
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
       qDebug() << "Has vendor ID: " << serialPortInfo.hasVendorIdentifier();
       if(serialPortInfo.hasVendorIdentifier()){
           qDebug() << "Vendor ID: " << serialPortInfo.vendorIdentifier();
       }
       qDebug() << "Has Product ID: " << serialPortInfo.hasProductIdentifier();
       if(serialPortInfo.hasProductIdentifier()){
           qDebug() << "Product ID: " << serialPortInfo.productIdentifier();
       }
    }
    */

    /*
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
       if(serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier()){
           if(serialPortInfo.vendorIdentifier() == arduino_uno_vendor_id){
               if(serialPortInfo.productIdentifier() == arduino_uno_product_id){
                   arduino_port_name = serialPortInfo.portName();
                   arduino_is_available = true;
               }
           }
       }
    }
    */

    if(arduino_is_available){
       // open and configure the serialport
       arduino->setPortName(arduino_port_name);
       arduino->open(QSerialPort::ReadWrite);
       arduino->setBaudRate(QSerialPort::Baud57600);
       arduino->setDataBits(QSerialPort::Data8);
       arduino->setParity(QSerialPort::NoParity);
       arduino->setStopBits(QSerialPort::OneStop);
       arduino->setFlowControl(QSerialPort::NoFlowControl);
    }else{
       // give error message if not available
       QMessageBox::warning(this, "Port error", "Couldn't find the Arduino!");
    }
}

MainWindow::~MainWindow()
{
    if(arduino->isOpen()){
        arduino->close();
    }
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{


    QByteArray sendData;
    QByteArray requestData;

    sendData[0] = 128;
    sendData[1] = 0;

    if(arduino->isWritable())
    {
        arduino->write(sendData);
        if (arduino->waitForReadyRead(10000))
        {

            // read request
            requestData = arduino->readAll();
            while (arduino->waitForReadyRead(10))
                requestData += arduino->readAll();

            QMessageBox::information(this, "Information", requestData.toUpper());
        }
    }
    else
    {
        qDebug() << "Couldn't write to serial!";
    }

}
