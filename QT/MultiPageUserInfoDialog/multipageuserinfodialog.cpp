#include "multipageuserinfodialog.h"

#include <QTextEdit>
#include <QFile>
#include <QDebug>
#include <QApplication>

// 通过实现修改用户资料功能这一案例来介绍如何使用布局方法实现一个复杂的窗口布局，如何使用布局以及如何使用堆栈窗体
// 最外层是一个分割窗体QSplitter，分割窗体的左侧是一个QListWidget，右侧是一个QVBoxLayout布局
// 此布局包括一个堆栈窗体QStackWidget和一个按钮布局
// 在此堆栈窗体QStackWidget中包括三个页面，每个页面采用基本布局方式进行布局管理

/*
不居中常用的方法有addWidget()和addLayout()

addWidget()方法用于加入需要布局的控件，原型如下
    void addWidget{
        QWidget *widget,    // 需要插入的控件对象
        int fromRow,        // 插入的行
        int rowSpan,        // 表示占用的行数
        int columnSpan,     // 表示占用的列数
        Qt::Alignment alignment = 0 // 描述各个控件的对齐方式
    }

addLayout()方法用于加入子布局，原型如下
    void addLayout{
        QLayout *layout,        // 表示需要插入的子布局对象
        int row,                // 插入的起始行
        int column,             // 插入的起始列
        int rowSpan,            // 表示插入的行数
        int columnSpan,         // 表示插入的列数
        Qt::Alignment alignment // 指定对齐方式
    }
*/

// 重要：QDialog 是独立弹窗窗口，Qt 内部有特殊窗口标记，**不能嵌入到 QSplitter 里面当子面板**，这是遇到运行空白的核心！
MultiPageUserInfoDialog::MultiPageUserInfoDialog(QWidget *parent)
    : QWidget(parent)
{

    stack = new QStackedWidget(this);
    // 对堆栈窗口的显示风格进行设置
    stack->setFrameStyle(QFrame::Panel | QFrame::Raised);
    // 插入三个页面
    baseInfo = new BaseInfo();
    contact = new Contact();
    detail = new Detail();
    stack->addWidget(baseInfo);
    stack->addWidget(contact);
    stack->addWidget(detail);

    // 创建两个按钮
    modifyButton = new QPushButton("修改");
    closeButton = new QPushButton("关闭");
    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addStretch(1);// 添加一个“弹簧”,空白拉伸
    btnLayout->addWidget(modifyButton);
    btnLayout->addWidget(closeButton);
    // 进行整体布局
    rightLayout = new QVBoxLayout(this);
    rightLayout->setMargin(10);// 设置布局与所在窗口边缘的距离
    rightLayout->setSpacing(6);// 设置布局内部各个子控件（或子布局）之间的间距
    rightLayout->addWidget(stack);
    rightLayout->addLayout(btnLayout);

    connect(closeButton,&QPushButton::clicked,this,&MultiPageUserInfoDialog::closeDialog);
}

MultiPageUserInfoDialog::~MultiPageUserInfoDialog()
{
}

void MultiPageUserInfoDialog::closeDialog()
{
    emit sigCloseWindow();
}
