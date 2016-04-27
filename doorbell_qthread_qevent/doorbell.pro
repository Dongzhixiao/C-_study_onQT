#-------------------------------------------------
#
# Project created by QtCreator 2014-05-11T13:44:55
#QT编制多线程实例：（1）继承QThread类；（2）重写run（）虚函数；（3）建立实例——构造线程对象；（4）调用QThread::start（）函数即可开启新线程。
#注意：如果run（）函数内通过QThread::exec（）启动线程的事件循环，则可以做一下几种事情：
#A 可以在本线程的对象之间使用信号和槽
#B 可以在本线程的对象之间传递事件，如：postEvent()和sendEvent()
#C 可以将本线程内对象的信号/槽连接到其他线程内对象的槽/信号上面
#D 可以从其他线程环境内向新线程环境中的对象（请使用postEvent()方法）发送事件；
#E 可以使用QT框架中需要事件循环的类库，如：QTimer、QTcpSocket、QTcpServer、QUdpSocket、QProcess、QNetworkAccessManger、QNetworkReply etc.
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = doorbell
TEMPLATE = app


SOURCES += main.cpp \
    doorbell.cpp

HEADERS  += \
    doorbell.h

CONFIG += mobility
MOBILITY = 

RESOURCES += \
    doorbell.qrc

android-g++ {
    LIBS += -lgnustl_shared
}

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

OTHER_FILES += \
    android/AndroidManifest.xml

