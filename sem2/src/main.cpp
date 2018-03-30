#include "view_home.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ViewHome w;
    w.show();

    return a.exec();
}
