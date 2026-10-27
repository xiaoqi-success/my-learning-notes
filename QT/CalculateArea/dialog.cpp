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


void Dialog::on_countButton_clicked()
{
    double radius = ui->radiusLineEdit->text().toDouble();
    double area = radius * radius * PI;
    ui->areaLabel_2->setText(QString::number(area,'f',2));
}



