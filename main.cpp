#include "program.h"
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Program w;
    w.show();
    return a.exec();
}
