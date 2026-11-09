#include "dockwindows.h"
#include <QTextEdit>
#include <QDockWidget>

// QDockWidget 是 Qt 框架中的一个可停靠窗口（也叫工具面板或实用窗口）。
// 它本身不是独立的应用程序窗口，而是依附在主窗口（QMainWindow）中央区域周围的辅助面板，
// 用户可以把它拖来拖去，也可以把它“拽”出来变成一个独立的小浮窗。
// 比如Photoshop：右侧的“图层”、“颜色”、“历史记录”面板。它们可以堆叠成标签页，也可以被拖拽出来悬浮在画布上
// 核心特点
    // 可停靠/可浮动：你可以把它吸附在主窗口的上下左右边缘，也可以双击标题栏或拖拽让它浮起来变成独立小窗，用完再拖回去
    // 辅助性质：它一般用来放工具或选项（比如列表、属性表），辅助中央主区域（比如画布、代码编辑区）的工作，而不是用来当主界面
    // 可限制：开发者可以限制它只能停在左边或右边，或者禁止关闭/移动，防止用户把界面搞乱

DockWindows::DockWindows(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(tr("DockWindows"));// 设置主窗口的标题栏文字
    QTextEdit *te = new QTextEdit(this);// 定义一个QTextEdit对象作为主窗口
    te->setText(tr("Main Window"));
    te->setAlignment(Qt::AlignCenter);
    setCentralWidget(te);// 将此编辑框设为主窗口的中央窗体

    // 停靠窗口1
    QDockWidget *dock = new QDockWidget(tr("DockWindows1"),this);
    // 设置为可移动的
    // setFeatures()方法设置停靠窗体的特性，DockWidget::DockWidgetMovable: 停靠窗体可移动。
    dock->setFeatures(QDockWidget::DockWidgetMovable);
    // setAllowedAreas()方法设置停靠窗体可停靠的区域，Qt::LeftDockWidgetArea: 可在主窗口的左侧停靠。
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    QTextEdit *te1 = new QTextEdit();
    te1->setText(tr("Windows1:用户可在各个停靠区域之间拖动该停靠窗口"));
    // 给这个窗口加内容
    dock->setWidget(te1);
    // 把这个停靠窗口"挂到主窗口上"，并指定初始停靠位置
    addDockWidget(Qt::RightDockWidgetArea,dock);

    // 停靠窗口2
    QDockWidget *dock2 = new QDockWidget(tr("DockWidget2"),this);
    dock2->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetFloatable);// 可关闭，可浮动
    QTextEdit *te2 = new QTextEdit();
    te2->setText(tr("Window2：停靠部件可从主窗口脱离，作为独立窗口悬浮，并且可以关闭"));
    dock2->setWidget(te2);
    addDockWidget(Qt::RightDockWidgetArea,dock2);

    // 停靠窗口3
    QDockWidget *dock3 = new QDockWidget(tr("DockWindow3"),this);
    dock3->setFeatures(QDockWidget::AllDockWidgetFeatures);// 全部特性
    QTextEdit *te3 = new QTextEdit();
    te3->setText(tr("Window3:停靠部件支持关闭、移动以及悬浮"));
    dock3->setWidget(te3);
    addDockWidget(Qt::RightDockWidgetArea,dock3);

    // 两者变成标签页,Photoshop 那种"图层/颜色/历史"堆叠成标签页，靠的就是这个
    tabifyDockWidget(dock2,dock3);
    dock2->raise();// 让 dock2 显示在前

}

DockWindows::~DockWindows()
{
}

