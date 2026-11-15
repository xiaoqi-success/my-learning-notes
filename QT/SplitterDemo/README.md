# 📌 高级界面布局实战：QSplitter 分割窗口与状态持久化

**📂 项目路径**：`QT/SplitterDemo`

**🎯 项目背景：**
实现了一个类似代码编辑器（如 VS Code）的嵌套分割窗口界面：左侧为固定比例的代码区，右侧为可上下拖拽的预览区。并且实现了**软件关闭时自动保存布局比例，下次启动时自动恢复**的高级功能。

## 🌍 一、典型使用场景

1. **代码编辑器 / IDE**：左侧显示项目目录树，右侧上下分割出代码编辑区和终端输出区。
2. **文件对比工具 (如 Beyond Compare)**：左右两个窗口分别显示两个文件的内容，中间的拖拽条可实时调整两边宽度。
3. **多面板数据看板**：左侧列表显示设备，右侧上方显示设备详情，右侧下方显示实时日志。

## 🛠️ 二、核心知识点深度拆解

### 1. 分割窗口的嵌套 (`QSplitter`)

- **基础用法**：`new QSplitter(Qt::Horizontal, parent)` 可以创建一个水平分割器。
- **嵌套技巧**：把一个 `QSplitter` 作为另一个 `QSplitter` 的子控件，就能实现复杂的“左一右二”或“上一中二”的布局。在项目中，右侧的垂直分割器就是以主水平分割器为父窗口。

### 2. 自适应拉伸因子 (`setStretchFactor`)

- **代码**：`splitterMain->setStretchFactor(1, 1);`
- **作用**：当拉伸整个主窗口时，索引为 1 的控件（右侧）会自动拉宽，而左侧保持原样。如果不设置，左右两边会按比例平分新增空间。

### 3. 折叠权限控制 (`setCollapsible`)

- **代码**：`splitterMain->setCollapsible(0, false);`
- **作用**：防止用户把左侧的核心区域直接拖拽到 0 宽度，避免界面布局被彻底破坏。

### 4. 布局状态的持久化 (`QSettings`) —— 🔥 高光难点

- **保存状态**：`QSplitter::saveState()` 会把当前分割条的位置保存为 `QByteArray`（二进制数据）。
- **恢复状态**：`QSplitter::restoreState()` 可以在软件启动时读取数据并还原比例。
- **配置文件读写**：利用 `QSettings("OrganizationName", "AppName")`，跨平台地将数据写入 Windows 注册表或 Mac 的 plist 文件中。

## ⚠️ 三、实战踩坑与避坑指南

### 🚨 坑点 1：拖拽不实时更新的问题

如果处理的界面非常复杂，拖拽分割条时实时重绘会严重卡顿。

- **✅ 解决方案**：`splitterRight->setOpaqueResize(false);`。这样拖拽时只显示一条灰色的虚线，释放鼠标后才真正改变布局。

### 🚨 坑点 2：Lambda 表达式捕获的“致命坑”（极其重要！）

在程序退出前保存状态时，使用了 `QApplication::aboutToQuit` 信号和 Lambda 表达式：

```cpp
// ❌ 错误示范：会导致退出时崩溃
// QObject::connect(&a, &QApplication::aboutToQuit, [&](){
//    settings.setValue(...); // 此时的 settings 可能已经被析构了
// });

// ✅ 正确示范：在 Lambda 内部重新实例化
QObject::connect(&a, &QApplication::aboutToQuit, [&](){
    QSettings settings("OrganizationName", "SplitterDemo"); 
    settings.setValue("splitterState", splitterMain->saveState());
});
```

**原因**：如果在外部定义了 `QSettings settings;`，当主窗口关闭时，栈上的 `settings` 可能已经被销毁。如果 Lambda 捕获了它的引用 `[&]`，在程序退出的瞬间再去调用它，就会导致**野指针崩溃**。在 Lambda 内部局部新建对象是最安全的做法。

## 💻 四、核心代码结构展示

```cpp
// 1. 创建主水平分割器
QSplitter *splitterMain = new QSplitter(Qt::Horizontal, 0);

// 2. 创建右侧垂直分割器，并作为主分割器的子控件
QSplitter *splitterRight = new QSplitter(Qt::Vertical, splitterMain);
splitterRight->setOpaqueResize(false); // 关闭实时更新，防卡顿

// 3. 填充控件
QTextEdit *textLeft = new QTextEdit("Left", splitterMain);
QTextEdit *textUp = new QTextEdit("Top", splitterRight);
QTextEdit *textBottom = new QTextEdit("Bottom", splitterRight);

// 4. 高级属性设置
splitterMain->setStretchFactor(1, 1); // 右侧自适应拉伸
splitterMain->setCollapsible(0, false); // 左侧不可折叠
splitterMain->setHandleWidth(5); // 分割条宽度

// 5. 状态恢复与保存 (QSettings)
QSettings settings("Org", "App");
QByteArray state = settings.value("splitterState").toByteArray();
if(!state.isEmpty()){
    splitterMain->restoreState(state);
} else {
    splitterMain->setSizes(QList<int>() << 100 << 400); // 初始比例 1:4
}

// 退出时自动保存状态 (Lambda内重新实例化QSettings)
QObject::connect(&a, &QApplication::aboutToQuit, [&](){
    QSettings localSettings("Org", "App");
    localSettings.setValue("splitterState", splitterMain->saveState());
});
```

