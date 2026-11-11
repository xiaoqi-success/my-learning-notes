#include "multipageuserinfodialog.h"

#include <QApplication>
#include <QFile>
#include <QDebug>
#include <QSplitter>
#include <QListWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFont font("Microsoft YaHei", 12); //设置整个程序采用的字体与字号
    a.setFont(font);

    // 新建一个水平分割窗口对象，作为主布局框
    QSplitter *mainSplitter = new QSplitter(Qt::Horizontal,0);
    mainSplitter->setOpaqueResize(true);
    // 在新建的水平分割窗的左侧窗口中插入一个QListWidget作为条目选择框，并依次插入基本信息等功能
    QListWidget *list = new QListWidget(mainSplitter);
    list->addItem("基本信息");
    list->addItem("联系方式");
    list->addItem("详细资料");
    // 在新建的水平分割窗的右侧窗口中插入MultiPageUserInfoDialog类对象。
    MultiPageUserInfoDialog *content = new MultiPageUserInfoDialog(mainSplitter);
    mainSplitter->setStretchFactor(0, 1);
    mainSplitter->setStretchFactor(1, 5);
    QObject::connect(list,&QListWidget::currentRowChanged,content->stack,&QStackedWidget::setCurrentIndex);
    // 新增：收到关闭信号，关闭顶层splitter（整个窗口）
    QObject::connect(content, &MultiPageUserInfoDialog::sigCloseWindow, mainSplitter, &QSplitter::close);

    // 设置主布局框即水平分割窗口的标题和图标
    mainSplitter->setWindowTitle(QObject::tr("修改用户资料"));
    mainSplitter->setWindowIcon(QIcon(":/Icons/usernfo.png"));

    QFile file(":/styles/style.qss");
    // 只读+文本模式（防止windows乱码换行）
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qWarning() << "加载QSS失败：" << file.errorString();
        return false;
    }
    QString styleSheet = QString::fromUtf8(file.readAll());
    qApp->setStyleSheet(styleSheet);
    file.close();


    mainSplitter->show();

//    MultiPageUserInfoDialog w;
//    w.show();
    return a.exec();
}
