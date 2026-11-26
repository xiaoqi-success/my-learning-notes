#include "texteditor.h"

TextEditor::TextEditor(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("文本编辑器");
    resize(2024,600);
    showWidget = new ShowWidget(this);
    setCentralWidget(showWidget);// 创建设置QLabel和文本编辑框的QWidget对象showWidget，并将该QWidget对象设置为中心部件
//    createActions();
//    createMenus();
//    createToolBars();
    if(img.load(":/images/butterfly.png")){
        // 在imageLabel对象中设置图片
        showWidget->imageLabel->setPixmap(QPixmap::fromImage(img).scaled(showWidget->imageLabel->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    }

    fileMenu = new QMenu(this);
}

TextEditor::~TextEditor()
{
}

