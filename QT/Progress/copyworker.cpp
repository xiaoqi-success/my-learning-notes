#include "copyworker.h"

#include <QThread>

CopyWorker::CopyWorker(int totalSteps,QObject *parent) : QObject(parent),m_totalSteps(totalSteps)
{

}

void CopyWorker::doWork()
{
    // 每次启动先重置取消标记！很重要，要不然上一次取消之后永远取消了
    m_cancel.fetchAndStoreOrdered(0);
    for(int i = 0;i <= m_totalSteps;++i){
        // m_cancel的值如果为真的话说明关闭了
        if(m_cancel.load()){
            emit canceled();
            return;
        }
        QThread::msleep(50);
        emit progressChanged(i);
    }
    emit finished();
}
