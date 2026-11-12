#include "dialog.h"

#include <QFileDialog>
#include <QColorDialog>
#include <QFontDialog>
#include <QFont>
#include <QMessageBox>
#include <QPixMap>

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

    customBtn = new QPushButton("用户自定义消息对话框实例");
    label = new QLabel();
    label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    mainLayout->addWidget(customBtn,4,0);
    mainLayout->addWidget(label,4,1);
    connect(customBtn,&QPushButton::clicked,this,&Dialog::showCustomDlg);
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

void Dialog::showCustomDlg()
{
    label->setText("Custom Message Box");
    QMessageBox customMsgBox;
    customMsgBox.setWindowTitle("用户自定义消息框");// 设置消息框的标题
    // 定义消息框所需要的按钮，由于QMessageBox::standardButtons只提供了常用的一些按钮，并不能满足所有应用的需求
    // 所以QMessageBox类提供了一个addButton()函数来为消息框增加自定义的按钮
    // addButton()函数的第一个参数为按钮显示的名字，第二个参数为按钮类型的描述(ActionRole:点击它通常意味着用户同意了某个操作)
    QPushButton *yesBtn = customMsgBox.addButton("Yes",QMessageBox::ActionRole);
    QPushButton *noBtn = customMsgBox.addButton("No",QMessageBox::ActionRole);
    // 为addButton()函数加入一个标准按钮。消息框将会按调用 addButton()函数的先后顺序在消息框中由左至右地依次插入按钮。
    QPushButton *cancelBtn = customMsgBox.addButton(QMessageBox::Cancel);

//    customMsgBox.setIconPixmap(":/icons/msg.png");// 直接进去会导致图片很大不好看，通过下面的步骤来设置一下即可

    // 1. 加载原图
    QPixmap originalPixmap(":/icons/msg.png");
    // 2. 缩放到 48x48，并保持长宽比，使用平滑缩放
    QPixmap scaledPixmap = originalPixmap.scaled(48, 48, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    // 3. 设置进去
    customMsgBox.setIconPixmap(scaledPixmap);// 直接进去会导致图片很大不好看，通过上面的步骤来设置一下即可

    customMsgBox.setText("测试自定义消息框");
    customMsgBox.exec();// 显示此自定义消息框
    if(customMsgBox.clickedButton() == yesBtn){
        label->setText("Custom Message Box/Yes");
    }
    if(customMsgBox.clickedButton() == noBtn){
        label->setText("Custom Message Box/No");
    }
    if(customMsgBox.clickedButton() == cancelBtn){
        label->setText("Custom Message Box/Cancel");
    }
}



