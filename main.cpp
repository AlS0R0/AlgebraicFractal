#include "fractalwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FractalWidget w;
    w.show();
    return QApplication::exec();
}
