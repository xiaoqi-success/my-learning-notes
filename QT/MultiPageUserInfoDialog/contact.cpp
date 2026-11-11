#include "contact.h"

Contact::Contact(QWidget *parent) : QWidget(parent)
{
    emailLabel = new QLabel("电子邮件:");
    addressLabel = new QLabel("联系地址:");
    postalCodeLabel = new QLabel("邮政编码:");
    mobilePhoneLabel = new QLabel("移动电话");
    messageCheckbox = new QCheckBox("接收留言");
    officeTelephoneLabel = new QLabel("办公电话");

    emailLineEdit = new QLineEdit();
    addressLineEdit = new QLineEdit();
    postalCodeLineEdit = new QLineEdit();
    mobilePhoneLineEdit = new QLineEdit();
    officeTelephoneLineEdit = new QLineEdit();

    mainLayout = new QGridLayout(this);
    mainLayout->setMargin(15);
    mainLayout->setSpacing(10);

    mainLayout->addWidget(emailLabel,0,0);
    mainLayout->addWidget(emailLineEdit,0,1);
    mainLayout->addWidget(addressLabel,1,0);
    mainLayout->addWidget(addressLineEdit,1,1);
    mainLayout->addWidget(postalCodeLabel,2,0);
    mainLayout->addWidget(postalCodeLineEdit,2,1);
    mainLayout->addWidget(mobilePhoneLabel,3,0);
    mainLayout->addWidget(mobilePhoneLineEdit,3,1);
    mainLayout->addWidget(messageCheckbox,3,2);
    mainLayout->addWidget(officeTelephoneLabel,4,0);
    mainLayout->addWidget(officeTelephoneLineEdit,4,1);


}
