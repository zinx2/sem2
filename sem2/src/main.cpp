#include "view_home.h"
#include "cs_checktable.h"
#include <QApplication>
#include <QFontDataBase>
int main(int argc, char *argv[])
{
    QFontDatabase::addApplicationFont(":/NanumBarunGothic.ttf");
    QApplication a(argc, argv);
    ViewHome w;
    w.show();
    return a.exec();
}
