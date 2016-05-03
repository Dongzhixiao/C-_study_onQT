#-------------------------------------------------
#
# Project created by QtCreator 2014-05-02T15:16:56
#本节学习为综合示例，涉及了：目录遍历、工作线程、文件展示、图片加载器、图片显示和变换、手势处理等
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qimageviewer
TEMPLATE = app


SOURCES += main.cpp\
        imageWidget.cpp \
    ../openFileWidget.cpp \
    imageLoadManager.cpp \  
    ../qDebug2Logcat.cpp \
    ../worker.cpp \
    ../imageButton.cpp

HEADERS  += imageWidget.h \
    ../openFileWidget.h \
    imageLoadManager.h \
    ../qDebug2Logcat.h \
    ../worker.h \
    ../imageButton.h

CONFIG += mobility
MOBILITY = 
android-g++ {
    LIBS += -lgnustl_shared
}

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

OTHER_FILES += \
    android/AndroidManifest.xml

RESOURCES += \
    qimageviewer.qrc

