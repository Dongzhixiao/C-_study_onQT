#-------------------------------------------------
#
# Project created by QtCreator 2014-05-13T12:14:17
#本节学习如何使用QFile进行log的实现
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = simplelog
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    log.cpp

HEADERS += \
    log.h
