#include "showwidget.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QToolButton>
#include <QGridLayout>

ShowWidget::ShowWidget(QWidget *parent) : QWidget(parent)
{
    imageLabel = new QLabel();
    imageLabel->setScaledContents(true);// 设置标签是否将内容缩放以填满所有可用空间，默认false不填充
    text = new QTextEdit();
    changeImgBtn = new QPushButton("更改图片");
    nextImgBtn = new QPushButton("下一张");
    prevImgBtn = new QPushButton("上一张");
    grayImgBtn = new QPushButton("灰度处理");
    inverseImgBtn = new QPushButton("反色处理");
    saveImgBtn = new QPushButton("保存图片");

    QGridLayout *btnLayout = new QGridLayout();
    btnLayout->addWidget(prevImgBtn,0,0);
    btnLayout->addWidget(changeImgBtn,0,1);
    btnLayout->addWidget(nextImgBtn,0,2);
    btnLayout->addWidget(grayImgBtn,1,0);
    btnLayout->addWidget(saveImgBtn,1,1);
    btnLayout->addWidget(inverseImgBtn,1,2);

    QVBoxLayout *leftLayout = new QVBoxLayout();
    leftLayout->addStretch();
    leftLayout->addWidget(imageLabel);
    leftLayout->addStretch();
    leftLayout->addLayout(btnLayout);

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
//    mainLayout->addWidget(imageLabel);
    mainLayout->addLayout(leftLayout);
    mainLayout->addWidget(text);
}
