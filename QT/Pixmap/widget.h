#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QLabel *showLabel;
    QPushButton *loadBtn;
    QPushButton *scaleBtn;
    QPushButton *drawBtn;
    QPushButton *saveBtn;
    QPushButton *copyBtn;
    QPixmap m_pix;// 保存原图

    QGridLayout *gLayout;
    QVBoxLayout *mainLayout;

private slots:
    void loadClicked();// 加载图片
    void scaleClicked();// 缩放
    void drawClicked();// 在pixmap上绘图
    void saveClicked();// 保存图片
    void copyClicked();// 截取图片
};
#endif // WIDGET_H
