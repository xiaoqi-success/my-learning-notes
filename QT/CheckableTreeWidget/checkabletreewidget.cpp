#include "checkabletreewidget.h"
#include "ui_checkabletreewidget.h"

// 练习树形控件
// 当选中顶层的树形节点时，子节点全部被选中
// 当取消选择顶层树形节点时，子节点的选中状态全部被取消
// 当选中子节点时，父节点显示部分选中的状态

CheckableTreeWidget::CheckableTreeWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CheckableTreeWidget)
{
    ui->setupUi(this);

    this->resize(1000,500);
    init();
    connect(ui->treeWidget,&QTreeWidget::itemChanged,this,&CheckableTreeWidget::treeItemChanged);
}

CheckableTreeWidget::~CheckableTreeWidget()
{
    delete ui;
}

// 在ui页面中拖拽出一个QTreeWidget树形控件之后进行初始化操作
void CheckableTreeWidget::init()
{
    // 先清除树形控件中的所有内容
    ui->treeWidget->clear();
    ui->treeWidget->resize(500,400);
    // 第一个分组,group1 是树中的一个节点（顶层节点）
    QTreeWidgetItem *group1 = new QTreeWidgetItem(ui->treeWidget);
    group1->setText(0,"group1");
    //setFlags的作用是为 group1 这个节点设置交互权限
    // ItemIsUserCheckable → 节点前面出现复选框，用户可以勾选
    // ItemIsEnabled → 节点可用（不置灰）
    // ItemIsSelectable → 节点可被选中高亮
    group1->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    // 第0列的复选框默认不勾选
    group1->setCheckState(0,Qt::Unchecked);

    QTreeWidgetItem *subItem11 = new QTreeWidgetItem(group1);
    subItem11->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem11->setText(0,"subItem11");
    subItem11->setCheckState(0,Qt::Unchecked);

    QTreeWidgetItem *subItem12 = new QTreeWidgetItem(group1);
    subItem12->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem12->setText(0,"subItem12");
    subItem12->setCheckState(0,Qt::Unchecked);

    QTreeWidgetItem *subItem13 = new QTreeWidgetItem(group1);
    subItem13->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem13->setText(0,"subItem13");
    subItem13->setCheckState(0,Qt::Unchecked);

    QTreeWidgetItem *subItem14 = new QTreeWidgetItem(group1);
    subItem14->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem14->setText(0,"subItem14");
    subItem14->setCheckState(0,Qt::Unchecked);

    // 第二个分组
    QTreeWidgetItem *group2 = new QTreeWidgetItem(ui->treeWidget);
    group2->setText(0,"book");
    group2->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    group2->setCheckState(0,Qt::Unchecked);
    QTreeWidgetItem *subItem21 = new QTreeWidgetItem(group2);
    subItem21->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem21->setText(0,"红楼梦");
    subItem21->setCheckState(0,Qt::Unchecked);

    QTreeWidgetItem *subItem22 = new QTreeWidgetItem(group2);
    subItem22->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem22->setText(0,"简爱");
    subItem22->setCheckState(0,Qt::Unchecked);

    QTreeWidgetItem *subItem23 = new QTreeWidgetItem(group2);
    subItem23->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem23->setText(0,"学会说话");
    subItem23->setCheckState(0,Qt::Unchecked);

}

void CheckableTreeWidget::updateParentItem(QTreeWidgetItem *item)
{
    QTreeWidgetItem *parent = item->parent();
    if(parent == NULL){
        return;
    }
    // 选中的子节点个数
    int selectedCount = 0;
    int childCount = parent->childCount();
    for(int i = 0;i < childCount;i++){
        QTreeWidgetItem *childItem = parent->child(i);
        if(childItem->checkState(0) == Qt::Checked){
            selectedCount++;
        }
    }
    if(selectedCount <= 0){
        // 未选中状态
        parent->setCheckState(0,Qt::Unchecked);
    }else if(selectedCount > 0 && selectedCount < childCount){
        // 部分选中状态
        parent->setCheckState(0,Qt::PartiallyChecked);
    }else if(selectedCount == childCount){
        // 选中状态
        parent->setCheckState(0,Qt::Checked);
    }
}

void CheckableTreeWidget::treeItemChanged(QTreeWidgetItem *item, int column)
{
    // 只处理"被勾选"的情况，不分层级（顶层/中间层/叶子节点都会进来）
    if(Qt::Checked == item->checkState(0)){
        int count = item->childCount();// 看这个 item 有几个子节点
        if(count > 0){
            // 有子节点 → 父节点（顶层或中间层），向下全选
            for(int i = 0;i < count;i++){
                // 子节点也选中
                item->child(i)->setCheckState(0,Qt::Checked);
            }
        }else{
            // 没有子节点 → 叶子节点，向上更新父节点状态
            updateParentItem(item);
        }
    }else if(Qt::Unchecked == item->checkState(0)){
        int count = item->childCount();
        if(count > 0){
            for(int i = 0;i < count;i++){
                item->child(i)->setCheckState(0,Qt::Unchecked);
            }
        }else{
            updateParentItem(item);
        }
    }
}

