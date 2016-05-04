#ifndef ROWDELEGATE_H
#define ROWDELEGATE_H
#include <QItemDelegate>
/*为了选中单元格不出现虚线框，继承QItemDelegate类，然后drawFocus啥也不写，就没虚线框了
 * QTableWidget<--QTableView<--QAbstractItemView里面有setItemDelegate设置view的delegate
 * Qt的model/view框架，类似我们常说的MVC模式，model存储数据模型，view展示用户接口，delegate负责item的绘制和编辑
 */
class RowDelegate : public QItemDelegate
{
public:
    RowDelegate(QObject * parent = 0) :QItemDelegate(parent)
    {
    }

    virtual void drawFocus(QPainter *painter, const QStyleOptionViewItem &option,
                           const QRect &rect) const
    {
    }

    virtual void drawCheck(QPainter *painter, const QStyleOptionViewItem &option,
                           const QRect &rect, Qt::CheckState state) const
    {
    }
};
#endif // ROWDELEGATE_H
