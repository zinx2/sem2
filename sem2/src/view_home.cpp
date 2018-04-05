#include "view_home.h"
#include "cs_qheader.h"
#include "cs_checktable.h"
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

	connect(m_styleSlide, SIGNAL(extendedChanged()), this, SLOT(onSlided()));

	/*** CREATE INSTANCES. ***/
	Command* btnSlideExt = (new Command("slide_ext", "<<", m_styleSlide->wCol01, m_styleSlide->height()))
		->initStyleSheet(m_styleSlide->btnExtReleasedSheet)
		->initEffect(m_styleSlide->btnExtReleasedSheet, m_styleSlide->btnExtReleasedSheet, m_styleSlide->btnExtHoverdSheet);

	Button* metaBtn;
	metaBtn = m_styleHeader->btnLogout();
	m_btnLogout = (new Command("logout", kr(metaBtn->name()), metaBtn->width(), metaBtn->height()))
		->initStyleSheet(metaBtn->releasedStyle())
		->initEffect(metaBtn->releasedStyle(), metaBtn->selectedStyle(), metaBtn->hoveredStyle())
		->initIcon(":/imgs/circle.png");

	metaBtn = m_styleSlide->btnDVCList();
	m_btnDVCList =
		(new Command(TAG_DVC_LIST, kr(metaBtn->name()), metaBtn->width(), metaBtn->height()))
		->initStyleSheet(metaBtn->releasedStyle())
		->initEffect(metaBtn->releasedStyle(), metaBtn->selectedStyle(), metaBtn->hoveredStyle())
		->initIcon(metaBtn->icon(), metaBtn->name());

	metaBtn = m_styleSlide->btnMNGList();
	m_btnMNGList =
		(new Command(TAG_MNG_LIST, kr(metaBtn->name()), metaBtn->width(), metaBtn->height()))
		->initStyleSheet(metaBtn->releasedStyle())
		->initEffect(metaBtn->releasedStyle(), metaBtn->selectedStyle(), metaBtn->hoveredStyle())
		->initIcon(metaBtn->icon(), metaBtn->name());

	metaBtn = m_styleSlide->btnMNTList();
	m_btnMNTList =
		(new Command(TAG_MNT_LIST, kr(metaBtn->name()), metaBtn->width(), metaBtn->height()))
		->initStyleSheet(metaBtn->releasedStyle())
		->initEffect(metaBtn->releasedStyle(), metaBtn->selectedStyle(), metaBtn->hoveredStyle())
		->initIcon(metaBtn->icon(), metaBtn->name());

	metaBtn = m_styleSlide->btnEMPList();
	m_btnEMPList =
		(new Command(TAG_EMP_LIST, kr(metaBtn->name()), metaBtn->width(), metaBtn->height()))
		->initStyleSheet(metaBtn->releasedStyle())
		->initEffect(metaBtn->releasedStyle(), metaBtn->selectedStyle(), metaBtn->hoveredStyle())
		->initIcon(metaBtn->icon(), metaBtn->name());

	m_cmdProvider = new CommandProvider();
	m_cmdProvider->append(m_btnDVCList)->append(m_btnMNGList)->append(m_btnMNTList)->append(m_btnEMPList);

	m_header = new QWidget(this);
	m_headerCol01 = (new CPLabel(m_styleHeader->wCol01, m_styleHeader->height(), kr(m_styleHeader->txtTitle)))
		->initAlignment(Qt::AlignLeft | Qt::AlignVCenter)
		->initContentsMargins(15, 0, 0, 0)
		->initFontSize(20)
		->initFontBold()
		->initStyleSheet("color:white;");
	m_headerCol02 = (new CPWidget(m_styleHeader->width() - m_styleHeader->wCol01, m_styleHeader->height(), new QHBoxLayout))
		->initAlignment(Qt::AlignRight | Qt::AlignVCenter)
		->initContentsMargins(0, 10, 0, 0);

	m_contentRow1 = (new CPWidget(m_styleContent->width(), m_styleContent->hRow01, new QHBoxLayout))
		->initAlignment(Qt::AlignLeft | Qt::AlignVCenter)
		->initContentsMargins(10, 0, 0, 0);

	m_contentRow2 = (new CPWidget(m_styleContent->width(), m_styleContent->height() - m_styleContent->hRow01, new QHBoxLayout))
		->initAlignment(Qt::AlignLeft | Qt::AlignTop)
		->initStyleSheet("background: blue;");

	m_lbCurrentContent = (new CPLabel(m_styleContent->wGrid1_1 - 40, m_styleContent->hRow01, kr("장비목록")))
		->initFontSize(20)
		->initAlignment(Qt::AlignLeft | Qt::AlignVCenter);

	//QLabel* lb = new QLabel(this);
	//lb->setPixmap(QPixmap(":/imgs/plus_24dp.png"));

	CPLabel* lbUserInfo = (new CPLabel(m_styleHeader->width() - m_styleHeader->wCol01 - m_btnLogout->width() - 10, m_styleHeader->height(), kr("시스템파트 김진환님 (관리자)")))
		->initAlignment(Qt::AlignRight | Qt::AlignVCenter)
		->initContentsMargins(0, 10, 0, 0)
		->initFontSize(12)
		->initStyleSheet("color:white;");

	m_body = new QWidget(this);
	m_footer = new QWidget(this);

	m_content = new QWidget(this);
	m_content->setLayout(new QVBoxLayout);
	m_content->layout()->setAlignment(Qt::AlignLeft | Qt::AlignTop);
	m_content->layout()->setMargin(0);
	m_content->layout()->setSpacing(0);

	m_slide = new QWidget(this);
	m_slideCol01 = new QWidget(m_slide);
	m_slideCol02 = (new CPWidget(m_styleSlide->wCol01, m_styleSlide->height(), new QVBoxLayout))
		->initAlignment(Qt::AlignRight | Qt::AlignTop)
		->initSpacing(10)->initContentsMargins(0, 10, 10, 0);
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

	m_content->setLayout(new QVBoxLayout);
	m_content->layout()->setMargin(0);
	m_content->layout()->setSpacing(0);

	m_slide->setLayout(new QHBoxLayout);
	m_slideCol01->setLayout(new QVBoxLayout);
	m_slideCol02->setLayout(new QVBoxLayout);

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

	m_headerCol02->append(lbUserInfo)->append(m_btnLogout);
	m_header->layout()->addWidget(m_headerCol01);
	m_header->layout()->addWidget(m_headerCol02);

	m_body->layout()->addWidget(m_content);
	m_body->layout()->addWidget(m_slide);

	m_contentRow1->append((new CPLabel(20, 20))->initImage(":/imgs/circle.png"))
		->initSpacing(10)
		->append(m_lbCurrentContent);
	m_content->layout()->addWidget(m_contentRow1);
	m_slide->layout()->addWidget(m_slideCol01);
	m_slide->layout()->addWidget(m_slideCol02);
	m_slideCol02->append(m_btnDVCList)->append(m_btnMNGList)->append(m_btnMNTList)->append(m_btnEMPList);


	/*** ADD WIDGETS. END. ***/

	initDVCList();
	m_btnDVCList->select(true);

	/* CONNECT COMMANDS. */
	btnSlideExt->initFunc([=]()
	{
		bool extended = m_styleSlide->extended();
		m_styleSlide->extend(!extended);
		btnSlideExt->initName(m_styleSlide->extended() ? ">>" : "<<");
		updateUI();
	});
	m_btnLogout->initFunc([=]()
	{
		print("CMD-LOGOUT", "logout...");
	});

	m_btnDVCList->initFunc([=]()
	{
		print("CMD-m_btnDVCList", "m_btnDVCList...");
		initDVCList();
	});
	m_btnMNGList->initFunc([=]()
	{
		print("CMD-m_btnMNGList", "m_btnMNGList...");
		initMNGList();
	});
	m_btnMNTList->initFunc([=]()
	{
		print("CMD-m_btnMNTList", "m_btnMNTList...");
		initMNTList();
	});
	m_btnEMPList->initFunc([=]()
	{
		print("CMD-m_btnEMPList", "m_btnEMPList...");
		initEMPList();
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
	m_contentRow1->initWidth(wContent);
	if (m_contentGrid1_2 != nullptr)
		m_contentGrid1_2->initWidth(wContent - m_styleContent->wGrid1_1);
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

	Button* metaBtn;
	metaBtn = m_styleSlide->btnDVCList();
	m_btnDVCList->initWidth(metaBtn->width())->initIcon(metaBtn->icon(), kr(metaBtn->name()));

	metaBtn = m_styleSlide->btnMNGList();
	m_btnMNGList->initWidth(metaBtn->width())->initIcon(metaBtn->icon(), kr(metaBtn->name()));

	metaBtn = m_styleSlide->btnMNTList();
	m_btnMNTList->initWidth(metaBtn->width())->initIcon(metaBtn->icon(), kr(metaBtn->name()));

	metaBtn = m_styleSlide->btnEMPList();
	m_btnEMPList->initWidth(metaBtn->width())->initIcon(metaBtn->icon(), kr(metaBtn->name()));

	if (!m_cmdProvider->selectedTag().compare(TAG_DVC_LIST))
	{
		MetaTableDVC* metaTable = qobject_cast<MetaTableDVC*>(m_metaTable);
		m_metaTable->setWidth(m_content->width());
		m_metaTable->setHeight(m_content->height() - m_contentRow1->height() - m_navi->height());
		m_tableCommon->setColumnCount(m_metaTable->header()->countCols());
		m_tableCommon->setFixedSize(m_metaTable->width(), m_metaTable->height());
		m_tableCommon->setHorizontalHeaderLabels(m_metaTable->header()->meta());
		m_tableCommon->horizontalHeader()->setFixedHeight(m_metaTable->header()->height());
		m_tableCommon->setColumnWidth(0, metaTable->wCol1);
		m_tableCommon->setColumnWidth(1, metaTable->wCol2);
		m_tableCommon->setColumnWidth(2, metaTable->wCol3);
		m_tableCommon->setColumnWidth(3, metaTable->wCol4);
		m_tableCommon->setColumnWidth(4, metaTable->wCol5);
		m_tableCommon->setColumnWidth(5, metaTable->wCol6);
		m_tableCommon->setColumnWidth(6, m_content->width() - metaTable->wCol1
			- metaTable->wCol2 - metaTable->wCol3 - metaTable->wCol4
			- metaTable->wCol5 - metaTable->wCol6 - 2);
		m_navi->setFixedWidth(m_content->width());
	}
	else if (!m_cmdProvider->selectedTag().compare(TAG_MNG_LIST))
	{
		MetaTableMNG* metaTable = qobject_cast<MetaTableMNG*>(m_metaTable);
		m_metaTable->setWidth(m_content->width());
		m_metaTable->setHeight(m_content->height() - m_contentRow1->height() - m_navi->height());
		m_tableCommon->setColumnCount(m_metaTable->header()->countCols());
		m_tableCommon->setFixedSize(m_metaTable->width(), m_metaTable->height());
		m_tableCommon->setHorizontalHeaderLabels(m_metaTable->header()->meta());
		m_tableCommon->horizontalHeader()->setFixedHeight(m_metaTable->header()->height());
		m_tableCommon->setColumnWidth(0, metaTable->wCol1);
		m_tableCommon->setColumnWidth(1, metaTable->wCol2);
		m_tableCommon->setColumnWidth(2, metaTable->wCol3);
		m_tableCommon->setColumnWidth(3, metaTable->wCol4);
		m_tableCommon->setColumnWidth(4, metaTable->wCol5);
		m_tableCommon->setColumnWidth(5, metaTable->wCol6);
		m_tableCommon->setColumnWidth(6, m_content->width() - metaTable->wCol1
			- metaTable->wCol2 - metaTable->wCol3 - metaTable->wCol4
			- metaTable->wCol5 - metaTable->wCol6 - 2);
		m_navi->setFixedWidth(m_content->width());
	}
	else if (!m_cmdProvider->selectedTag().compare(TAG_MNT_LIST))
	{
		MetaTableMNT* metaTable = qobject_cast<MetaTableMNT*>(m_metaTable);
		m_metaTable->setWidth(m_content->width());
		m_metaTable->setHeight(m_content->height() - m_contentRow1->height());

		m_checkTable->initSize(m_content->width()-20);
		m_mntStack->setFixedSize(m_content->width()-20, m_checkTable->height());
		m_mntScrArea->setFixedSize(m_mntStack->width()+20, m_mntStack->height());
		m_mntScrArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	}
	else if (!m_cmdProvider->selectedTag().compare(TAG_EMP_LIST))
	{
		MetaTableEMP* metaTable = qobject_cast<MetaTableEMP*>(m_metaTable);
		m_metaTable->setWidth(m_content->width());
		m_metaTable->setHeight(m_content->height() - m_contentRow1->height());
		m_tableCommon->setColumnCount(m_metaTable->header()->countCols());
		m_tableCommon->setFixedSize(m_metaTable->width(), m_metaTable->height());
		m_tableCommon->setHorizontalHeaderLabels(m_metaTable->header()->meta());
		m_tableCommon->horizontalHeader()->setFixedHeight(m_metaTable->header()->height());
		m_tableCommon->setColumnWidth(0, metaTable->wCol1);
		m_tableCommon->setColumnWidth(1, metaTable->wCol2);
		m_tableCommon->setColumnWidth(2, metaTable->wCol3);
		m_tableCommon->setColumnWidth(3, metaTable->wCol4);
		m_tableCommon->setColumnWidth(4, metaTable->wCol5);
		m_tableCommon->setColumnWidth(5, metaTable->wCol6);
		m_tableCommon->setColumnWidth(6, m_content->width() - metaTable->wCol1
			- metaTable->wCol2 - metaTable->wCol3 - metaTable->wCol4
			- metaTable->wCol5 - metaTable->wCol6 - 2);
	}

}
void ViewHome::initDVCList()
{
	if (!initPage(TAG_DVC_LIST, kr("장비목록"))) return;

	Button* metaBtn;
	metaBtn = m_styleContent->btnPrint();
	m_btnPrint = (new Command("print", kr(metaBtn->name()), metaBtn->width(), metaBtn->height()))
		->initStyleSheet(metaBtn->releasedStyle())
		->initEffect(metaBtn->releasedStyle(), metaBtn->selectedStyle(), metaBtn->hoveredStyle())
		->initIcon(m_styleContent->btnPrint()->icon());

	metaBtn = m_styleContent->btnEdit();
	m_btnEdit = (new Command("edit", kr(metaBtn->name()), metaBtn->width(), metaBtn->height()))
		->initStyleSheet(metaBtn->releasedStyle())
		->initEffect(metaBtn->releasedStyle(), metaBtn->selectedStyle(), metaBtn->hoveredStyle())
		->initIcon(m_styleContent->btnEdit()->icon());

	metaBtn = m_styleContent->btnRemove();
	m_btnRemove = (new Command("remove", kr(metaBtn->name()), metaBtn->width(), metaBtn->height()))
		->initStyleSheet(metaBtn->releasedStyle())
		->initEffect(metaBtn->releasedStyle(), metaBtn->selectedStyle(), metaBtn->hoveredStyle())
		->initIcon(m_styleContent->btnRemove()->icon());

	metaBtn = m_styleContent->btnNew();
	m_btnNew = (new Command("new", kr(metaBtn->name()), metaBtn->width(), metaBtn->height()))
		->initStyleSheet(metaBtn->releasedStyle())
		->initEffect(metaBtn->releasedStyle(), metaBtn->selectedStyle(), metaBtn->hoveredStyle())
		->initIcon(m_styleContent->btnNew()->icon());

	m_contentGrid1_2->append(m_btnNew)->append(m_btnEdit)->append(m_btnRemove)->append(m_btnPrint);

	m_btnPrint->initFunc([=]()
	{
		print("CMD-PRINT", "print...");
	});
	m_btnRemove->initFunc([=]()
	{
		print("CMD-btnRemove", "print...");
	});
	m_btnEdit->initFunc([=]()
	{
		print("CMD-btnEdit", "print...");
	});
	m_btnNew->initFunc([=]()
	{
		print("CMD-btnNew", "print...");
	});

	newTable(20, TAG_DVC_LIST);
	newNavi();
	updateUI();
}
void ViewHome::initMNGList()
{
	if (!initPage(TAG_MNG_LIST, kr("관리대장"))) return;


	newTable(20, TAG_MNG_LIST);
	newNavi();
	updateUI();
}
void ViewHome::initMNTList()
{
	if (!initPage(TAG_MNT_LIST, kr("월별대장"))) return;
	newMetaTable(TAG_MNT_LIST);

	m_mntStack = (new CPWidget(m_content->width(), m_content->height(), new QVBoxLayout))
		->initAlignment(Qt::AlignLeft | Qt::AlignTop)
		->initStyleSheet("background: green;");
	m_mntScrArea = new QScrollArea(this);
	m_mntScrArea->setWidget(m_mntStack);
	m_content->layout()->addWidget(m_mntScrArea);

	m_checkTable = new CheckTable();
	m_mntStack->layout()->addWidget(m_checkTable);

	updateUI();
}
void ViewHome::initEMPList()
{
	if (!initPage(TAG_EMP_LIST, kr("직원관리"))) return;
	newTable(100, TAG_EMP_LIST);
	updateUI();
}
bool ViewHome::initPage(QString tag, QString titleTxt)
{
	if (isCurrentMetaTable(tag)) return false;
	if (m_contentGrid1_2 != nullptr)
	{
		delete m_contentGrid1_2;
		m_contentGrid1_2 = nullptr;
	}
	if (m_tableCommon != nullptr)
	{
		delete m_tableCommon;
		m_tableCommon = nullptr;
	}
	if (m_navi != nullptr)
	{
		delete m_navi;
		m_navi = nullptr;
	}
	if (m_checkTable != nullptr)
	{
		delete m_checkTable;
		m_checkTable = nullptr;
	}
	if (m_mntStack != nullptr)
	{
		delete m_mntStack;
		m_mntStack = nullptr;
	}
	if (m_mntScrArea != nullptr)
	{
		delete m_mntScrArea;
		m_mntScrArea	 = nullptr;
	}
	m_lbCurrentContent->setText(titleTxt);
	m_contentGrid1_2 = (new CPWidget(m_styleContent->width() - m_styleContent->wGrid1_1, m_styleContent->hRow01, new QHBoxLayout))
		->initSpacing(10)
		->initAlignment(Qt::AlignRight | Qt::AlignVCenter)
		->initContentsMargins(0, 20, 0, 0);
	m_contentRow1->layout()->addWidget(m_contentGrid1_2);

	return true;
}
ViewHome::~ViewHome()
{

}
bool ViewHome::isCurrentMetaTable(QString tag)
{
	return !m_cmdProvider->selectedTag().compare(tag);
}
void ViewHome::newMetaTable(QString tag)
{
	m_cmdProvider->select(tag);
	if (!tag.compare(TAG_DVC_LIST)) m_metaTable = new MetaTableDVC();
	else if (!tag.compare(TAG_MNG_LIST)) m_metaTable = new MetaTableMNG();
	else if (!tag.compare(TAG_MNT_LIST)) m_metaTable = new MetaTableMNT();
	else if (!tag.compare(TAG_EMP_LIST)) m_metaTable = new MetaTableEMP();
}
void ViewHome::newNavi()
{
	if (m_navi != nullptr)
	{
		delete m_navi;
		m_navi = nullptr;
	}
	Button* metaBtn;
	metaBtn = m_styleContent->btnNaviLeft();
	m_btnNaviLeft =
		(new Command("navi_left", kr(metaBtn->name()), metaBtn->width(), metaBtn->height()))
		->initStyleSheet(metaBtn->releasedStyle())
		->initEffect(metaBtn->releasedStyle(), metaBtn->selectedStyle(), metaBtn->hoveredStyle());

	metaBtn = m_styleContent->btnNaviRight();
	m_btnNaviRight =
		(new Command("navi_right", kr(metaBtn->name()), metaBtn->width(), metaBtn->height()))
		->initStyleSheet(metaBtn->releasedStyle())
		->initEffect(metaBtn->releasedStyle(), metaBtn->selectedStyle(), metaBtn->hoveredStyle());
	m_lbNavi = (new CPLabel(100, 30, "50/70"))->initAlignment(Qt::AlignCenter);
	m_navi = (new CPWidget(m_styleContent->width(), 0, new QHBoxLayout))
		->initAlignment(Qt::AlignCenter)
		->append(m_btnNaviLeft)->append(m_lbNavi)->append(m_btnNaviRight);
	m_content->layout()->addWidget(m_navi);
	m_navi->setFixedHeight(m_metaTable->hNavi());
}
void ViewHome::newTable(int rowCount, QString tag)
{
	newMetaTable(tag);

	if (m_tableCommon != nullptr)
	{
		delete m_tableCommon;
		m_tableCommon = nullptr;
	}
	m_tableCommon = new QTableWidget(this);
	m_tableCommon->setRowCount(rowCount);
	m_tableCommon->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_tableCommon->setStyleSheet("border: 1px; background:orange;");
	m_tableCommon->setSelectionMode(QAbstractItemView::SingleSelection);
	m_tableCommon->horizontalScrollBar()->setDisabled(true);
	m_tableCommon->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	//m_tableCommon->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_tableCommon->verticalHeader()->hide();
	m_content->layout()->addWidget(m_tableCommon);
}