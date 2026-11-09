#include "stackedwidget.h"
#include <QHBoxLayout>

/*
QStackedWidget 和 QDockWidget 思路完全不同，它其实是最简单的一个容器,就记一句话：
    一堆页面叠在一起，同一时间只显示一个，像一摞卡片，翻到哪张显示哪张。
生活中的对应物：
    手机设置界面：点“WiFi”进 WiFi 页，点“蓝牙”进蓝牙页，返回又回列表——底层就是堆栈窗体在切换。
    安装向导：下一步 / 上一步，每步一个页面。
    QQ/微信左侧导航：点“聊天”显示聊天列表，点“联系人”显示联系人，右侧区域不变，只换内容。
    Photoshop 右侧面板：图层/颜色/历史记录，点标签切换，同一块区域只显示一个。
和 QDockWidget 的区别一句话：
    QDockWidget = 可以拖来拖去的附属面板（能浮动、能停靠）
    QStackedWidget = 固定位置的多页面容器（不能拖，只能切）
*/

StackedWidget::StackedWidget(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("StackedWidget"));

    // QListWidget是一个"列表控件"，用来显示一列条目（item），每个条目可以带文字、图标、复选框，用户能点选、拖拽、增删
    list = new QListWidget(this);// 新建一个QListWidget控件对象
    list->insertItem(0,tr("Window1"));
    list->insertItem(1,tr("Window2"));
    list->insertItem(2,tr("Window3"));

    // 创建三个QLabel标签控件对象，作为堆栈窗口需要显示的三层窗体
    label1 = new QLabel(tr("WindowTest1"));
    label2 = new QLabel(tr("WindowTest2"));
    label3 = new QLabel(tr("WindowTest3"));

    stack = new QStackedWidget(this);// 新建一个QStackedWidget堆栈窗体对象

    // 将创建的三个QLabel标签控件依次插入堆栈窗体中
    stack->addWidget(label1);
    stack->addWidget(label2);
    stack->addWidget(label3);

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(5,5,5,5);// 设定布局的左上右下的间距
    mainLayout->addWidget(list);
    mainLayout->addWidget(stack,0,Qt::AlignHCenter);
    mainLayout->setStretchFactor(list,1);// 布局中列表占一份宽
    mainLayout->setStretchFactor(stack,3);// 栈体占3份宽

    // currentRowChanged:表示当前行变成第几行了
    // setCurrentIndex:收到行号之后执行翻到哪一页
    connect(list,&QListWidget::currentRowChanged,stack,&QStackedWidget::setCurrentIndex);

    list->setCurrentRow(1);// 默认显示哪一个窗体
}

StackedWidget::~StackedWidget()
{
}

