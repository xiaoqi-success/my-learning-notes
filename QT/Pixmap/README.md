# 📌图像处理与显示核心：QPixmap 深度实战指南

**📂 项目路径**：`QT/Pixmap`

**🎯 项目背景：**
`QPixmap` 是 Qt 中用于在界面上显示图片的专属类，底层与操作系统的窗口绘图系统深度绑定。本项目系统整理了 `QPixmap` 的核心特性、高频 API（加载、缩放、离屏绘图、保存），并深度对比了它与 `QImage` 在多线程环境下的区别。这是开发相册、绘图板、截图工具的必修课。

## 🌍 一、典型使用场景

1. **UI 界面美化**：给按钮、标签设置图标，或者为窗口设置背景图。
2. **绘图工具/画板**：作为离屏画布（Off-screen Canvas），先用 `QPainter` 画好，再一次性贴到界面上显示。
3. **相册/看图软件**：加载本地图片并按比例缩放显示。

## 🛠️ 二、核心特性与 API 拆解

### 1. 必须背诵的核心特性

1. 平台相关：在 Windows/X11/macOS 底层是原生绘图表面，**适合显示、QPainter 绘图**
2. ❗ 线程限制：**不能在子线程创建、修改 QPixmap**；子线程处理图片优先用 QImage，主线程再 fromImage 转 QPixmap
3. 不适合像素运算：读写像素很慢，像素处理交给 QImage
4. 支持格式：png、jpg、bmp、ppm、xbm、xpm；gif 只支持静态图（动画 gif 用 QMovie）
5. 空图判断：`pix.isNull()`，加载失败返回 true，排查图片路径首选

### 2. 高频 API 速查

| 操作                                                         | 代码示例                                                     |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| **从Qt资源文件加载（:/ 开头，qrc资源）**                     | `QPixmap pix(":/res/logo.png");`                             |
| **从本地绝对路径加载**                                       | `QPixmap pix("/home/xxx/test.png");`                         |
| **从 QImage 转换（跨线程安全方案）**                         | `QImage img("test.jpg");      QPixmap pix = QPixmap::fromImage(img);` |
| **构造空白pixmap（指定宽高）**                               | `QPixmap pix(400, 300); pix.fill(Qt::white);// 填充底色`     |
| **缩放（KeepAspectRatio 保持比例；KeepAspectRatioByExpanding铺满）** | `QPixmap scaledPix = pix.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation);`注意：scaled 返回新 QPixmap，**原 pix 不会变** |
| **截取一部分图片**                                           | `pix.copy(x, y, w, h);`                                      |
| **保存图片**（保存到文件，第二个参数是格式 "png" "jpg"）     | `pix.save("out.png", "png");`                                |

### 3. 离屏绘图 (`QPainter` 在 `QPixmap` 上绘图)

QPixmap 可以作为画布，先画好再贴到界面，很常用

```cpp
QPixmap pix(400, 300);
pix.fill(Qt::white); // 必须有底色，否则默认是黑色

QPainter painter(&pix);
painter.setPen(QPen(Qt::blue, 2));
painter.drawEllipse(50, 50, 100, 100);
painter.drawText(100, 200, "QPixmap 离屏绘图");
painter.end(); // 必须调用 end，释放绘图资源
```

## ⚔️ 三、面试高频：QPixmap vs QImage

| 特性         | `QPixmap`          | `QImage`                       |
| ------------ | ------------------ | ------------------------------ |
| **使用线程** | 仅限 UI 主线程     | 任意线程                       |
| **核心用途** | 界面显示、离屏绘图 | 图像处理、像素读写、子线程加载 |
| **读写像素** | 慢                 | 快                             |
| **平台依赖** | 与窗口系统绑定     | 独立于平台，适合算法处理       |

**✅ 标准多线程处理流程**：**子线程加载 + 处理 QImage → 信号发给主线程 → fromImage 转 QPixmap 展示**

## ⚠️ 四、实战避坑清单（重点！）

### 🚨 坑点 1：子线程直接 new QPixmap/load

- **现象**：程序崩溃或界面花屏。
- **✅ 解决方案**：严格遵守线程限制，子线程用 `QImage`，主线程再转 `QPixmap`。

### 🚨 坑点 2：混淆 `scaled` 与 `setScaledContents`

- **现象**：图片被暴力拉伸，比例严重变形。
- **✅ 解决方案**：`label->setScaledContents(true)` 会强制拉伸填满 Label。若要等比例缩放，应该关闭它，并用 `pix.scaled(label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation)`。

### 🚨 坑点 3：资源路径写错

- **现象**：图片死活加载不出来。
- **✅ 解决方案**：Qt 资源文件路径是 `:/`（冒号斜杠），**千万不要写成 `://`**。务必用 `pix.isNull()` 判断是否加载成功。

### 🚨 坑点 4：用 QPixmap 做算法处理

- **现象**：做灰度、二值化处理时卡顿严重。
- **✅ 解决方案**：`QPixmap` 的像素读写极慢，算法处理（如遍历像素）必须换成 `QImage`。
- QPixmap::fromImage 大图片转换耗时，主线程会卡，图片预处理放子线程 QImage