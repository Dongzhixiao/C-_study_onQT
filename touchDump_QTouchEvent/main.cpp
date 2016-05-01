#include "widget.h"
#include <QApplication>
#include "../qDebug2Logcat.h"

int main(int argc, char *argv[])
{
    installLogcatMessageHandler("touchDump");  //安装消息处理器，这样就可使用"adb logcat -s touchDump"命令来查看示例输出的信息
    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}
