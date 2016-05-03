//文件选择控件
#ifndef OPENFILEWIDGET_H
#define OPENFILEWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QLabel>
#include "worker.h"
#include <QFileInfoList>
#include <QIcon>
#include <QFont>

class DirectoryTraverse;
class OpenFileWidget : public QWidget
{
    Q_OBJECT
public:
    OpenFileWidget(const QString &path, QStringList &nameFilters, QWidget *parent = 0);
    ~OpenFileWidget();

    bool event(QEvent *e);

    void getPath(QString & path);    //获取用户选中文件所在的目录
    void getFileList(QStringList & files);   //获取所选文件同目录下的同类型文件的列表

#ifndef ANDROID
    QSize sizeHint() const { return QSize(320,480); }
#endif

    bool onBackKey();  //在处理“BACK”按键时调用的，本身没有处理这个按键

signals:
    void selected(QString strFile);  //当用户选择文件是，发射此信号
    void canceled();    //用户点击“取消”按钮则发送次信号

protected slots:
    void onItemClicked(QListWidgetItem * item);
    void onItemDoubleClicked(QListWidgetItem * item);
    void onParent();
    void onCancel();
    void onOpen();

protected:
    void setupGUI();
    void updateList(QFileInfoList & files);
    void startTraverse();
    void setupPath(QListWidgetItem *item);
    const QIcon &getFileIcon(const QString &fileName);

private:
    QPushButton *m_parentButton;
    QPushButton *m_openButton;
    QPushButton *m_cancelButton;
    QLabel *m_pathLabel;
    QListWidget *m_fileList;
    QString m_path;
    QStringList m_files;
    WorkerThread *m_worker;
    DirectoryTraverse *m_dirTraverse;
    QIcon m_folderIcon;
    QIcon m_imageFileIcon;
    QIcon m_audioFileIcon;
    QIcon m_videoFileIcon;
    QIcon m_txtFileIcon;
    QIcon m_binFileIcon;
};

#endif // OPENFILEWIDGET_H
