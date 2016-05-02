#ifndef IMAGEBUTTON_H
#define IMAGEBUTTON_H
#include <QAbstractButton>
#include <QPixmap>
/*继承QAbstractButton的原因：
 * 1.已经处理了各个事件，能正常响应触摸操作
 * 2.有pressed()和released()两个信号可以反馈下压和释放两种状态
 * 3.重载painEvent()函数可以改变按钮形状(QWidget子类共有的特点)
 */
class ImageButton : public QAbstractButton
{
    Q_OBJECT
public:
    ImageButton(QPixmap normal, QPixmap pressed, QWidget *parent = 0);

protected slots:
    void onPressed();
    void onReleased();

protected:
    void paintEvent(QPaintEvent *e);

protected:
    QPixmap m_normal;   //正常状态图片
    QPixmap m_pressed;  //下压状态图片
    bool m_bPressed;
};

#endif // IMAGEBUTTON_H
