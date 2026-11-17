#include "progressdlg.h"

#include <QDebug>

ProgressDlg::ProgressDlg(QWidget *parent)
    : QDialog(parent)
{
//    QWidget *page = new QWidget();
    fileNumLabel = new QLabel("文件数目：",this);
    fileNumEdit = new QLineEdit(this);
    displayTypeLabel = new QLabel("显示类型：",this);
    displayTypeBox = new QComboBox(this);
    displayTypeBox->addItem("progressBar");
    displayTypeBox->addItem("progressDialog");

    proBar = new QProgressBar(this);
//    proBar->setMinimum(0);// 设置步数最小值
//    proBar->setMaximum(100);
    proBar->setRange(0,100);
    proBar->setValue(0);// 当前步数通过setValue() 设置
//    proBar->reset();// 使用reset() 可将进度条重置为起始位置

    startBtn = new QPushButton("开始",this);
    cancelBtn = new QPushButton("取消", this);

    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(fileNumLabel,0,0);
    mainLayout->addWidget(fileNumEdit,0,1);
    mainLayout->addWidget(displayTypeLabel,1,0);
    mainLayout->addWidget(displayTypeBox,1,1);
    mainLayout->addWidget(proBar,2,0,1,0);
    mainLayout->addWidget(startBtn,3,0);
    mainLayout->addWidget(cancelBtn,3,1);

    connect(startBtn,&QPushButton::clicked,this,&ProgressDlg::startWork);
    connect(cancelBtn,&QPushButton::clicked,this,[this](){
        if(m_worker){
            m_worker->cancel();
        }
    });
}

ProgressDlg::~ProgressDlg()
{
    if(m_thread){
        m_thread->quit();
        m_thread->wait();
    }
}

// 点击按钮来更新进度条的值
void ProgressDlg::startWork()
{
    // 如果线程已经存在（任务正在跑），直接 return，不往下执行，防止重复点击开始按钮
    if(m_thread){
        return;
    }

    bool ok;
    int num = fileNumEdit->text().toInt(&ok);
    if(!ok || num <= 0){
        return;
    }
    proBar->setRange(0, num);
    proBar->setValue(0);
    // 禁用开始按钮，防止任务运行期间重复点击
    startBtn->setEnabled(false);

    m_thread = new QThread(this);
    m_worker = new CopyWorker(num);
    m_worker->moveToThread(m_thread);// 移动到子线程中执行

    // 线程启动之后自动调用doWork（doWork跑在子线程）
    connect(m_thread,&QThread::started,m_worker,&CopyWorker::doWork);
    // 子线程推送进度 → UI更新
    connect(m_worker,&CopyWorker::progressChanged,this,&ProgressDlg::onProgress);
    connect(m_worker,&CopyWorker::finished,this,&ProgressDlg::onFinished);
    connect(m_worker,&CopyWorker::canceled,this,&ProgressDlg::onCanceled);
    // 正常完成、用户取消，都通知线程退出
    connect(m_worker,&CopyWorker::finished,m_thread,&QThread::quit);
    connect(m_worker,&CopyWorker::canceled,m_thread,&QThread::quit);
    // 线程结束后自动释放worker，防止内存泄漏
    connect(m_thread,&QThread::finished,m_worker,&QObject::deleteLater);

    // 判断显示模式
    // 采用进度条的方式显示进度
    if(displayTypeBox->currentIndex() == 0){
        proBar->setRange(0,num);
        proBar->setValue(0);
    }else if(displayTypeBox->currentIndex() == 1){
        // 创建一个进度对话框
        m_progressDlg = new QProgressDialog(this);
        m_progressDlg->setRange(0,num);
        // 设置进度对话框采用模态方法进行显示，即在显示进度的同时，其他窗口将不响应输入信号
        m_progressDlg->setWindowModality(Qt::WindowModal);
        // 设置进度对话框出现等待的时间
        // 这个要注意一下，默认是4000ms
        // 任务很快跑完（比如一共只需要 2 秒）弹窗来不及显示，直接就结束，你感觉：好像直接消失、没出现过
        // 任务跑得慢（超过 4 秒）弹窗正常弹出来，进度走完之后，它不会自己关！会停在那里，卡在屏幕上
        m_progressDlg->setMinimumDuration(0);
        m_progressDlg->setWindowTitle("请等待...");
        m_progressDlg->setLabelText("Copying...");// 设置进度对话框的显示文字信息。
        m_progressDlg->setCancelButtonText("取消");// 进度对话框的默认显示文字为Cancel，可以更改
        connect(m_progressDlg,&QProgressDialog::canceled,this,[this](){
           if(m_worker){
               m_worker->cancel();
           }
        });
    }
    m_thread->start();// 启动线程
}

// 收到进度更新信号
void ProgressDlg::onProgress(int value)
{
    qDebug() << "收到进度：" << value;
    if(displayTypeBox->currentIndex() == 0){
        proBar->setValue(value);
    }else{
        if(m_progressDlg){
            m_progressDlg->setValue(value);
        }
    }
}

// 任务正常完成
void ProgressDlg::onFinished()
{
    startBtn->setEnabled(true);
    if(m_progressDlg){
        m_progressDlg->close();
        m_progressDlg->deleteLater();
        m_progressDlg = nullptr;
    }
    m_thread->deleteLater();
    m_thread = nullptr;
    m_worker = nullptr;
}
// 任务被取消
void ProgressDlg::onCanceled()
{
    startBtn->setEnabled(true);
    proBar->setValue(0);
    if(m_progressDlg){
        m_progressDlg->close();
        m_progressDlg->deleteLater();
        m_progressDlg = nullptr;
    }
    m_thread->deleteLater();
    m_thread = nullptr;
    m_worker = nullptr;
}

