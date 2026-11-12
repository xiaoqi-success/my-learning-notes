#include "msgboxdlg.h"
#include <QMessageBox>

MsgBoxDlg::MsgBoxDlg(QWidget *parent) :QDialog(parent)
{
    tipLabel = new QLabel("请选择一个消息框");
    quesMsg = new QPushButton("QuestionMsg");
    infoMsg = new QPushButton("InformationMsg");
    warnMsg = new QPushButton("WarningMsg");
    critMsg = new QPushButton("CriticalMsg");
    aboutMsg = new QPushButton("AboutMsg");
    aboutQtMsg = new QPushButton("AboutQtMsg");
    mainLayout = new QGridLayout(this);

    mainLayout->addWidget(tipLabel,0,0);
    mainLayout->addWidget(quesMsg,1,0);
    mainLayout->addWidget(infoMsg,1,1);
    mainLayout->addWidget(warnMsg,2,0);
    mainLayout->addWidget(critMsg,2,1);
    mainLayout->addWidget(aboutMsg,3,0);
    mainLayout->addWidget(aboutQtMsg,3,1);

    connect(quesMsg,&QPushButton::clicked,this,&MsgBoxDlg::showQuestionMsg);
    connect(infoMsg,&QPushButton::clicked,this,&MsgBoxDlg::showInformationMsg);
    connect(warnMsg,&QPushButton::clicked,this,&MsgBoxDlg::showWarningMsg);
    connect(critMsg,&QPushButton::clicked,this,&MsgBoxDlg::showCriticalMsg);
    connect(aboutMsg,&QPushButton::clicked,this,&MsgBoxDlg::showAboutMsg);
    connect(aboutQtMsg,&QPushButton::clicked,this,&MsgBoxDlg::showAboutQtMsg);

}

/*
Question 消息框使用 QMessageBox::question() 函数完成，静态函数，弹出【询问】消息框，一般用来询问用户、确认操作
static StandardButton question(QWidget *parent, // 父窗口
            const QString &title,               // 标题
            const QString &text,                // 提示信息
            StandardButtons buttons = StandardButtons(Yes | No), // 标准按钮（比如 QMessageBox::Yes）
            StandardButton defaultButton = NoButton);            // 回车默认操作的按钮
*/
void MsgBoxDlg::showQuestionMsg()
{
    switch (QMessageBox::question(this,"Question消息框","修改完成，是否要结束程序？",
                                  QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes)) {
        case QMessageBox::Yes:
            tipLabel->setText("Question button/Yes");
            break;
        case QMessageBox::No:
            tipLabel->setText("Question button/No");
            break;
        default:
            break;
    }
    return;
}

/*
 * 适用于普通信息的提示
static StandardButton information(QWidget *parent,
            const QString &title,
            const QString &text,
            StandardButtons buttons = Ok,
            StandardButton defaultButton = NoButton);
*/
void MsgBoxDlg::showInformationMsg()
{
    tipLabel->setText("Information Message Box");
    QMessageBox::information(this,"Information消息框","这是Information消息框测试，欢迎您！");
    return;
}

/*
 * 警告提醒
static StandardButton warning(QWidget *parent,
                const QString &title,
                const QString &text, StandardButtons buttons = Ok,
                StandardButton defaultButton = NoButton);
*/
void MsgBoxDlg::showWarningMsg()
{
    tipLabel->setText("Warning Message Box");
    auto ret = QMessageBox::warning(this,"Warning消息框","您修改的内容还未保存，是否要保存对文档的修改？",
                               QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel,QMessageBox::Save);
    if(ret == QMessageBox::Save){
        tipLabel->setText("Warning button/Save");
    }else if(ret == QMessageBox::Discard){
        tipLabel->setText("Warning button/Discard");
    }else if(ret == QMessageBox::Cancel){
        tipLabel->setText("Warning button/Cancel");
    }
    return;
}

/*
 * 错误提示
static StandardButton critical(QWidget *parent,
                const QString &title,
                const QString &text,
                StandardButtons buttons = Ok,
                StandardButton defaultButton = NoButton);
*/
void MsgBoxDlg::showCriticalMsg()
{
    tipLabel->setText("Critical Message Box");
    QMessageBox::critical(this,"Critical消息框","这是一个Critical消息测试框!");
    return;
}

/*
 * 关于信息
    static void about(QWidget *parent, const QString &title, const QString &text);

*/
void MsgBoxDlg::showAboutMsg()
{
    tipLabel->setText("About Message Box");
    QMessageBox::about(this,"About消息框","这是一个About消息测试框");
    return;
}

/*
 * Qt版权信息
    static void aboutQt(QWidget *parent, const QString &title = QString());
*/
void MsgBoxDlg::showAboutQtMsg()
{
    tipLabel->setText("AboutQt Message Box");
    QMessageBox::aboutQt(this,"AboutQt消息框");
    return;
}
