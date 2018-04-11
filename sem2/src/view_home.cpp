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

	m->request(true, Notificator::RequestPartsList);

	init();
	//clearAutoLogin();
	/* POSTPHONE AUTO LOGIN. */
	//if (s->isLoginAuto())
	//{
	//	m->user()->setId(s->id());
	//	m->user()->setPass(s->pass());
	//	m->request(true, Notificator::RequestLogin);
	//}
	//else
	//{
	m_login = new CPLogin();
	m_login->setParent(this);
	m_login->show();
	//}
	connect(m, SIGNAL(devicesChanged()), this, SLOT(updateUI()));
	connect(m, SIGNAL(rentsChanged()), this, SLOT(updateUI()));
	connect(m, SIGNAL(singsChanged()), this, SLOT(updateUI()));
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

	setMinimumWidth(m_style->width()); setMinimumHeight(m_style->height());
	setLayout(new QVBoxLayout);
	layout()->setAlignment(Qt::AlignTop);
	layout()->setMargin(0);
	layout()->setSpacing(0);

	connect(m_styleSlide, SIGNAL(extendedChanged()), this, SLOT(onSlided()));

#pragma region INITIALIZE BUTTONS IN SLIDE.
	m_btnSlideExt = (new Command("slide_ext", kr("◀"), m_styleSlide->wCol01, m_styleSlide->height()))
		->initStyleSheet(m_styleSlide->btnExtReleasedSheet)->initFontSize(8)
		->initEffect(m_styleSlide->btnExtReleasedSheet, m_styleSlide->btnExtReleasedSheet, m_styleSlide->btnExtHoverdSheet)
		->initFunc([=]()
	{
		bool extended = m_styleSlide->extended();
		m_styleSlide->extend(!extended);
		QString arrow = m_styleSlide->extended() ? kr("▶") : kr("◀");
		m_btnSlideExt->initName(arrow);
		updateUI();
	});

	Button* metaBtn;
	metaBtn = m_styleHeader->btnLogout();
	m_btnLogout = (new Command("logout", kr(metaBtn->name()), metaBtn->width(), metaBtn->height()))
		->initStyleSheet(metaBtn->releasedStyle())
		->initEffect(metaBtn->releasedStyle(), metaBtn->selectedStyle(), metaBtn->hoveredStyle())
		->initIcon(":/imgs/circle.png")->initFunc([=]()
	{
		m_question->initSize(350, 120)->setMessage(kr("로그아웃 하시겠습니까?"));
		m_question->func = [=]() {
			n->logout()->request();
		};
		m_question->show();
	});

	metaBtn = m_styleSlide->btnDVCList();
	m_btnDVCList =
		(new Command(TAG_DVC_LIST, kr(metaBtn->name()), metaBtn->width(), metaBtn->height()))
		->initStyleSheet(metaBtn->releasedStyle())
		->initEffect(metaBtn->releasedStyle(), metaBtn->selectedStyle(), metaBtn->hoveredStyle())
		->initIcon(metaBtn->icon(), metaBtn->name())
		->initFunc([=]()
	{
		netGetDeviceList();
		initDVCList();
	});

	metaBtn = m_styleSlide->btnMNGList();
	m_btnMNGList =
		(new Command(TAG_MNG_LIST, kr(metaBtn->name()), metaBtn->width(), metaBtn->height()))
		->initStyleSheet(metaBtn->releasedStyle())
		->initEffect(metaBtn->releasedStyle(), metaBtn->selectedStyle(), metaBtn->hoveredStyle())
		->initIcon(metaBtn->icon(), metaBtn->name())->initFunc([=]()
	{
		netGetRentList(0);
		initMNGList();
	});

	metaBtn = m_styleSlide->btnMNTList();
	m_btnMNTList =
		(new Command(TAG_MNT_LIST, kr(metaBtn->name()), metaBtn->width(), metaBtn->height()))
		->initStyleSheet(metaBtn->releasedStyle())
		->initEffect(metaBtn->releasedStyle(), metaBtn->selectedStyle(), metaBtn->hoveredStyle())
		->initIcon(metaBtn->icon(), metaBtn->name())
		->initFunc([=]()
	{
		initMNTList();
	});

	metaBtn = m_styleSlide->btnEMPList();
	m_btnEMPList =
		(new Command(TAG_EMP_LIST, kr(metaBtn->name()), metaBtn->width(), metaBtn->height()))
		->initStyleSheet(metaBtn->releasedStyle())
		->initEffect(metaBtn->releasedStyle(), metaBtn->selectedStyle(), metaBtn->hoveredStyle())
		->initIcon(metaBtn->icon(), metaBtn->name())
		->initFunc([=]()
	{
		initEMPList();
	});

	metaBtn = m_styleSlide->btnImExport();
	m_btnImExport = (new Command(TAG_IMEXPORT, kr(metaBtn->name()), metaBtn->width(), metaBtn->height()))
		->initStyleSheet(metaBtn->releasedStyle())
		->initEffect(metaBtn->releasedStyle(), metaBtn->selectedStyle(), metaBtn->hoveredStyle())
		->initIcon(metaBtn->icon(), metaBtn->name())
		->initFunc([=]()
	{
		m_barcoder = new Barcoder(kr("대출/반납하기"), 520, 230);
		m_barcoder->show();
	});

	m_cmdProviderList = new CommandProvider();
	m_cmdProviderList->append(m_btnDVCList)->append(m_btnMNGList)->append(m_btnMNTList)->append(m_btnEMPList);
