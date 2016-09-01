#-------------------------------------------------
#
# Project created by QtCreator 2016-08-25T14:28:44
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Fritz
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    configwindow.cpp \
    aboutbox.cpp \
    serial.cpp

HEADERS  += mainwindow.h \
    configwindow.h \
    aboutbox.h \
    serial.h

FORMS    += mainwindow.ui \
    aboutbox.ui \
    configwindow.ui
