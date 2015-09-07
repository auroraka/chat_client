#-------------------------------------------------
#
# Project created by QtCreator 2015-09-07T00:36:58
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = client
TEMPLATE = app


SOURCES += main.cpp\
    tcp.cpp \
    chatdialog.cpp \
    loginwindow.cpp \
    userlist.cpp \
    switcher.cpp \
    environment.cpp \
    userinfo.cpp

HEADERS  += \
    tcp.h \
    chatdialog.h \
    loginwindow.h \
    userlist.h \
    switcher.h \
    enviroment.h \
    userinfo.h

FORMS    += \
    chatdialog.ui \
    loginwindow.ui \
    userlist.ui

RESOURCES += \
    userlist.qrc

CONFIG += c++11
