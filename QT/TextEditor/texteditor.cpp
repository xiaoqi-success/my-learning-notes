#include "texteditor.h"

#include <QApplication>


TextEditor::TextEditor(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("文本编辑器");
    setWindowIcon(QIcon(":/icons/textedit.png"));
    resize(2024,1000);

    // 设置菜单的文字大小
    QFont menuFont = menuBar()->font();
    menuFont.setPointSize(10);
    menuBar()->setFont(menuFont);

    showWidget = new ShowWidget(this);
    setCentralWidget(showWidget);// 创建设置QLabel和文本编辑框的QWidget对象showWidget，并将该QWidget对象设置为中心部件
    createActions();// 先造动作（造灵魂）
    createMenus();// 再把动作放在菜单里（穿衣服）
    createToolBars();// 再把动作放在工具栏里（换衣服）
    if(img.load(":/images/butterfly.png")){
        // 在imageLabel对象中设置图片
        showWidget->imageLabel->setPixmap(QPixmap::fromImage(img).scaled(showWidget->imageLabel->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    }
}

TextEditor::~TextEditor()
{
}

// 动作的实现
void TextEditor::createActions()
{
    // 打开动作
    openFileAction = new QAction(QIcon(":/icons/open.png"),"打开",this);// 在创建“打开文件”动作的同时，指定了此动作的图标名称和父窗口
    openFileAction->setShortcut(tr("Ctrl+O"));// 设置此动作的组合键为Ctrl+O
    // 设定了状态栏显示，当鼠标光标移动到此动作对应的菜单条目或工具栏按钮上时，在状态栏上显示“打开一个文件”的提示
    openFileAction->setStatusTip("打开一个文件");
    // 新建动作
    newFileAction = new QAction(QIcon(":/icons/new.png"),"新建",this);
    newFileAction->setShortcut(tr("Ctrl+N"));
    newFileAction->setStatusTip("新建一个文件");
    // 退出动作
    exitAction = new QAction(QIcon(":/icons/quit.png"),"退出",this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip("退出程序");
    connect(exitAction,&QAction::triggered,this,&TextEditor::close);
    // 复制动作
    copyAction = new QAction(QIcon(":/icons/copy.png"),"复制",this);
    copyAction->setShortcut(tr("Ctrl+C"));
    copyAction->setStatusTip("复制文件");
    connect(copyAction,&QAction::triggered,showWidget->text,&QTextEdit::copy);
    // 剪切动作
    cutAction = new QAction(QIcon(":/icons/cut.png"),"剪切",this);
    cutAction->setShortcut(tr("Ctrl+X"));
    cutAction->setStatusTip("剪切文件");
    connect(cutAction,&QAction::triggered,showWidget->text,&QTextEdit::cut);
    // 粘贴动作
    pasteAction = new QAction(QIcon(":/icons/paste.png"),"粘贴",this);
    pasteAction->setShortcut(tr("Ctrl+V"));
    pasteAction->setStatusTip("粘贴文件");
    connect(pasteAction,&QAction::triggered,showWidget->text,&QTextEdit::paste);
    // 关于动作
    aboutAction = new QAction(QIcon(":/icons/about.png"),"关于",this);
    connect(aboutAction,&QAction::triggered,qApp,&QApplication::aboutQt);
    // 打印文本动作
    printTextAction = new QAction(QIcon(":/icons/printText.png"),"打印文本",this);
    printTextAction->setStatusTip("打印一个文本");
    // 打印图片动作
    printImageAction = new QAction(QIcon(":/icons/printImg.png"),"打印图片",this);
    printImageAction->setStatusTip("打印一幅图片");
    // 更换图片动作
    changeImgAction = new QAction(QIcon(":/icons/changeimg.png"),"更换图片",this);
    changeImgAction->setStatusTip("更换一张图片");
    // 放大动作
    zoomInAction = new QAction(QIcon(":/icons/zoomin.png"),"放大",this);
    zoomInAction->setStatusTip("放大一张图片");
    // 缩小动作
    zoomOutAction = new QAction(QIcon(":/icons/zoomout.png"),"缩小",this);
    zoomOutAction->setStatusTip("缩小一张图片");
    // 实现图片旋转的动作
    // 旋转90°
    rotate90Action = new QAction(QIcon(":/icons/rotate90.png"),"旋转90°",this);
    rotate90Action->setStatusTip("将一幅图旋转90°");
    // 旋转180°
    rotate180Action = new QAction(QIcon(":/icons/rotate180.png"),"旋转180°",this);
    rotate180Action->setStatusTip("将一幅图旋转180°");
    // 旋转270°
    rotate270Action = new QAction(QIcon(":/icons/rotate270.png"),"旋转270°",this);
    rotate270Action->setStatusTip("将一幅图旋转270°");
    // 实现图像镜像的动作
    // 纵向镜像
    mirrorVerticalAction = new QAction(QIcon(":/icons/mirrorVertical.png"),"纵向镜像",this);
    mirrorVerticalAction->setStatusTip("对一幅图做纵向镜像");
    // 横向镜像
    mirrorHorizontalAction = new QAction(QIcon(":/icons/mirrorHorizontal.png"),"横向镜像",this);
    mirrorHorizontalAction->setStatusTip("对一幅图做横向镜像");
    // 实现撤销和重做的动作
    // 撤销和重做
    undoAction = new QAction(QIcon(":/icons/undo.png"),"撤销",this);
    connect(undoAction,&QAction::triggered,showWidget->text,&QTextEdit::undo);
    redoAction = new QAction(QIcon(":/icons/redo.png"),"重做",this);
    connect(redoAction,&QAction::triggered,showWidget->text,&QTextEdit::redo);
}

// 菜单的实现
// 在实现各个动作之后，需要将它们通过菜单和工具栏或快捷键的方式体现出来
void TextEditor::createMenus()
{
    // 文件菜单
    // 直接调用QMainWindow的menuBar(需要加入头文件)函数，即可得到主窗口的菜单栏指针
    // 再调用菜单栏QMenuBar的addMenu函数即可完成在菜单栏中插入一个新菜单fileMenu，fileMenu为一个QMenu类对象
    fileMenu = menuBar()->addMenu("文件");
    // 调用QMenu的addAction()函数在菜单中添加菜单条目“打开”“新建”“打印文本”“打印图片”等
    fileMenu->addAction(openFileAction);
    fileMenu->addAction(newFileAction);
    fileMenu->addAction(printTextAction);
    fileMenu->addAction(printImageAction);
    fileMenu->addSeparator();// 添加个分割线
    fileMenu->addAction(exitAction);

    // 编辑菜单
    zoomMenu = menuBar()->addMenu("编辑");
    zoomMenu->addAction(copyAction);
    zoomMenu->addAction(cutAction);
    zoomMenu->addAction(pasteAction);
    zoomMenu->addAction(aboutAction);
    zoomMenu->addSeparator();
    zoomMenu->addAction(changeImgAction);
    zoomMenu->addAction(zoomInAction);
    zoomMenu->addAction(zoomOutAction);

    // 旋转菜单
    rotateMenu = menuBar()->addMenu("旋转");
    rotateMenu->addAction(rotate90Action);
    rotateMenu->addAction(rotate180Action);
    rotateMenu->addAction(rotate270Action);

    // 镜像菜单
    mirrorMenu = menuBar()->addMenu("镜像");
    mirrorMenu->addAction(mirrorHorizontalAction);
    mirrorMenu->addAction(mirrorVerticalAction);
}

// 主窗口的工具栏可以有多个工具条，通常采用一个菜单对应一个工具条的方式，也可以根据需要进行工具条的划分
void TextEditor::createToolBars()
{
    // 文件工具条
    // 直接调用QMainWindow的addToolBar函数即可获得主窗口的工具条对象
    // 每新增一个工具条调用一次addToolBar函数，赋予不同的名称，即可在主窗口中新增一个工具条
    fileTool = addToolBar("File");
    // 调用QTollBar的addAction函数在工具条中插入属于本工具条的动作，类似的，实现编辑旋转撤销和重做工具条
    // 工具条的显示可以由用户进行选择，在工具栏上单击鼠标右键将弹出工具条的显示的选择菜单，用户对需要显示的工具条进行选择即可
    fileTool->addAction(openFileAction);
    fileTool->addAction(newFileAction);
    fileTool->addAction(printTextAction);
    fileTool->addAction(printImageAction);
    // 编辑工具条
    zoomTool = addToolBar("Edit");
    zoomTool->addAction(copyAction);
    zoomTool->addAction(cutAction);
    zoomTool->addAction(pasteAction);
    zoomTool->addSeparator();
    zoomTool->addAction(changeImgAction);
    zoomTool->addAction(zoomInAction);
    zoomTool->addAction(zoomOutAction);
    // 旋转工具条
    rotateTool = addToolBar("rotate");
    rotateTool->addAction(rotate90Action);
    rotateTool->addAction(rotate180Action);
    rotateTool->addAction(rotate270Action);
    // 撤销和重做工具条
    doToolBar = addToolBar("doEdit");
    doToolBar->addAction(undoAction);
    doToolBar->addAction(redoAction);

    // 工具条是一个可移动的窗口，可停靠的区域由QToolBar的allowAreas决定，包括上下左右和全区局，默认出现主窗口的顶部
    fileTool->setAllowedAreas(Qt::TopToolBarArea | Qt::LeftToolBarArea);
    zoomTool->setAllowedAreas(Qt::TopToolBarArea | Qt::RightToolBarArea);
    rotateTool->setAllowedAreas(Qt::TopToolBarArea | Qt::LeftToolBarArea);
    doToolBar->setAllowedAreas(Qt::AllToolBarAreas);

    // 设置工具条不可移动
//    fileTool->setMovable(false);
//    zoomTool->setMovable(false);
//    rotateTool->setMovable(false);
//    doToolBar->setMovable(false);
}

