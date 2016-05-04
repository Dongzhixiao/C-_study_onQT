#include "widget.h"
#include <QApplication>
#include "../qDebug2Logcat.h"

    //"  background: #04040a;"
//下面定义了全局样式表,其中QPushButton使用了线性渐变颜色,还专门设置了按压按键后的颜色
#define GLOBAL_STYLES \
    "QWidget {"\
    "  background-color: #050306;"\
    "  color: #F0F0F0;"\
    "}"\
    "QPushButton {"\
    "    border: 1px solid #8f8f91;"\
    "    border-radius: 6px;"\
    "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #383a3f, STOP:0.5 #1c1e23, stop:1 #383a3f);"\
    "    min-width: 60px;"\
    "    min-height: 25px;"\
    "}"\
    "QPushButton:pressed {"\
    "    color: #ff9A02;"\
    "}"
/*
    "QListWidget {"\
    "border: 1px solid  #8f8f91;"\
    "border-radius: 4px;"\
    "padding: 2px;"\
    "}"
*/

int main(int argc, char *argv[])
{
    installLogcatMessageHandler("aMusic");
    QApplication a(argc, argv);
    Widget w;
    a.installEventFilter(&w);    //应用级别的事件处理器：先于窗口部件处理任何事件！！！为了处理BACK按键！！
    w.setStyleSheet(GLOBAL_STYLES);
    w.show();

    return a.exec();
}
