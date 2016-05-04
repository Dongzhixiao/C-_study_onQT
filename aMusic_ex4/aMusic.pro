#-------------------------------------------------
#
# Project created by QtCreator 2014-05-18T09:58:25
#综合实例,学习Qt实现多媒体框架,目前软件支持一下功能：
#1.选择一个音乐文件进行播放
#2.把一个文件夹下所有音乐文件加入到默认的播放列表
#3.支持单曲播放、单曲循环、顺序播放、列表循环、随机播放等播放模式
#4.支持摇动手势，可以摇一摇切歌
#5.支持翻转手势，当手机翻转时暂停播放
#注意：本实例还有界面定制功能：Qt样式表！！即QSS(Qt Style Sheets),其参考了HTML里面的层叠样式表CSS(Cascading Style Sheets)的语法和思想！！
#-------------------------------------------------

QT       += core gui multimedia sensors  #多媒体需要加上multimedia，里面有70多个类，本节只用到QMediaPlayer、QMediaPlaylist、QMediaContent三个类

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = aMusic
TEMPLATE = app

android-g++ {
    LIBS += -lgnustl_shared
}

SOURCES += main.cpp\
        widget.cpp \
    ../openFileWidget.cpp \
    ../worker.cpp \
    ../qDebug2Logcat.cpp \
    ../imageButton.cpp \
    musicWidget.cpp

HEADERS  += widget.h \
    ../openFileWidget.h \
    ../worker.h \
    ../qDebug2Logcat.h \
    ../imageButton.h \
    musicWidget.h \
    rowDelegate.h

CONFIG += mobility
MOBILITY = 

RESOURCES += \
    amusic.qrc

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

OTHER_FILES += \
    android/AndroidManifest.xml

