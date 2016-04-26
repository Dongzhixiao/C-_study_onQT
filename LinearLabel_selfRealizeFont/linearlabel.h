#ifndef LINEARLABEL_H
#define LINEARLABEL_H
#include <QWidget>
#include <QColor>
#include <QPixmap>
#include <QLinearGradient>
#include <QSize>

class LinearLabel : public QWidget
{
    Q_OBJECT
public:
    LinearLabel(const QString &text, QWidget *parent = 0);
    ~LinearLabel();

    void setBackgroundColor(const QColor & color)   //设置背景颜色
    {
        m_backgroundColor = color;
    }
    void setBackgroundImage(const QPixmap &pixmap)  //设置背景图片
    {
        m_backgroundPixmap = pixmap;
    }
    void setTextColor(const QColor &color)   //设置文字颜色
    {
        m_textColor = color;
    }

    void setColorAt(qreal position, const QColor & color);  //设置渐变的节点以及对应颜色
    void clearGradient();    //清除上一个函数设置的渐变方法

    void setAlignment(Qt::AlignmentFlag flag)  //设置对其方式
    {
        m_flags = flag;
    }

    void setPenWidth(qreal width)   //设置画笔粗细
    {
        m_penWidth = width;
    }

    QSize sizeHint() const;   //这个属性函数返回次widget的大小

public slots:
    void setText(const QString &text)
    {
        m_text = text;
        update();
    }

protected:
    void paintEvent(QPaintEvent *e);  //可以学习如何使用QPainter绘制背景、文字、颜色之类的

private:
    QString m_text;
    QColor m_backgroundColor;
    QPixmap m_backgroundPixmap;
    QColor m_textColor;
    QLinearGradient *m_linearGradient;
    int m_flags;
    qreal m_penWidth;
};

#endif // LINEARLABEL_H
