# 🚀 我的编程学习之路

欢迎来到我的代码仓库！这里记录了我从零开始学习编程的点点滴滴，主要包含 Qt (C++) 基础、算法练习以及日常代码积累。

## 📁 仓库目录

- **`QT/CalculateArea`**：使用 Qt Designer (UI 拖拽) 实现圆面积计算
- **`QT/CalculateArea2`**：纯代码手写实现圆面积计算，加深对控件和布局的理解
- **`QT/QStringPracticeQString`**： QString类常用 API 实操
- **`QT/ContainerPractice`** ：实操了容器类的核心知识点

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

#### 🛡️ 代码严谨性：异常输入拦截（极其重要）
无论是 UI 版本还是纯代码版本，我都加入了完善的“防御性编程”逻辑：
- **空输入拦截**：`if (inputText.isEmpty())`
- **非数字拦截**：利用 `bool ok` 和 `if (!ok)`
- **业务逻辑拦截**：`if (radius < 0)` 拦截不合法的负数半径。

---

#### 💻 核心代码展示 (纯代码布局版)

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

```

### 📌 Qt 进阶核心：信号与槽 (Signals & Slots)

信号与槽是 Qt 实现对象间通信的绝对核心机制。

- **信号 (Signal)**：某个特定情况或动作发生时被触发（比如按钮被点击 `clicked()`）。
- **槽 (Slot)**：等同于接收并处理信号的函数（比如计算面积 `showArea()`）。

#### 1. 连接方式
- **一对一**：`connect(发送者, SIGNAL(信号), 接收者, SLOT(槽))`
- **一对多**：一个信号可以连接多个槽，触发时依次执行。
- **多对一**：多个不同的信号可以连接同一个槽。
- **信号连信号**：一个信号触发另一个信号的发送。

#### 2. 新旧语法的区别（重点！）
- **旧写法（C语言风格字符串）**：`connect(button, SIGNAL(clicked()), this, SLOT(showArea()));` 这种写法编译时查不出错，运行时才会报错。
- **新写法（C++11 函数指针）**：`connect(button, &QPushButton::clicked, this, &Dialog::showArea);` 这种写法编译期就能检查类型，推荐使用。
- *(补充：旧写法底层是用宏把函数名转成了字符串，所以没有类型安全检查。)*

#### 3. 信号与槽的优缺点
- **优点**：
  - **类型安全**：参数类型和个数必须匹配（槽的参数可以比信号少，但必须忽略最后几个参数）。
  - **松散耦合**：发送者不知道接收者是谁，即使接收者在运行时被 `delete` 了，程序也不会崩溃。
- **缺点**：
  - **性能损耗**：比直接调用函数慢约 10 倍。因为需要定位对象、遍历关联、编组参数等。但对于现代 GUI 程序，这点损耗完全可以忽略。
  - 必须继承自 `QObject` 类，且**不支持模板**。

---

### 📌 Qt 元对象系统 (Meta-Object System)

Qt 能在 C++ 基础上实现信号与槽，全靠它独有的“元对象系统”（这是对标准 C++ 的扩展）。它基于三个事实：

1.  **基类 `QObject`**：任何想使用信号槽的类，必须直接或间接继承自 `QObject`。
2.  **`Q_OBJECT` 宏**：必须写在类的 `private` 声明区。它就像个开关，启动了元对象特性。
3.  **`moc` 编译器**：Qt 独有的元对象编译器（Meta-Object Compiler），它会预处理带有 `Q_OBJECT` 的头文件，生成底层的 C++ 代码。

---

### 📌 界面布局管理：QGridLayout

比起手动设定控件的绝对坐标（x, y），使用布局管理器能让界面自适应缩放。今天重点练习了网格布局（`QGridLayout`）：

```cpp
// 创建网格布局对象，并指定父窗口 this
QGridLayout *mainLayout = new QGridLayout(this);

// 添加控件：控件指针, 行号, 列号, 跨行数, 跨列数
mainLayout->addWidget(label1, 0, 0); 
mainLayout->addWidget(lineEdit, 0, 1);
mainLayout->addWidget(label2, 1, 0);
mainLayout->addWidget(button, 1, 1);

// 如果不指定父窗口，最后需要把布局设置给窗口
// setLayout(mainLayout);
```

### 📌 QString 常用 API 实操总结

今天我通过一个完整的 `QString` 测试 Demo，系统验证了其强大的字符串处理能力。重点掌握了以下高频操作：

1. **拼接与格式化**：
   - 强烈推荐 `QString("%1,%2").arg(a).arg(b)`。它比 `+` 号拼接性能更好，且支持强大的占位符替换。
   - `arg(123, 5, 10, QChar('0'))` 这种高级用法可以轻松实现数字补零（输出 `00123`）。
2. **查找与截取**：`indexOf()` 找位置，`left()`、`right()`、`mid()` 随心切分，`section()` 按规则分段。
3. **切割与合并**：`split()` 配合 `QStringList` 可以把逗号分隔的数据拆开，再用 `join()` 拼回来。
4. **空白处理**：`trimmed()` 去除首尾空格，`simplified()` 去除首尾并将中间连续空格压缩为单个，绝对是处理用户表单输入的神器。
5. **数字互转**：`QString::number()` 与 `toInt(&ok)` 结合，通过 `bool` 变量精准拦截非法转换。

### 📌 Qt 容器类与迭代器核心总结

今天通过 `QT/ContainerPractice` 实操了容器类的核心知识点：

1. **QList 基础**：最常用的列表，支持 `<<` 插入、`at()` 安全访问、`indexOf()` 查找。
2. **迭代器三剑客（重点）**：
   - `QListIterator`：Java 风格只读迭代器，用 `hasNext()` 和 `next()`。
   - `QMutableListIterator`：Java 风格读写迭代器，可以在遍历时用 `remove()` 删除或用 `setValue()` 修改元素。
   - `QList<int>::const_iterator`：STL 风格迭代器，像指针一样用 `++` 和 `*`，效率最高，最贴近原生 C++。
3. **QMap vs QHash**：
   - `QMap` 底层是红黑树，自动按 Key 升序排序。
   - `QHash` 底层是哈希表，完全无序，但查找速度极快。
   - *实操发现*：打印 QMap 时是有序的，而打印 QHash 时顺序是随机的。
