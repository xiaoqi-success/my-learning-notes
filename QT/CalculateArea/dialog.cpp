#include "dialog.h"
#include "ui_dialog.h"

// 输入半径计算圆的面积

const static double PI = 3.14;

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}


//void Dialog::on_countButton_clicked()
//{
//    double radius = ui->radiusLineEdit->text().toDouble();
//    double area = radius * radius * PI;
//    ui->areaLabel_2->setText(QString::number(area,'f',2));
//}

// 更严谨点的版本：防止输入非法的字符
void Dialog::on_countButton_clicked()
{
    // 获取输入文本
    QString inputText = ui->radiusLineEdit->text();
    // 判断是否为空
    if(inputText.isEmpty()){
        ui->areaLabel_2->setText("请输入半径！");
        return;
    }
    bool ok;
    // 使用ok来判断转换是否成功
    // 此函数在内部的转换
    // 如果文字是 "2.5"，转换成功，函数不仅返回 2.5 给 radius，还会偷偷跑到那个内存地址，把 ok 改成 true
    // 如果文字是 "abc"，转换失败，函数返回 0.0 给 radius，同时把 ok 改成 false
    double radius = inputText.toDouble(&ok);
    // 如果用户输入了字母等非数字字符
    if(!ok){
        ui->areaLabel_2->setText("请输入有效的数字！");
        return;
    }
    double area = radius * radius * PI;
    ui->areaLabel_2->setText(QString::number(area,'f',2));
}

