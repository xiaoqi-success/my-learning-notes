#ifndef MYQQEXAMPLE_H
#define MYQQEXAMPLE_H

#include <QToolBox>
#include <QToolButton>
#include <QStringList>

class MyQQExample : public QToolBox
{
    Q_OBJECT

public:
    MyQQExample(QWidget *parent = nullptr);
    ~MyQQExample();

private:
    // 老方法，如果成员很多，很麻烦
//    QToolButton *toolBtn1_1;
//    QToolButton *toolBtn1_2;
//    QToolButton *toolBtn1_3;
//    QToolButton *toolBtn1_4;

//    QToolButton *toolBtn2_1;
//    QToolButton *toolBtn2_2;
//    QToolButton *toolBtn2_3;

//    QToolButton *toolBtn3_1;
//    QToolButton *toolBtn3_2;

    // 提取出一个通用方法，用来创建单个抽屉页面
    // 避免代码重复（DRY 原则：不要重复自己）
    void createDrawerPage(const QString &title,
                          const QStringList &names,
                          const QStringList &iconPaths);
};
#endif // MYQQEXAMPLE_H
