#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include "workthread.h"

// 补充：多线程案例：QImage 子线程加载图片，主线程转 QPixmap 展示（嵌入式标准写法）
/*
核心规则（背下来）
- 子线程不能操作 QPixmap
- 子线程只处理 QImage（加载、解码、图像处理）
- 处理完成通过信号槽把 QImage 传到主线程
- 主线程里面：QPixmap::fromImage() 转成 QPixmap 给 label 显示
>
> 场景：加载一张很大的图片，如果主线程直接 load，UI 会卡死，子线程加载就不会卡顿。
*/
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

signals:
    // 新增加载信号
    void startLoad(QString filePath);

private:
    QLabel *showLabel;
    QPushButton *loadBtn;
    QPushButton *scaleBtn;
    QPushButton *drawBtn;
    QPushButton *saveBtn;
    QPushButton *copyBtn;
    QPixmap m_pix;// 保存原图
    // 补充
    WorkThread* m_worker;
    QThread* m_thread;

    QGridLayout *gLayout;
    QVBoxLayout *mainLayout;

    bool m_isLoading;   // 新增：加载标记

private slots:
    void loadClicked();// 加载图片
    void scaleClicked();// 缩放
    void drawClicked();// 在pixmap上绘图
    void saveClicked();// 保存图片
    void copyClicked();// 截取图片

    // 补充：接收子线程传来的图片
    void onImageReady(const QImage &img);
    void onLoadFailed();
};
#endif // WIDGET_H
