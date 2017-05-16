#-------------------------------------------------
#
# Project created by QtCreator 2013-03-22T21:02:13
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11

TARGET = qmqtt-client1
TEMPLATE = app


#NOTICE: add DYLD_LIBRARY_PATH to build environment.
INCLUDEPATH += ../src
#LIBS += -L../src -L../src/debug -L../src/release -lqmqtt
LIBS += -L../src -L../src/release -lqmqtt

SOURCES += main.cpp \
    mainwindow.cpp \
    connform.cpp \
    pubform.cpp \
    subform.cpp \
    cJSON.c \
    form.cpp \
    qcustomplot.cpp \
    windowtitlebar.cpp \
    utility.cpp
        mainwindow.cpp

HEADERS  += mainwindow.h \
    connform.h \
    pubform.h \
    subform.h \
    mqttform.h \
    cJSON.h \
    form.h \
    qcustomplot.h \
    windowtitlebar.h \
    utility.h

FORMS    += mainwindow.ui \
    connform.ui \
    pubform.ui \
    subform.ui \
    form.ui \
    windowtitlebar.ui \
    utility.ui

DISTFILES +=

RESOURCES += \
    res.qrc

RC_FILE = myappico.rc