#pragma endregion

#pragma region  INITIALIZE HEADER.
	m_header = new QWidget(this);
	m_header->setLayout(new QHBoxLayout);
	m_header->layout()->setMargin(0);
	m_header->layout()->setSpacing(0);
	m_header->layout()->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	m_headerCol01 = (new CPLabel(m_styleHeader->wCol01, m_styleHeader->height(), kr(m_styleHeader->txtTitle)))
		->initAlignment(Qt::AlignLeft | Qt::AlignVCenter)
		->initContentsMargins(15, 0, 0, 0)
		->initFontSize(20)
		->initFontBold()
		->initStyleSheet("color:white;");

	m_headerCol02 = (new CPWidget(m_styleHeader->width() - m_styleHeader->wCol01, m_styleHeader->height(), new QHBoxLayout))
		->initAlignment(Qt::AlignRight | Qt::AlignVCenter)
		->initContentsMargins(0, 10, 0, 0);

	m_lbUserInfo = (new CPLabel(m_styleHeader->width() - m_styleHeader->wCol01 - m_btnLogout->width() - 10, m_styleHeader->height(), ""))
		->initAlignment(Qt::AlignRight | Qt::AlignVCenter)
		->initContentsMargins(0, 10, 0, 0)
		->initFontSize(12)
		->initStyleSheet("color:white;");

	m_headerCol02->append(m_lbUserInfo)->append(m_btnLogout);
	m_header->layout()->addWidget(m_headerCol01);
	m_header->layout()->addWidget(m_headerCol02);
