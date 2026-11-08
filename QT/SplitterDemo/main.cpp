#include "mainwindow.h"

#include <QApplication>
#include <QSplitter>
#include <QTextEdit>
#include <QSettings>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFont font("ZYSong18030",12); // 显示指定的字体
    a.setFont(font);

    // 主分割窗口
    QSplitter *splitterMain = new QSplitter(Qt::Horizontal,0);// 设定此分割窗口为水平分割窗口
    QTextEdit *textLeft = new QTextEdit(QObject::tr("Left Widget"),splitterMain);// 插入主分割窗口中
    textLeft->setAlignment(Qt::AlignCenter);// 设定里面的文字的对齐方式

    // 右分割窗口
    QSplitter *splitterRight = new QSplitter(Qt::Vertical,splitterMain);// 设定此分割窗口为垂直分割窗口，并以主分割窗口为父窗口
    // 此方法用于设置分割窗口的分割条在拖拽时是否为实时更新显示
    // 若为true则实时更新显示
    // 若为false则在拖拽时只显示一条灰色的粗细线，在拖拽到位并释放鼠标后再显示分割条，默认为true
    splitterRight->setOpaqueResize(false);
    QTextEdit *textUp = new QTextEdit(QObject::tr("Top Widget"),splitterRight);
    textUp->setAlignment(Qt::AlignCenter);
    QTextEdit *textBottom = new QTextEdit(QObject::tr("Bottom Widget"),splitterRight);
    textBottom->setAlignment(Qt::AlignCenter);
    // 此方法用于设定可伸缩控件
    // 参数1：指定控件的索引。分割器内的控件按插入顺序从 0 开始编号，1 代表第二个控件
    // 参数2：拉伸因子。该值大于 0 表示此控件是可伸缩控件，这个例子中设定右部的分割窗口为可伸缩控件；若设为 0，则调整窗口时该控件大小基本不变
    splitterMain->setStretchFactor(1,1);
    splitterMain->setWindowTitle(QObject::tr("Splitter"));

    // 设置分隔条宽度
    splitterMain->setHandleWidth(5);
    // 控制某个子控件是否允许被折叠到 0 大小
    splitterMain->setCollapsible(0,false);// 左侧不允许被完全折叠
    splitterMain->setCollapsible(1,true);// 右侧允许被完全折叠

    // 用户希望下次打开软件时，分割器的比例还是上次调整的样子，QSplitter内置了saveState()和restoreState()
    QSettings settings("OrganizationName","SplitterDemo");
    QByteArray state = settings.value("splitterState").toByteArray();
    if(!state.isEmpty()){
        splitterMain->restoreState(state);
    }else{
        // 设置初始比例（左：右 = 1:4）
        splitterMain->setSizes(QList<int>() << 100 << 400);
    }
    // --------重点：lambda里面新建QSettings，不要引用外面栈上的settings--------
    QObject::connect(&a,&QApplication::aboutToQuit,[&](){
        QSettings settings("OrganizationName","SplitterDemo");
        settings.setValue("splitterState",splitterMain->saveState());
    });

    splitterMain->show();

//    MainWindow w;
//    w.show();
    return a.exec();
}
