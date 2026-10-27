#include "dialog.h"

#include <QGridLayout> // 表格布局的头文件
#include <QDebug>

const static double PI = 3.14;

// 通过编写代码来实现计算圆面积的功能

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    this->setFixedSize(600,300);

    radiusLabel = new QLabel("半径",this);
    //    radiusLabel->setText("半径");
    radiusLineEdit = new QLineEdit(this);
    areaLabel = new QLabel("面积",this);
    areaResultLabel = new QLabel(this);
    // 计算的结果文字靠左，但在垂直方向上居中
    areaResultLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    countButton = new QPushButton("计算面积",this);
    countButton->setFixedSize(100,40);

    // 使用表格布局将各个组件放进去
    QGridLayout *gLayout = new QGridLayout(this);
    gLayout->addWidget(radiusLabel,0,0);
    gLayout->addWidget(radiusLineEdit,0,1);
    gLayout->addWidget(areaLabel,1,0);
    gLayout->addWidget(areaResultLabel,1,1);
    // 按钮横跨两列，放在第3行，居中对齐
    gLayout->addWidget(countButton,2,0,1,2,Qt::AlignCenter);

    connect(countButton,&QPushButton::clicked,this,&Dialog::showArea);

}

Dialog::~Dialog()
{
}

void Dialog::showArea()
{
    bool ok;
    // 获取输入的文本
    QString inputText = radiusLineEdit->text();
    // 判断是否为空
    if(inputText.isEmpty()){
        areaResultLabel->setText("请输入半径！");
        return;
    }
    // 判断输入的是否为非数字字符
    double result = inputText.toDouble(&ok);
    if(!ok){
        areaResultLabel->setText("请输入有效数字！");
        return;
    }
    if(result < 0){
        areaResultLabel->setText("半径不能为负数！");
        return;
    }
    double area = result * result * PI;
    areaResultLabel->setText(QString::number(area,'f',2));
//    qDebug() << "半径：" << result << "面积：" << area;
}

