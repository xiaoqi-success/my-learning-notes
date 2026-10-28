#include <QCoreApplication>

#include <QtDebug>

// 完成 Qt 核心容器类 (QList/QMap/QHash) 实操测试

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // =====================================================================
    // 模块一：QList 基础操作（最常用的容器）
    // =====================================================================
    qDebug() << "========== 1. QList 基础操作 ==========";
    QList<QString> fruits;

    // 1.1添加元素：三种添加元素的方式
    fruits << "Apple" << "Pear";// 流操作符，最简洁
    fruits.append("Banana");    // 最标准的方法名
    fruits.insert(1,"Orange");  // 在索引1的位置插入，原来的元素往后移
    qDebug() << "fruit:" << fruits; // ("Apple", "Orange", "Pear", "Banana")

    // 1.2访问元素
    qDebug() << "第一个水果：" << fruits.at(0);// 推荐使用at()，比[]更安全
    qDebug() << "第一个水果：" << fruits[0];  // []也可以，但越界时不报错，容易崩溃

    // 1.3修改与删除
    fruits[0] = "Red Apple"; // 直接修改
    fruits.removeAt(1);     // 删除索引为1的元素
    qDebug() << "修改删除后的fruits：" << fruits;      // ("Red Apple", "Pear", "Banana")

    // 1.4判断与查找
    qDebug() << "是否包含Banana:" << fruits.contains("Banana");// true
    qDebug() << "Banana 的索引：" << fruits.indexOf("Banana");// 2

    // =====================================================================
    // 模块二：QList 迭代器实操
    // =====================================================================
    qDebug() << "\n========== 2. 迭代器实操 ==========";
    QList<int> nums;
    nums << 1 << 2 << 3 << 4 << 5;
    qDebug() << "原始数据：" << nums;    // (1, 2, 3, 4, 5)

    // ---------------------------------------------------------------------
    // 2.1 Java 风格只读迭代器： QListIterator
    // 特点：只读。使用 hasNext() 看有没有下一个，next() 取下一个。
    // ---------------------------------------------------------------------
    qDebug() << "--- Java 风格（只读遍历） ---";
    QListIterator<int> readIt(nums);
//    while(readIt.hasNext()){
    // 或者
    for(;readIt.hasNext();){
        qDebug() << readIt.next();
    }
    // ---------------------------------------------------------------------
    // 2.2 Java 风格读写迭代器：QMutableListIterator
    // 特点：可以一边遍历，一边删改
    // ---------------------------------------------------------------------
    QMutableListIterator<int> mutIt(nums);
    while(mutIt.hasNext()){
        int val = mutIt.next();// 拿到当前值，并且迭代点向后移动
        if(val % 2 == 0){
            mutIt.remove();// 删除偶数
        }else{
            mutIt.setValue(val * 10);// 奇数变十倍
        }
    }
    qDebug() << "修改后的数据：" << nums; // (10, 30, 50)

    // ---------------------------------------------------------------------
    // 2.3 STL 风格迭代器（现代 C++ 标准写法，效率最高）
    // 特点：像指针一样，使用 ++ 移动，使用 * 解引用
    // ---------------------------------------------------------------------
    qDebug() << "--- STL 风格（只读遍历） ---";
    QList<int>::const_iterator stlReadIt;
    // constBegin 保证你不会通过迭代器误改数据,或者使用begin()函数可修改的
    for(stlReadIt = nums.constBegin();stlReadIt != nums.constEnd();++stlReadIt){
        qDebug() << "元素：" << *stlReadIt;// 解引用获取数据
    }

    // =====================================================================
    // 模块三：QMap 键值对（字典）
    // =====================================================================
    qDebug() << "\n========== 3. QMap 键值对实操 ==========";
    QMap<QString,QString> cityCodes;
    // 3.1插入数据
    cityCodes.insert("Beijing","010");
    cityCodes["Shanghai"] = "021";// 也可以用[]像数组那样插入
    cityCodes.insert("Nanjing","025");
    // 注意：QMap 的底层是红黑树，它会自动按照 Key（这里是城市名首字母）从小到大排序！
    qDebug() << "自动排序后的 Map:" << cityCodes; // QMap(("Beijing", "010")("Nanjing", "025")("Shanghai", "021"))
    // 3.2查找与修改
    if(cityCodes.contains("Beijing")){
        cityCodes["Beijing"] = "010-8888";// 修改值
    }
    // 3.3 STL 风格迭代器遍历 QMap
    // 注意：对于 Map，迭代器解引用后，分别用 it.key() 和 it.value() 取键和值
    qDebug() << "--- QMap 遍历 ---";
    QMap<QString,QString>::iterator mapIt;
    for(mapIt = cityCodes.begin();mapIt != cityCodes.end();++mapIt){
        qDebug() << "城市：" << mapIt.key() << "区号：" << mapIt.value();
    }

    // =====================================================================
    // 模块四：QHash（哈希表，追求极速查找）
    // =====================================================================
    qDebug() << "\n========== 4. QHash 键值对实操 ==========";
    QHash<QString,int> hash;
    // 4.1 插入数据
    hash.insert("Apple", 10);
    hash.insert("Banana", 20);
    hash["Orange"] = 30; // 也可以用 [] 赋值

    // 4.2 查找速度极快
    qDebug() << "Apple 的数量:" << hash.value("Apple");

    // 4.3 核心区别：QHash 是无序的！
    // 你打印出来会发现，它并不像 QMap 那样按 A-Z 排序，而是根据底层哈希算法随机排列。
    qDebug() << "QHash 打印结果 (注意看顺序):" << hash; // QHash(("Orange", 30)("Apple", 10)("Banana", 20))

    // 4.4 判断是否包含
    if (hash.contains("Banana")) {
        qDebug() << "包含 Banana，其值为:" << hash.value("Banana");
    }

    // 4.5 使用 STL 风格迭代器遍历 QHash
    qDebug() << "--- 遍历 QHash ---";
    QHash<QString, int>::const_iterator hashIt;
    for (hashIt = hash.constBegin(); hashIt != hash.constEnd(); ++hashIt) {
        qDebug() << "键:" << hashIt.key() << " 值:" << hashIt.value();
    }



    return a.exec();
}
