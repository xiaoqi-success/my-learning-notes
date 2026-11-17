#ifndef COPYWORKER_H
#define COPYWORKER_H

#include <QObject>
#include <QAtomicInt>

// 职责：在子线程里干活，每完成一块发 progressChanged(int)，干完发 finished()

class CopyWorker : public QObject
{
    Q_OBJECT
public:
    explicit CopyWorker(int totalSteps,QObject *parent = nullptr);
    // 取消任务：把取消标记置1，子线程循环检测到非0就停止工作
    void cancel(){
        m_cancel.fetchAndStoreOrdered(1);
    }

signals:
    void progressChanged(int value);
    void finished();
    void canceled();

private:
    int m_totalSteps;
    /*
        QAtomicInt = QAtomicInteger<int>，Qt Core 提供的跨平台原子整型，
        专门用于多线程无锁（lock-free）并发，不需要 QMutex 就能安全做加减、CAS 等操作Qt。
        常用接口：
            QAtomicInt cnt(0);
            cnt.ref();        // +1，返回新值（引用计数专用）
            cnt.deref();      // -1；返回false代表减到0了，可以释放资源
            cnt.fetchAndAddOrdered(1); // 原子+1，返回旧值（最常用）
            cnt.testAndSetOrdered(expected, newValue); // CAS：如果等于expected，就改成newValue，返回是否成功
            cnt.loadRelaxed();// 原子读取
            cnt.storeRelaxed(5);// 原子写入
    */
    // 初始为0表示还在工作
    QAtomicInt m_cancel{0};

public slots:
    void doWork();// 在子线程中执行

};

#endif // COPYWORKER_H
