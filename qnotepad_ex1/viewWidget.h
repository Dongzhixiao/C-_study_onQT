#ifndef VIEWWIDGET_H
#define VIEWWIDGET_H

#include "note.h"
#include <QWidget>
#include <QTextEdit>
#include <QLabel>
#include "../imageButton.h"
//笔记浏览与编辑
class NoteViewWidget : public QWidget{
    Q_OBJECT
public:
    NoteViewWidget(QList<QNote*> &notes,
                   QWidget * parent = 0, Qt::WindowFlags f = 0);
    ~NoteViewWidget();

    void setNote(QNote *note);

signals:
    void notesUpdate();

protected slots:
    void onThumbnails();
    void onSave();
    void onDelete();
    void onAdd();
    void onTextChanged();

protected:
    void paintEvent(QPaintEvent * e);  //绘制整体背景、顶部功能区、地步标题栏的背景
    //重写后三个函数，为了用户单机BACK按键时返回应用首页而非直接退出应用
    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);
    bool eventFilter(QObject *obj, QEvent *event);

private:
    void setupGUI();
    void saveNotes();
    void checkChangeSave();

private:
    QNote *m_note;
    QList<QNote*> &m_notes;
    ImageButton *m_thumbnailsButton;
    ImageButton *m_saveButton;
    ImageButton *m_deleteButton;
    ImageButton *m_addButton;
    QTextEdit *m_edit;
    QLabel *m_titleLabel;
    bool m_bTextChanged;
};

#endif // VIEWWIDGET_H
