#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QThread>
#include <QPointer>

class SecondFirer : public QObject //这个类会在新线程中构建它的实例，这是正统的做法，用来实现倒计时的触发逻辑
{                                   //实际运用时可以处理需要在线程中实现的触发逻辑
    Q_OBJECT
public:
    SecondFirer(int seconds) : m_nSeconds(seconds){}

signals:
    void secondLeft(int sec, unsigned int id);
public slots:
    void onTimeout();
private:
    int m_nSeconds;
};

class CountThread : public QThread  //使用线程必须继承QThread
{
public:
    CountThread(QWidget * receiver);  //本例中通过线程对象的构造函数传入主线程对象的指针
    ~CountThread();

protected:
    void run();  //线程内实现的逻辑需要在run()函数内实现

private:
    QPointer<QWidget> m_receiver;  //智能指针保存Widget的实例，它保存的QObject指针指向的对象销毁时会得到通知自行归NULL
};                                 //我们用它的isNull()方法判断是否可以访问它持有的对象的指针

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void onSecondLeft(int sec, unsigned int id);

private:
    QLabel * m_label;
};

#endif // WIDGET_H
