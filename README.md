# my-learning-notes
记录编程知识点练习代码
# 🚀 我的编程学习之路

欢迎来到我的代码仓库！这里记录了我从零开始学习编程的点点滴滴，主要包含 Qt (C++) 基础、算法练习以及日常代码积累。

## 📁 仓库目录

- **`QT/CalculateArea`**：使用 Qt Designer (UI 拖拽) 实现圆面积计算。
- **`QT/CalculateArea2`**：纯代码手写实现圆面积计算，加深对控件和布局的理解。

---

## 📝 学习笔记与知识点总结

### 📌 Qt 基础学习
1. **字符串与数字的转换**：
   - 使用 `ui->lineEdit->text().toDouble()` 可以将文本转为浮点数。
   - **进阶用法**：`toDouble(&ok)`。传入一个 `bool` 变量的地址，函数内部不仅返回转换后的数字，还会把是否成功的结果偷偷写进 `ok` 所在的内存地址，完美避免非法输入导致程序崩溃。
2. **UI 显示控制**：
   - 使用 `QString::number(变量, 'f', 2)` 可以强制保留计算结果两位小数。
   - 使用 `label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);` 可以让多行文本靠左并在垂直方向居中。
3. **内存泄漏防范**：在 Qt 中创建组件（如 `new QLabel`）时，只要有传入 `this` 作为父对象，或者加入了布局（`QGridLayout`），控件就会自动加入到 Qt 的对象树中，在窗口关闭时自动释放，不需要手动 `delete`。

### 🛡️ 代码严谨性：异常输入拦截（极其重要）
无论是 UI 版本还是纯代码版本，我都加入了完善的“防御性编程”逻辑：
- **空输入拦截**：`if (inputText.isEmpty())`
- **非数字拦截**：利用 `bool ok` 和 `if (!ok)`
- **业务逻辑拦截**：`if (radius < 0)` 拦截不合法的负数半径。

---

## 💻 核心代码展示 (纯代码布局版)

相比 UI 拖拽，纯代码手写界面让我彻底搞懂了控件的层级和布局（QGridLayout）的使用。以下是 `QT/CalculateArea2` 的核心逻辑：

```cpp
#include <QGridLayout>

// 1. 界面初始化（纯代码布局）
Dialog::Dialog(QWidget *parent) : QDialog(parent)
{
    this->setFixedSize(600, 300);
    radiusLabel = new QLabel("半径", this);
    radiusLineEdit = new QLineEdit(this);
    areaLabel = new QLabel("面积", this);
    areaResultLabel = new QLabel(this);
    areaResultLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    countButton = new QPushButton("计算面积", this);
    countButton->setFixedSize(100, 40);

    // 使用表格布局 (行, 列, 跨行, 跨列, 对齐方式)
    QGridLayout *gLayout = new QGridLayout(this);
    gLayout->addWidget(radiusLabel, 0, 0);
    gLayout->addWidget(radiusLineEdit, 0, 1);
    gLayout->addWidget(areaLabel, 1, 0);
    gLayout->addWidget(areaResultLabel, 1, 1);
    gLayout->addWidget(countButton, 2, 0, 1, 2, Qt::AlignCenter); // 按钮跨两列居中

    // 2. 信号与槽连接
    connect(countButton, &QPushButton::clicked, this, &Dialog::showArea);
}

// 3. 核心业务逻辑
void Dialog::showArea()
{
    bool ok;
    QString inputText = radiusLineEdit->text();
    
    if(inputText.isEmpty()){
        areaResultLabel->setText("请输入半径！");
        return;
    }
    
    double result = inputText.toDouble(&ok);
    if(!ok){
        areaResultLabel->setText("请输入有效数字！");
        return;
    }
    
    if(result < 0){
        areaResultLabel->setText("半径不能为负数！");
        return;
    }
    
    const double PI = 3.14;
    double area = result * result * PI;
    areaResultLabel->setText(QString::number(area, 'f', 2));
}
