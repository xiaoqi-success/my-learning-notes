# 📌 Qt 基础实战：圆面积计算 (UI 拖拽版)

**📂 项目路径**：`QT/CalculateArea`

**🎯 项目背景：**
这是一个基于 Qt Designer (UI 拖拽) 的经典入门项目。通过输入半径计算圆面积，重点练习了如何通过 `ui` 指针访问界面控件、字符串与浮点数的安全转换，以及**“防御性编程”**思想（防止用户输入非法字符导致程序崩溃）

### 1. 字符串与数字的安全转换 (`QString::toDouble`)

在处理用户输入时，绝不能假设用户会乖乖输入数字。

- **常规用法**：`ui->lineEdit->text().toDouble()`。但如果用户输入 "abc"，它会默默返回 `0.0`，导致计算结果错误。
- **🔥 进阶用法**：`toDouble(&ok)`。
  - 传入一个 `bool` 变量的地址。
  - 函数内部不仅返回转换后的数字，还会把是否成功的结果“偷偷”写进 `ok` 所在的内存地址。
  - 完美避免非法输入，通过 `if(!ok)` 精准拦截。

### 2. UI 显示控制 (`QString::number` / `setAlignment`)

- **保留小数**：使用 `QString::number(变量, 'f', 2)` 可以强制保留计算结果两位小数。
- **对齐方式**：使用 `label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);` 可以让多行文本靠左并在垂直方向居中。

### 3. 内存泄漏防范 (Qt 对象树)

- 在 Qt 中创建组件（如 `new QLabel`）时，只要有传入 `this` 作为父对象，或者加入了布局（`QGridLayout`），控件就会自动加入到 Qt 的对象树中。
- 窗口关闭时，父对象会自动释放所有子对象，**不需要手动 `delete`**。

## 💻 核心代码实现

### 1. 头文件声明 (`dialog.h`)

基于 UI 文件的类，不需要手动声明控件，只需要声明 UI 指针和槽函数即可。

```cpp
#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_countButton_clicked(); // 自动关联的槽函数

private:
    Ui::Dialog *ui; // 核心：UI 指针
};
#endif // DIALOG_H
```

### 2. 核心业务逻辑 (`dialog.cpp`)

这里展示了**“防御性编程”**的极佳案例。

```cpp
#include "dialog.h"
#include "ui_dialog.h"

// 输入半径计算圆的面积

const static double PI = 3.14;

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}


//void Dialog::on_countButton_clicked()
//{
//    double radius = ui->radiusLineEdit->text().toDouble();
//    double area = radius * radius * PI;
//    ui->areaLabel_2->setText(QString::number(area,'f',2));
//}

// 更严谨点的版本：防止输入非法的字符
void Dialog::on_countButton_clicked()
{
    // 获取输入文本
    QString inputText = ui->radiusLineEdit->text();
    // 判断是否为空
    if(inputText.isEmpty()){
        ui->areaLabel_2->setText("请输入半径！");
        return;
    }
    bool ok;
    // 使用ok来判断转换是否成功
    // 此函数在内部的转换
    // 如果文字是 "2.5"，转换成功，函数不仅返回 2.5 给 radius，还会偷偷跑到那个内存地址，把 ok 改成 true
    // 如果文字是 "abc"，转换失败，函数返回 0.0 给 radius，同时把 ok 改成 false
    double radius = inputText.toDouble(&ok);
    // 如果用户输入了字母等非数字字符
    if(!ok){
        ui->areaLabel_2->setText("请输入有效的数字！");
        return;
    }
    // 新增：负数不能作为半径
    if(radius < 0){
        ui->areaLabel_2->setText("半径不能为负数！");
        return;
    }
    double area = radius * radius * PI;
    ui->areaLabel_2->setText(QString::number(area,'f',2));
}
```

## 🚧 实战踩坑与经验总结

- **❌ 错误认知**：认为 `toDouble()` 遇到非数字会报错。实际上它默默返回 `0`，导致无法区分用户是输入了 "0" 还是输入了 "abc"。
- **✅ 正确做法**：必须引入 `bool ok` 指针来接收转换状态，并配合 `if (!ok)` 进行拦截。
- **🛡️ 体验优化**：不要把所有的错误都弹出一个 `QMessageBox`，对于这种简单的输入，直接把提示信息显示在界面上的 `QLabel` 里，用户体验更流畅。