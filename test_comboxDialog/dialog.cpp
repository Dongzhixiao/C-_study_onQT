#include "dialog.h"
#include "ui_dialog.h"
#include <QMenu>

#include <QDebug>

//ComboBox::ComboBox(QWidget *parent):QComboBox(parent)
//{}

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->treeWidget->setHeaderLabels(QStringList()<<tr("名称")<<tr("选项"));   //增加条目标题
    ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);   //使得该控件可以支持右键菜单
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_treeWidget_customContextMenuRequested(const QPoint &pos)
{
    QMenu *popMenu = new QMenu(this);//定义一个右键弹出菜单
    QTreeWidgetItem *curItem=ui->treeWidget->itemAt(pos);
    if (curItem == NULL) //空白处点击
    {
        popMenu->addAction(ui->action_add);
        ui->treeWidget->closePersistentEditor(_lastItem,_lastColumn);
        _lastItem = nullptr;
        _lastColumn = 0;
    }
    else
        popMenu->addAction(ui->action_delete);

    popMenu->exec(QCursor::pos());//弹出右键菜单，菜单位置为光标位置
}

void Dialog::on_action_add_triggered()
{
    QTreeWidgetItem *child = new QTreeWidgetItem(ui->treeWidget);
    child->setText(0,tr("请修改"));
    ComboBox *comb = new ComboBox(this);
    connect(comb,SIGNAL(mousePressed()),this,SLOT(on_comboBox_changed()));
    //comb->addItems(QStringList()<<"条目1"<<"条目2");
    ui->treeWidget->setItemWidget(child,1,comb);
    allComboBox.append(comb);    //增加对应的ComboBox
    //修改所有comboBox
    int ComNum = allComboBox.count();
    for(int i=0 ; i != ComNum; ++i)
    {
        ComboBox *tem = allComboBox.at(i);
        int temNum = tem->currentIndex(); //保存当前选择的条目数
        tem->clear();
        for(int j = 0 ;j != ComNum ; ++j)
            tem->addItem(QString("条目%1").arg(j+1));
        tem->setCurrentIndex(temNum);
    }
}

void Dialog::on_action_delete_triggered()
{
    QTreeWidgetItem *curItem = ui->treeWidget->currentItem();
    ComboBox *curCom = (ComboBox *)ui->treeWidget->itemWidget(curItem,1);
    for(int i = 0 ; i != allComboBox.count() ;  ++i)
        if(allComboBox.at(i) == curCom)
        {
            allComboBox.removeAt(i);     //删除对应的ComboBox
            break;   //注意，这个不要忘记加！！！！否则会越界！
        }
    delete curItem;
    //修改所有comboBox
    int ComNum = allComboBox.count();
    for(int i=0 ; i != ComNum; ++i)
    {
        ComboBox *tem = allComboBox.at(i);
        int temNum = tem->currentIndex(); //保存当前选择的条目数
        tem->clear();
        for(int j = 0 ;j != ComNum ; ++j)
            tem->addItem(QString("条目%1").arg(j+1));
        tem->setCurrentIndex(temNum);   //设置超过条目数目也没事！！Qt果然厉害
    }
}

void Dialog::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    if(column == 0)
        ui->treeWidget->openPersistentEditor(item,column);
    _lastColumn = column;
    _lastItem = item;
}

void Dialog::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    if(_lastColumn != column || _lastItem != item)
        ui->treeWidget->closePersistentEditor(_lastItem,_lastColumn);
    _lastColumn = column;
    _lastItem = item;
}

void Dialog::on_comboBox_changed()
{
    //Q_UNUSED(curNum);
    ComboBox * temCom = (ComboBox *)qobject_cast<ComboBox *>(sender());
    QIcon empty;  //定义空图标
    QList<int> tem;
    for(int i = 0 ; i != allComboBox.count() ;  ++i)
        if(allComboBox.at(i) != temCom)
            tem.append(allComboBox.at(i)->currentIndex());
    //qDebug()<<tem.count();
    for(int i = 0 ; i != allComboBox.count() ;  ++i)
        if(tem.contains(i))
            temCom->setItemIcon(i,QIcon(":/Pic/delete_item.png"));
        else
            temCom->setItemIcon(i,empty);
}
