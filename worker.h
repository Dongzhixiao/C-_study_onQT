//目录遍历工作线程：采用“线程+工人+事件”模式！
#ifndef WORKER_H
#define WORKER_H

#include <QThread>
#include <QEvent>
#include <QPointer>
#include <QList>

/* NOTES:
 *   1. the caller MUST maintain Runnable's life cycle
 *   2. the derived class MUST offer a QObject instance
 *      to receive RunnableExcutedEvent
 */
class Runnable
{
public:
    Runnable(QObject *observer)
        : m_observer(observer)
    {}
    virtual ~Runnable(){}
    virtual void run() = 0;
    virtual bool notifyAfterRun(){ return true; }

    QPointer<QObject> m_observer;
};
/*为什么我需要使用事件，而不是使用信号槽呢？主要原因是，事件的分发既可以是同步的，又可以是异步的，而函数的调用或者说是槽的回调总是同步的。
 * 事件的另外一个好处是，它可以使用过滤器。
 */
class RunnableExcutedEvent : public QEvent
{
public:
    RunnableExcutedEvent(Runnable *r);
    Runnable *m_runnable;

    static QEvent::Type evType();

private:
    static QEvent::Type s_evType;
};

class WorkerThread : public QThread  //工作线程接受具有Runnable接口的对象，执行完后反馈RunnableExcutedEvent给Runnable携带的观察者
{
public:
    WorkerThread(QObject *parent = 0);
    ~WorkerThread();

    void postRunnable(Runnable *r);   //用于提交待执行任务，具体任务由Worker类负责执行

protected:
    void run();

private:
    QPointer<QObject> m_worker;
    QList<Runnable*> *m_runnables; //temp queue
};

class Worker : public QObject
{
    friend class WorkerThread;
public:
    Worker() : m_runnables(0)
    {}
    ~Worker();

    bool event(QEvent *e);

private:
    void excuteQueuedRunnables();
    void excuteRunnable(Runnable *runnable);

private:
    QList<Runnable*> *m_runnables;
};

#endif // WORKER_H
