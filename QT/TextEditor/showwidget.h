#ifndef SHOWWIDGET_H
#define SHOWWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QImage>
#include <QTextEdit>
#include <QPushButton>

// 该工程提供主要显示文本编辑函数所在的文件

class ShowWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ShowWidget(QWidget *parent = nullptr);

    QImage img;
    QLabel *imageLabel;// 显示图像
    QTextEdit *text;// 显示文件内容

    QPushButton *changeImgBtn;
    QPushButton *nextImgBtn;
    QPushButton *prevImgBtn;
    QPushButton *grayImgBtn;
    QPushButton *inverseImgBtn;
    QPushButton *saveImgBtn;

signals:

};

#endif // SHOWWIDGET_H
