#-------------------------------------------------
#
# Project created by QtCreator 2014-05-29T17:38:50
#本节学习为综合示例，涉及了：Json数据格式、百度API的使用、http下载、布局管理器、编辑框等
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IpQuery
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    ipQuery.cpp

HEADERS  += widget.h \
    ipQuery.h

CONFIG += mobility
MOBILITY = 

android-g++ {
    LIBS += -lgnustl_shared
}

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

OTHER_FILES += \
    android/AndroidManifest.xml

