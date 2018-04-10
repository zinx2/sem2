#include "view_home.h"
#include "cs_qheader.h"
#include "cs_checktable.h"
#include "cs_form_add.h"
#include "cs_form_edit.h"
#include "cs_barcoder.h"

ViewHome::ViewHome(QWidget *parent)
	: QWidget(parent)
{
	setWindowTitle(kr("온라인평생교육원 자산 관리 시스템"));

	m = Model::instance();
	n = NetWorker::instance();
	s = Settings::instance();

	m_alarm = new Alarm(kr("알림"), "", 350, 200);
	m_question = new Question(kr("알림"), "", 350, 200);
	connect(m, SIGNAL(alarmedChanged()), this, SLOT(handler()));
	
	init();
	if (s->isLoginAuto())
	{
		n->login(s->id(), s->pass())->request();
	}
	else
	{
		m_login = new CPLogin();
		m_login->setParent(this);
		m_login->show();
	}
	//n->getDeviceList()->request();
	connect(m, SIGNAL(devicesChanged()), this, SLOT(updateUI()));
	//setFixedSize(0, 0);
	//run();
}
void ViewHome::init()
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
	m_lbUserInfo = (new CPLabel(m_styleHeader->width() - m_styleHeader->wCol01 - m_btnLogout->width() - 10, m_styleHeader->height(), ""))
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
	//m_body->setStyleSheet("background: orange");
	m_footer->setStyleSheet("background: " + m_styleFooter->palette()->navy01);
	m_slide->setStyleSheet("background: " + m_styleHeader->palette()->navy02);
	m_slideCol01->setStyleSheet("background: " + m_styleHeader->palette()->navy03);
	/*** SET STYLE SHEETS. END. ***/

	/*** ADD WIDGETS. ***/
	layout()->addWidget(m_header);
	layout()->addWidget(m_body);
	layout()->addWidget(m_footer);

	m_headerCol02->append(m_lbUserInfo)->append(m_btnLogout);
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

	m_emptyArea = (new CPLabel(0, 0, ""));

	metaBtn = m_styleSlide->btnImExport();
	m_btnImExport = (new Command(TAG_IMEXPORT, kr(metaBtn->name()), metaBtn->width(), metaBtn->height()))
		->initStyleSheet(metaBtn->releasedStyle())
		->initEffect(metaBtn->releasedStyle(), metaBtn->selectedStyle(), metaBtn->hoveredStyle())
		->initIcon(metaBtn->icon(), metaBtn->name());
	m_slideCol02->append(m_emptyArea);
	m_slideCol02->append(m_btnImExport);
	m_cmdProvider->append(m_btnImExport);

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
		m_question->initSize(350, 120)->setMessage(kr("로그아웃 하시겠습니까?"));
		m_question->func = [=]() {
			n->logout()->request();
		};
		m_question->show();
	});

	m_btnDVCList->initFunc([=]()
	{
		initDVCList();
	});
	m_btnMNGList->initFunc([=]()
	{
		initMNGList();
	});
	m_btnMNTList->initFunc([=]()
	{		
		initMNTList();
	});
	m_btnEMPList->initFunc([=]()
	{		
		initEMPList();
	});
	m_btnImExport->initFunc([=]()
	{
		m_barcoder = new Barcoder(kr("대출/반납하기"), 520, 230);
		m_barcoder->show();
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
	m_emptyArea->setFixedSize(1, hSlide - m_cmdProvider->totalHeight() - 10 * (m_cmdProvider->count()+2));

	/*print("HEADER", wHeader, hHeader);
	print("FOOTER", wFooter, hFooter);
	print("BODY", wBody, hBody);
	print("CONTENT", wContent, hContent);
	print("SLIDE", wSlide, hSlide);
	print("SLIDE-COL01", wSlideCol01, hSlide);
	print("SLIDE-COL02", wSlideCol02, hSlide);*/

	Button* metaBtn;
	metaBtn = m_styleSlide->btnDVCList();
	m_btnDVCList->initWidth(metaBtn->width())->initIcon(metaBtn->icon(), kr(metaBtn->name()));

	metaBtn = m_styleSlide->btnMNGList();
	m_btnMNGList->initWidth(metaBtn->width())->initIcon(metaBtn->icon(), kr(metaBtn->name()));

	metaBtn = m_styleSlide->btnMNTList();
	m_btnMNTList->initWidth(metaBtn->width())->initIcon(metaBtn->icon(), kr(metaBtn->name()));

	metaBtn = m_styleSlide->btnEMPList();
	m_btnEMPList->initWidth(metaBtn->width())->initIcon(metaBtn->icon(), kr(metaBtn->name()));

	metaBtn = m_styleSlide->btnImExport();
	m_btnImExport->initWidth(metaBtn->width())->initIcon(metaBtn->icon(), kr(metaBtn->name()));

	QString mm = m_cmdProvider->selectedTag();
	if (!m_cmdProvider->selectedTag().compare(TAG_DVC_LIST))
	{
		newTable(20, TAG_DVC_LIST);
		MetaTableDVC* castedMetaTable = qobject_cast<MetaTableDVC*>(m_metaTable);
		m_metaTable->setWidth(m_content->width());
		m_metaTable->setHeight(m_content->height() - m_contentRow1->height() - m_navi->height());		
		m_tableCommon->setColumnCount(m_metaTable->header()->countCols());
		m_tableCommon->setFixedSize(m_metaTable->width(), m_metaTable->height());
		m_tableCommon->setHorizontalHeaderLabels(m_metaTable->header()->meta());
		m_tableCommon->horizontalHeader()->setFixedHeight(m_metaTable->header()->height());
		m_tableCommon->setColumnWidth(0, castedMetaTable->wCol1);
		m_tableCommon->setColumnWidth(1, castedMetaTable->wCol2);
		m_tableCommon->setColumnWidth(2, castedMetaTable->wCol3);
		m_tableCommon->setColumnWidth(3, castedMetaTable->wCol4);
		m_tableCommon->setColumnWidth(4, castedMetaTable->wCol5);
		m_tableCommon->setColumnWidth(5, castedMetaTable->wCol6);
		m_tableCommon->setColumnWidth(6, m_content->width() - castedMetaTable->wCol1
			- castedMetaTable->wCol2 - castedMetaTable->wCol3 - castedMetaTable->wCol4
			- castedMetaTable->wCol5 - castedMetaTable->wCol6 - 20);
		m_navi->setFixedWidth(m_content->width());		

		for (int row = 0; row < m->devices().size(); row++)
		{
			Device* dv = m->devices().at(row);

			QTableWidgetItem* item0 = new QTableWidgetItem(QString("%1").arg((row + 1) + (m->pageNumber() - 1)*COUNT_PAGE));
			item0->setTextAlignment(Qt::AlignCenter);
			m_tableCommon->setItem(row, 0, item0);

			QTableWidgetItem* item1 = new QTableWidgetItem(QString("%1").arg(dv->noAsset()));
			item1->setTextAlignment(Qt::AlignCenter);
			m_tableCommon->setItem(row, 1, item1);

			QTableWidgetItem* item2 = new QTableWidgetItem(dv->nameDevice());
			item2->setTextAlignment(Qt::AlignCenter);
			m_tableCommon->setItem(row, 2, item2);

			QTableWidgetItem* item3 = new QTableWidgetItem(QString(kr("%L1원  ")).arg(dv->price()));
			item3->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
			m_tableCommon->setItem(row, 3, item3);

			QTableWidgetItem* item4 = new QTableWidgetItem(dv->dateTaked());
			item4->setTextAlignment(Qt::AlignCenter);
			m_tableCommon->setItem(row, 4, item4);

			QTableWidgetItem* item5 = new QTableWidgetItem(dv->borrowed() ? "O" : "X");
			item5->setTextAlignment(Qt::AlignCenter);
			m_tableCommon->setItem(row, 5, item5);

			QTableWidgetItem* item6 = new QTableWidgetItem(dv->memo());
			item6->setTextAlignment(Qt::AlignCenter);
			m_tableCommon->setItem(row, 6, item6);
		}
	}
	else if (!m_cmdProvider->selectedTag().compare(TAG_MNG_LIST))
	{
		newTable(20, TAG_MNG_LIST);
		MetaTableMNG* castedMetaTable = qobject_cast<MetaTableMNG*>(m_metaTable);
		m_metaTable->setWidth(m_content->width());
		m_metaTable->setHeight(m_content->height() - m_contentRow1->height() - m_navi->height());
		m_tableCommon->setColumnCount(m_metaTable->header()->countCols());
		m_tableCommon->setFixedSize(m_metaTable->width(), m_metaTable->height());
		m_tableCommon->setHorizontalHeaderLabels(m_metaTable->header()->meta());
		m_tableCommon->horizontalHeader()->setFixedHeight(m_metaTable->header()->height());
		m_tableCommon->setColumnWidth(0, castedMetaTable->width() * 0.03); //1. 번호
		m_tableCommon->setColumnWidth(1, castedMetaTable->width() * 0.08); //2. 자산번호
		m_tableCommon->setColumnWidth(2, castedMetaTable->width() * 0.10); //3. 장비명
		m_tableCommon->setColumnWidth(3, castedMetaTable->width() * 0.12 - 7); //4. 대출날짜
		m_tableCommon->setColumnWidth(4, castedMetaTable->width() * 0.09); //5. 대출자
		m_tableCommon->setColumnWidth(5, castedMetaTable->width() * 0.10); //6. 서명
		m_tableCommon->setColumnWidth(6, castedMetaTable->width() * 0.09); //. 용도
		m_tableCommon->setColumnWidth(7, castedMetaTable->width() * 0.12 - 7); //7. 반납날짜
		m_tableCommon->setColumnWidth(8, castedMetaTable->width() * 0.09); //8. 확인자
		m_tableCommon->setColumnWidth(9, castedMetaTable->width() * 0.10); //9. 서명
		m_tableCommon->setColumnWidth(10, castedMetaTable->width() * 0.05); //9. 보안점검
		m_tableCommon->setColumnWidth(11, castedMetaTable->width() * 0.03); //10. 확인
		m_navi->setFixedWidth(m_content->width());
		for (int row = 0; row < m->rents().size(); row++)
		{
			m_tableCommon->setRowHeight(row, 50);
			Rent* dv = m->rents().at(row);
			QTableWidgetItem* item0 = new QTableWidgetItem(QString("%1").arg((row + 1) + (m->pageNumber() - 1)*COUNT_PAGE));
			item0->setTextAlignment(Qt::AlignCenter);
			m_tableCommon->setItem(row, 0, item0);

			QTableWidgetItem* item1 = new QTableWidgetItem(dv->noAsset());
			item1->setTextAlignment(Qt::AlignCenter);
			m_tableCommon->setItem(row, 1, item1);

			QTableWidgetItem* item2 = new QTableWidgetItem(dv->nameDevice());
			item2->setTextAlignment(Qt::AlignCenter);
			m_tableCommon->setItem(row, 2, item2);

			QTableWidgetItem* item3 = new QTableWidgetItem(dv->dateBorrowed());
			item3->setTextAlignment(Qt::AlignCenter);
			m_tableCommon->setItem(row, 3, item3);

			QTableWidgetItem* item4 = new QTableWidgetItem(dv->nameUser());
			item4->setTextAlignment(Qt::AlignCenter);
			m_tableCommon->setItem(row, 4, item4);

			CPLazyImage *lbSignBorrwed = new CPLazyImage(dv->signUser(), m_tableCommon->width() * 0.10);
			lbSignBorrwed->setFixedSize(m_tableCommon->width() * 0.10, 50);
			QHBoxLayout *lySignBorrwed = new QHBoxLayout();
			lySignBorrwed->addWidget(lbSignBorrwed);
			lySignBorrwed->setMargin(0);
			QWidget *wdSignBorrwed = new QWidget();
			wdSignBorrwed->setLayout(lySignBorrwed);
			wdSignBorrwed->setStyleSheet("border: 0px;");
			m_tableCommon->setCellWidget(row, 5, wdSignBorrwed);

			QTableWidgetItem* itemPP = new QTableWidgetItem(dv->purpose());
			itemPP->setTextAlignment(Qt::AlignCenter);
			m_tableCommon->setItem(row, 6, itemPP);

			QTableWidgetItem* item7 = new QTableWidgetItem(dv->dateReturned());
			item7->setTextAlignment(Qt::AlignCenter);
			m_tableCommon->setItem(row, 7, item7);

			QTableWidgetItem* item8 = new QTableWidgetItem(dv->nameAdmin());
			item8->setTextAlignment(Qt::AlignCenter);
			m_tableCommon->setItem(row, 8, item8);

			CPLazyImage *lbSignReturned = new CPLazyImage(dv->signAdmin(), m_tableCommon->width() * 0.10);
			lbSignReturned->setFixedSize(m_tableCommon->width() * 0.10, 50);
			QHBoxLayout *lySignReturned = new QHBoxLayout();
			lySignReturned->addWidget(lbSignReturned);
			lySignReturned->setMargin(0);
			QWidget *wdSignReturned = new QWidget();
			wdSignReturned->setLayout(lySignReturned);
			wdSignReturned->setStyleSheet("border: 0px;");
			m_tableCommon->setCellWidget(row, 9, wdSignReturned);

			QTableWidgetItem* itemSecu = new QTableWidgetItem(dv->initial() ? "O" : "X");
			itemSecu->setTextAlignment(Qt::AlignCenter);
			m_tableCommon->setItem(row, 10, itemSecu);

			QTableWidgetItem* item11 = new QTableWidgetItem(dv->completed() ? "O" : "X");
			item11->setTextAlignment(Qt::AlignCenter);
			m_tableCommon->setItem(row, 11, item11);
		}
	}
	else if (!m_cmdProvider->selectedTag().compare(TAG_MNT_LIST))
	{
		MetaTableMNT* metaTable = qobject_cast<MetaTableMNT*>(m_metaTable);
		m_metaTable->setWidth(m_content->width());
		m_metaTable->setHeight(m_content->height() - m_contentRow1->height());
		m_checkTable->initSize(m_content->width()-20);
		m_btnCheckExt->setFixedWidth(m_content->width() - 20);

		int hMntStack = m_checkTable->height() + metaTable->hExt * (m_checkTable->meta()->parts().size() + 1);
		for (int i = 0; i < m_mntTables.size(); i++)
		{
			Command* cmd = m_cmdProviderExt->command(i);
			cmd->initWidth(m_content->width());

			CPTable* tb = m_mntTables.at(i);
			tb->initWidth(m_content->width())->initVible(cmd->selected())->resize();
			hMntStack = hMntStack + cmd->height() + tb->height();
		}
		m_mntStack->setFixedSize(m_content->width() - 20, hMntStack);
		m_mntScrArea->setFixedSize(m_mntStack->width() + 20, m_content->height() - m_contentRow1->height());
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
		print(m_tableCommon);
	});
	m_btnRemove->initFunc([=]()
	{
		if (m_tableCommon->currentRow() < 0) {
			m_alarm->initSize(350, 120)->setMessage(kr("삭제할 장비를 선택하세요."));
			m_alarm->show();
			return;
		}
		if (!m_tableCommon->item(m_tableCommon->currentRow(), 0)->isSelected()) {
			m_alarm->initSize(350, 120)->setMessage(kr("삭제할 장비를 선택하세요."));
			m_alarm->show();
			return;
		}
		for (int i = 0; i < m_tableCommon->columnCount(); i++)
			m_tableCommon->item(m_tableCommon->currentRow(), i)->setSelected(false);

		QString strNameDevice = m->devices().at(m_tableCommon->currentRow())->nameDevice();
		QString strNoAsset = m->devices().at(m_tableCommon->currentRow())->noAsset();
		m_question->initSize(350, 120)->setMessage(kr("선택한 장비를 삭제 하시겠습니까?\n\n장비명: ") + strNameDevice + kr("\n자산번호: ") + strNoAsset);
		m_question->func = [=]() {
			
		};
		m_question->show();
	});
	m_btnEdit->initFunc([=]()
	{
		FormAdd* f = new FormAdd(410, 340);
		f->show();
	});
	m_btnNew->initFunc([=]()
	{
		FormAdd* f = new FormAdd(410, 340);
		f->show();		
	});

	//newMetaTable(TAG_DVC_LIST);
	//newTable(20, TAG_DVC_LIST);
	//newNavi();
	updateUI();
}
void ViewHome::initMNGList()
{
	if (!initPage(TAG_MNG_LIST, kr("관리대장"))) return;
	m_cmdProvider->select(TAG_MNG_LIST);
	//newMetaTable(TAG_MNG_LIST);
	//newTable(20, TAG_MNG_LIST);
	//newNavi();
	updateUI();
}
void ViewHome::initMNTList()
{
	if (!initPage(TAG_MNT_LIST, kr("월별대장"))) return;
	//newMetaTable(TAG_MNT_LIST);

	MetaTableMNT* metaTable = qobject_cast<MetaTableMNT*>(m_metaTable);
	m_btnCheckExt = (new Command("check_ext", metaTable->txt1, m_content->width(), metaTable->hExt))
		->initStyleSheet(metaTable->btnExtReleasedSheet)->initIcon("", metaTable->txt2)
		->initEffect(metaTable->btnExtReleasedSheet, metaTable->btnExtHoverdSheet, metaTable->btnExtHoverdSheet)
		->initFunc([=]() {	

		bool folded = m_btnCheckExt->selected();
		int h = folded ? (12 * 30 + 24) : 0;
		m_checkTable->initHeight(h);
		m_btnCheckExt->initName(folded ? metaTable->txt1 : metaTable->txt2);
		m_btnCheckExt->select(!folded);
		updateUI();
	});
	m_cmdProviderExt = new CommandProvider();
	m_cmdProviderExt->append(m_btnCheckExt);

	m_mntStack = (new CPWidget(m_content->width(), m_content->height(), new QVBoxLayout))
		->initAlignment(Qt::AlignLeft | Qt::AlignTop);
	m_mntScrArea = new QScrollArea(this);
	m_mntScrArea->setWidget(m_mntStack);
	m_content->layout()->addWidget(m_mntScrArea);

	m_checkTable = new CheckTable();
	m_mntStack->append(m_btnCheckExt)->append(m_checkTable);

	m_mntTables.clear();
	for (int i = 0; i < 8; i++)
	{
		Command* m_btnExt = (new Command("ext_" + QString("%1").arg(i), metaTable->txt1, m_content->width(), metaTable->hExt))
			->initStyleSheet(metaTable->btnExtReleasedSheet)->initIcon("", metaTable->txt2)
			->initEffect(metaTable->btnExtReleasedSheet, metaTable->btnExtHoverdSheet, metaTable->btnExtHoverdSheet)
			->initFunc([=]() {
			Command* cmd = m_cmdProviderExt->command(i);
			bool folded = cmd->selected();
			cmd->select(!folded);
			updateUI();
		});
		m_cmdProviderExt->append(m_btnExt);
		m_mntStack->append(m_btnExt);

		CPTable* table = (new CPTable(new MetaTableExtendable, 30))->initWidth(m_content->width())->resize();
		m_mntTables.append(table);
		m_mntStack->append(table);
	}
	updateUI();
}
void ViewHome::initEMPList()
{
	if (!initPage(TAG_EMP_LIST, kr("직원관리"))) return;
	//newMetaTable(TAG_EMP_LIST);
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
		->initEffect(metaBtn->releasedStyle(), metaBtn->selectedStyle(), metaBtn->hoveredStyle())
		->initFunc([=]() { prev(); });

	metaBtn = m_styleContent->btnNaviRight();
	m_btnNaviRight =
		(new Command("navi_right", kr(metaBtn->name()), metaBtn->width(), metaBtn->height()))
		->initStyleSheet(metaBtn->releasedStyle())
		->initEffect(metaBtn->releasedStyle(), metaBtn->selectedStyle(), metaBtn->hoveredStyle())
		->initFunc([=]() { next(); });

	m_lbNavi = (new CPLabel(100, 30, getCountDevice()))->initAlignment(Qt::AlignCenter);
	m_navi = (new CPWidget(m_styleContent->width(), 0, new QHBoxLayout))
		->initAlignment(Qt::AlignCenter)
		->append(m_btnNaviLeft)->append(m_lbNavi)->append(m_btnNaviRight);
	m_content->layout()->addWidget(m_navi);
	m_navi->setFixedHeight(m_metaTable->hNavi());

	m_lbNavi->setText(getCountDevice());

	Palette* p = new Palette();
	if (m->countCurrentDevice() > 20)
	{
		m_btnNaviLeft->initEnabled(true)->initStyleSheet(metaBtn->releasedStyle())
			->initEffect(metaBtn->releasedStyle(), metaBtn->selectedStyle(), metaBtn->hoveredStyle());
	}
	else
	{
		m_btnNaviLeft->initEnabled(false)->initStyleSheet(p->btnSelectedStyleDiabled)
					 ->initEffect(p->btnSelectedStyleDiabled, 
					 			  p->btnSelectedStyleDiabled, 
					 			  p->btnSelectedStyleDiabled);
	}

	if (m->countCurrentDevice() < m->countTotalDevice())
	{
		m_btnNaviRight->initEnabled(true)->initStyleSheet(metaBtn->releasedStyle())
			->initEffect(metaBtn->releasedStyle(), metaBtn->selectedStyle(), metaBtn->hoveredStyle());
	}
	else
	{
		m_btnNaviRight->initEnabled(false)->initStyleSheet(p->btnSelectedStyleDiabled)
					 ->initEffect(p->btnSelectedStyleDiabled,
								  p->btnSelectedStyleDiabled,
								  p->btnSelectedStyleDiabled);
	}
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
	//m_tableCommon->setStyleSheet("border: 1px; background:orange;");
	m_tableCommon->setSelectionMode(QAbstractItemView::SingleSelection);
	m_tableCommon->horizontalScrollBar()->setDisabled(true);
	m_tableCommon->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_tableCommon->horizontalHeader()->setStyleSheet("QHeaderView::section { background-color:#eeeeee }");
	//m_tableCommon->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_tableCommon->verticalHeader()->hide();
	m_content->layout()->addWidget(m_tableCommon);

	if (!tag.compare(TAG_DVC_LIST) || !tag.compare(TAG_MNG_LIST)) {
		newNavi();
	}

}