#pragma endregion

	m_body = new QWidget(this);
	m_body->setLayout(new QHBoxLayout);
	m_body->layout()->setMargin(0);
	m_body->layout()->setSpacing(0);

	m_footer = new QWidget(this);

	m_content = new QWidget(this);
	m_content->setLayout(new QVBoxLayout);
	m_content->layout()->setAlignment(Qt::AlignLeft | Qt::AlignTop);
	m_content->layout()->setMargin(0);
	m_content->layout()->setSpacing(0);

	m_slide = new QWidget(this);
	m_slide->setLayout(new QHBoxLayout);
	m_slideCol01 = new QWidget(m_slide);
	m_slideCol01->setLayout(new QVBoxLayout);
	m_slideCol02 = (new CPWidget(m_styleSlide->wCol01, m_styleSlide->height(), new QVBoxLayout))
		->initAlignment(Qt::AlignRight | Qt::AlignTop)
		->initSpacing(10)->initContentsMargins(0, 10, 10, 0);

	m_slide->layout()->setMargin(0);
	m_slide->layout()->setSpacing(0);
	m_slideCol01->layout()->setAlignment(Qt::AlignCenter);
	m_slideCol01->layout()->setMargin(0);
	m_slideCol01->layout()->addWidget(m_btnSlideExt);
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

	m_body->layout()->addWidget(m_content);
	m_body->layout()->addWidget(m_slide);

	m_slide->layout()->addWidget(m_slideCol01);
	m_slide->layout()->addWidget(m_slideCol02);
	m_slideCol02->append(m_btnDVCList)->append(m_btnMNGList)->append(m_btnMNTList)->append(m_btnEMPList);

	m_emptyArea = (new CPLabel(0, 0, ""));


	m_slideCol02->append(m_emptyArea);
	m_slideCol02->append(m_btnImExport);
	m_cmdProviderList->append(m_btnImExport);

	/*** ADD WIDGETS. END. ***/

	initDVCList();
	m_btnDVCList->select(true);

	updateUI();
}
void ViewHome::resizeEvent(QResizeEvent *e)
{
	if (!m_initedUI) {
		m_initedUI = true;
		return;
	}

	QSize newSize = e->size();
	QSize oldSize = e->oldSize();
	m_style->setWidth(newSize.width());
	m_style->setHeight(newSize.height());
	print("MAIN", newSize.width(), newSize.height());
	updateUI();
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

	int wGrid1_1 = m_contentRow1->width() / 2;
	int wGrid1_2 = 0;
	int wGrid1_3 = m_contentRow1->width() / 2;
	if (!m_cmdProviderList->selectedTag().compare(TAG_MNG_LIST) ||
		!m_cmdProviderList->selectedTag().compare(TAG_MNT_LIST)) {
		wGrid1_1 = m_contentRow1->width() / 3;
		wGrid1_2 = m_contentRow1->width() / 3;
		wGrid1_3 = m_contentRow1->width() / 3;
	}
	m_contentGrid1_1->setFixedWidth(wGrid1_1);
	m_contentGrid1_2->setFixedWidth(wGrid1_2);
	m_contentGrid1_3->setFixedWidth(wGrid1_3);

	m_slide->setFixedSize(wSlide, hSlide);
	m_slideCol01->setFixedSize(wSlideCol01, hSlide);
	m_slideCol02->setFixedSize(wSlideCol02, hSlide);
	m_emptyArea->setFixedSize(1, hSlide - m_cmdProviderList->totalHeight() - 10 * (m_cmdProviderList->count() + 2));

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

	QString mm = m_cmdProviderList->selectedTag();
	if (!m_cmdProviderList->selectedTag().compare(TAG_DVC_LIST))
	{
		newTable(20, TAG_DVC_LIST);
		newNavi();
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
	else if (!m_cmdProviderList->selectedTag().compare(TAG_MNG_LIST))
	{
		newTable(100, TAG_MNG_LIST);
		MetaTableMNG* castedMetaTable = qobject_cast<MetaTableMNG*>(m_metaTable);
		m_metaTable->setWidth(m_content->width());
		m_metaTable->setHeight(m_content->height() - m_contentRow1->height());
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

		QString selectedTime = m_currentYear + m_currentMonth;
		QString tYear = QDateTime::currentDateTime().addMonths(0).toString("yyyy");
		QString tMonth = QDateTime::currentDateTime().addMonths(0).toString("MM");
		QString tTime = tYear + tMonth;
		metaBtn = m_styleContent->btnCalendarNext();
		if (selectedTime.toInt() < tTime.toInt())
		{
			m_btnCalendarNext->initEnabled(true)->initStyleSheet(metaBtn->releasedStyle())
				->initEffect(metaBtn->releasedStyle(), metaBtn->selectedStyle(), metaBtn->hoveredStyle());
		}
		else
		{
			Palette* p = new Palette();
			m_btnCalendarNext->initEnabled(false)->initStyleSheet(p->btnSelectedStyleDiabled)
				->initEffect(p->btnSelectedStyleDiabled,
					p->btnSelectedStyleDiabled,
					p->btnSelectedStyleDiabled);
		}
	}
	else if (!m_cmdProviderList->selectedTag().compare(TAG_MNT_LIST))
	{
		MetaTableMNT* metaTable = qobject_cast<MetaTableMNT*>(m_metaTable);
		m_metaTable->setWidth(m_content->width());
		m_metaTable->setHeight(m_content->height() - m_contentRow1->height());
		m_checkTable->initSize(m_content->width() - 20);
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

		QString selectedTime = m_currentYear + m_currentMonth;
		QString tYear = QDateTime::currentDateTime().addMonths(0).toString("yyyy");
		QString tMonth = QDateTime::currentDateTime().addMonths(0).toString("MM");
		QString tTime = tYear + tMonth;
		metaBtn = m_styleContent->btnCalendarNext();
		if (selectedTime.toInt() < tTime.toInt())
		{
			m_btnCalendarNext->initEnabled(true)->initStyleSheet(metaBtn->releasedStyle())
				->initEffect(metaBtn->releasedStyle(), metaBtn->selectedStyle(), metaBtn->hoveredStyle());
		}
		else
		{
			Palette* p = new Palette();
			m_btnCalendarNext->initEnabled(false)->initStyleSheet(p->btnSelectedStyleDiabled)
				->initEffect(p->btnSelectedStyleDiabled,
					p->btnSelectedStyleDiabled,
					p->btnSelectedStyleDiabled);
		}
	}
	else if (!m_cmdProviderList->selectedTag().compare(TAG_EMP_LIST))
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
#pragma region INITIALIZE BUTTONS.
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

	m_contentGrid1_3->append(m_btnNew)->append(m_btnEdit)->append(m_btnRemove)->append(m_btnPrint);

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
#pragma endregion
	updateUI();
}
void ViewHome::initMNGList()
{
	if (!initPage(TAG_MNG_LIST, kr("관리대장"))) return;

#pragma region INITIALIZE BUTTONS.
	Button* metaBtn;
	metaBtn = m_styleContent->btnViewAll();
	m_btnViewAll = (new Command(TAG_VIEW_ALL, kr(metaBtn->name()), metaBtn->width(), metaBtn->height()))
		->initStyleSheet(metaBtn->releasedStyle())
		->initEffect(metaBtn->releasedStyle(), metaBtn->selectedStyle(), metaBtn->hoveredStyle())
		->initIcon(m_styleContent->btnViewAll()->icon())
		->initFunc([=]() {		
		if (m_cmdProviderView->selectedTag().compare(TAG_VIEW_ALL))
		{			
			netGetRentList(0);
			m_cmdProviderView->select(TAG_VIEW_ALL);
			m_btnCalendarPrev->setVisible(false);
			m_lbCalendar->setVisible(false);
			m_btnCalendarNext->setVisible(false);
		}		
	});

	metaBtn = m_styleContent->btnViewDate();
	m_btnViewDate = (new Command(TAG_VIEW_DATE, kr(metaBtn->name()), metaBtn->width(), metaBtn->height()))
		->initStyleSheet(metaBtn->releasedStyle())
		->initEffect(metaBtn->releasedStyle(), metaBtn->selectedStyle(), metaBtn->hoveredStyle())
		->initIcon(m_styleContent->btnViewDate()->icon())
		->initFunc([=]() {
		if (m_cmdProviderView->selectedTag().compare(TAG_VIEW_DATE))
		{
			netGetRentList(1);
			m_lbCalendar->initText(getCurrentDate(0));
			m_cmdProviderView->select(TAG_VIEW_DATE);
			m_btnCalendarPrev->setVisible(true);
			m_lbCalendar->setVisible(true);
			m_btnCalendarNext->setVisible(true);
		}
	});

	metaBtn = m_styleContent->btnCalendarPrev();
	m_btnCalendarPrev =
		(new Command("cal_prev", kr(metaBtn->name()), metaBtn->width(), metaBtn->height()))
		->initStyleSheet(metaBtn->releasedStyle())->initVisible(false)
		->initEffect(metaBtn->releasedStyle(), metaBtn->selectedStyle(), metaBtn->hoveredStyle())
		->initFunc([=]() {
		m_lbCalendar->initText(getCurrentDate(--m_countMonth));
		updateUI();
	});

	metaBtn = m_styleContent->btnCalendarNext();
	m_btnCalendarNext =
		(new Command("cal_next", kr(metaBtn->name()), metaBtn->width(), metaBtn->height()))
		->initStyleSheet(metaBtn->releasedStyle())->initVisible(false)
		->initEffect(metaBtn->releasedStyle(), metaBtn->selectedStyle(), metaBtn->hoveredStyle())
		->initFunc([=]() {
		m_lbCalendar->initText(getCurrentDate(++m_countMonth));
		updateUI();
	});

#pragma endregion

	if (m_cmdProviderView != nullptr) m_cmdProviderView->clear();
	else m_cmdProviderView = new CommandProvider();
	m_cmdProviderView->append(m_btnViewAll)->append(m_btnViewDate);
	m_cmdProviderView->select(TAG_VIEW_ALL);

	m_lbCalendar = (new CPLabel(100, 30, getCurrentDate(0)))->initVisible(false)
		->initAlignment(Qt::AlignCenter)->initFontSize(15);
	m_contentGrid1_2->append(m_btnCalendarPrev)->append(m_lbCalendar)->append(m_btnCalendarNext);
	m_contentGrid1_3->append(m_btnViewAll)->append(m_btnViewDate);
#pragma endregion

	updateUI();
}
void ViewHome::initMNTList()
{
	if (!initPage(TAG_MNT_LIST, kr("월별대장"))) return;
	//newMetaTable(TAG_MNT_LIST);

#pragma region INITIALIZE BUTTONS.
	Button* metaBtn;
	metaBtn = m_styleContent->btnCalendarPrev();
	m_btnCalendarPrev =
		(new Command("cal_prev", kr(metaBtn->name()), metaBtn->width(), metaBtn->height()))
		->initStyleSheet(metaBtn->releasedStyle())
		->initEffect(metaBtn->releasedStyle(), metaBtn->selectedStyle(), metaBtn->hoveredStyle())
		->initFunc([=]() {
		m_lbCalendar->initText(getCurrentDate(--m_countMonth));
		updateUI();
	});

	metaBtn = m_styleContent->btnCalendarNext();
	m_btnCalendarNext =
		(new Command("cal_next", kr(metaBtn->name()), metaBtn->width(), metaBtn->height()))
		->initStyleSheet(metaBtn->releasedStyle())
		->initEffect(metaBtn->releasedStyle(), metaBtn->selectedStyle(), metaBtn->hoveredStyle())
		->initFunc([=]() {
		m_lbCalendar->initText(getCurrentDate(++m_countMonth));
		updateUI();
	});
#pragma endregion

	m_lbCalendar = (new CPLabel(100, 30, getCurrentDate(0)))
		->initAlignment(Qt::AlignCenter)->initFontSize(15);
	m_contentGrid1_2->append(m_btnCalendarPrev)->append(m_lbCalendar)->append(m_btnCalendarNext);
#pragma endregion

	MetaTableMNT* metaTable = qobject_cast<MetaTableMNT*>(m_metaTable);
	m_btnCheckExt = (new Command("check_ext", metaTable->txt2, m_content->width(), metaTable->hExt))
		->initStyleSheet(metaTable->btnExtReleasedSheet)->initIcon("", metaTable->txt2)
		->initEffect(metaTable->btnExtReleasedSheet, metaTable->btnExtHoverdSheet, metaTable->btnExtHoverdSheet)
		->initFunc([=]() {

		bool folded = !m_btnCheckExt->selected();
		int h = folded ? (12 * 30 + 24) : 0;
		m_checkTable->initHeight(h);
		m_btnCheckExt->initName(folded ? metaTable->txt2 : metaTable->txt1);
		m_btnCheckExt->select(folded);
		updateUI();
	});
	m_btnCheckExt->select(true);

	m_mntStack = (new CPWidget(m_content->width(), m_content->height(), new QVBoxLayout))
		->initAlignment(Qt::AlignLeft | Qt::AlignTop);
	m_mntScrArea = new QScrollArea(this);
	m_mntScrArea->setWidget(m_mntStack);
	m_content->layout()->addWidget(m_mntScrArea);

	m_checkTable = new CheckTable();
	m_mntStack->append(m_btnCheckExt)->append(m_checkTable);

	m_mntTables.clear();
	m_cmdProviderExt = new CommandProvider();
	for (int i = 0; i < 8; i++)
	{
		Command* m_btnExt = (new Command("ext_" + QString("%1").arg(i), metaTable->txt1, m_content->width(), metaTable->hExt))
			->initStyleSheet(metaTable->btnExtReleasedSheet)->initIcon("", metaTable->txt2)
			->initEffect(metaTable->btnExtReleasedSheet, metaTable->btnExtHoverdSheet, metaTable->btnExtHoverdSheet)
			->initFunc([=]() {
			Command* cmd = m_cmdProviderExt->command(i);
			bool folded = cmd->selected();
			cmd->initName(folded ? metaTable->txt1 : metaTable->txt2);
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
	/* DON'T INITIALIZE. */
	if (!m_cmdProviderList->selectedTag().compare(tag)) return false;

	m->setPageNumber(1);		/* INITIALIZE PAGE NUMBER */
	m_cmdProviderList->select(tag); /* SELECT BUTTON & UPDATE TAG */

#pragma region INITIALIZE MetaTable.
	if (!tag.compare(TAG_DVC_LIST)) m_metaTable = new MetaTableDVC();
	else if (!tag.compare(TAG_MNG_LIST)) m_metaTable = new MetaTableMNG();
	else if (!tag.compare(TAG_MNT_LIST)) m_metaTable = new MetaTableMNT();
	else if (!tag.compare(TAG_EMP_LIST)) m_metaTable = new MetaTableEMP();
#pragma endregion
#pragma region INITIALIZE Widgets.
	if (m_contentGrid1_1 != nullptr)
	{
		delete m_contentGrid1_1;
		m_contentGrid1_1 = nullptr;
	}
	if (m_contentGrid1_2 != nullptr)
	{
		delete m_contentGrid1_2;
		m_contentGrid1_2 = nullptr;
	}
	if (m_contentGrid1_3 != nullptr)
	{
		delete m_contentGrid1_3;
		m_contentGrid1_3 = nullptr;
	}
	if (m_contentRow1 != nullptr)
	{
		delete m_contentRow1;
		m_contentRow1 = nullptr;
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
		m_mntScrArea = nullptr;
	}
#pragma endregion
#pragma region INITIALIZE Row1
	m_contentRow1 = (new CPWidget(m_styleContent->width(), m_styleContent->hRow01, new QHBoxLayout))
		->initAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	m_content->layout()->addWidget(m_contentRow1);

	int wGrid1_1 = m_contentRow1->width() / 2;
	int wGrid1_2 = 0;
	int wGrid1_3 = m_contentRow1->width() / 2;
	if (!tag.compare(TAG_MNG_LIST) || !tag.compare(TAG_MNT_LIST)) {
		wGrid1_1 = m_contentRow1->width() / 3;
		wGrid1_2 = m_contentRow1->width() / 3;
		wGrid1_3 = m_contentRow1->width() / 3;
	}

	m_contentGrid1_1 = (new CPWidget(wGrid1_1, m_styleContent->hRow01, new QHBoxLayout))
		->initAlignment(Qt::AlignLeft | Qt::AlignVCenter)->initContentsMargins(10, 0, 0, 0)->initSpacing(10)
		->append((new CPLabel(20, 20))->initImage(":/imgs/circle.png"))
		->append((new CPLabel(m_styleContent->wGrid1_1 - 40, m_styleContent->hRow01, titleTxt))->initFontSize(20)
			->initAlignment(Qt::AlignLeft | Qt::AlignVCenter));
	m_contentRow1->append(m_contentGrid1_1);

	m_contentGrid1_2 = (new CPWidget(wGrid1_2, m_styleContent->hRow01, new QHBoxLayout))
		->initSpacing(10)
		->initAlignment(Qt::AlignCenter);
	//->initContentsMargins(0, 20, 0, 0);
	m_contentRow1->append(m_contentGrid1_2);

	m_contentGrid1_3 = (new CPWidget(wGrid1_3, m_styleContent->hRow01, new QHBoxLayout))
		->initSpacing(10)
		->initAlignment(Qt::AlignRight | Qt::AlignVCenter)
		->initContentsMargins(0, 10, 0, 0);
	m_contentRow1->append(m_contentGrid1_3);
#pragma endregion

	return true;
}
void ViewHome::newTable(int rowCount, QString tag)
{
	if (m_tableCommon != nullptr)
	{
		delete m_tableCommon;
		m_tableCommon = nullptr;
	}
	m_tableCommon = new QTableWidget(this);
	m_tableCommon->setRowCount(rowCount);
	m_tableCommon->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_tableCommon->setSelectionMode(QAbstractItemView::SingleSelection);
	m_tableCommon->horizontalScrollBar()->setDisabled(true);
	m_tableCommon->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_tableCommon->horizontalHeader()->setStyleSheet("QHeaderView::section { background-color:#eeeeee }");
	m_tableCommon->verticalHeader()->hide();
	m_content->layout()->addWidget(m_tableCommon);

#pragma region INITIALIZE NAVIGATION BUTTON.

#pragma endregion
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
	m_btnNaviPrev =
		(new Command("navi_left", kr(metaBtn->name()), metaBtn->width(), metaBtn->height()))
		->initStyleSheet(metaBtn->releasedStyle())
		->initEffect(metaBtn->releasedStyle(), metaBtn->selectedStyle(), metaBtn->hoveredStyle())
		->initFunc([=]() { prev(); });

	metaBtn = m_styleContent->btnNaviRight();
	m_btnNaviNext =
		(new Command("navi_right", kr(metaBtn->name()), metaBtn->width(), metaBtn->height()))
		->initStyleSheet(metaBtn->releasedStyle())
		->initEffect(metaBtn->releasedStyle(), metaBtn->selectedStyle(), metaBtn->hoveredStyle())
		->initFunc([=]() { next(); });

	Palette* p = new Palette();
	m_lbNavi = (new CPLabel(100, 30, getCountDevice()))->initAlignment(Qt::AlignCenter);
	m_navi = new QWidget();
	m_navi->setFixedSize(m_styleContent->width(), m_metaTable->hNavi());
	m_navi->setLayout(new QHBoxLayout);
	m_navi->layout()->setMargin(0);
	m_navi->layout()->setSpacing(0);
	m_navi->layout()->setAlignment(Qt::AlignCenter);
	//m_navi->setStyleSheet("background: " + p->navy04);
	m_navi->layout()->addWidget(m_btnNaviPrev);
	m_navi->layout()->addWidget(m_lbNavi);
	m_navi->layout()->addWidget(m_btnNaviNext);
	m_content->layout()->addWidget(m_navi);
	m_lbNavi->setText(getCountDevice());


	if (m->countCurrentDevice() > 20)
	{
		m_btnNaviPrev->initEnabled(true)->initStyleSheet(metaBtn->releasedStyle())
			->initEffect(metaBtn->releasedStyle(), metaBtn->selectedStyle(), metaBtn->hoveredStyle());
	}
	else
	{
		m_btnNaviPrev->initEnabled(false)->initStyleSheet(p->btnSelectedStyleDiabled)
			->initEffect(p->btnSelectedStyleDiabled,
				p->btnSelectedStyleDiabled,
				p->btnSelectedStyleDiabled);
	}

	if (m->countCurrentDevice() < m->countTotalDevice())
	{
		m_btnNaviNext->initEnabled(true)->initStyleSheet(metaBtn->releasedStyle())
			->initEffect(metaBtn->releasedStyle(), metaBtn->selectedStyle(), metaBtn->hoveredStyle());
	}
	else
	{
		m_btnNaviNext->initEnabled(false)->initStyleSheet(p->btnSelectedStyleDiabled)
			->initEffect(p->btnSelectedStyleDiabled,
				p->btnSelectedStyleDiabled,
				p->btnSelectedStyleDiabled);
	}

}

void ViewHome::handler()
{
	if (m->alarmed())
	{
		bool result = false;
		Notificator* noti = m->notificator();
		if (noti->type() == Notificator::RequestLogin)
		{
			QTimer::singleShot(500, this, SLOT(netLogin()));
		}
		else if (noti->type() == Notificator::Login)
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

				QTimer::singleShot(500, this, SLOT(netGetDeviceList()));

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

				if (m->user()->typeAlarm() == 1)
				{
					m_alarm->initSize(350, 120)->setMessage(m->user()->textAlarm());
					m_alarm->show();
				}
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
			//close();
		}
		else if (noti->type() == Notificator::DVIList)
		{
			//newData(TAG_DVC_LIST);
			updateUI();
		}
		else if (noti->type() == Notificator::RequestPartsList)
		{
			n->getPartList()->request();
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
		m->alarm(false);
	}
}

void ViewHome::prev()
{
	m->setPageNumber(m->pageNumber() - 1);
	qDebug() << m->pageNumber();
	netGetDeviceList();
}
void ViewHome::next()
{
	m->setPageNumber(m->pageNumber() + 1);
	qDebug() << m->pageNumber();
	netGetDeviceList();

}

#pragma region UTILITY FUNCTION.
QString ViewHome::getCountDevice()
{
	return QString("%1").arg(m->countCurrentDevice()) + "/" + QString("%1").arg(m->countTotalDevice());
}
QString ViewHome::getCurrentDate(int month)
{
	m_currentYear = QDateTime::currentDateTime().addMonths(month).toString("yyyy");
	m_currentMonth = QDateTime::currentDateTime().addMonths(month).toString("MM");
	return m_currentYear + "." + m_currentMonth;
}
void ViewHome::netGetDeviceList(int searchType)
{
	switch (m->user()->typeAdmin())
	{
	case 1:
	case 2:
	{
		n->getDeviceList(searchType)->request();
		break;
	}
	case 3:
	case 4:
	{
		n->getDeviceListForAdmin(0, searchType)->request();
		break;
	}
	}
}
void ViewHome::netGetRentList(int type, int noPart)
{
	switch (m->user()->typeAdmin())
	{
	case 1:
	case 2:
	{
		n->getRentList(type, m_currentYear.toInt(), m_currentMonth.toInt())->request();
		break;
	}
	case 3:
	case 4:
	{
		n->getRentListForAdmin(type, m_currentYear.toInt(), m_currentMonth.toInt(), noPart)->request();
		break;
	}
	}
}
void ViewHome::netLogin()
{
	n->login(m->user()->id(), m->user()->pass())->request();
}
#pragma endregion



void ViewHome::clearAutoLogin()
{
	s->setId("");
	s->setPass("");
	s->loginAuto(false);
}
ViewHome::~ViewHome()
{

}