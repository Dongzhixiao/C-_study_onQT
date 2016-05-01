#include "widget.h"
#include <QEvent>
#include <QTouchEvent>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_AcceptTouchEvents);  //构造函数中使用为了其可接受触摸事件
}

Widget::~Widget()
{

}

bool Widget::event(QEvent *e)
{//QTouchEvent默认会被QWodget忽略，因此必须重载函数显示的调用accept()函数来接受事件
    QEvent::Type type = e->type();
    switch(type)
    {
    case QEvent::TouchBegin:
        e->accept();
        dumpTouchEvent(e);
        return true;
    case QEvent::TouchUpdate:
        e->accept();
        dumpTouchEvent(e);
        return true;
    case QEvent::TouchEnd:
        e->accept();
        dumpTouchEvent(e);
        return true;
    case QEvent::TouchCancel:
        e->accept();
        dumpTouchEvent(e);
        return true;
    default:
        break;
    }
    return QWidget::event(e);
}

void Widget::dumpTouchEvent(QEvent *e)   //此函数用来打印触摸事件的详细信息
{
    QTouchEvent * te = (QTouchEvent *)e;
    qDebug() << "type - " << te->type();
    qDebug() << "device - " << te->device();
    qDebug() << "touchPointStates - " << te->touchPointStates();
    const QList<QTouchEvent::TouchPoint> & points= te->touchPoints();
    int count = points.size();
    if(!count) return;
    for(int i = 0; i < count; i++)
    {
        const QTouchEvent::TouchPoint &point = points.at(i);
        qDebug() << "point " << i+1  << "information:";
        qDebug() << "  --relative to widget";
        qDebug() << "    pos - " << point.pos();   //当前位置
        qDebug() << "    startPos - " << point.startPos();  //起始位置
        qDebug() << "    lastPos - " << point.lastPos();    //上一个触点位置
        qDebug() << "    rect - " << point.rect();
        qDebug() << "  --relative to screen";
        qDebug() << "    screenPos - " << point.screenPos();
        qDebug() << "    scrennRect - " << point.screenRect();
    }
}
