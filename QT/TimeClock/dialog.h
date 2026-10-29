#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

#include <QLabel>
#include <QPushButton>
#include <QTimer>

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    QLabel *dateLabel;// 显示日期的标签
    QLabel *timeLabel;// 显示时间的标签
    QPushButton *startBtn;// 开始/停止按钮
    QTimer *timer;      // 定时器对象

private slots:
    void updateTime();// 更新显示的时间
    void toggleTimer();// 控制定时器的开关
};
#endif // DIALOG_H
