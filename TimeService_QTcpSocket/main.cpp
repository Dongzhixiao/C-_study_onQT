#include "widget.h"
#include "timeService.h"
#include <QApplication>
#include "../qDebug2Logcat.h"

int main(int argc, char *argv[])
{
    installLogcatMessageHandler("timeservice");
    QApplication a(argc, argv);

    TimeServer server;
    server.listen(QHostAddress::Any,37);
    server.listen(QHostAddress("192.168.10.102"),37);   //实际使用手注意输入自己电脑的IP地址

    Widget w;
    w.show();

    return a.exec();
}
