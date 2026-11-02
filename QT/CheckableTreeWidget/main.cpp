#include "checkabletreewidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CheckableTreeWidget w;
    w.show();
    return a.exec();
}
