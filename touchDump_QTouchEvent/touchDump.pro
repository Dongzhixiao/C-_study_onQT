#-------------------------------------------------
#
# Project created by QtCreator 2014-05-30T22:31:12
#本节学习QTouchEvent类，即常用的触摸和手势的使用！
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = touchDump
TEMPLATE = app

android-g++{
    LIBS += -lgnustl_shared
}

SOURCES += main.cpp\
        widget.cpp \
    ../qDebug2Logcat.cpp

HEADERS  += widget.h \
    ../qDebug2Logcat.h

CONFIG += mobility
MOBILITY = 

