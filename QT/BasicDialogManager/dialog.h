#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QFrame>

#include "inputdlg.h"
#include "msgboxdlg.h"

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    QGridLayout *mainLayout;

    QPushButton *fileBtn;
    QLineEdit *fileLineEdit;

    QPushButton *colorBtn;
    QFrame *colorFrame;

    QPushButton *fontBtn;
    QLineEdit *fontLineEdit;

    QPushButton *inputBtn;
    InputDlg *inputDlg;

    QPushButton *msgBtn;
    MsgBoxDlg *msgDlg;


private slots:
    void showFile();
    void showColor();
    void showFont();
    void showInputDlg();
    void showMsg();
};
#endif // DIALOG_H
