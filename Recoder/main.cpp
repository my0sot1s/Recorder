#include "mainrecoder.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainRecoder w;
    w.show();

    return a.exec();
}
