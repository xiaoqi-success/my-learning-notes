#ifndef MSGBOXDLG_H
#define MSGBOXDLG_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>

class MsgBoxDlg : public QDialog
{
    Q_OBJECT
public:
    MsgBoxDlg(QWidget* parent = nullptr);

private:
    QPushButton *quesMsg;
    QPushButton *infoMsg;
    QPushButton *warnMsg;
    QPushButton *critMsg;
    QPushButton *aboutMsg;
    QPushButton *aboutQtMsg;
    QLabel *tipLabel;
    QGridLayout *mainLayout;

private slots:
    void showQuestionMsg();
    void showInformationMsg();
    void showWarningMsg();
    void showCriticalMsg();
    void showAboutMsg();
    void showAboutQtMsg();
};

#endif // MSGBOXDLG_H
