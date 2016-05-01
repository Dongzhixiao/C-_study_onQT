#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

/*使用QWidget处理触摸事件的步骤：
 * 1.使用Qt::WA_AcceptTouchEvents属性
 * 2.重写bool event(QEvent *)方法
 * 3.调用accept()接受触摸事件
 * 4.使用QTouchEvent、QTouchPoint类获知事件详情并根据需要处理
 */

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

    bool event(QEvent *);

private:
    void dumpTouchEvent(QEvent *e);
};

#endif // WIDGET_H
