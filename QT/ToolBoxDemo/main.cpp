#include "myqqexample.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyQQExample w;
    w.show();
    return a.exec();
}
