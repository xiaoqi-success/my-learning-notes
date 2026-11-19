#include "digiclock.h"

// 完成外观的设置和定时器的初始化操作

DigiClock::DigiClock(QWidget *parent)
    : QLCDNumber(parent)
{
    // 窗口无边框与半透明设置
    setWindowFlags(Qt::FramelessWindowHint);
    resize(200,100);
    setWindowOpacity(0.5);// 设置窗体的透明度为0.5，即半透明,值越小越透明
    // LCD显示设置
    setDigitCount(8);// 设置电子时钟显示的位数，默认只显示5位

    // 设置时钟背景
    QPalette p = palette();
    // 设置时钟窗体的背景颜色
    p.setColor(QPalette::Window,Qt::blue);
    p.setColor(QPalette::WindowText,Qt::white);
    setPalette(p);

    QTimer *timer = new QTimer(this);// 定时器对象
    connect(timer,&QTimer::timeout,this,&DigiClock::showTime);
    timer->start(1000);// 以1s为周期启动定时器

    showTime();// 初始的时候显示一次时间

    showColon = true;// 默认显示":"
}

DigiClock::~DigiClock()
{
}

/*
mousePressEvent：鼠标按下事件（重写QLCDNumber自带的鼠标事件）
逻辑：
- 如果按下【鼠标左键】：记录鼠标相对于窗口左上角的偏移量 dragPosition
- 如果按下【鼠标右键】：关闭这个时钟窗口
*/
void DigiClock::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        // globalPos()：鼠标在屏幕上的绝对坐标
        // frameGeometry().topLeft()：窗口左上角在屏幕上的坐标
        // 两者相减 = 鼠标点距离窗口左上角的偏移，拖动的时候要用
        dragPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();// 接收这个事件，不再往下传递
    }
    if(event->button() == Qt::RightButton){
        close();// 右键按下，关闭窗口
    }
}

/*
mouseMoveEvent：鼠标移动事件
event->buttons()：当前按住了哪些鼠标按键（可以同时多个）
判断：是否按住左键
如果按住左键：
    用鼠标当前屏幕坐标 - 刚才记录的偏移量，得到窗口左上角应该放到哪里，调用move移动窗口
*/
void DigiClock::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton){
        move(event->globalPos() - dragPosition);
        event->accept();
    }
}

void DigiClock::showTime()
{
    // 获取当前系统的时间
    QTime time = QTime::currentTime();
    QString text = time.toString("hh:mm:ss");
    // 这个if...else...主要体现在“:”可以动，更灵活
    if(showColon){
        text[2] = ':';
        showColon = false;
    }else{
        text[2] = ' ';
        showColon = true;
    }
    display(text);// QLCDNumber中显示字符串s 所表示的数字的公共函数display(const QString &s)
}

