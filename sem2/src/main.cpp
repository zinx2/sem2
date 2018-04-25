//#include "view_home.h"
#include "cs_checktable.h"
#include <QApplication>
#include <QFontDataBase>

#include "cs_selector_part.h"
#include "cs_form_signature.h"
#include "cs_barcoder.h"
#include "cs_form_borrow.h"
#include "cs_alarm.h"
#include "cs_login.h"
#include "view_home.h"
#include "cs_component.h"
#include "cs_form_add.h"
#include "cs_form_borrow.h"
#include "cs_form_return.h"
int main(int argc, char *argv[])
{
    QFontDatabase::addApplicationFont(":/NanumBarunGothic.ttf");
    QApplication a(argc, argv);

	//Barcoder*
	//FormReturn* fr = new FormReturn("QWQWQ", 500, 450);
	//fr->show();
	//FormSignature* sg = new FormSignature(0, 500, 250);
	//sg->show();

	//FormBorrow* fb = new FormBorrow(500, 450);
	//fb->show();

	//FormAdd* fa = new FormAdd(410, 340);
	//fa->show();
    ViewHome w;
    w.show();



	//Model* m = Model::instance();
	//QList<Rent*> list;
	//Rent* r = new Rent();
	//r->setNoAsset("A");

	//Rent* r1 = new Rent();
	//r1->setNoAsset("B");
	//list.append(r);
	//list.append(r1);

	//CPMNTTable* t = new CPMNTTable(0);
	//t->setModel(list);
	//t->show();
	//FormAdd* f = new FormAdd(410, 340);
	//f->show();

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
