//#include "view_home.h"
#include "cs_checktable.h"
#include <QApplication>
#include <QFontDataBase>

#include "cs_selector_part.h"
#include "cs_barcoder.h"
#include "cs_form_borrow.h"
#include "cs_alarm.h"
#include "cs_login.h"
#include "view_home.h"

int main(int argc, char *argv[])
{
    QFontDatabase::addApplicationFont(":/NanumBarunGothic.ttf");
    QApplication a(argc, argv);
    ViewHome w;
    w.show();
	//CPLogin* m_login = new CPLogin();
	//m_login->show();
	//FormBorrow* f = new FormBorrow("대출하기", 500, 540);
	//f->show();
	//Barcoder* b = new Barcoder(kr("대출/반납하기"), 520, 230);
	//b->show();
    /*CPLogin* login = new CPLogin(); 
    login->show();*/

    /*CPJoin* join = new CPJoin();
    join->show();*/

    //SelectorPart* part = new SelectorPart(kr("부서찾기"), 400, 500);
    //part->show();

    return a.exec();
}