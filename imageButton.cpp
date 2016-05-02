#include "imageButton.h"
#include <QPainter>
#include <QRect>

ImageButton::ImageButton(QPixmap normal, QPixmap pressed, QWidget *parent)
    : QAbstractButton(parent)
    , m_normal(normal)
    , m_pressed(pressed)
    , m_bPressed(false)
{
    connect(this, SIGNAL(pressed()), this, SLOT(onPressed()));
    connect(this, SIGNAL(released()), this, SLOT(onReleased()));
    setAttribute(Qt::WA_NoSystemBackground); //此函数必须有：它声明不用系统背景，这样我们在painEvent()函数绘制带Alpha通道的图片时
    //才可以与父控件和谐融合在一起，否则你就会看到图片虽然是圆角的，可是按钮却带了灰色背景！！
}

void ImageButton::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    if(m_bPressed)
    {
        painter.drawPixmap(rect(), m_pressed);  //此函数自动拉伸m_pressed图片填充指定rect()函数返回的矩形
    }
    else
    {
        painter.drawPixmap(rect(), m_normal);
    }
}

void ImageButton::onPressed()
{
    m_bPressed = true;
    update();
}

void ImageButton::onReleased()
{
    m_bPressed = false;
    update();
}
