#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

#include <QLabel>
#include <QLineEdit>
#include<QPushButton>

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    QLabel *radiusLabel;// 半径label
    QLineEdit *radiusLineEdit;// 半径输入框
    QLabel *areaLabel;// 面积label
    QLabel *areaResultLabel;// 计算得到的面积结果
    QPushButton *countButton;// 计算按钮

private slots:
    void showArea();

};
#endif // DIALOG_H
