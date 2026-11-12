#include "inputdlg.h"

#include <QInputDialog>

InputDlg::InputDlg(QWidget* parent) :QDialog(parent)
{
    setWindowTitle("标准输入对话框实例");
    nameLabel1 = new QLabel("姓名:");
    nameLabel2 = new QLabel("张三");
    nameLabel2->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    nameBtn = new QPushButton("修改姓名");
    sexLabel1 = new QLabel("性别:");
    sexLabel2 = new QLabel("男");
    sexLabel2->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    sexBtn = new QPushButton("修改性别");
    ageLabel1 = new QLabel("年龄:");
    ageLabel2 = new QLabel("21");
    ageLabel2->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    ageBtn = new QPushButton("修改年龄");
    scoreLabel1 = new QLabel("成绩");
    scoreLabel2 = new QLabel("80");
    scoreLabel2->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    scoreBtn = new QPushButton("修改成绩");
    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(nameLabel1,0,0);
    mainLayout->addWidget(nameLabel2,0,1);
    mainLayout->addWidget(nameBtn,0,2);
    mainLayout->addWidget(sexLabel1,1,0);
    mainLayout->addWidget(sexLabel2,1,1);
    mainLayout->addWidget(sexBtn,1,2);
    mainLayout->addWidget(ageLabel1,2,0);
    mainLayout->addWidget(ageLabel2,2,1);
    mainLayout->addWidget(ageBtn,2,2);
    mainLayout->addWidget(scoreLabel1,3,0);
    mainLayout->addWidget(scoreLabel2,3,1);
    mainLayout->addWidget(scoreBtn,3,2);
    // 设置布局内部边距，布局里所有控件，和布局自身边框之间留出空白(左、上、右、下）
    mainLayout->setContentsMargins(10,10,10,10);

    connect(nameBtn,&QPushButton::clicked,this,&InputDlg::ChangeName);
    connect(sexBtn,&QPushButton::clicked,this,&InputDlg::ChangeSex);
    connect(ageBtn,&QPushButton::clicked,this,&InputDlg::ChangeAge);
    connect(scoreBtn,&QPushButton::clicked,this,&InputDlg::ChangeScore);
}

//QInputDialog::getText
/*
static QString getText(QWidget *parent, // 父窗口
            const QString &title,       // 标题
            const QString &label,       // 标签提示
            QLineEdit::EchoMode echo = QLineEdit::Normal,  // 指定标准输入对话框中QLineEdit控件的输入模式
            const QString &text = QString(),  // 标准字符串输入对话框弹出时QLineEdit控件中默认出现的文字
// 指示标准输入对话框的哪个按钮被触发，若为 true, 则表示用户单击了 "OK" (确定）按钮；若为 false,则表示用户单击了 "Cancle" (取消）按钮
            bool *ok = nullptr,
            Qt::WindowFlags flags = Qt::WindowFlags(),  // 指明标准输入对话框的窗体标识
            Qt::InputMethodHints inputMethodHints = Qt::ImhNone);
*/
void InputDlg::ChangeName()
{
    bool ok;
    QString newName = QInputDialog::getText(this,"更改姓名","新名字",QLineEdit::Normal,nameLabel2->text(),&ok);
    if(ok && !newName.isEmpty()){
        nameLabel2->setText(newName);
    }
}

/*
static QString getItem(QWidget *parent,     // 父窗口
    const QString &title,           // 窗口标题
    const QString &label,           // 对话框内提示文字
    const QStringList &items,       // 下拉列表里的所有选项字符串合集
    int current = 0,                // 默认选中的下标，默认0（第一个）
    bool editable = true,           // 下拉框是否允许手动输入文字；true=可编辑，false=只能下拉选择不能自己输
    bool *ok = nullptr,             // true 用户点确定，返回值有效；false 用户点取消，返回值无意义
    Qt::WindowFlags flags = Qt::WindowFlags(), // 窗口标志，控制对话框样式，例如置顶、有无最大化按钮等
    Qt::InputMethodHints inputMethodHints = Qt::ImhNone); // 输入法提示标记，用来告诉输入法该输入什么类型（数字、密码等），默认无特殊提示
*/
void InputDlg::ChangeSex()
{
    bool ok;
    QStringList items = {"男","女","保密"};
    QString newSex = QInputDialog::getItem(this,"请选择您的性别","实际性别",items,2,false,&ok);
    if(ok && !newSex.isEmpty()){
        sexLabel2->setText(newSex);
    }
}

/*
static int getInt(QWidget *parent,  // 父窗口
        const QString &title,       // 窗口标题
        const QString &label,       // 提示信息
        int value = 0,              // 指定标准输入对话框中 QSpinBox 控件的默认显示值
        int minValue = -2147483647, // 指定 QSpinBox 控件的数值范围
        int maxValue = 2147483647,
        int step = 1,               // 指定 QSpinBox 控件的步进值,就是每次增加几个
        bool *ok = nullptr,         // 状态
        Qt::WindowFlags flags = Qt::WindowFlags()); // 指明标准输入对话框的窗口标识

*/
void InputDlg::ChangeAge()
{
    bool ok;
    int newAge = QInputDialog::getInt(this,"输入年龄","年龄范围0-150",ageLabel2->text().toInt(),0,150,1,&ok);
    if(ok){
        ageLabel2->setText(QString("%1").arg(newAge));
    }
}

/*
static double getDouble(QWidget *parent,    // 父窗口
        const QString &title,               // 标题
        const QString &label,               // 提示信息
        double value = 0,                   // 默认设置
        double minValue = -2147483647,      // 范围
        double maxValue = 2147483647,
        int decimals = 1,                   // 小数位数
        bool *ok = nullptr,                 // 状态
        Qt::WindowFlags flags = Qt::WindowFlags()); // 窗口标识
*/
void InputDlg::ChangeScore()
{
    bool ok;
    double newScore = QInputDialog::getDouble(this,"输入新成绩","新成绩：",scoreLabel2->text().toDouble(),0.00,100.00,2,&ok);
    if(ok){
        scoreLabel2->setText(QString("%1").arg(newScore));
    }
}
