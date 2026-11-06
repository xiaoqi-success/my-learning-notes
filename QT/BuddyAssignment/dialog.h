#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

    QLabel *timeLabel;
    QPushButton *startButton;
    QTimer *timer;

private slots:
    void updateTime();
    void toggleTimer();

private:
    Ui::Dialog *ui;
};
#endif // DIALOG_H
