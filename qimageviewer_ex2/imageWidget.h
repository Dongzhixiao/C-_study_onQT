/*本例实现大体分三部分：图片列表、手势处理、图标显示和变换
 */
#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
#include <QImage>
#include "imageLoadManager.h"
#include "../openFileWidget.h"
#include "../imageButton.h"

class QGestureEvent;
class QPanGesture;
class QPinchGesture;
class QSwipeGesture;

class ImageWidget : public QWidget
{
    Q_OBJECT

public:
    ImageWidget(QWidget *parent = 0);
    ~ImageWidget();

protected:
    bool event(QEvent *event);  //重载event函数来处理触摸手势
    void paintEvent(QPaintEvent *event);  //重写painEvent来显示图片
    void resizeEvent(QResizeEvent *event);

protected slots:
    void onFileSelected(QString strFile);  //用户选择图片则触发该槽
    void onFileSelectCanceled();
    void goNextImage();   //进入下一张
    void goPrevImage();   //进入上一张

private:
    bool gestureEvent(QGestureEvent *event);   //处理手势事件的函数
    void panTriggered(QPanGesture*);  //此函数中记录水平、垂直偏移量m_horizontalOffset和m_vertialOffset，然后painevent函数会处理！
    void pinchTriggered(QPinchGesture*);  //此函数changeFlags方法会返回手势变化类型，注意学习！！
    void swipeTriggered(QSwipeGesture*);
    void resetPaintParameters();

    void openDirectory();
    void updateImage();
    void loadImage();   //可以调用loadImager()函数异步加载图片
    void goToImage(int index);
    void reposControllers(const QSize &size);
    void checkNextPrevIndicator();

    QString m_strPath;
    QStringList m_files;  //保存一个目录下所有图片文件
    int m_position;
    QImage m_image;
    ImageLoadManager *m_loader;
    OpenFileWidget * m_fileSelector;
    QLabel *m_loadingLabel;
    ImageButton * m_prevButton;
    ImageButton * m_nextButton;

    float m_horizontalOffset;
    float m_verticalOffset;
    float m_rotationAngle;
    float m_scaleFactor;
    float m_currentStepScaleFactor;
    bool m_bLoading;
};

#endif
