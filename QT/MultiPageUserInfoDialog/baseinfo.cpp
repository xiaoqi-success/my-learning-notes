#include "baseinfo.h"

BaseInfo::BaseInfo(QWidget *parent) : QWidget(parent)
{
    // 左侧
    userNameLabel = new QLabel("用户名:");
    userNameLineEdit = new QLineEdit();
    userNameLineEdit->setPlaceholderText("请输入用户名");
    nameLabel = new QLabel("姓名:");
    nameLineEdit = new QLineEdit();
    sexLabel = new QLabel("性别:");
    sexComboBox = new QComboBox();
    sexComboBox->addItem("男");
    sexComboBox->addItem("女");
    sexComboBox->setCurrentIndex(1);// 设置默认显示"女"这个选项
    departmentLabel = new QLabel("部门");
    departmentTextEdit = new QTextEdit();
    ageLabel = new QLabel("年龄:");
    ageLineEdit = new QLineEdit();
    noteEdit = new QLineEdit("备注:");
    noteEdit->setFrame(QFrame::Panel | QFrame::Sunken);
    // 右边分割窗口左边使用网格布局
    leftLayout = new QGridLayout();
    leftLayout->addWidget(userNameLabel,0,0);
    leftLayout->addWidget(userNameLineEdit,0,1);
    leftLayout->addWidget(nameLabel,1,0);
    leftLayout->addWidget(nameLineEdit,1,1);
    leftLayout->addWidget(sexLabel,2,0);
    leftLayout->addWidget(sexComboBox,2,1);
    leftLayout->addWidget(departmentLabel,3,0);
    leftLayout->addWidget(departmentTextEdit,3,1);
    leftLayout->addWidget(ageLabel,4,0);
    leftLayout->addWidget(ageLineEdit,4,1);
    leftLayout->addWidget(noteEdit,5,0,1,2);
    // 占用比1:3
    leftLayout->setColumnStretch(0,1);
    leftLayout->setColumnStretch(1,3);
    // 右上角
    headLabel = new QLabel("头像");
    headIconLabel = new QLabel();
    QPixmap icon(":/Icons/usernfo.png");
    headIconLabel->setPixmap(icon);
    headIconLabel->resize(icon.width(),icon.height());
    updateHeadButton = new QPushButton("更新");
    topRightLayout = new QHBoxLayout();
    topRightLayout->setSpacing(20);
    topRightLayout->addWidget(headLabel);
    topRightLayout->addWidget(headIconLabel);
    topRightLayout->addWidget(updateHeadButton);
    // 右下角
    introductionLabel = new QLabel("个人说明:");
    introductionTextEdit = new QTextEdit();
    rightLayout = new QVBoxLayout();
    rightLayout->setMargin(10);

    rightLayout->addLayout(topRightLayout);
    rightLayout->addWidget(introductionLabel);
    rightLayout->addWidget(introductionTextEdit);

    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->setMargin(15);
    mainLayout->setSpacing(10);
    mainLayout->addLayout(leftLayout,0,0);
    mainLayout->addLayout(rightLayout,0,1);
    // 不设置固定大小了
//    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
}
