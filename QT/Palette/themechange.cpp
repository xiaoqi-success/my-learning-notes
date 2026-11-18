#include "themechange.h"

#include <QApplication>

ThemeChange::ThemeChange(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("简易换肤演示（QPalette）");
    resize(800,400);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("用户名:"));
    layout->addWidget(new QLineEdit("请输入用户名"));
    layout->addWidget(new QLabel("备注："));
    layout->addWidget(new QTextEdit("这是一段多行文本..."));
    QHBoxLayout *btnLayout = new QHBoxLayout();
    QPushButton *btnLight = new QPushButton("☀️ 日间模式");
    QPushButton *btnDark = new QPushButton("🌙 夜间模式");
    btnLayout->addWidget(btnLight);
    btnLayout->addWidget(btnDark);
    layout->addLayout(btnLayout);

    connect(btnLight, &QPushButton::clicked, this, &ThemeChange::applyLightTheme);
    connect(btnDark, &QPushButton::clicked, this, &ThemeChange::applyDarkTheme);
}

ThemeChange::~ThemeChange()
{
}

void ThemeChange::applyTheme(const QColor &bgColor, const QColor &textColor, const QColor &baseColor)
{
    // 核心逻辑：获取QApplication(整个程序)的调色板
    QPalette appPal = qApp->palette();
    // 设置窗口背景和文字
    appPal.setColor(QPalette::Window,bgColor);
    appPal.setColor(QPalette::WindowText,textColor);
    // 设置输入框(QLineEdit/QTextEdit)的背景和颜色
    appPal.setColor(QPalette::Base,baseColor);
    appPal.setColor(QPalette::Text,textColor);
    // 设置按钮的背景和颜色
    appPal.setColor(QPalette::Button,bgColor);
    appPal.setColor(QPalette::ButtonText,textColor);

    // 应用：把调色板应用到全局，所有窗口和控件都会跟着变化
    qApp->setPalette(appPal);
}

void ThemeChange::applyLightTheme()
{
    // 日间模式
    applyTheme(Qt::white,Qt::black,Qt::white);
}

void ThemeChange::applyDarkTheme()
{
    applyTheme(QColor(53, 53, 53), Qt::white, QColor(30, 30, 30));
}

