#ifndef CONTACT_H
#define CONTACT_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QCheckBox>

class Contact : public QWidget
{
    Q_OBJECT
public:
    explicit Contact(QWidget *parent = nullptr);

signals:

public:
    QLabel *emailLabel;
    QLabel *addressLabel;
    QLabel *postalCodeLabel;
    QLabel *mobilePhoneLabel;
    QLabel *officeTelephoneLabel;
    QCheckBox *messageCheckbox;

    QLineEdit *emailLineEdit;
    QLineEdit *addressLineEdit;
    QLineEdit *postalCodeLineEdit;
    QLineEdit *mobilePhoneLineEdit;
    QLineEdit *officeTelephoneLineEdit;

    QGridLayout *mainLayout;

};

#endif // CONTACT_H
