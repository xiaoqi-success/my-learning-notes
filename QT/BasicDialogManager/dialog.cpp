#include "dialog.h"

#include <QFileDialog>
#include <QColorDialog>
#include <QFontDialog>
#include <QFont>

// 演示各种标准对话框的使用

/*
 * 标准文件对话框
static QString getOpenFileName(QWidget *parent = nullptr,// 标准文件对话框的父窗口
       const QString &caption = QString(),// 标准文件对话框的标题名
       const QString &dir = QString(),// 指定了默认的目录，若此参数带有文件名，则文件将是默认选中的文件
       const QString &filter = QString(),// 对文件类型进行过滤，只有与过滤器匹配的文件类型才显示，过滤多种使用;;隔开
       QString *selectedFilter = nullptr,// 用户选择的过滤器通过此参数返回
       Options options = Options());// 选择显示文件名的格式，默认是同时显示目录与文件名

 * 标准颜色对话框
static QColor getColor(const QColor &initial = Qt::white,   // 指定颜色，默认白色
           QWidget *parent = nullptr,                       // 父对象
           const QString &title = QString(),                // 标题名
            // 指定影响颜色对话框外观的各种选项
            // QColorDialog::ShowAlphaChannel:允许用户选择颜色的alpha分量
            // QColorDialog::NoButtons:不要显示OK和Cancel按钮。（对“实时对话”很有用。）
            QColorDialog::DontUseNativeDialog:使用Qt的标准颜色对话框，而不是操作系统自带的颜色对话框
           ColorDialogOptions options = ColorDialogOptions());
 * 标准字体对话框
static QFont getFont(bool *ok, // 结果状态指针，用户点击确认按钮，将该参数*ok将设为true,函数返回用户所选择的字体，否则设为false，此时函数返回默认字体
            const QFont &initial, // 初始字体
            QWidget *parent = nullptr, // 父窗口
            const QString &title = QString(),// 对话框标题
            FontDialogOptions options = FontDialogOptions()); // 外观选项
 * 标准输入对话框：标准输入对话框提供四种数据类型的输入，包括字符串、下拉列表框的条目、 int 数据类型和double数据类型
 *

*/

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("各种标准对话框的实例");

    fileBtn = new QPushButton();
    fileBtn->setText("文件标准对话框实例");
    fileLineEdit = new QLineEdit();
    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(fileBtn,0,0);
    mainLayout->addWidget(fileLineEdit,0,1);
    connect(fileBtn,&QPushButton::clicked,this,&Dialog::showFile);

    colorBtn = new QPushButton();
    colorBtn->setText("标准颜色对话框");
    colorFrame = new QFrame();
    colorFrame->setFrameShape(QFrame::Box);
    colorFrame->setAutoFillBackground(true);
    mainLayout->addWidget(colorBtn,1,0);
    mainLayout->addWidget(colorFrame,1,1);
    connect(colorBtn,&QPushButton::clicked,this,&Dialog::showColor);

    fontBtn = new QPushButton();
    fontBtn->setText("标准字体对话框");
    fontLineEdit = new QLineEdit("测试字体");
    mainLayout->addWidget(fontBtn,2,0);
    mainLayout->addWidget(fontLineEdit,2,1);
    connect(fontBtn,&QPushButton::clicked,this,&Dialog::showFont);

    inputBtn = new QPushButton();
    inputBtn->setText("标准输入对话框");
    mainLayout->addWidget(inputBtn,3,0);
    connect(inputBtn,&QPushButton::clicked,this,&Dialog::showInputDlg);

    msgBtn = new QPushButton("标准消息对话框");
    mainLayout->addWidget(msgBtn,3,1);
    connect(msgBtn,&QPushButton::clicked,this,&Dialog::showMsg);
}

Dialog::~Dialog()
{
}

// 就是电脑中打开文件或目录的那样
void Dialog::showFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,"请选择文件！","/","C++ file(*.cpp);;C file(*.c)");
    fileLineEdit->setText(fileName);
}

// 类似ps中那个颜色对话框
void Dialog::showColor()
{
    QColor color = QColorDialog::getColor(Qt::blue,this,"请选择需要的颜色",QColorDialog::DontUseNativeDialog);
    if(color.isValid()){
        colorFrame->setPalette(QPalette(color));
    }
}

void Dialog::showFont()
{
    bool ok;
    QFont fontName = QFontDialog::getFont(&ok,fontLineEdit->font(),this,"请选择要设置的字体");
    if(ok){
        fontLineEdit->setFont(fontName);
    }
}

void Dialog::showInputDlg()
{
    inputDlg = new InputDlg(this);
    inputDlg->show();
}

void Dialog::showMsg()
{
    msgDlg = new MsgBoxDlg(this);
    msgDlg->show();
}



