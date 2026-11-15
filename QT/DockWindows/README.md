# 📌 高级界面组件：QDockWidget (停靠窗口) 深度解析

**📂 项目路径**：`QT/DockWindows`

**🎯 项目背景：**
在开发类似 Photoshop、VS Code 或 Qt Creator 这种大型桌面软件时，往往需要在主界面周围提供大量辅助面板（如文件树、属性栏、工具箱等）。`QDockWidget` 就是 Qt 专门用来实现这种“可停靠、可浮动、可关闭”辅助面板的神器。它必须依附于 `QMainWindow` 存在，不能单独作为主窗口使用。

## 🌍 一、典型使用场景

1. **IDE/代码编辑器（如 VS Code、Qt Creator）**：左侧的“项目文件树”、下方的“编译输出/终端”、右侧的“大纲视图”，全是用 `QDockWidget` 做的。
2. **图形图像软件（如 Photoshop、AutoCAD）**：右侧的“图层”、“颜色”、“历史记录”面板，支持拖拽悬浮，极大地提升了画布空间的利用率。
3. **视频剪辑软件（如 PR、剪映）**：左上角的“效果控件”、右上角的“预览窗口”、左中角的“素材库”，都是可自定义布局的停靠窗口。

## 🛠️ 二、核心知识点与代码拆解

### 1. 主窗口的“灵魂”：中央部件 (`setCentralWidget`)

`QMainWindow` 有四个区域：菜单栏、工具栏、状态栏和中央部件。
在使用停靠窗口之前，必须先用 `setCentralWidget()` 设置一个核心内容。所有的 `QDockWidget` 都是围绕着这个中央区域向四周吸附的。

```cpp
QTextEdit *te = new QTextEdit(this);
te->setText("这是核心编辑区");
setCentralWidget(te); // 设置为主窗口的中央部件
```

### 2. 灵活的特性控制 (`setFeatures`)

面板能干嘛，全凭开发者一句话。通过位运算（`|`）可以随意组合它的权限：

| 特性枚举                             | 说明                                                 |
| ------------------------------------ | ---------------------------------------------------- |
| `QDockWidget::DockWidgetMovable`     | 允许用户在左右停靠区之间拖动。                       |
| `QDockWidget::DockWidgetClosable`    | 面板右上角出现关闭按钮（关掉后可通过菜单重新呼出）。 |
| `QDockWidget::DockWidgetFloatable`   | 允许用户把它“拽”出来，变成一个独立的悬浮小窗口。     |
| `QDockWidget::AllDockWidgetFeatures` | 拥有以上所有特性。                                   |
| `QDockWidget::NoDockWidgetFeatures`  | 禁止所有交互（禁止拖拽、关闭、浮动）。               |

### 3. 限制停靠区域 (`setAllowedAreas`)

如果不加限制，用户可能会把右侧的面板拖到顶部菜单栏下面，导致界面极其难看。

- `Qt::LeftDockWidgetArea`（左侧）
- `Qt::RightDockWidgetArea`（右侧）
- `Qt::TopDockWidgetArea` / `Qt::BottomDockWidgetArea`（上下）
- `Qt::AllDockWidgetAreas`（四面八方均可）

```C++
// 只允许停靠在左侧或右侧
dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
```

### 4. 🔥 空间魔术：标签页堆叠 (`tabifyDockWidget`)

这是极其高级且实用的功能！如果你同时有“属性”、“历史”、“图层”三个面板，全并排显示太占空间。`tabifyDockWidget(窗口1, 窗口2)` 可以把它们叠在一起，变成浏览器标签页的样子，用户点击标签就能切换。

```cpp
tabifyDockWidget(dock2, dock3); 
dock2->raise(); // 核心技巧：默认让 dock2 显示在最前面，否则一启动可能会显示 dock3
```

### 5. 🚀 梦幻联动：停靠状态持久化 (`QSettings`)

和之前学的 `QSplitter` 一样，用户辛苦拖好的面板布局，下次打开软件必须保留。`QMainWindow` 自带 `saveState()` 和 `restoreState()`。

```cpp
// 保存：在软件退出时调用
QByteArray dockState = this->saveState();
// 恢复：在构造函数末尾调用
this->restoreState(dockState);
```

*(结合 `QSettings` 存入本地注册表或 `.ini` 文件，即可实现高端的“记忆功能”。)*

## ⚠️ 三、实战踩坑与经验总结

### 🚨 坑点 1：浮动窗的“孤儿”现象

- **现象**：如果用户把 `QDockWidget` 拖出来变成了悬浮窗，然后直接在悬浮窗上点击 `X` 关闭，这个对象并不会被销毁。如果你把它拖到另一个屏幕上，可能会导致主窗口失去焦点。
- **✅ 解决方案**：在不需要浮动的地方，直接禁用 `Floatable`。如果允许关闭，一定要在连接 `visibilityChanged` 信号时，安全地处理对象状态。

### 🚨 坑点 2：菜单栏与面板的显隐联动

- **现象**：高端软件通常可以在“视图”菜单里勾选是否显示某个面板，但手动去绑定 `QAction` 和 `setVisible` 非常麻烦。
- **✅ 解决方案**：使用 `QDockWidget::toggleViewAction()`。把这个函数返回的 `QAction` 直接加到菜单栏里，它会自动处理对勾（✔）的显示与隐藏状态，不需要写任何多余逻辑。

### 🚨 坑点 3：初始尺寸设置（容易被挤压）

- **现象**：如果中央部件默认尺寸很大，右侧的 `QDockWidget` 往往会被挤压得很小，甚至只显示一条边。
- **✅ 解决方案**：可以使用 `resizeDocks()` 函数来设置初始比例。例如 `resizeDocks({dock1, dock2}, {200, 200}, Qt::Horizontal);`，强行分配宽/高。

## 💻 四、核心代码结构展示

```cpp
// 1. 设置中央部件（必须有，否则面板没地方靠）
QTextEdit *mainArea = new QTextEdit("主画布", this);
setCentralWidget(mainArea);

// 2. 创建面板 1（只允许左右移动）
QDockWidget *dock1 = new QDockWidget("图层", this);
dock1->setFeatures(QDockWidget::DockWidgetMovable);
dock1->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
dock1->setWidget(new QTextEdit("图层内容"));
addDockWidget(Qt::RightDockWidgetArea, dock1);

// 3. 创建面板 2 和 3（做成标签页）
QDockWidget *dock2 = new QDockWidget("历史记录", this);
dock2->setWidget(new QTextEdit("历史内容"));
addDockWidget(Qt::RightDockWidgetArea, dock2);

QDockWidget *dock3 = new QDockWidget("颜色面板", this);
dock3->setWidget(new QTextEdit("颜色内容"));
addDockWidget(Qt::RightDockWidgetArea, dock3);

// 4. 核心操作：将 2 和 3 堆叠，并默认显示 2
tabifyDockWidget(dock2, dock3);
dock2->raise(); 
```

