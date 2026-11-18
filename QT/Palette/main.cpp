#include "themechange.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QApplication::setStyle(QStyleFactory::create("Fusion"));

    ThemeChange w;
    w.show();
    return a.exec();
}
