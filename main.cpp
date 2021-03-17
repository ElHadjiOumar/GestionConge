#include "flowcontroller.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    FlowController fc;
    fc.exec();

    return a.exec();
}
