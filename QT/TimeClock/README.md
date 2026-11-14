# 📌 Qt 小项目实战：数字时钟与日历 (TimeClock)

**📂 项目路径**：`QT/TimeClock`

**🎯 项目背景：**
利用纯代码布局（无 `.ui` 文件）实现一个数字时钟。本项目不仅能够实时刷新系统的日期与时间，还深入练习了 `QTimer` 的事件驱动机制、`QDateTime` 的时间格式化，以及 `QFont` 动态修改字体样式的技巧。

## 🛠️ 核心技术栈拆解

### 1. 获取与格式化时间 (`QDateTime`)

在 Qt 中，处理时间和日期极其方便：

- **获取当前时间**：`QDateTime::currentDateTime()` 获取系统当前的绝对时间和日期。
- **格式化转换**：使用 `.toString()` 函数，将时间对象转化为我们想要的格式字符串：
  - 日期格式：`toString("yyyy-MM-dd")` （`yyyy` 代表四位年份，`MM` 代表月份，`dd` 代表日期）。
  - 时间格式：`toString("HH:mm:ss")`。
    - 🔥 **避坑点**：`HH` 代表 24 小时制，如果是 `hh` 则是 12 小时制。`mm` 是分钟，`ss` 是秒（严格区分大小写）。
- **类型转换**：格式化后的结果依然是 `QString`，可以直接用 `setText()` 赋值给 `QLabel` 进行显示。

### 2. 定时器机制 (`QTimer`)

`QTimer` 是 Qt 中实现周期性任务的神器，它的本质是**事件驱动**，而不是死循环。

- **设置周期**：`timer->setInterval(1000);` 表示周期为 1000 毫秒（即 1 秒）。
- **启动与停止**：使用 `timer->start()` 启动，`timer->stop()` 停止。
- **状态判断**：使用 `timer->isActive()` 判断当前定时器是否正在运行，返回 `bool` 值，常用于按钮的一键启停逻辑。

### 3. 信号与槽的动态交互

- **刷新逻辑**：将 `QTimer` 的 `timeout()` 信号，连接到我们自定义的槽函数 `updateTime()` 上。这样每隔 1 秒钟，`updateTime()` 就会被自动调用一次，从而实现界面的刷新。
- **控制逻辑**：将“开始/停止”按钮的 `clicked()` 信号连接到 `toggleTimer()` 槽函数，在函数内部判断定时器状态，实现启停控制。

### 4. 纯代码界面布局与美化 (`QVBoxLayout` / `QFont`)

- 纯手工创建了 `QLabel` 和 `QPushButton`，使用 `QVBoxLayout` 将日期、时间、按钮从上到下依次排列。
- **UI 优化技巧**：通过 `timeLabel->font()` 获取当前控件的字体对象，修改字号 `setPointSize(30)` 后重新 `setFont()` 赋给控件，并设置居中对齐 `setAlignment(Qt::AlignCenter)`，让时间显示极其醒目。

## 💻 核心代码片段

### 1. 界面初始化与定时器配置

```cpp
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("数字闹钟");
    resize(300, 150);

    // 初始化时间与日期标签，并设置大号字体居中
    timeLabel = new QLabel("00:00:00", this);
    dateLabel = new QLabel("0000-00-00", this);
    
    QFont font = timeLabel->font();
    font.setPointSize(30);
    timeLabel->setFont(font);
    timeLabel->setAlignment(Qt::AlignCenter);
    
    QFont font1 = dateLabel->font();
    font1.setPointSize(30);
    dateLabel->setFont(font1);
    dateLabel->setAlignment(Qt::AlignCenter);

    startBtn = new QPushButton("开始计时", this);

    // 初始化定时器
    timer = new QTimer(this);
    timer->setInterval(1000); // 定时周期为1s

    // 布局设置
    QVBoxLayout *vLayout = new QVBoxLayout(this);
    vLayout->addWidget(dateLabel);
    vLayout->addWidget(timeLabel);
    vLayout->addWidget(startBtn);

    // 信号与槽的连接
    connect(timer, &QTimer::timeout, this, &Dialog::updateTime);
    connect(startBtn, &QPushButton::clicked, this, &Dialog::toggleTimer);

    // 启动时立即刷新一次，防止界面初始显示 "00:00:00"
    updateTime();
}
```

### 2. 核心刷新与启停控制

```cpp
void Dialog::updateTime()
{
    QDateTime current = QDateTime::currentDateTime();
    
    // 格式化输出：HH代表24小时制，yyyy-MM-dd 为年月日
    QString dateStr = current.toString("yyyy-MM-dd");
    QString timeStr = current.toString("HH:mm:ss");
    
    // 显示在标签中
    dateLabel->setText(dateStr);
    timeLabel->setText(timeStr);
}

void Dialog::toggleTimer()
{
    if (timer->isActive()) {
        // 如果正在运行，就停止
        timer->stop();
        startBtn->setText("开始计时");
    } else {
        // 如果停止了就启动
        timer->start();
        startBtn->setText("停止计时");
    }
}
```

## 🚧 实战踩坑与经验总结

1. **时间格式大小写陷阱**：一开始没有区分 `HH` 和 `hh`，导致对 24 小时制理解不深。经过测试发现，只有 `HH` 才是标准的 24 小时制，`hh` 是 12 小时制。
2. **界面死板问题**：最初的 Label 字体太小，且默认靠左。后来通过重新设置 `QFont` 实现了大字号显示，并通过 `setAlignment(Qt::AlignCenter)` 让文字居中，视觉效果瞬间提升。
3. **定时器本质认知**：深刻理解了 `QTimer` 本身不是循环，而是通过发出 `timeout` 信号来触发事件。这种事件驱动的机制，比传统 C 语言里的 `while` 死循环加 `sleep()` 要优雅得多，**绝不会卡死主界面的 UI 线程**。