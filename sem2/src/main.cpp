#include "view_home.h"
#include "cs_checktable.h"
#include <QApplication>
#include <QFontDataBase>

#include "cs_login.h"
#include "cs_join.h"
#include "cs_selector_part.h"
int main(int argc, char *argv[])
{
    QFontDatabase::addApplicationFont(":/NanumBarunGothic.ttf");
    QApplication a(argc, argv);
//    ViewHome w;
//    w.show();

//    CPLogin* login = new CPLogin();
//    login->show();

//    CPJoin* join = new CPJoin();
//    join->show();

    SelectorPart* part = new SelectorPart();
    part->show();

    return a.exec();
}
