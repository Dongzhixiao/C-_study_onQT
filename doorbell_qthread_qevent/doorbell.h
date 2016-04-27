#ifndef DOORBELL_H
#define DOORBELL_H
#include <QWidget>
#include <QEvent>
#include <QLabel>
#include <QThread>
#include <QPointer>
#include <QStringList>
#include <QTimer>

class BellEvent : public QEvent  //用于线程之间通信的一个自定义事件，主要学习自定义事件的写法！！！
{
public:
    BellEvent(const QString & visitor, const QStringList & gifts);
    QString m_visitor;
    QStringList m_gifts;

    static Type eventType();
protected:
    static Type m_evType;
};

class BellThread;
class QTimer;
class Ringer : public QObject
{
    Q_OBJECT
public:
    Ringer(BellThread * t);
public slots:
    void onTimeout();
private:
    BellThread *m_thread;
};

class BellThread : public QThread
{
    friend class Ringer;
public:
    BellThread(QObject * receiver);

protected:
    void run();

private:
    QPointer<QObject> m_receiver;   //持有接收门铃事件的对象，即主线程的指针！！！这样才好实现线程直接的信号传递！！
};

class Master : public QWidget
{
    Q_OBJECT

public:
    Master(QWidget *parent = 0);
    ~Master();
protected:
    bool event(QEvent * e);

private:
    QLabel * m_visitorLabel;   //用来显示客人和礼物
    QLabel * m_movie;          //播放一个gif动画
};

#endif // DOORBELL_H
