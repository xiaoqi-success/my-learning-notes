#ifndef DETAIL_H
#define DETAIL_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QTextEdit>
#include <QGridLayout>

class Detail : public QWidget
{
    Q_OBJECT
public:
    explicit Detail(QWidget *parent = nullptr);

signals:

public:
    QLabel *countryLabel;
    QLabel *provenceLabel;
    QLabel *cityLabel;
    QLabel *personalStateLabel;
    QComboBox *countryComboBox;
    QComboBox *provenceComboBox;
    QLineEdit *cityLineEdit;
    QTextEdit *perStateTextEdit;

    QGridLayout *mainLayout;

private slots:
    void onCountryChanged(const QString &countryName);

};

#endif // DETAIL_H
