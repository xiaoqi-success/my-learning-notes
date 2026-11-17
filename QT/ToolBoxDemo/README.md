# 📌 高级容器组件：QToolBox 折叠抽屉与 QToolButton 实战

**📂 项目路径**：`QT/ToolBoxDemo`

**🎯 项目背景：**
在开发通讯软件或后台管理系统时，经常需要将大量功能或联系人按类别折叠展示，以节省屏幕空间。`QToolBox` 提供了一个“列状层叠窗体”容器，结合 `QToolButton`，可以极其轻松地实现类似 QQ 好友列表（我的好友、陌生人、黑名单）的折叠抽屉效果。

## 🌍 一、典型使用场景

1. **通讯软件联系人列表**：如 QQ、微信电脑版的左侧好友分组，点击组名可展开/折叠。
2. **各类工具的属性面板**：如 Photoshop 右侧的折叠菜单，将“颜色”、“图层”、“历史”分门别类折叠起来。
3. **大型设置面板**：把繁杂的设置项按“基础设置”、“网络设置”、“高级设置”折叠，让用户不至于眼花缭乱。

## 🛠️ 二、核心技术栈拆解

### 1. 折叠抽屉容器 (`QToolBox`)

- **本质**：一个垂直排列的“卡片盒”。
- **使用**：通过 `addItem(QWidget *page, const QString &title)` 方法，将一个包含多个控件的页面（通常是一个 `QWidget` 容器）和一个分类标题加入其中。点击标题即可展开或折叠该页面。

### 2. 工具按钮 (`QToolButton`)

- **本质**：专为工具栏、工具箱设计的按钮，比普通 `QPushButton` 更轻量，且支持图标与文本的丰富排版。
- **文本与图标排版**：通过 `setToolButtonStyle` 设置：
  - `Qt::ToolButtonIconOnly`：只显示图标。
  - `Qt::ToolButtonTextBesideIcon`：文字在图标旁边（本案例使用）。
  - `Qt::ToolButtonTextUnderIcon`：文字在图标下方。
- **悬停反馈**：`btn->setAutoRaise(true);` 让按钮在鼠标移开时呈现扁平化，移入时才有凸起效果，视觉体验极佳。

### 3. DRY 原则与代码封装（高光点）

- **痛点**：如果不封装，手写 QQ 列表需要几十个 `QToolButton *btn1_1`、`btn2_1`...，代码极其臃肿且难以维护。
- **✅ 你的亮点**：提取了 `createDrawerPage(const QString &title, const QStringList &names, const QStringList &iconPaths)` 函数，通过遍历 `QStringList` 批量生成按钮。只需三行代码，即可生成整个抽屉，完美符合 **DRY (Don't Repeat Yourself)** 原则。

### 4. 指针隐式转换与父对象管理

- 将 `QWidget *page` 加入 `QToolBox` 时，直接调用 `this->addItem(page, title)` 即可。`MyQQExample*` 隐式转换为 `QToolBox*`，无需生硬的 `(QWidget*)` C 风格强转。

## ⚠️ 三、实战避坑与优化建议

### 🚨 坑点 1：`setMargin` 的废弃警告

- Qt 5.15 以后，`layout->setMargin(10)` 已被废弃，编译会报 Warning。
- **✅ 解决方案**：改用 `layout->setContentsMargins(10, 10, 10, 10);` （左、上、右、下）。

### 🚨 坑点 2：图标加载失败的闪退

- 如果图标路径写错或图片损坏，直接 `btn->setIcon(QIcon(pix))` 可能会导致按钮显示异常或程序崩溃。
- **✅ 解决方案**：提前使用 `if (!pix.isNull())` 拦截，保证程序健壮性。

### 🚨 坑点 3：按钮全部挤在中部或底部

- 如果你的抽屉页面里只有几个按钮，它们可能会被平均分配在页面的各个位置。
- **✅ 解决方案**：在布局末尾加入 `layout->addStretch();`，利用弹簧把所有的按钮全部顶到上方

## 💻 四、核心代码实现

### 1. 头文件声明 (`myqqexample.h`)

```cpp
#ifndef MYQQEXAMPLE_H
#define MYQQEXAMPLE_H

#include <QToolBox>
#include <QToolButton>
#include <QStringList>

class MyQQExample : public QToolBox
{
    Q_OBJECT

public:
    MyQQExample(QWidget *parent = nullptr);
    ~MyQQExample();

private:
    // 提取通用方法：避免创建几十个按钮变量的“代码噩梦”
    void createDrawerPage(const QString &title,
                          const QStringList &names,
                          const QStringList &iconPaths);
};
#endif // MYQQEXAMPLE_H
```

### 2. 核心逻辑 (`myqqexample.cpp`)

```cpp
#include "myqqexample.h"
#include <QVBoxLayout>
#include <QIcon>
#include <QPixmap>

MyQQExample::MyQQExample(QWidget *parent) : QToolBox(parent)
{
    setWindowTitle("MY QQ");

    // 准备数据
    QStringList friendNames = {"张三", "李四", "王五"};
    QStringList friendIcons = {":/icons/zhangsan.png", ":/icons/lisi.png", ":/icons/wangwu.png"};
    QStringList strangerNames = {"小王"};
    QStringList strangerIcons = {":/icons/moshengren.jpg"};

    // 调用封装好的通用方法，三行代码创建三个抽屉
    createDrawerPage(tr("我的好友"), friendNames, friendIcons);
    createDrawerPage(tr("陌生人"), strangerNames, strangerIcons);
}

MyQQExample::~MyQQExample() {}

void MyQQExample::createDrawerPage(const QString &title, const QStringList &names, const QStringList &iconPaths)
{
    // 1. 创建抽屉容器和垂直布局
    QWidget *page = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(page);
    layout->setContentsMargins(10, 10, 10, 10); // 现代写法
    layout->setAlignment(Qt::AlignHCenter);     // 按钮居中

    // 2. 循环批量生成工具按钮
    for(int i = 0; i < names.size(); i++){
        QToolButton *btn = new QToolButton(page);
        btn->setText(names.at(i));

        // 加载图标（防空判断）
        QPixmap pix(iconPaths.at(i));
        if(!pix.isNull()){
            btn->setIcon(QIcon(pix));
            btn->setIconSize(pix.size());
        }

        btn->setAutoRaise(true); // 悬浮凸起效果
        btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon); // 文字在图标旁边

        layout->addWidget(btn);
    }

    // 3. 加弹簧把按钮顶上去
    layout->addStretch();

    // 4. 组装到 QToolBox
    this->addItem(page, title);
}
```

