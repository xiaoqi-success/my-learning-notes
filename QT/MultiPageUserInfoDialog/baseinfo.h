#ifndef BASEINFO_H
#define BASEINFO_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QTextEdit>
#include <QPushButton>
#include <QGridLayout>

class BaseInfo : public QWidget
{
    Q_OBJECT
public:
    explicit BaseInfo(QWidget *parent = nullptr);

signals:

public:
    // 左侧
    QLabel *userNameLabel;
    QLineEdit *userNameLineEdit;
    QLabel *nameLabel;
    QLineEdit *nameLineEdit;
    QLabel *sexLabel;
    QComboBox *sexComboBox;
    QLabel *departmentLabel;
    QTextEdit *departmentTextEdit;
    QLabel *ageLabel;
    QLineEdit *ageLineEdit;
    QLineEdit *noteEdit;
    QGridLayout *leftLayout;
    // 右侧
    QLabel *headLabel;// 头像文字
    QLabel *headIconLabel;// 头像图片
    QPushButton *updateHeadButton;
    QHBoxLayout *topRightLayout;
    QLabel *introductionLabel;
    QTextEdit *introductionTextEdit;
    QVBoxLayout *rightLayout;

};

#endif // BASEINFO_H
