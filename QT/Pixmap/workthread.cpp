#include "workthread.h"

WorkThread::WorkThread(QObject *parent) : QObject(parent)
{

}

void WorkThread::loadImageInThread(const QString &filePath)
{
    // QImage可以在子线程加载
    QImage img(filePath);
    if(img.isNull()){
        emit loadFailed();
        return;
    }
    // 发射信号，把图片传给主线程
    emit imageReady(img);
}
