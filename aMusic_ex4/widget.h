#ifndef WIDGET_H
#define WIDGET_H
#include "../openFileWidget.h"
#include "musicWidget.h"
#include <QStackedLayout>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
#ifndef ANDROID
    QSize sizeHint() const { return QSize(320,480); }
#endif

protected slots:
    void onSelectSong();    //响应“打开”按钮！
    void onFileSelected(QString strFile);
    void onFileSelectCanceled();

protected:
    void resizeEvent(QResizeEvent *event);
    bool eventFilter(QObject *, QEvent *);  //事件过滤器，为了当焦点跑到子控件上时，返回事件仍然可以被处理，过滤器安装在main()函数中
                                            //的应用级别上，如果子控件少，也可以直接在本身构造函数中一个个安装:
                                            //m_layout->installEventFilter(this);
                                            //m_fileSelector->installEventFilter(this);
                                            //m_player->installEventFilter(this);
private:
    void setupGUI();

private:
    QStackedLayout *m_layout;
    OpenFileWidget * m_fileSelector;
    MusicWidget *m_player;
};

#endif // WIDGET_H
