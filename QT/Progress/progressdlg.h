#ifndef PROGRESSDLG_H
#define PROGRESSDLG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QGridLayout>
#include <QProgressBar>
#include <QProgressDialog>

#include <QThread>
#include "copyworker.h"

// 主窗口职责：连信号到 QProgressBar/QProgressDialog，点"取消"时置标志位

class ProgressDlg : public QDialog
{
    Q_OBJECT

public:
    ProgressDlg(QWidget *parent = nullptr);
    ~ProgressDlg();

private:
    QLabel *fileNumLabel;// 文件数目
    QLineEdit *fileNumEdit;
    QLabel *displayTypeLabel;// 显示类型
    QComboBox *displayTypeBox;
    QProgressBar *proBar;// 进度条
    QPushButton *startBtn;// 开始按钮
    QPushButton *cancelBtn;
    QGridLayout *mainLayout;

    QThread *m_thread = nullptr;
    CopyWorker *m_worker = nullptr;
    QProgressDialog *m_progressDlg = nullptr;

private slots:
    void startWork();
    void onProgress(int value);
    void onFinished();
    void onCanceled();

};
#endif // PROGRESSDLG_H
