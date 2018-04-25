#include "view_home.h"

ViewHome::ViewHome(QWidget* parent) : Page(1200, 800, new QVBoxLayout, parent)
{
	setWindowTitle(kr("온라인평생교육원 자산 관리 시스템"));
}
ViewHome::~ViewHome()
{

}