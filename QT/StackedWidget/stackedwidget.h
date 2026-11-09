#ifndef STACKEDWIDGET_H
#define STACKEDWIDGET_H

#include <QDialog>
#include <QListWidget>
#include <QStackedWidget>
#include <QLabel>

class StackedWidget : public QDialog
{
    Q_OBJECT

public:
    StackedWidget(QWidget *parent = nullptr);
    ~StackedWidget();

private:
    QListWidget *list;
    QStackedWidget *stack;
    QLabel *label1;
    QLabel *label2;
    QLabel *label3;

};
#endif // STACKEDWIDGET_H
