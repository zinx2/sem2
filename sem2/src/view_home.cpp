#include "view_home.h"
#include "cs_qheader.h"
ViewHome::ViewHome(QWidget *parent)
    : QWidget(parent)
{
	m_style = Style::instance()->main();
	m_styleHeader = m_style->header();
	m_styleFooter = m_style->footer();
	m_styleBody = m_style->body();
	setMinimumWidth(m_style->width()); setMinimumHeight(m_style->height());

	//style->main()->header()->width(), style->main()->header()->height()
	setLayout(new QVBoxLayout);
	layout()->setAlignment(Qt::AlignTop);
	layout()->setMargin(0);
	layout()->setSpacing(0);

	m_header = new QWidget(this);
	m_body = new QWidget(this);
	m_footer = new QWidget(this);
	m_body = new QWidget(this);
	m_slide = new QWidget(this);

	m_header->setStyleSheet("background: " + m_styleHeader->palette()->navy01);
	m_body->setStyleSheet("background: orange");
	m_footer->setStyleSheet("background: " + m_styleFooter->palette()->navy01);

	layout()->addWidget(m_header);
	layout()->addWidget(m_body);
	layout()->addWidget(m_footer);

	//Command* cmdLogout = new Command("LOGOUT", m_styleHeader->btnLogout()->name(), m_styleHeader->btnLogout()->width(), m_styleHeader->btnLogout()->height());

	resizeWidget();
}

void ViewHome::resizeEvent(QResizeEvent *e)
{
	if (!initedUI) {
		initializeUI();
		return;
	}

	QSize newSize = e->size();
	QSize oldSize = e->oldSize();
	m_style->setWidth(newSize.width());
	m_style->setHeight(newSize.height());

	resize();
}
void ViewHome::initializeUI()
{
	initedUI = true;
}

void ViewHome::resize()
{
	resizeWidget();
}

void ViewHome::resizeWidget()
{
	int wHeader = m_styleHeader->width();
	int hHeader = m_styleHeader->height();
	int wFooter = m_styleFooter->width();
	int hFooter = m_styleFooter->height();
	int wBody   = m_styleBody->width();
	int hBody   = m_styleBody->height();

	m_header->setFixedSize(wHeader, hHeader);
	m_body->setFixedSize(wBody, hBody);
	m_footer->setFixedSize(wFooter, hFooter);
}

ViewHome::~ViewHome()
{

}
