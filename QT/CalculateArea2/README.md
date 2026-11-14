# 📌 Qt 基础进阶：纯代码布局版圆面积计算

**📂 项目路径**：`QT/CalculateArea2`

**🎯 项目背景：**
不依赖 Qt Designer (UI 文件)，完全通过 C++ 代码手写实现圆面积计算器。本项目彻底搞懂了控件的层级、`QGridLayout` 网格布局的强大之处，并深入实践了信号与槽（Signals & Slots）的底层运行机制。

## 🛠️ 核心技术栈拆解

### 1. 纯代码界面布局 (`QGridLayout`)

不使用 `.ui` 文件，完全靠代码将控件“拼”起来。`QGridLayout` 是最强大的布局之一：

- **核心 API**：`gLayout->addWidget(控件指针, 行号, 列号, 跨行数, 跨列数, 对齐方式)`。
- **实战技巧**：比如 `gLayout->addWidget(countButton, 2, 0, 1, 2, Qt::AlignCenter);`，表示将按钮放在视觉上第 3 行、第 1 列开始，占 1 行 2 列，单元格内居中

### 2. 信号与槽 (Signals & Slots) —— 核心通信机制

信号与槽是 Qt 实现对象间通信的绝对核心机制。

- **信号 (Signal)**：某个特定情况或动作发生时被触发（比如按钮被点击 `clicked()`）。
- **槽 (Slot)**：等同于接收并处理信号的函数（比如计算面积 `showArea()`）。

#### 📕连接方式

- **一对一**：`connect(发送者, SIGNAL(信号), 接收者, SLOT(槽))`
- **一对多**：一个信号可以连接多个槽，触发时依次执行。
- **多对一**：多个不同的信号可以连接同一个槽。
- **信号连信号**：一个信号触发另一个信号的发送。

#### 💡 新旧语法的区别（极其重要）

- **❌ 旧写法（宏定义）**：`connect(button, SIGNAL(clicked()), this, SLOT(showArea()));`
  - 缺点：编译时查不出错，只有在运行时才会报错（字符串匹配）。
- **✅ 新写法（C++11 函数指针）**：`connect(countButton, &QPushButton::clicked, this, &Dialog::showArea);`
  - 优点：编译期就能进行严格的类型检查，是当前标准写法。

#### ⚖️ 信号与槽的优缺点

- **优点**：
  - **类型安全**：参数类型和个数必须匹配。
  - **松散耦合**：发送者不知道接收者是谁，即使接收者在运行时被 `delete` 了，程序也不会崩溃。
- **缺点**：
  - **性能损耗**：比直接调用函数慢约 10 倍（需要定位对象、遍历关联）。但在现代 GUI 程序中，这种损耗完全可以忽略不计。

### 3. 元对象系统 (Meta-Object System)

Qt 能在标准 C++ 基础上实现信号与槽，全靠它独有的“元对象系统”。它基于三个事实：

1. **基类 `QObject`**：任何想使用信号槽的类，必须直接或间接继承自 `QObject`（`QDialog` 继承自 `QWidget`，最终继承自 `QObject`）。
2. **`Q_OBJECT` 宏**：必须写在类的 `private` 声明区开头。它就像一个开关，启动了元对象特性。
3. **`moc` 编译器**：Qt 独有的元对象编译器，它在编译前预处理带有 `Q_OBJECT` 的头文件，自动生成底层的 C++ 代码。

## 💻 核心代码实现

### 1. 头文件声明 (`dialog.h`)

注意，因为没有 UI 文件，所有的控件都必须手动 `new` 出来，并在头文件中声明为成员变量。

```Cpp
#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class Dialog : public QDialog
{
    Q_OBJECT // 核心宏：启用元对象特性

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    QLabel *radiusLabel;       // 半径标签
    QLineEdit *radiusLineEdit; // 半径输入框
    QLabel *areaLabel;         // 面积标签
    QLabel *areaResultLabel;   // 面积结果展示
    QPushButton *countButton;  // 计算按钮

private slots:
    void showArea(); // 自定义槽函数
};
#endif // DIALOG_H
```

### 2. 核心业务逻辑 (`dialog.cpp`)

```cpp
#include "dialog.h"
#include <QGridLayout>

const static double PI = 3.14;

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    this->setFixedSize(600, 300);

    // 1. 界面初始化（纯代码 new 控件）
    radiusLabel = new QLabel("半径", this);
    radiusLineEdit = new QLineEdit(this);
    areaLabel = new QLabel("面积", this);
    
    areaResultLabel = new QLabel(this);
    // 结果文字靠左，但在垂直方向上居中
    areaResultLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    
    countButton = new QPushButton("计算面积", this);
    countButton->setFixedSize(100, 40);

    // 2. 使用网格布局
    QGridLayout *gLayout = new QGridLayout(this);
    gLayout->addWidget(radiusLabel, 0, 0);
    gLayout->addWidget(radiusLineEdit, 0, 1);
    gLayout->addWidget(areaLabel, 1, 0);
    gLayout->addWidget(areaResultLabel, 1, 1);
    // 按钮横跨两列(1行2列)，放在第3行，居中对齐
    gLayout->addWidget(countButton, 2, 0, 1, 2, Qt::AlignCenter);

    // 3. 信号与槽连接（新式写法）
    connect(countButton, &QPushButton::clicked, this, &Dialog::showArea);
}

Dialog::~Dialog()
{
}

// 4. 核心业务逻辑（防御性编程）
void Dialog::showArea()
{
    bool ok;
    QString inputText = radiusLineEdit->text();
    
    // 空输入拦截
    if(inputText.isEmpty()){
        areaResultLabel->setText("请输入半径！");
        return;
    }
    
    // 非数字拦截
    double result = inputText.toDouble(&ok);
    if(!ok){
        areaResultLabel->setText("请输入有效数字！");
        return;
    }
    
    // 负数拦截
    if(result < 0){
        areaResultLabel->setText("半径不能为负数！");
        return;
    }
    
    // 安全计算与展示（保留两位小数）
    double area = result * result * PI;
    areaResultLabel->setText(QString::number(area, 'f', 2));
}
```

