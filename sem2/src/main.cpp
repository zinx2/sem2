#include "view_home.h"
#include <QApplication>
#include <QFontDataBase>
int main(int argc, char *argv[])
{
	QFontDatabase::addApplicationFont(":/fonts/fonts/NanumBarunGothic.ttf");
	QFontDatabase::addApplicationFont(":/fonts/fonts/NanumBarunGothicBold.ttf");
    QApplication a(argc, argv);
    ViewHome w;
    w.show();

    return a.exec();
}
