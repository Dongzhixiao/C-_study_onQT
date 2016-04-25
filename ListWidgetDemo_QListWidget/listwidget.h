#ifndef LISTWIDGET_H
#define LISTWIDGET_H
#include <QWidget>
#include <QComboBox>
#include <QListWidget>

class FileExplorer : public QWidget
{
    Q_OBJECT
public:
    FileExplorer(QWidget *parent = 0);

protected slots:
    void onViewModeChanged(const QString &mode);

private:
    QComboBox *m_modeCombo;
    QListWidget *m_list;  //其内部需要加入的item是QListWidgetItem类型的
};

#endif // LISTWIDGET_H
