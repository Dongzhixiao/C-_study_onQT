#include "worker.h"
#include <QCoreApplication>

QEvent::Type RunnableExcutedEvent::s_evType = QEvent::None;
RunnableExcutedEvent::RunnableExcutedEvent(Runnable *r)
    : QEvent(evType())
     ,m_runnable(r)
{
}

QEvent::Type RunnableExcutedEvent::evType()
{
/*继承QEvent类，你需要提供一个QEvent::Type类型的参数，作为自定义事件的类型值。这里的QEvent::Type类型是QEvent里面定义的一个enum，
 * 因此，你是可以传递一个int的。重要的是，你的事件类型不能和已经存在的type值重复，否则会有不可预料的错误发生！
 * 因为系统会将你的事件当做系统事件进行派发和调用。在Qt中，系统将保留0 - 999的值，也就是说，你的事件type要大于999.
 * 具体来说，你的自定义事件的type要在QEvent::User和QEvent::MaxUser的范围之间。其中，QEvent::User值是1000，
 * QEvent::MaxUser的值是65535。从这里知道，你最多可以定义64536个事件，相信这个数字已经足够大了！
 * 但是，即便如此，也只能保证用户自定义事件不能覆盖系统事件，并不能保证自定义事件之间不会被覆盖。为了解决这个问题，
 * Qt提供了一个函数：registerEventType(),用于自定义事件的注册。
 */
    if(s_evType == QEvent::None)
    {
        s_evType = (QEvent::Type)registerEventType();
    }
    return s_evType;
}

class NewRunnableEvent : public QEvent
{
public:
    NewRunnableEvent(Runnable* runnable)
        : QEvent(evType())
        , m_runnable(runnable)
    {}
    static QEvent::Type evType()
    {
        if(s_evType == QEvent::None)
        {
            s_evType = (QEvent::Type)registerEventType();
        }
        return s_evType;
    }

    Runnable * m_runnable;

private:
    static QEvent::Type s_evType;
};
QEvent::Type NewRunnableEvent::s_evType = QEvent::None;

Worker::~Worker()
{
    if(m_runnables)
    {
        delete m_runnables;
    }
}

bool Worker::event(QEvent *e)
{
    QEvent::Type t = e->type();
    if(t == NewRunnableEvent::evType())
    {
        NewRunnableEvent * re = (NewRunnableEvent*)e;
        if(!re->m_runnable)
        {
            excuteQueuedRunnables();
        }
        else
        {
            excuteRunnable(re->m_runnable);
        }
        return true;
    }
    return QObject::event(e);
}

void Worker::excuteQueuedRunnables()
{
    int count = m_runnables ? m_runnables->size() : 0;
    if(count > 0)
    {
        excuteRunnable(m_runnables->takeFirst());
        QCoreApplication::postEvent(this, new NewRunnableEvent(0));
    }
}

void Worker::excuteRunnable(Runnable *runnable)
{
    runnable->run();
    if(runnable->notifyAfterRun() && runnable->m_observer)
    {
        QCoreApplication::postEvent(runnable->m_observer
                                    , new RunnableExcutedEvent(runnable));
    }
}

WorkerThread::WorkerThread(QObject *parent)
    : QThread(parent)
    , m_runnables(0)
{

}

WorkerThread::~WorkerThread()
{
    if(m_runnables)
    {
        delete m_runnables;
    }
}

void WorkerThread::postRunnable(Runnable *r)
{
    if(m_worker)
    {
        QCoreApplication::postEvent(m_worker, new NewRunnableEvent(r));
    }
    else
    {
        m_runnables = new QList<Runnable*>();
        m_runnables->append(r);
    }
}

void WorkerThread::run()
{
    Worker *worker = new Worker();
    m_worker = worker;
    if(m_runnables && m_runnables->size() > 0)
    {
        worker->m_runnables = m_runnables;
        m_runnables = 0;
        QCoreApplication::postEvent(worker, new NewRunnableEvent(0));
    }
    exec();
}
