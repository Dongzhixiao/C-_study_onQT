#ifndef DOORBELL_H
#define DOORBELL_H
#include <QWidget>
#include <QEvent>
#include <QLabel>
#include <QThread>
#include <QPointer>
#include <QStringList>
#include <QTimer>
/*你可以在QEvent子类中添加自己的事件所需要的数据，然后进行事件的发送。Qt中提供了两种发送方式：
 *1.static bool QCoreApplication::sendEvent(QObjecy * receiver, QEvent * event)：事件被QCoreApplication的notify()函数
 * 直接发送给receiver对象，返回值是事件处理函数的返回值。使用这个函数必须要在栈上创建对象，例如：
 * QMouseEvent event(QEvent::MouseButtonPress, pos, 0, 0, 0);
 * QApplication::sendEvent(mainWindow, &event);
 *2.static bool QCoreApplication::postEvent(QObject * receiver, QEvent * event)：事件被QCoreApplication追加到事件列表的最后，
 * 并等待处理，该函数将事件追加后会立即返回，并且注意，该函数是线程安全的。另外一点是，使用这个函数必须要在堆上创建对象，例如：
 * QApplication::postEvent(object, new MyEvent(QEvent::registerEventType(2048)));
 * 这个对象不需要手动delete，Qt会自动delete掉！因此，如果在post事件之后调用delete，程序可能会崩溃。
 * 另外，postEvent()函数还有一个重载的版本，增加一个优先级参数，具体请参见API。通过调用sendPostedEvent()函数可以让已提交的事件立即得到处理。
 * 注意：跨线程一定要用第二种！！！！
 */
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
    Ringer(BellThread * t);   //Ringer事件构造时传入线程的指针
public slots:
    void onTimeout();
private:
    BellThread *m_thread;
};

class BellThread : public QThread
{
    friend class Ringer;
public:
    BellThread(QObject * receiver);   //线程构造时传入主线程的指针

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
