# 📌 界面导航神器：QStackedWidget (堆栈窗体) 实战

**📂 项目路径**：`QT/StackedWidget`

**🎯 项目背景：**
在开发复杂的桌面软件时，经常需要实现“左侧点击菜单，右侧切换不同内容页”的功能。`QStackedWidget` 就是专门为此而生的控件，它像一个**固定位置的多页面容器**，同一时间只显示一页，像一摞卡片，翻到哪张显示哪张。

## 🌍 一、典型使用场景

1. **手机设置界面**：点“WiFi”进 WiFi 页，点“蓝牙”进蓝牙页，返回又回列表——底层就是堆栈窗体在切换。
2. **安装向导**：下一步 / 上一步，每步一个页面，共用同一个窗口框架。
3. **QQ/微信电脑版左侧导航**：点“聊天”显示聊天列表，点“联系人”显示联系人，右侧区域不变，只换内容。
4. **Photoshop 右侧面板**：图层/颜色/历史记录，点标签切换，同一块区域只显示一个。

> 💡 **与 QDockWidget 的本质区别**：
>
> - `QDockWidget` = 可以拖来拖去的附属面板（能浮动、能停靠）。
> - `QStackedWidget` = **固定位置的多页面容器（不能拖，只能切）**。

## 🛠️ 二、核心知识点拆解

### 1. 添加页面 (`addWidget`)

- 使用 `stack->addWidget(pageWidget)` 将多个页面（如 `QLabel` 或自定义的 `QWidget`）依次压入栈中。
- 它们会按插入顺序分配索引（0, 1, 2...）。

### 2. 信号槽完美联动（最优雅的操作）

- 不需要写 `if-else` 判断。左侧列表的 `currentRowChanged(int)` 信号，可以直接连接到右侧堆叠窗口的 `setCurrentIndex(int)` 槽函数。
- **代码**：`connect(list, &QListWidget::currentRowChanged, stack, &QStackedWidget::setCurrentIndex);`
- **原理**：当列表中选中行的索引变化时，发出的整数直接作为 `QStackedWidget` 要切换的页面索引，实现完美同步。

### 3. 初始化默认页 (`setCurrentRow`)

- 在构造函数末尾调用 `list->setCurrentRow(1)`。
- 这不仅能让列表默认选中第二项，还会**自动触发一次 `currentRowChanged` 信号**，让右侧也同步显示第二页。

### 4. 布局比例分配 (`setStretchFactor`)

- 在水平布局中，使用 `setStretchFactor(list, 1)` 和 `setStretchFactor(stack, 3)`，让左侧导航栏和右侧内容区实现 1:3 的宽度比例，拉伸窗口时也能完美保持比例。

## 💻 三、核心代码实现

### 1. 头文件声明 (`stackedwidget.h`)

```Cpp
#ifndef STACKEDWIDGET_H
#define STACKEDWIDGET_H

#include <QDialog>
#include <QListWidget>
#include <QStackedWidget>
#include <QLabel>

class StackedWidget : public QDialog
{
    Q_OBJECT

public:
    StackedWidget(QWidget *parent = nullptr);
    ~StackedWidget();

private:
    QListWidget *list;      // 左侧导航列表
    QStackedWidget *stack;  // 右侧堆叠容器
    QLabel *label1;         // 页面 1
    QLabel *label2;         // 页面 2
    QLabel *label3;         // 页面 3
};
#endif // STACKEDWIDGET_H
```

### 2. 核心逻辑 (`stackedwidget.cpp`)

```cpp
#include "stackedwidget.h"
#include <QHBoxLayout>

StackedWidget::StackedWidget(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("StackedWidget"));

    // 1. 创建左侧导航列表
    list = new QListWidget(this);
    list->insertItem(0, tr("Window1"));
    list->insertItem(1, tr("Window2"));
    list->insertItem(2, tr("Window3"));

    // 2. 创建右侧三个页面
    label1 = new QLabel(tr("WindowTest1"));
    label2 = new QLabel(tr("WindowTest2"));
    label3 = new QLabel(tr("WindowTest3"));

    // 3. 创建堆叠容器并压入页面
    stack = new QStackedWidget(this);
    stack->addWidget(label1);
    stack->addWidget(label2);
    stack->addWidget(label3);

    // 4. 布局设置与比例分配 (左侧占 1 份，右侧占 3 份)
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(5, 5, 5, 5);
    mainLayout->addWidget(list);
    mainLayout->addWidget(stack, 0, Qt::AlignHCenter);
    mainLayout->setStretchFactor(list, 1);
    mainLayout->setStretchFactor(stack, 3);

    // 5. 核心联动：列表行号变化自动切换堆栈页面
    connect(list, &QListWidget::currentRowChanged, stack, &QStackedWidget::setCurrentIndex);

    // 6. 默认选中第二行（自动触发信号，右侧同步显示第二页）
    list->setCurrentRow(1);
}

StackedWidget::~StackedWidget()
{
}
```

**万能联动公式**：

```cpp
connect(左侧列表, &QListWidget::currentRowChanged, 右侧堆栈, &QStackedWidget::setCurrentIndex);
```

