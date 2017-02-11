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
    serial.cpp \
    robot.cpp \
    speak.cpp \
    worker.cpp \
    keyenterreceiver.cpp \
    animate.cpp

HEADERS  += mainwindow.h \
    configwindow.h \
    aboutbox.h \
    serial.h \
    i.h \
    robot.h \
    speak.h \
    worker.h \
    keyenterreceiver.h \
    animate.h

FORMS    += mainwindow.ui \
    aboutbox.ui \
    configwindow.ui

OTHER_FILES += \
    speech/consonantphons.txt \
    speech/consonants.txt \
    speech/vowels.txt \
    speech/vowelsphons.txt \
    images/aaah.png \
    images/eee.png \
    images/fuh.png \
    images/i.png \
    images/laa.png \
    images/mmm.png \
    images/oh.png \
    images/oooh.png \
    images/phoneme mouth chart.png \
    images/sss.png \
    speech/cookies.txt
