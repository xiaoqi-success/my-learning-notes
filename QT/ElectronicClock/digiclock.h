#ifndef DIGICLOCK_H
#define DIGICLOCK_H

//#include <QDialog>
#include <QLCDNumber>

#include <QTimer>
#include <QTime>
#include <QLCDNumber>
#include <QPalette>
#include <QMouseEvent>

// 通过实现显示于桌面上并可随意拖曳至桌面任意位置的电子时钟综合实例，
// 实践 QPalette 类、 QTime 类和 mousePressEvent/mouseMoveEvent 类的用法

// 继承QLCDNumber类，该类中重定义了鼠标按下事件和鼠标移动事件以使电子时钟可随意拖拽，同时还定义了相关的槽函数和私有变量
class DigiClock : public QLCDNumber
{
    Q_OBJECT

public:
    DigiClock(QWidget *parent = nullptr);
    ~DigiClock();

protected: // 建议设为 protected，因为这是事件处理函数
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private slots:
    void showTime();// 显示当前的时间

private:
    QPoint dragPosition;// 保存鼠标点相对电子时钟窗体左上角的偏移值
    bool showColon;// 用于显示时间时是否显示“:”
};
#endif // DIGICLOCK_H
