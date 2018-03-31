#include "view_home.h"
#include "cs_qheader.h"
ViewHome::ViewHome(QWidget *parent)
    : QWidget(parent)
{
	/*** GET STYLE INSTANCES. ***/
	m_style = Style::instance()->main();
	m_styleHeader = m_style->header();
	m_styleFooter = m_style->footer();
	m_styleBody = m_style->body();
	m_styleContent = m_styleBody->content();
	m_styleSlide = m_styleBody->slide();
	/*** GET STYLE INSTANCES. END. ***/

	/*** CREATE INSTANCES. ***/
	Command* btnSlideExt = new Command("slide_ext", "<<", m_styleSlide->wCol01, m_styleSlide->height());
	btnSlideExt->initStyleSheet("color: white; background-color: transparent;");
	Command* btnLogout = new Command("logout", kr(m_styleHeader->btnLogout()->name()), m_styleHeader->btnLogout()->width(), m_styleHeader->btnLogout()->height());
	btnLogout->initStyleSheet(m_style->palette()->btnReleasedStyle);

	m_header = new QWidget(this);
	m_headerCol01 = (new CPLabel(500, m_styleHeader->height(), kr(m_styleHeader->txtTitle)))
		->initAlignment(Qt::AlignLeft | Qt::AlignVCenter)
		->initContentsMargins(15, 0, 0, 0)
		->initFontSize(20)
		->initFontBold()
		->initStyleSheet("color:white;");
	m_headerCol02 = (new CPWidget(m_styleHeader->width() - m_styleHeader->wCol01, m_styleHeader->height(), new QHBoxLayout))
		->initAlignment(Qt::AlignRight | Qt::AlignVCenter)
		->initContentsMargins(0, 10, 0, 0);
		
	QImage img()
	CPLabel* lbUserInfo = (new CPLabel(m_styleHeader->width() - m_styleHeader->wCol01 - btnLogout->width() - 10, m_styleHeader->height(), kr("시스템파트 김진환님 (관리자)")))
		->initAlignment(Qt::AlignRight | Qt::AlignVCenter)
		->initContentsMargins(0, 10, 0, 0)
		->initFontSize(12)
		->initStyleSheet("color:white;");

	m_body = new QWidget(this);
	m_footer = new QWidget(this);
	m_content = new QWidget(this);

	m_slide = new QWidget(this);
	m_slideCol01 = new QWidget(m_slide);
	m_slideCol02 = new QWidget(m_slide);
	/*** CREATE INSTANCES. END. ***/

	/*** INITIALIZE PARENT. ***/
	setMinimumWidth(m_style->width()); setMinimumHeight(m_style->height());
	setLayout(new QVBoxLayout);
	layout()->setAlignment(Qt::AlignTop);
	layout()->setMargin(0);
	layout()->setSpacing(0);
	/*** INITIALIZE PARENT. END. ***/

	/*** SET LAYOUT. ***/
	m_header->setLayout(new QHBoxLayout);
	m_header->layout()->setMargin(0);
	m_header->layout()->setSpacing(0);
	m_header->layout()->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

	m_body->setLayout(new QHBoxLayout);
	m_body->layout()->setMargin(0);
	m_body->layout()->setSpacing(0);

	m_slide->setLayout(new QHBoxLayout);
	m_slideCol01->setLayout(new QVBoxLayout);

	m_slide->layout()->setMargin(0);
	m_slide->layout()->setSpacing(0);
	m_slideCol01->layout()->setAlignment(Qt::AlignCenter);
	m_slideCol01->layout()->setMargin(0);
	m_slideCol01->layout()->addWidget(btnSlideExt);
	/*** SET LAYOUT. END. ***/
	
	/*** SET STYLE SHEETS. ***/
	m_header->setStyleSheet("background: " + m_styleHeader->palette()->navy01);
	m_body->setStyleSheet("background: orange");
	m_footer->setStyleSheet("background: " + m_styleFooter->palette()->navy01);
	m_content->setStyleSheet("background: yellow");
	m_slide->setStyleSheet("background: " + m_styleHeader->palette()->navy02);
	m_slideCol01->setStyleSheet("background: " + m_styleHeader->palette()->navy03);	
	/*** SET STYLE SHEETS. END. ***/

	/*** ADD WIDGETS. ***/
	layout()->addWidget(m_header);
	layout()->addWidget(m_body);
	layout()->addWidget(m_footer);

	m_headerCol02->append(lbUserInfo)->append(btnLogout);
	m_header->layout()->addWidget(m_headerCol01);
	m_header->layout()->addWidget(m_headerCol02);

	m_body->layout()->addWidget(m_content);
	m_body->layout()->addWidget(m_slide);

	m_slide->layout()->addWidget(m_slideCol01);
	m_slide->layout()->addWidget(m_slideCol02);
	/*** ADD WIDGETS. END. ***/

	/* CONNECT COMMANDS. */
	connect(btnSlideExt, &QPushButton::clicked, [=]()
	{
		bool extended = m_styleSlide->extended();
		m_styleSlide->extend(!extended);
		btnSlideExt->initName(m_styleSlide->extended() ? ">>" : "<<");
		updateUI();
	});
	connect(btnLogout, &QPushButton::clicked, [=]()
	{
		print("CMD-LOGOUT", "logout...");
	});

	/* CONNECT COMMANDS. END. */

	updateUI();
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
	print("MAIN", newSize.width(), newSize.height());
	updateUI();
}
void ViewHome::initializeUI()
{
	initedUI = true;
}
void ViewHome::updateUI()
{
	int wHeader = m_styleHeader->width();
	int hHeader = m_styleHeader->height();
	int wFooter = m_styleFooter->width();
	int hFooter = m_styleFooter->height();
	int wBody = m_styleBody->width();
	int hBody = m_styleBody->height();
	int wContent = m_styleContent->width();
	int hContent = m_styleContent->height();
	int wSlide = m_styleSlide->width();
	int wSlideCol01 = m_styleSlide->wCol01;
	int wSlideCol02 = wSlide - wSlideCol01;
	int hSlide = m_styleSlide->height();

	m_header->setFixedSize(wHeader, hHeader);
	m_headerCol02->initWidth(m_styleHeader->width() - m_styleHeader->wCol01);

	m_body->setFixedSize(wBody, hBody);
	m_footer->setFixedSize(wFooter, hFooter);
	m_content->setFixedSize(wContent, hContent);
	m_slide->setFixedSize(wSlide, hSlide);
	m_slideCol01->setFixedSize(wSlideCol01, hSlide);
	m_slideCol02->setFixedSize(wSlideCol02, hSlide);

	print("HEADER", wHeader, hHeader);
	print("FOOTER", wFooter, hFooter);
	print("BODY", wBody, hBody);
	print("CONTENT", wContent, hContent);
	print("SLIDE", wSlide, hSlide);
	print("SLIDE-COL01", wSlideCol01, hSlide);
	print("SLIDE-COL02", wSlideCol02, hSlide);
}

ViewHome::~ViewHome()
{

}
