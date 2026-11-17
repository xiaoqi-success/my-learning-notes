#include "myqqexample.h"

#include <QVBoxLayout>
#include <QToolButton>
#include <QIcon>
#include <QPixmap>

// 工具盒类又称为 QToolBox QToolBox 提供了一种列状的层叠窗体，
// 而 QToolButton 提供了一种快速访问命令或选择项的按钮，通常在工具条中使用

MyQQExample::MyQQExample(QWidget *parent)
    : QToolBox(parent)
{
    setWindowTitle("MY QQ");
    // 准备数据（在实际项目中，这些数据可能来自数据库或网络请求）
    QStringList friendNames = {"张三", "李四", "王五", "小赵", "小孙"};
    QStringList friendIcons = {":/icons/zhangsan.png", ":/icons/lisi.png", ":/icons/wangwu.png",
                               ":/icons/14.png", ":/icons/sunwukong.png"};

    QStringList strangerNames = {"小王", "小张"};
    QStringList strangerIcons = {":/icons/moshengren.jpg", ":/icons/zhaoliu.png"};

    QStringList blacklistNames = {"小陈", "小李"};
    QStringList blacklistIcons = {":/icons/lihua.png", ":/icons/tangseng.png"};

    // 调用封装的方法，只需三行代码完成三个抽屉的创建
    createDrawerPage(tr("我的好友"), friendNames, friendIcons);
    createDrawerPage(tr("陌生人"), strangerNames, strangerIcons);
    createDrawerPage(tr("黑名单"), blacklistNames, blacklistIcons);
}

MyQQExample::~MyQQExample()
{
}

void MyQQExample::createDrawerPage(const QString &title, const QStringList &names, const QStringList &iconPaths)
{
    // 创建抽屉容器
    QWidget *page = new QWidget(this);
    // 创建布局
    QVBoxLayout *layout = new QVBoxLayout(page);
    // 现代写法：setMargin 已废弃，改用 setContentsMargins(左, 上, 右, 下)
    layout->setContentsMargins(10, 10, 10, 10);
    layout->setAlignment(Qt::AlignHCenter); // 按钮居中
    // 循环遍历数据，批量生成按钮
    for(int i = 0;i < names.size();i++){
        // new的时候指定page为父对象
        QToolButton *btn = new QToolButton(page);
        btn->setText(names.at(i));
        // 加载图标（加入防空判断，防止图片不存在导致报错）
        QPixmap pix(iconPaths.at(i));
        if(!pix.isNull()){
            btn->setIcon(QIcon(pix));
            btn->setIconSize(pix.size());
        }
        btn->setAutoRaise(true);// 点击会有按下去的效果，视觉反馈更强
        /*
            控制工具按钮是仅显示图标，仅显示文本，还是在图标旁或下方显示文本
            Qt::ToolButtonIconOnly：默认只显示图标
            Qt::ToolButtonTextOnly：仅显示文本
            Qt::ToolButtonTextBesideIcon：文字显示在图标旁边
            Qt::ToolButtonTextUnderIcon：文字显示在图标下方
        */
        btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        // 将按钮加入布局
        layout->addWidget(btn);
    }
    // 添加占位符，把所有按钮顶到上方
    layout->addStretch();

    // 将组装好的页面插入 QToolBox
    // 现代 C++ 中，子类指针转父类指针（QWidget*）是完全隐式的，不需要 (QWidget*) 强转
    // this 是指向当前实例的指针，类型是 MyQQExample*
    // MyQQExample 继承自 QToolBox，所以当前对象就是一个 QToolBox
    this->addItem(page, title);
}

