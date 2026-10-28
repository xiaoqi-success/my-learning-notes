#include <QCoreApplication>

#include <QDebug>

// QString类常用API测试

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // ==========================================
    // 常用构造函数
    // ==========================================
    QString str1;               // 空字符串
    QString str2("hello");      // 从普通字符串构造
    QByteArray ba("world");
    QString str3(ba);           // 从QByteArray构造
    QString str4(5,'A');        // 从指定数量的字符构造
    QString str5(str4);         // 复制构造
    qDebug() << "str1 = " << str1;// ""
    qDebug() << "str2 = " << str2;// "hello"
    qDebug() << "str3 = " << str3;// "world"
    qDebug() << "str4 = " << str4;// "AAAAA"
    qDebug() << "str5 = " << str5;// "AAAAA"

    // ==========================================
    // 1. 基本操作 (长度与判空)
    // ==========================================
    QString str = "Hello QT";
    int len = str.length();
    int size = str.size();
    bool isEmpty = str.isEmpty();
    bool isNull = str.isNull();
    qDebug() << "长度:" << len;          // 长度: 8
    qDebug() << "长度:" << size;         // 长度: 8
    qDebug() << "是否为空:" << isEmpty;   // 是否为空: false
    qDebug() << "是否为空:" << isNull;    // 是否为空: false

    // ==========================================
    // 2. 字符串连接
    // ==========================================
    QString str6 = "Hello";
    QString str7 = "World";
    // 方法1: 使用 operator+ (直观，但多段拼接时性能稍弱)
    qDebug() << "str6 + , + str7 = " << str6 + "," + str7;
    // 方法2: 使用 append 链式调用
    QString result1;
    result1.append(str6).append(",").append(str7);
    qDebug() << "str6 + , + str7 = " << result1;
    // 方法3: 使用 arg() (高效，推荐，支持占位符)
    QString result2 = QString("%1,%2").arg(str6).arg(str7);
    qDebug() << "str6 + , + str7 = " << result2;

    // ==========================================
    // 3. 修改字符串
    // ==========================================
    QString s = "Hello World";
    qDebug() << "原始:" << s;

    s[0] = 'h';               // 修改第一个字符
    qDebug() << "修改首字符:" << s;// "hello World"

    s[6] = 'w';               // 修改第7个字符（W→w）
    qDebug() << "修改第7字符:" << s; // "hello world"

    s.replace("world", "Qt"); // 替换字符串
    qDebug() << "替换:" << s;  // "hello Qt"

    s.prepend("Hi ");         // 在开头插入
    qDebug() << "前置:" << s; // "Hi hello Qt"

    s.append("!");            // 在末尾追加
    qDebug() << "追加:" << s; // "Hi hello Qt!"

    s.insert(3, "xxx");       // 在指定位置插入
    qDebug() << "插入:" << s;  // "Hi xxxhello Qt!"

    s.remove(3, 3);           // 从指定位置删除指定长度的字符
    qDebug() << "删除:" << s; // "Hi hello Qt!"

    s = s.toUpper();          // 全部转大写
    qDebug() << "转大写:" << s;  // "HI HELLO QT!"

    s = s.toLower();          // 全部转小写
    qDebug() << "转小写:" << s;  // "hi hello qt!"

    // ==========================================
    // 4. 查找与截取
    // ==========================================
    QString s1 = "Hello World, Hello Qt";
    qDebug() << "完整字符串:" << s1;

    int pos = s1.indexOf("World");            // 查找首次出现位置(从0开始算)
    qDebug() << "World位置:" << pos;          // 6

    int last = s1.lastIndexOf("Hello");       // 查找最后一次出现位置
    qDebug() << "最后一个Hello位置:" << last;   // 13

    bool contains = s1.contains("Qt");        // 是否包含子串
    qDebug() << "包含Qt吗:" << contains;       // true

    QString left = s1.left(5);                // 截取左边 n 个字符
    qDebug() << "左边5个字符:" << left;         // "Hello"

    QString right = s1.right(3);              // 截取右边 n 个字符
    qDebug() << "右边3个字符:" << right;       // " Qt"

    QString mid = s1.mid(6, 5);               // 从指定位置截取 n 个字符
    qDebug() << "从位置6取5个字符:" << mid;     // "World"

    // section 切割：按指定分隔符切分，取指定区间的段
    // 根据参数1分隔符（逗号等）把字符串切分成若干段
    // 参数2和3表示从第0个段开始，到第0个段结束（取第0个段）
    QString section = s1.section(",", 0, 0);
    qDebug() << "逗号前部分:" << section;        // "Hello World"

    // ==========================================
    // 5. 分割与合并 (依赖 QStringList)
    // ==========================================
    QString s2 = "apple,banana,orange";
    qDebug() << "原始:" << s2;                // 原始: "apple,banana,orange"

    QStringList list = s2.split(",");         // 按分隔符拆分成字符串列表
    qDebug() << "分割后:" << list;             // 分割后: ("apple", "banana", "orange")
    qDebug() << "第1个:" << list[0];          // 第1个: "apple"
    qDebug() << "第2个:" << list[1];
    qDebug() << "第3个:" << list[2];

    QString joined = list.join(";");          // 将列表按指定符号合并成一个字符串
    qDebug() << "合并:" << joined;            // 合并: "apple;banana;orange"

    // ==========================================
    // 6. 空白处理
    // ==========================================
    QString s3 = "  Hello    World  ";

    s3 = s3.trimmed();      // 去掉两端空白
    qDebug() << "去掉两端空白：" << s3;        // "Hello    World"

    s3 = s3.simplified();   // 去两端，且中间连续空白变一个空格
    qDebug() << "去两端+中间连续空白变一个空格：" << s3;// "Hello World"

    // ==========================================
    // 7. 数字与字符串转换
    // ==========================================
    // ---- 数字 ---> 字符串 ----
    QString numStr = QString::number(123);
    qDebug() << "123转字符串:" << numStr;       // "123"

    numStr = QString::number(3.14159, 'f', 2); // 'f'表示浮点，2表示保留2位小数
    qDebug() << "3.14159转字符串(2位):" << numStr;// "3.14"

    numStr = QString::number(12345.67, 'e', 2); // 'e'表示科学计数法
    qDebug() << "科学计数法:" << numStr;         // 1.23e+04

    numStr = QString::number(255, 16);         // 转十六进制字符串
    qDebug() << "255转十六进制:" << numStr;

    // ---- 字符串 ---> 数字 ----
    bool ok;

    int i = QString("123").toInt(&ok);         // 字符串转整数
    qDebug() << "'123'转int:" << i << "成功:" << ok;

    i = QString("abc").toInt(&ok);             // 转换失败的情况
    qDebug() << "'abc'转int:" << i << (ok == true ? "成功" : "失败"); // 失败的情况

    double d = QString("3.14").toDouble(&ok);  // 字符串转浮点数
    qDebug() << "'3.14'转double:" << d << "成功:" << ok;

    int hex = QString("FF").toInt(&ok, 16);    // 十六进制字符串转整数
    qDebug() << "'FF'转十六进制:" << hex << "成功:" << ok;

    int bin = QString("1010").toInt(&ok, 2);   // 二进制字符串转整数
    qDebug() << "'1010'转二进制:" << bin << "成功:" << ok;

    // ==========================================
    // 8. 格式化输出 (arg 高级用法)
    // ==========================================
    QString s4 = QString("Name:%1,Age:%2").arg("Alice").arg(25);
    qDebug() << s4;

    // arg(数值, 字段宽度, 进制, 填充字符)
    QString s5 = QString("%1").arg(123, 5, 10, QChar('0'));
    qDebug() << s5;  // 输出: "00123"

    QString s6 = QString("%1 + %2 = %3").arg(1).arg(2).arg(3);
    qDebug() << s6;     // "1 + 2 = 3"

    QString s7 = QString("%1 + %1 = %2").arg(2).arg(4); // 重复使用参数1
    qDebug() << s7;     // "2 + 2 = 4"

    QString s8 = QString("十进制：%1，十六进制：%2").arg(255).arg(255, 0, 16);
    qDebug() << s8;     // "十进制：255，十六进制：ff"

    // ==========================================
    // 9. 判断操作
    // ==========================================
    QString str13 = "Hello123";

    qDebug() << "以He开头?" << str13.startsWith("He");  // true
    qDebug() << "以123结尾?" << str13.endsWith("123");  // true
    qDebug() << "包含ell?" << str13.contains("ell");  // true

    // 大小写敏感比较
    qDebug() << "相等?" << (QString("Hello") == QString("HELLO"));// false

    // 忽略大小写比较
    bool equalIgnore = QString::compare("Hello", "HELLO", Qt::CaseInsensitive) == 0;
    qDebug() << "忽略大小写相等?" << equalIgnore; // true

    // ==========================================
    // 10. 遍历字符串操作
    // ==========================================
    QString list1 = "Hello";

    qDebug() << "--- 索引遍历 ---";
    for(int j = 0; j < list1.length(); j++) {
        qDebug() << "索引" << j << ":" << list1[j];
    }

    qDebug() << "--- foreach 遍历 ---";
    foreach(QChar ch, list1) {
        qDebug() << ch;
    }

    qDebug() << "--- C++11 范围 for 循环 ---";
    for(QChar ch : list1) {
        qDebug() << ch;
    }


    return a.exec();
}
