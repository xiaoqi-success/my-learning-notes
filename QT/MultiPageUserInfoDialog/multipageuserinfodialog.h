#ifndef MULTIPAGEUSERINFODIALOG_H
#define MULTIPAGEUSERINFODIALOG_H

#include <QDialog>
#include "baseinfo.h"
#include "contact.h"
#include <detail.h>

#include <QPushButton>
#include <QStackedWidget>
#include <QVBoxLayout>

class MultiPageUserInfoDialog : public QWidget
{
    Q_OBJECT

public:
    MultiPageUserInfoDialog(QWidget *parent = nullptr);
    ~MultiPageUserInfoDialog();

public:
    QStackedWidget *stack;
    QVBoxLayout *rightLayout;
    // 底部按钮
    QPushButton *modifyButton;// 修改
    QPushButton *closeButton;// 关闭
    BaseInfo *baseInfo;
    Contact *contact;
    Detail *detail;

    void closeDialog();

    bool loadStyleSheet(const QString &qssPath);

signals:
    void sigCloseWindow();
};
#endif // MULTIPAGEUSERINFODIALOG_H
