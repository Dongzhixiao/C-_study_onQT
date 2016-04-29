#-------------------------------------------------
#
# Project created by QtCreator 2014-05-09T09:47:13
#学习使用QNetworkAccessManager进行http编程，其步骤为：
#1. 根据URL生成QUrl对象，然后根据QUrl创建一个网络请求QNetworkRequest,必要时可设置一些header。
#2. 调用QNetworkAccessManager的get()、post()等方法中的一个。
#3. 使用QNetworkAccessManager返回的QNetworkReply实例来跟踪应答的各种状态反馈。
#-------------------------------------------------

QT       += core gui widgets network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = httpTestTool
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h
