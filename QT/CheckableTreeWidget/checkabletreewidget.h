#ifndef CHECKABLETREEWIDGET_H
#define CHECKABLETREEWIDGET_H

#include <QWidget>

// QTreeWidgetItem 是 QTreeWidget（树形控件）里的“一个节点”（或者叫“一行”）
#include <QTreeWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class CheckableTreeWidget; }
QT_END_NAMESPACE

class CheckableTreeWidget : public QWidget
{
    Q_OBJECT

public:
    CheckableTreeWidget(QWidget *parent = nullptr);
    ~CheckableTreeWidget();

    void init();
    void updateParentItem(QTreeWidgetItem *item);

private slots:
    void treeItemChanged(QTreeWidgetItem *item,int column);

private:
    Ui::CheckableTreeWidget *ui;
};
#endif // CHECKABLETREEWIDGET_H
