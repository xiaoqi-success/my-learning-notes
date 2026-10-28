#include <QCoreApplication>

#include <QVariant>
#include <QDebug>
// QColor 是 GUI 类：QColor 属于 Qt 的 GUI 模块。如果在写一个纯控制台项目（QCoreApplication），默认是不包含 GUI 模块的
// 如果用的是纯控制台项目（Qt Console Application），仅仅 #include <QColor> 可能还是会报错（提示找不到头文件或者链接失败）需要在项目的 .pro 文件里，加上QT += gui
#include <QColor>

// 练习QVariant类：QVariant类类似于C++的联合（union）数据类型，它不仅能保存很多Qt类型的值，包括QColor，QFont,QRect,QString和QSize等，而且能存放Qt的容器类型的值
// Qt的很多功能都是建立在QVariant基础上的，如Qt的对象属性及数据库功能等

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // 1.基础存取
    QVariant v(709);
    qDebug() << "v 转 int：" << v.toInt();

    QVariant w("How Are You!");
    qDebug() << "w转QString：" << w.toString();

    // 2.进阶用法：用QVariant存不同数据类型在一个Map里
    QMap<QString,QVariant> map;
    map["int"] = 709;
    map["double"] = 709.709;
    map["string"] = "How are you!";
    map["color"] = QColor(255,0,0); // 存一个红色

    qDebug() << "\n--- 从 Map 中提取不同类型的值 ---";
    qDebug() << "int：" << map["int"].toInt();
    qDebug() << "double：" << map["double"].toDouble();
    qDebug() << "string：" << map["string"].toString();
    // 提取颜色必须用 value<QColor>() 模板方式
    // value<T>() 是 Qt QVariant 的模板成员函数，<QColor> 就是模板参数，告诉编译器：我要把这个 QVariant 里面存的数据，转成 QColor 类型
    // 而 toInt() / toDouble() / toString() 是普通成员函数，不是模板
    qDebug() << "color：" << map["color"].value<QColor>();// QColor(ARGB 1, 1, 0, 0)

    // 补充：安全提取与类型检查 (实际开发常用)
    qDebug() << "\n--- 安全提取测试 ---";
    // 假设我们不知道 map["color"] 里存的是不是颜色
    if (map["color"].canConvert<QColor>()) {
        qDebug() << "检查通过：里面确实是 QColor 类型";
    }

    // 尝试把一个字符串强转成 int，并判断是否成功
    bool ok;
    int testNum = map["string"].toInt(&ok);
    qDebug() << "把字符串转int的结果:" << testNum << " 转换成功了吗? " << (ok ? "成功" : "失败");

    return a.exec();
}
