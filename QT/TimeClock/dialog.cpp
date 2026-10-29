#include "dialog.h"

#include <QVBoxLayout>
#include <QDateTime>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("数字闹钟");
    resize(300,150);
    timeLabel = new QLabel("00:00:00",this);
    dateLabel = new QLabel("0000-00-00",this);
    // 字体大一点，居中显示
    QFont font = timeLabel->font();
    font.setPointSize(30);
    timeLabel->setFont(font);
    timeLabel->setAlignment(Qt::AlignCenter);
    QFont font1 = dateLabel->font();
    font1.setPointSize(30);
    dateLabel->setFont(font1);
    dateLabel->setAlignment(Qt::AlignCenter);

    startBtn = new QPushButton("开始计时",this);

    // 初始化定时器
    timer = new QTimer(this);
    timer->setInterval(1000);// 定时周期为1s

    // 布局设置
    QVBoxLayout *vLayout = new QVBoxLayout(this);
    vLayout->addWidget(dateLabel);
    vLayout->addWidget(timeLabel);
    vLayout->addWidget(startBtn);

    // 信号与槽的连接
    // 把定时器的 timeout 信号，连接到 updateTime 函数
    connect(timer,&QTimer::timeout,this,&Dialog::updateTime);
    connect(startBtn,&QPushButton::clicked,this,&Dialog::toggleTimer);

    // 启动时更新一次时间
    updateTime();
}

Dialog::~Dialog()
{
}

void Dialog::updateTime()
{
    QDateTime current = QDateTime::currentDateTime();
    // 格式化输出：HH代表24小时制，mm:分，ss秒
    QString dateStr = current.toString("yyyy-MM-dd");
    QString timeStr = current.toString("HH:mm:ss");
    // 显示在标签中
    dateLabel->setText(dateStr);
    timeLabel->setText(timeStr);
}

// 控制定时器的启动和停止
void Dialog::toggleTimer()
{
    if(timer->isActive()){
        // 如果正在运行，就停止
        timer->stop();
        startBtn->setText("开始计时");
    }else{
        // 如果停止了就启动
        timer->start();
        startBtn->setText("停止计时");
    }
}

