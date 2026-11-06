#include "dialog.h"
#include "ui_dialog.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDateTime>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
//    ui->setupUi(this);

    setWindowTitle("数字闹钟（伙伴编辑模式）");
    resize(300,150);

    // 1.创建时间标签
    timeLabel = new QLabel("00:00:00",this);
    QFont font = timeLabel->font();
    font.setPointSize(30);
    timeLabel->setFont(font);
    timeLabel->setAlignment(Qt::AlignCenter);

    // 2.创建带有快捷键提示的标签（注意这里的&S）
    QLabel *tipLabel = new QLabel("开始计时(&S)",this);

    // 3.创建按钮
    startButton = new QPushButton("开始计时",this);

    // 核心：用代码设置伙伴关系，用于当用户按下Alt + S 时，相当于点击了startButton按钮
    tipLabel->setBuddy(startButton);

    // 布局设置
    QHBoxLayout *hLayout = new QHBoxLayout();
    QVBoxLayout *vLayout = new QVBoxLayout(this);
    hLayout->addWidget(tipLabel);
    hLayout->addWidget(startButton);
    vLayout->addWidget(timeLabel);
    vLayout->addLayout(hLayout);

    timer = new QTimer(this);
    timer->setInterval(2000);

    connect(timer,&QTimer::timeout,this,&Dialog::updateTime);
    connect(startButton,&QPushButton::clicked,this,&Dialog::toggleTimer);

    // 启动时立即刷新一次时间
    updateTime();

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::updateTime()
{
    QDateTime current = QDateTime::currentDateTime();
    timeLabel->setText(current.toString("HH:mm:ss"));
}

// 控制启停
void Dialog::toggleTimer()
{
    if(timer->isActive()){
        timer->stop();
        startButton->setText("继续计时");
        // 暂停变红
        startButton->setStyleSheet("font-size:40px;background-color:#E81123;color:white;border-radius:5px;");
    }else{
        timer->start();
        startButton->setText("暂停计时");
        // 开始变蓝
        startButton->setStyleSheet("font-size:40px; background-color:#0078D7;color:white;border-radius:5px;");
    }
}

