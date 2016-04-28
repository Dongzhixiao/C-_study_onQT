#include "widget.h"
#include <QtConcurrent>
#include <QFuture>
#include <QFutureWatcher>
#include <QPainter>
#include <QTimer>

QImage loadImage(const QString & uri)
{
    QImage image(uri);
    return image;
}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , m_watcher(this)
{
    connect(&m_watcher, SIGNAL(finished()),
            this, SLOT(onFinished()));
    QTimer::singleShot(5000, this, SLOT(onLoad()));
}

void Widget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    if(m_image.isNull())
    {
        painter.drawText(rect(), Qt::AlignCenter, "Loading...");
    }
    else
    {
        painter.drawImage(rect(), m_image);
    }
}

void Widget::onLoad()
{
    QString uri(":/airplay.gif");
    QFuture<QImage> future =
            QtConcurrent::run(loadImage, uri);  //这里提交一个异步任务，指定指向任务的函数是loadImage(),函数需要的参数紧跟在函数名字后面
            //run()函数返回值为QFuture类型的对象，QFuture<T>模板类的T类型和run()方法执行的函数的返回类型相匹配！
    m_watcher.setFuture(future); //这里把future对象传递给QFutureWatcher来进行跟踪管理！！
}

void Widget::onFinished()
{
    m_image = m_watcher.future().result();  //future()获取当前QFuture对象，result()得到异步任务的结果
    if(!m_image.isNull())
    {
        repaint();   //如果结果有图像，就更新界面咯~
    }
}