void ViewHome::newData(QString tag)
{
	initDVCList();
	if (!tag.compare(TAG_DVC_LIST))
	{
		
	}

}
void ViewHome::getDeviceList()
{
	n->getDeviceList()->request();
}
void ViewHome::getRentList()
{
	n->getRentList()->request();
}
void ViewHome::handler()
{
	if (m->alarmed())
	{
		bool result = false;
		Notificator* noti = m->notificator();
		if (noti->type() == Notificator::Login)
		{
			result = noti->result();
			if (result) {

				QString typeAdmin = "";
				if (m->user()->typeAdmin() == 1) typeAdmin = kr("파트담당자");
				else if (m->user()->typeAdmin() == 2) typeAdmin = kr("파트장");
				else if (m->user()->typeAdmin() == 3) typeAdmin = kr("보직자");
				else if (m->user()->typeAdmin() == 4) typeAdmin = kr("시스템관리자");
				QString userType = m->user()->namePart() + " " + m->user()->nameUser() + kr("(") + typeAdmin + kr(")");
				m_lbUserInfo->setText(userType);

				QTimer::singleShot(500, this, SLOT(getDeviceList()));

				bool isLogined = s->isLoginAuto();
				if (isLogined)
				{
					s->setId(m->user()->id());
					s->setPass(m->user()->pass());
				}
				else
				{
					s->setId("");
					s->setPass("");
				}

				if (m_login != nullptr)
					m_login->hide();

			}
			else {
				m_alarm->initSize(350, 120)->setMessage(m->notificator()->message());
				m_alarm->show();
			}				
		}
		else if (noti->type() == Notificator::Logout)
		{
			result = noti->result();
			if (result) {

				//setFixedSize(0, 0);

				m_login = new CPLogin();
				m_login->setParent(this);
				m_login->show();

				s->loginAuto(false);
				s->setId("");
				s->setPass("");
				m->user()->clear();
			}
			else {
				m_alarm->initSize(350, 120)->setMessage(m->notificator()->message());
				m_alarm->show();
			}
		}		
		else if (noti->type() == Notificator::Join)
		{
			QString message = noti->message();
			if (message.isEmpty())
			{
				message = kr("회원가입에 성공하였습니다.");
			}

			m_alarm->initSize(350, 120)->setMessage(message);
			m_alarm->show();
		}
		else if (noti->type() == Notificator::Exit)
		{
			close();
		}
		if (noti->type() == Notificator::DVIList)
		{
			//newData(TAG_DVC_LIST);
			updateUI();
		}
		else
		{
			result = m->notificator()->result();
			if (!result) 
			{
				m_alarm->initSize(350, 120)->setMessage(m->notificator()->message());
				m_alarm->show();
			}
		}
		//if (m->notificator()->type() == Notificator::DVIBorrowedSearch) return;
	//	if (m->notificator()->type() == Notificator::DVIReturnedSearch) return;
	//	bool result = m->notificator()->result();
	//	if (m->notificator()->dialog()) {
	//		m_alarm->setMessage(result ?
	//			"성공적으로 반영되었습니다." : m->notificator()->message());
	//		m_alarm->show();
	//	}

	//	if (result)
	//	{
	//		if (m->notificator()->type() == Notificator::DVIList) listDVIces();
	//		else if (m->notificator()->type() == Notificator::MNGList) listMNGements();
	//		else if (m->notificator()->type() == Notificator::DVIModified) QTimer::singleShot(500, this, SLOT(listDVIces()));
	//		else if (m->notificator()->type() == Notificator::MNGModified) QTimer::singleShot(500, this, SLOT(listMNGements()));
	//		else if (m->notificator()->type() == Notificator::EMPList) listEMPloyees();
	//	}
	//	else
	//	{
	//		m_alarm->setMessage(m->notificator()->message());
	//		m_alarm->show();
	//	}
		m->alarm(false);
	}
}

void ViewHome::prev()
{
	m->setPageNumber(m->pageNumber() - 1);
	qDebug() << m->pageNumber();
	n->getDeviceList()->request();
}
void ViewHome::next()
{
	m->setPageNumber(m->pageNumber() + 1);
	qDebug() << m->pageNumber();
	n->getDeviceList()->request();

}

QString ViewHome::getCountDevice()
{
	return QString("%1").arg(m->countCurrentDevice()) + "/" + QString("%1").arg(m->countTotalDevice());
}