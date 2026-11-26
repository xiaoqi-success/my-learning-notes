#include "showwidget.h"

#include <QHBoxLayout>

ShowWidget::ShowWidget(QWidget *parent) : QWidget(parent)
{
    imageLabel = new QLabel();
//    imageLabel->setGeometry(0,0,1302,886);
    imageLabel->setScaledContents(true);// 设置标签是否将内容缩放以填满所有可用空间，默认false不填充
    text = new QTextEdit();
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(imageLabel);
    mainLayout->addWidget(text);
}
