# 📌 进阶实战：带复选框的树形控件 (QTreeWidget)

**📂 项目路径**：`QT/CheckableTreeWidget`

**🎯 项目背景：**
在开发权限管理系统、资源管理器或联系人列表时，树形控件 (`QTreeWidget`) 是必不可少的。本项目实现了一个带有复选框的树形控件，并完美解决了**父子节点状态联动（三态逻辑）**，以及**信号递归触发导致崩溃的史诗级大坑**。

## 🛠️ 核心知识点拆解

### 1. 树形节点的创建与权限 (`QTreeWidgetItem`)

- **基本概念**：`QTreeWidget` 是整棵树（容器），而 `QTreeWidgetItem` 是树上的一个节点（行）。
- **创建节点**：`new QTreeWidgetItem(parentItem)`，如果传入的是树控件指针，则作为顶层节点；如果传入的是其他节点指针，则作为其子节点。
- **设置复选框**：默认情况下节点只有文字。必须使用 `setFlags` 赋予交互权限：
  - `Qt::ItemIsUserCheckable`：显示复选框，允许用户勾选。
  - `Qt::ItemIsEnabled`：节点可用（不被置灰）。
  - `Qt::ItemIsSelectable`：节点可被选中高亮。
- **设置初始状态**：`setCheckState(0, Qt::Unchecked)` （只针对第 0 列操作）。

### 2. 联动逻辑：向下级联（父影响子）

当用户点击顶层或中间层节点时，如果该节点被选中，需要遍历其所有的子节点，将它们的状态同步设为选中（或取消）。

### 3. 联动逻辑：向上反馈与三态 (`PartiallyChecked`)

当用户点击叶子节点时，需要反向去计算其父节点的状态。

- 遍历父节点下的所有子节点，统计被选中的个数 `selectedCount`。
- **三态判断**：
  - 如果 `selectedCount == 0`，父节点设为 `Qt::Unchecked`（全不选）。
  - 如果 `selectedCount == childCount`，父节点设为 `Qt::Checked`（全选）。
  - **如果选中数介于两者之间**，父节点设为 **`Qt::PartiallyChecked`**（半选状态，表现为灰色打钩或实心方块）。

## ⚠️ 实战史诗级避坑：死循环与信号递归

### 🚨 坑点 1：死循环与信号递归（最致命）

在实现上述逻辑时，新手极容易遇到程序崩溃或卡死。

- **坑点描述**：在代码中调用 `item->child(i)->setCheckState(0, Qt::Checked)` 修改子节点状态时，**会再次触发 `QTreeWidget::itemChanged` 信号**。信号又进入槽函数，槽函数又去改状态，导致无限递归（死循环），最终栈溢出崩溃。
- **✅ 解决方案（标志位锁）**：
  在头文件中定义一个 `bool isUpdating;` 变量（初始化为 `false`）。在批量修改子节点前加锁，修改完后解锁。

```cpp
if (isUpdating) return; // 拦截递归
isUpdating = true;
// ... 批量修改子节点代码 ...
isUpdating = false; // 解锁
```

### 🚨 坑点 2：性能问题（大数据量卡顿）

- **坑点描述**：如果你的树有上千个节点，每次点击父节点全选时，都会触发成百上千次 `setCheckState` 和信号发送，导致界面严重卡顿。

- **✅ 解决方案（信号阻塞）**：
  在批量更新期间，直接使用 `QSignalBlocker` 或者 `blockSignals(true)` 临时屏蔽该控件的所有信号，更新完毕后再恢复。

  ```Cpp
  ui->treeWidget->blockSignals(true); // 屏蔽所有信号
  // ... 执行批量更新 ...
  ui->treeWidget->blockSignals(false); // 恢复信号
  ```

*(注：如果你用了 `blockSignals`，就不再需要 `isUpdating` 锁了，因为信号根本没发出来。)*

### 🚨 坑点 3：懒加载与动态刷新

- **坑点描述**：如果数据是从数据库读的，一次性生成几千个 `QTreeWidgetItem` 会让启动极慢。
- **✅ 解决方案**：初始化时只加载顶层节点。监听 `itemExpanded` 信号，当用户点开某个父节点时，再去数据库查它的子节点并动态添加到树上。

