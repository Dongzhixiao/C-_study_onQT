#include "widget.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QTimer>
#include <QDebug>

void SecondFirer::onTimeout()
{
    if(m_nSeconds >= 0)
    {
        unsigned int id = (unsigned int)QThread::currentThreadId();
        emit secondLeft(m_nSeconds, id);
        --m_nSeconds;
        qDebug() << "fire secondLeft signal";
    }
    else
    {
        QThread::currentThread()->exit(0);
    }
}

CountThread::CountThread(QWidget *receiver) : m_receiver(receiver)
{
}

CountThread::~CountThread()
{
    qDebug() << "~CountThread";
}

void CountThread::run()
{
    qDebug() << "CountThread id - " << (unsigned int)QThread::currentThreadId();
    QTimer timer;
    SecondFirer firer(10);
    connect(&timer, SIGNAL(timeout()), &firer, SLOT(onTimeout()));  //onTimerout()函数可以负责结束本线程的事件循环
    timer.start(1000);

    if(!m_receiver.isNull())
    {
        qDebug() << "connect firer && receiver";
        //下面这个连接跨线程了，因为m_receiver是构造时传进来的一个QWidget类，即主线程的指针，就可以实现与主线程的通信
        connect(&firer, SIGNAL(secondLeft(int,uint)), m_receiver.data(), SLOT(onSecondLeft(int,uint)));
    }

    exec();
}


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , m_label(new QLabel)
{
    QVBoxLayout * layout = new QVBoxLayout;
    layout->addWidget(m_label);
    setLayout(layout);
    CountThread * t = new CountThread(this);
    connect(t, SIGNAL(finished()), t, SLOT(deleteLater()));
    t->start();
}

Widget::~Widget()
{
}

void Widget::onSecondLeft(int iLeft, unsigned int id)
{
    QString str = QString("remain %1, current thread id %2, fire thread id %3").arg(iLeft)
                  .arg((unsigned int)QThread::currentThreadId()).arg(id);
    m_label->setText(str);
    if(iLeft == 0)
    {
        QMessageBox::information(this, "CLAP NOW", "It\'s time to clap now!\nClap! Clap! Clap!");
    }
}
