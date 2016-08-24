#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QList>
#include <QComboBox>

class QTreeWidgetItem;

namespace Ui {
class Dialog;
}

class ComboBox:public QComboBox
{
    Q_OBJECT
public:
    explicit ComboBox(QWidget *parent = Q_NULLPTR):QComboBox(parent)
    {}
protected:
    void mousePressEvent(QMouseEvent *e) override
    {
        emit mousePressed();
        QComboBox::mousePressEvent(e);
    }
signals:
    void mousePressed();
};

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_treeWidget_customContextMenuRequested(const QPoint &pos);

    void on_action_add_triggered();

    void on_action_delete_triggered();

    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

    void on_comboBox_changed();
private:
    Ui::Dialog *ui;
    QTreeWidgetItem * _lastItem = nullptr;
    int _lastColumn = 0;
    QList<ComboBox *> allComboBox;
};

#endif // DIALOG_H
