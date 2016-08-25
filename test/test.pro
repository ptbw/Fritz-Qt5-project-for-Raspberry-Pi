#-------------------------------------------------
#
# Project created by QtCreator 2016-02-12T09:44:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

LIBS     += -L/usr/local/lib -llaika -lpthread -lcwiid

QMAKE_CXXFLAGS += -Wall

RESOURCES += \
    resource.qrc

