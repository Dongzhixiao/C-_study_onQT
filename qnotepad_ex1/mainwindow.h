#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QString>
#include <QList>
#include "note.h"
#include "viewWidget.h"
#include <QPoint>

class MainWindow : public QWidget  //没有使用标准Qt控件，“新建笔记”按钮、笔记缩略图全部自绘，因此重写了painEvent()函数
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void onNotesUpdate();

protected:
    void resizeEvent(QResizeEvent *e);
    void paintEvent(QPaintEvent * e);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

private:
    void setupGeometry(const QSize & size);
    void releaseGeometryRects();
    void drawBackground(QPainter &painter);
    void drawAddButton(QPainter &painter);
    void drawThumbnails(QPainter &painter);
    void initializeNoteView();
    /* return rect index */
    int rectHitTest(QPoint & pos);
    void newNote();
    void openNote(QNote *note);
    /* return true on newNote() or openNote() */
    bool checkNoteAction(QPoint & pos);
    bool goPrevPage();
    bool goNextPage();
    void releaseNotes();

private:
    QList<QNote*> m_notes;
    QPixmap *m_background;
    QPixmap *m_thumbBackground;
    QPixmap *m_thumbAdd;
    QList<QRect*> m_thumbRects;  //记录界面内可显示笔记的所有矩形
    int m_nStartNote;
    int m_nEndNote;

    NoteViewWidget *m_noteView;
    QPen m_framePen;          //用来绘制元素边框
    QPen m_focusFramePen;     //用来绘制用户点击的元素的边框
    int m_nPressRect;    //表示用户单机矩形区域在m_thumbRects列表中的索引
    QPoint m_pressedPos; //用来跟踪手指是否划过屏幕(Qt默认会把未处理的触摸事件合成为鼠标事件)，因此重写了mousePressEvent mouseMoveEvent mouseReleaseEvent函数
    bool m_bMoving;      //同上
};

#endif // MAINWINDOW_H
