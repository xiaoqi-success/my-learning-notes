# 📌 Qt 核心进阶：字符串与容器类实战 (QString / QList / QMap / QHash)

**📂 项目路径**：`QT/ContainerPractice`

**🎯 项目背景：**
在 C++ 原生标准库（STL）之外，Qt 提供了一套更轻量、更安全且跨平台一致的容器类和字符串类。本项目通过控制台程序，系统实操了 `QString` 的高频 API，以及 `QList`、`QMap`、`QHash` 的底层逻辑与迭代器用法。

## 🌍 一、典型使用场景

1. **QString**：处理所有用户输入、文件路径读取、UI 文本显示、网络数据解析。
2. **QList**：存储同类型的批量数据（如查询数据库返回的多个用户信息、下拉框的选项列表）。
3. **QMap / QHash**：存储键值对（如配置文件的键值映射、词典数据、学生姓名与成绩的对应关系）。

## 🛠️ 二、核心知识点拆解

### 1. 字符串处理 (`QString`)

- **拼接与格式化**：强烈推荐 `QString("%1,%2").arg(a).arg(b)`。它比 `+` 号拼接性能更好，且支持占位符替换。`arg(123, 5, 10, QChar('0'))` 这种高级用法可以轻松实现数字补零（输出 `00123`）。
- **查找与截取**：`indexOf()` 找位置，`left()`、`right()`、`mid()` 随心切分，`section()` 按规则分段。
- **切割与合并**：`split()` 配合 `QStringList` 可以把逗号分隔的数据拆开，再用 `join()` 拼回来。
- **空白处理**：`trimmed()` 去除首尾空格，`simplified()` 去除首尾并将中间连续空格压缩为单个，绝对是处理用户表单输入的神器。
- **数字互转**：`QString::number()` 与 `toInt(&ok)` 结合，通过 `bool` 变量精准拦截非法转换。

### 2. 顺序容器 (`QList`)

- **特点**：最常用的列表。类似于 C++ 的 `std::vector`。
- **常用 API**：`append()` 尾部添加、`insert()` 指定位置插入、`at()` 安全访问、`indexOf()` 查找、`removeAt()` 删除。
- **⚠️ 避坑**：访问元素时推荐用 `at(i)`，它带有边界检查；而 `[i]` 不检查越界，如果索引写错会导致程序直接崩溃。

### 3. 键值对容器 (`QMap` vs `QHash`) —— 🔥 面试高频

两者都用于存储 Key-Value 数据，但底层机制完全不同：

| 特性         | `QMap`                  | `QHash`              |
| ------------ | ----------------------- | -------------------- |
| **底层结构** | 红黑树 (Red-Black Tree) | 哈希表 (Hash Table)  |
| **排序**     | 自动按 Key 升序排序     | 完全无序（随机排列） |
| **查找速度** | 较慢 (O(log n))         | 极快 (Amort. O(1))   |
| **适用场景** | 需要按键排序输出时      | 纯追求查找速度时     |

### 4. 迭代器三剑客

| 迭代器类型                 | 风格      | 特点与用法                                               |
| -------------------------- | --------- | -------------------------------------------------------- |
| `QListIterator`            | Java 风格 | 只读。用 `hasNext()` 判断，`next()` 移动并取值。         |
| `QMutableListIterator`     | Java 风格 | 读写。在遍历时可用 `remove()` 删除、`setValue()` 修改。  |
| `QList<T>::const_iterator` | STL 风格  | 只读。像指针一样用 `++` 移动、`*` 解引用，**效率最高**。 |

## ⚠️ 三、实战避坑与性能优化指南

### 🚨 坑点 1：QMap 与 QHash 的选择陷阱

- **场景**：如果你需要频繁遍历一个字典并希望按照字母顺序展示，用 `QHash` 会非常痛苦，因为每次运行的顺序都可能不一样。此时必须用 `QMap`。
- **反向场景**：如果你有一个十万条数据的缓存表，只关心查询速度，不管顺序，用 `QMap` 的 O(log n) 查找会明显拖慢程序，此时必须用 `QHash`。

### 🚨 坑点 2：STL 迭代器失效

- **场景**：在使用 STL 风格迭代器（如 `QList<int>::iterator`）遍历时，如果你调用了 `list.removeAt()` 或 `list.append()` 导致底层内存重新分配，当前的迭代器就会**失效（变成野指针）**，继续 `++` 会直接导致程序崩溃。
- **✅ 解决方案**：如果在遍历中需要大量删除元素，请使用 Java 风格的 `QMutableListIterator`，它的 `remove()` 会安全地处理迭代点。

### 🚨 坑点 3：隐式共享 (Copy-on-Write)

- Qt 的容器采用了**隐式共享（写时复制）**技术。当你写 `QList<int> list2 = list1;` 时，不会立即复制数据，而是共享同一块内存。
- **好处**：赋值极快，节省内存。
- **坑点**：当你尝试修改 `list2` 时，Qt 才会真正复制一份数据给 `list2`。如果在多线程环境下，直接操作共享容器可能会导致数据竞争，需配合 `QReadWriteLock` 或使用 `detach()` 强制分离。

## 💻 四、核心代码实现

### 1. QList 与迭代器实操

```cpp
// 初始化
QList<QString> fruits;
fruits << "Apple" << "Pear"; // 流插入
fruits.append("Banana");     // 追加
fruits.insert(1, "Orange");  // 插入

// Java 风格读写迭代器：奇数乘10，偶数删除
QMutableListIterator<int> mutIt(nums);
while (mutIt.hasNext()) {
    int val = mutIt.next();
    if (val % 2 == 0) {
        mutIt.remove();
    } else {
        mutIt.setValue(val * 10);
    }
}

// STL 风格只读迭代器
QList<int>::const_iterator stlIt;
for (stlIt = nums.constBegin(); stlIt != nums.constEnd(); ++stlIt) {
    qDebug() << "元素：" << *stlIt; // 解引用
}
```

### 2. QMap 与 QHash 实操对比

```cpp
// --- QMap：自动排序 ---
QMap<QString, QString> cityCodes;
cityCodes.insert("Beijing", "010");
cityCodes["Shanghai"] = "021";
cityCodes.insert("Nanjing", "025");
// 输出时会是：(Beijing, 010) (Nanjing, 025) (Shanghai, 021)
qDebug() << "排序后的 Map:" << cityCodes;

// --- QHash：无序但极速 ---
QHash<QString, int> hash;
hash.insert("Apple", 10);
hash.insert("Banana", 20);
hash["Orange"] = 30;
// 输出时顺序是随机的（每次运行可能不同）
qDebug() << "无序的 Hash:" << hash;
```

