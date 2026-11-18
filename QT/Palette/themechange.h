#ifndef THEMECHANGE_H
#define THEMECHANGE_H

/*
实现简易的换肤功能：
    界面上有输入框、按钮和标签。
    提供两个按钮：“夜间模式” 和 “日间模式”。
    点击后，通过 QPalette 瞬间改变整个应用（包括输入框、文本和窗口背景）的颜色配置。
    最关键的：我们会用到 QApplication::setPalette()，体会一下什么是全局换肤。
*/

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QPalette>
#include <QStyleFactory>

class ThemeChange : public QWidget
{
    Q_OBJECT

public:
    ThemeChange(QWidget *parent = nullptr);
    ~ThemeChange();
private:
    void applyTheme(const QColor &bjColor,const QColor &textColor,const QColor &baseColor);
private slots:
    void applyLightTheme();
    void applyDarkTheme();
};
#endif // THEMECHANGE_H
