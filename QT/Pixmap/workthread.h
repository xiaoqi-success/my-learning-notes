#ifndef WORKTHREAD_H
#define WORKTHREAD_H

#include <QObject>

#include <QThread>
#include <QImage>

class WorkThread : public QObject
{
    Q_OBJECT
public:
    explicit WorkThread(QObject *parent = nullptr);

signals:
    // 加载完成，把QImage发出去给主线程
    void imageReady(const QImage &img);
    // 加载失败信号
    void loadFailed();
public slots:
    // 子线程槽函数：加载图片，在子线程中执行
    void loadImageInThread(const QString &filePath);

};

#endif // WORKTHREAD_H
