#include "linearlabel.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QFontMetrics>
#include <QRectF>

LinearLabel::LinearLabel(const QString &text, QWidget *parent)
    : QWidget(parent)
    , m_text(text)
    , m_backgroundColor(Qt::transparent)
    , m_textColor(Qt::black)
    , m_linearGradient(0)
    , m_flags(Qt::AlignLeft | Qt::AlignVCenter)
    , m_penWidth(1)
{
    //构造函数使用setSizePolicy设置其本身的尺寸策略。水平方向根据情况设置LinearLabel的宽度
    //垂直方向会保持sizeHint()返回的高度不变。
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
}

LinearLabel::~LinearLabel()
{
    if(m_linearGradient) delete m_linearGradient;
}

void LinearLabel::setColorAt(qreal position, const QColor &color)
{
    if(!m_linearGradient)
    {
        m_linearGradient = new QLinearGradient();
    }
    m_linearGradient->setColorAt(position, color);
}

void LinearLabel::clearGradient()
{
    if(m_linearGradient)
    {
        delete m_linearGradient;
        m_linearGradient = 0;
        update();
    }
}

QSize LinearLabel::sizeHint() const
{//这里根据当前字体，计算文本占用的宽度，提取当前字体的高度，宽、高各留一些余量，构造Qsize对象并返回
    if(m_text.isEmpty()) return QSize();
    QFontMetrics fm = fontMetrics();
    return QSize( fm.width(m_text) + 8, fm.height() + 4 );
}

void LinearLabel::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    QRect r = rect();   //这个函数属性保存了本身widget的内部几何大小
    if(m_backgroundPixmap.isNull())
    {
        painter.fillRect(r, m_backgroundColor);
    }
    else
    {
        painter.drawPixmap(r, m_backgroundPixmap);
    }

    QFontMetrics fm = painter.fontMetrics();
    QString elidedText = fm.elidedText(m_text, Qt::ElideRight
                                       , r.width() - 4
                                       );
    if(m_linearGradient)
    {
        QRectF boundingRect = fm.boundingRect(r, m_flags,elidedText);
        m_linearGradient->setStart(boundingRect.topLeft());   //渐变起点为左上
        m_linearGradient->setFinalStop(boundingRect.bottomLeft());  //渐变终点为右下
        QPen linearPen(QBrush(*m_linearGradient), m_penWidth);  //QBrush接收渐变对象，然后赋给画笔
        painter.setPen(linearPen);
        painter.drawText(boundingRect, m_flags, elidedText);
    }
    else
    {
        QPen pen(m_textColor, m_penWidth);
        painter.setPen(pen);
        painter.drawText(r, m_flags, elidedText);
    }
}