## 💻 核心代码展示

### 1. 头文件声明 (`checkabletreewidget.h`)

```cpp
#ifndef CHECKABLETREEWIDGET_H
#define CHECKABLETREEWIDGET_H

#include <QWidget>
#include <QTreeWidgetItem> // 引入树节点类

QT_BEGIN_NAMESPACE
namespace Ui { class CheckableTreeWidget; }
QT_END_NAMESPACE

class CheckableTreeWidget : public QWidget
{
    Q_OBJECT

public:
    CheckableTreeWidget(QWidget *parent = nullptr);
    ~CheckableTreeWidget();

    void init(); // 初始化节点
    void updateParentItem(QTreeWidgetItem *item); // 向上反馈函数

private slots:
    void treeItemChanged(QTreeWidgetItem *item, int column); // 节点状态变化槽函数

private:
    Ui::CheckableTreeWidget *ui;
    bool isUpdating; // 🔥 防止死循环的锁标志位
};
#endif // CHECKABLETREEWIDGET_H
```

### 2. 核心业务逻辑 (`checkabletreewidget.cpp`)

```cpp
#include "checkabletreewidget.h"
#include "ui_checkabletreewidget.h"

CheckableTreeWidget::CheckableTreeWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CheckableTreeWidget)
{
    ui->setupUi(this);
    this->resize(1000, 500);
    isUpdating = false; // 初始化锁
    init();
    
    // 绑定节点状态改变信号
    connect(ui->treeWidget, &QTreeWidget::itemChanged, this, &CheckableTreeWidget::treeItemChanged);
}

// 初始化节点（以部分为例）
void CheckableTreeWidget::init()
{
    ui->treeWidget->clear();
    
    // 顶层节点 group1
    QTreeWidgetItem *group1 = new QTreeWidgetItem(ui->treeWidget);
    group1->setText(0, "group1");
    group1->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    group1->setCheckState(0, Qt::Unchecked);

    // 子节点 subItem11
    QTreeWidgetItem *subItem11 = new QTreeWidgetItem(group1);
    subItem11->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem11->setText(0, "subItem11");
    subItem11->setCheckState(0, Qt::Unchecked);
    
    // ... 其他节点略 ...
}

// 向上反馈：根据子节点状态更新父节点
void CheckableTreeWidget::updateParentItem(QTreeWidgetItem *item)
{
    QTreeWidgetItem *parent = item->parent();
    if (parent == nullptr) return;

    int selectedCount = 0;
    int childCount = parent->childCount();

    // 统计选中的子节点个数
    for (int i = 0; i < childCount; i++) {
        if (parent->child(i)->checkState(0) == Qt::Checked) {
            selectedCount++;
        }
    }

    // 三态逻辑判断
    if (selectedCount <= 0) {
        parent->setCheckState(0, Qt::Unchecked);
    } else if (selectedCount > 0 && selectedCount < childCount) {
        parent->setCheckState(0, Qt::PartiallyChecked); // 半选状态
    } else if (selectedCount == childCount) {
        parent->setCheckState(0, Qt::Checked);
    }
}

// 核心槽函数：处理节点状态改变
void CheckableTreeWidget::treeItemChanged(QTreeWidgetItem *item, int column)
{
    if (isUpdating) return; // 拦截递归
    isUpdating = true;

    if (Qt::Checked == item->checkState(0)) {
        int count = item->childCount();
        if (count > 0) {
            // 父节点被选中，向下级联全选
            for (int i = 0; i < count; i++) {
                item->child(i)->setCheckState(0, Qt::Checked);
            }
        } else {
            // 叶子节点被选中，向上反馈
            updateParentItem(item);
        }
    } else if (Qt::Unchecked == item->checkState(0)) {
        int count = item->childCount();
        if (count > 0) {
            // 父节点取消，向下级联取消
            for (int i = 0; i < count; i++) {
                item->child(i)->setCheckState(0, Qt::Unchecked);
            }
        } else {
            updateParentItem(item);
        }
    }

    isUpdating = false; // 解锁
}
```

