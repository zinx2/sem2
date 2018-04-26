#include "view_home.h"
#include "cs_qheader.h"
#include "cs_checktable.h"
#include "cs_form_add.h"
#include "cs_form_edit.h"
#include "cs_barcoder.h"
#include "cs_form_borrow.h"
#include "cs_form_return.h"
#include "cs_form_signature.h"
ViewHomePC::ViewHomePC(QWidget *parent)
	: ViewHome(parent)
{
	setWindowTitle(kr("온라인평생교육원 자산 관리 시스템"));

	m = Model::instance();
	n = NetWorker::instance();
	s = Settings::instance();

	m_alarm = new Alarm(kr("알림"), "", 350, 200);
	m_question = new Question(kr("알림"), "", 350, 200);


	//m->request(true, Notificator::RequestPartsList);

	initParent();
	//clearAutoLogin();
	/* POSTPHONE AUTO LOGIN. */
	if (s->isLoginAuto())
	{
		m->user()->setId(s->id());
		m->user()->setPass(s->pass());
		m->request(true, Notificator::RequestLogin);
	}
	else
	{
		m_login = new CPLogin();
		m_login->setParent(this);
		m_login->show();
	}

	connect(m, SIGNAL(alarmedChanged()), this, SLOT(netHandler()));
	connect(m, SIGNAL(devicesChanged()), this, SLOT(initListDVC()));
	connect(m, SIGNAL(rentsChanged()), this, SLOT(updateUI()));
	connect(m, SIGNAL(employeesChanged()), this, SLOT(updateUI()));
	connect(m, SIGNAL(signaturesChanged()), this, SLOT(updateMNGSign()));
	connect(m, SIGNAL(signaturesChanged()), this, SLOT(updateMNTCheckTable()));
	//setFixedSize(0, 0);
	//run();
}
void ViewHomePC::initParent()
{
	initStyles();
	initSlideButton();
	initParentLayout();
	initHeader();
	initBody();
	initContent();
	initFooter();
	initSlide();
	initListDVC();

	connect(m_styleSlide, SIGNAL(extendedChanged()), this, SLOT(onSlided()));
}
void ViewHomePC::resizeEvent(QResizeEvent *e)
{
	if (!m_initedUI) {
		m_initedUI = true;
		return;
	}

	QSize newSize = e->size();
	QSize oldSize = e->oldSize();
	m_style->setWidth(newSize.width());
	m_style->setHeight(newSize.height());
	//print("MAIN", newSize.width(), newSize.height());
	updateUI();
}
void ViewHomePC::updateUI()
{
	updateBody();
	updateContent();
	updateHeader();
	updateFooter();
	updateContentRow1();
	updateContentRow2();
	updateSlideButtons();
	updateSlide();

	QString tag = m_cmdProviderList->selectedTag();
	if (!tag.compare(TAG_DVC_LIST)) initTableDVC();
	else if (!tag.compare(TAG_MNG_LIST)) initTableMNG();
	else if (!tag.compare(TAG_MNT_LIST)) initTableMNT();
	else if (!tag.compare(TAG_EMP_LIST)) initTableEMP();
}
void ViewHomePC::initListDVC()
{
	//if (!initPage(TAG_DVC_LIST, kr("장비목록"))) return;
	m_titleTxt = kr("장비목록");
	m_cmdProviderList->select(TAG_DVC_LIST); /* SELECT BUTTON & UPDATE TAG */
	m_metaTable = new MetaTableDVC();
	initWidgets();
	initContentRow1();
	initContentRow2();

	initButtonsDVC();
	updateUI();
}
void ViewHomePC::initListMNG()
{
	if (!initPage(TAG_MNG_LIST, kr("관리대장"))) return;
	m_countMonth = 0;
	getCurrentDate(0);
	initButtonsMNG();
	initMNGNaviCalendar();
	updateUI();
}
void ViewHomePC::initListMNT(bool skip)
{
	if (!initPage(TAG_MNT_LIST, kr("월별대장"), skip)) return;
	initButtonsMNT();

	QString dateTime = (m_currentYear + "." + m_currentMonth);
	if (skip) {
		m_countMonth = 0;
		dateTime = getCurrentDate(0);
	}

	m_lbCalendar = (new CPLabel(100, 30, dateTime))
		->initAlignment(Qt::AlignCenter)->initFontSize(12);
	m_contentGrid1_2->append(m_btnCalendarPrev)->append(m_lbCalendar)->append(m_btnCalendarNext);

	MetaTableMNT* metaTable = qobject_cast<MetaTableMNT*>(m_metaTable);
	m_btnCheckExt = (new Command("check_ext", metaTable->txt2 + kr("월별점검"), m_content->width(), metaTable->hExt))
		->initStyleSheet(metaTable->btnExtReleasedSheet)->initIcon("", metaTable->txt2 + kr("월별점검"))
		->initEffect(metaTable->btnExtReleasedSheet, metaTable->btnExtHoverdSheet, metaTable->btnExtHoverdSheet)
		->initFunc([=]() {

		bool folded = !m_btnCheckExt->selected();
		int h = folded ? (12 * 30 + 24) : 0;
		m_checkTable->initHeight(h);
		m_btnCheckExt->initName(folded ? metaTable->txt2 + kr("월별점검") : metaTable->txt1 + kr("월별점검"));
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
	/*** 상위 사인 점검 출력 ***/

	m_mntTables.clear();
	m_mntZoneSign.clear();
	m_cmdProviderExt = new CommandProvider();
	for (int i = 0; i < m->parts().size(); i++)
	{
		CPBoxSign* zoneSign = new CPBoxSign(m_content->width() - 25, 0, new QHBoxLayout,
			[=]() {
			QString currentNamePart = m_mntZoneSign.at(i)->namePart();//zoneSign->namePart();
			int currentYear = m_currentYear.toInt();
			int currentMonth = m_currentMonth.toInt();
			foreach(Sign* s, m->signatures())
			{
				if (!currentNamePart.compare(s->namePart()) && currentYear == s->year() && currentMonth == s->month())
				{
					FormSignature* sg = new FormSignature(s->noSign(), 500, 250);
					sg->show();
					break;
				}
			}
		});
		zoneSign->setNamePart(m->parts().at(i)->namePart());
		m_mntZoneSign.append(zoneSign);

		QString releaseTxt = metaTable->txt1 + m->parts().at(i)->namePart();
		QString selectedTxt = metaTable->txt2 + m->parts().at(i)->namePart();
		/** 확장버튼 생성 **/
		Command* m_btnExt = (new Command(m->parts().at(i)->namePart(), releaseTxt, m_content->width(), metaTable->hExt))
			->initStyleSheet(metaTable->btnExtReleasedSheet)->initIcon("", selectedTxt)
			->initEffect(metaTable->btnExtReleasedSheet, metaTable->btnExtHoverdSheet, metaTable->btnExtHoverdSheet)
			->initFunc([=]() {
			Command* cmd = m_cmdProviderExt->command(i);
			bool folded = cmd->selected();

			int hZoneSign = !folded ? 60 : 0;
			bool searched = false;
			for (int i = 0; i < m->rents().size(); i++)
			{
				if (!cmd->tag().compare(m->rents().at(i)->namePart()))
					searched = true;
			}
			if (!searched) hZoneSign = 0;
			zoneSign->setFixedHeight(hZoneSign);
			cmd->initName(folded ? releaseTxt : selectedTxt);
			cmd->select(!folded);

			CPTable* tb = m_mntTables.at(i);
			tb->setFixedHeight(folded ? 0 : tb->metaHeight());
			updateUI();
		});
		m_cmdProviderExt->append(m_btnExt);
		m_mntStack->append(m_btnExt);
		m_mntStack->append(zoneSign);

		CPTable* table = (new CPTable(new MetaTableExtendable));// ->resize();
		m_mntTables.append(table);
		m_mntStack->append(table); 	/*** 표 넣기 ***/
	}
	updateUI();
}
void ViewHomePC::initListEMP()
{
	if (!initPage(TAG_EMP_LIST, kr("직원관리"))) return;
	newTable(100, TAG_EMP_LIST);
	initButtonsEMP();
	updateUI();
}
bool ViewHomePC::initPage(QString tag, QString titleTxt, bool skip)
{
	m_titleTxt = titleTxt;
	/* DON'T INITIALIZE. */
	if (!m_cmdProviderList->selectedTag().compare(tag) && skip) return false;

	m->setPageNumber(1);		/* INITIALIZE PAGE NUMBER */
	m_cmdProviderList->select(tag); /* SELECT BUTTON & UPDATE TAG */

#pragma region INITIALIZE MetaTable.
	if (!tag.compare(TAG_DVC_LIST)) m_metaTable = new MetaTableDVC();
	else if (!tag.compare(TAG_MNG_LIST)) m_metaTable = new MetaTableMNG();
	else if (!tag.compare(TAG_MNT_LIST)) m_metaTable = new MetaTableMNT();
	else if (!tag.compare(TAG_EMP_LIST)) m_metaTable = new MetaTableEMP();
#pragma endregion

	initWidgets();
	initContentRow1();
	initContentRow2();

	return true;
}
void ViewHomePC::newTable(int rowCount, QString tag)
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
}
void ViewHomePC::newNavi()
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
		->initDisabledEffect(metaBtn->disabledReleasedStyle(), metaBtn->disabledSelectedStyle(), metaBtn->disabledHoveredStyle())
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

void ViewHomePC::prev()
{
	m->setPageNumber(m->pageNumber() - 1);
	qDebug() << m->pageNumber();
	netGetDeviceList();
}
void ViewHomePC::next()
{
	m->setPageNumber(m->pageNumber() + 1);
	qDebug() << m->pageNumber();
	netGetDeviceList();
}

#pragma region UTILITY FUNCTION.
QString ViewHomePC::getCountDevice()
{
	int current = (m->countCurrentDevice() / COUNT_PAGE) + (m->countCurrentDevice() % COUNT_PAGE == 0 ? 0 : 1);
	int total = (m->countTotalDevice() / COUNT_PAGE) + (m->countTotalDevice() % COUNT_PAGE == 0 ? 0 : 1);
	return QString("%1").arg(current) + "/" + QString("%1").arg(total);
}
QString ViewHomePC::getCurrentDate(int month)
{
	m_currentYear = QDateTime::currentDateTime().addMonths(month).toString("yyyy");
	m_currentMonth = QDateTime::currentDateTime().addMonths(month).toString("MM");
	return m_currentYear + "." + m_currentMonth;
}
void ViewHomePC::netGetDeviceList(int searchType)
{
	switch (m->user()->typeAdmin())
	{
	case User::PartManager:
	case User::PartChair:
	{
		n->getDeviceList(searchType)->request();
		break;
	}
	case User::SpecialList:
	case User::SystemAdmin:
	{
		n->getDeviceListForAdmin(0, searchType)->request();
		break;
	}
	}
}
void ViewHomePC::netGetRentList(int type)
{
	qDebug() << m_currentYear.toInt() << "/" << m_currentMonth.toInt();
	switch (m->user()->typeAdmin())
	{
	case User::PartManager:
	case User::PartChair:
	{
		QString tag = m_cmdProviderList->selectedTag();
		if (!m_cmdProviderList->selectedTag().compare(TAG_MNG_LIST))
		{
			if (m_cmdProviderView == nullptr)
				n->getRentList(type, m_currentYear.toInt(), m_currentMonth.toInt())->request();
			else if (!m_cmdProviderView->selectedTag().compare(TAG_VIEW_ALL))
				n->getRentList(type, m_currentYear.toInt(), m_currentMonth.toInt())->request();
			else
				n->getTotalRentListMonth(m_currentYear.toInt(), m_currentMonth.toInt())->request();
		}
		else if (!m_cmdProviderList->selectedTag().compare(TAG_MNT_LIST))
		{
			n->getTotalRentListMonth(m_currentYear.toInt(), m_currentMonth.toInt())->request();
		}
		break;
	}
	case User::SpecialList:
	case User::SystemAdmin:
	{
		if (!m_cmdProviderList->selectedTag().compare(TAG_MNG_LIST))
		{
			if (m_cmdProviderView == nullptr)
				n->getRentListForAdmin(type, m_currentYear.toInt(), m_currentMonth.toInt())->request();
			else if (!m_cmdProviderView->selectedTag().compare(TAG_VIEW_ALL))
				n->getRentListForAdmin(type, m_currentYear.toInt(), m_currentMonth.toInt())->request();
			else
				n->getTotalRentListMonth(m_currentYear.toInt(), m_currentMonth.toInt())->request();
		}
		else if (!m_cmdProviderList->selectedTag().compare(TAG_MNT_LIST))
		{
			n->getTotalRentListMonth(m_currentYear.toInt(), m_currentMonth.toInt())->request();
		}

		break;
	}
	}
}
void ViewHomePC::netGetEmployeeList()
{
	n->getUserList()->request();
}
void ViewHomePC::netSignForMonth()
{
	n->signForMonth()->request();
}
void ViewHomePC::netLogin()
{
	n->login(m->user()->id(), m->user()->pass())->request();
}
void ViewHomePC::netHandler()
{
	if (m->alarmed())
	{
		bool result = false;
		Notificator* noti = m->notificator();
		int type = noti->type();
		if (type == Notificator::RequestLogin)
		{
			QTimer::singleShot(500, this, SLOT(netLogin()));
		}
		else if (type == Notificator::Login)
		{
			result = noti->result();
			m->login(result);
			if (result) {

				QString typeAdminStr = "";
				int type = m->user()->typeAdmin();
				int count = m_cmdProviderList->count();
				switch (m->user()->typeAdmin())
				{
				case User::PartManager:
				{
					count = count - 1;
					typeAdminStr = kr("파트담당자");
					m_btnMNGList->initVisible(true);
					m_btnMNTList->initVisible(false);
					break;
				}
				case User::PartChair:
				{
					count = count - 1;
					typeAdminStr = kr("파트장");
					m_btnMNGList->initVisible(true);
					m_btnMNTList->initVisible(false);
					break;
				}
				case User::SpecialList:
				{
					count = count - 1;
					typeAdminStr = kr("결재자");
					m_btnMNGList->initVisible(true);
					m_btnMNTList->initVisible(true);
					break;
				}
				case User::SystemAdmin:
				{
					typeAdminStr = kr("시스템관리자");
					break;
				}
				default:
					break;
				}

				int hSlide = m_styleSlide->height();
				int hBtn = m_cmdProviderList->totalHeight() / m_cmdProviderList->count();
				m_emptyArea->setFixedSize(1, hSlide - (hBtn * count) - 10 * (count + 2));

				QString userType = m->user()->namePart() + " " + m->user()->nameUser() + kr("(") + typeAdminStr + kr(")");
				m_lbUserInfo->setText(userType);

				n->getPartList();
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
					//switch (m->user()->typeAdmin())
					//{
					//case User::PartManager:
					//case User::PartChair:
					//{
					//	m_alarm->setFunc([=]() {
					//		initListMNG();
					//		netGetRentList(0); 
					//	});
					//	
					//	break;
					//}
					//case User::SpecialList:
					//{
					//	m_alarm->setFunc([=]() {
					//		initListMNT();
					//		netGetRentList(0);
					//	});
					//	break;
					//}
					//}					

					m_alarm->initSize(350, 120)->setMessage(m->user()->textAlarm());
					m_alarm->show();
				}
			}
			else {
				m_alarm->initSize(350, 120)->setMessage(m->notificator()->message());
				m_alarm->show();
			}
		}
		else if (type == Notificator::Logout)
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
		else if (type == Notificator::Join)
		{
			QString message = noti->message();
			if (message.isEmpty())
			{
				message = kr("회원가입에 성공하였습니다.");
			}

			m_alarm->initSize(350, 120)->setMessage(message);
			m_alarm->show();
		}
		else if (type == Notificator::Exit)
		{
			close();
		}
		else if (type == Notificator::DVIList)
		{
			result = m->notificator()->result();
			QString msg = m->notificator()->message();
			if (result)
			{
				msg = kr("정상적으로 처리되었습니다.");
				updateUI();
			}

			if (!msg.isEmpty())
			{
				m_alarm->initSize(350, 120)->setMessage(msg);
				m_alarm->show();
			}
			QTimer::singleShot(500, this, SLOT(netGetDeviceList()));
		}
		else if (type == Notificator::RequestPartsList)
		{
			n->getPartList()->request();
		}
		else if (type == Notificator::ErrorNoLogined)
		{
			m_alarm->initSize(350, 120)->setMessage(kr("로그인을 해주세요."));
			m_alarm->show();
		}
		else if (type == Notificator::ErrorNoFile)
		{
			m_alarm->initSize(350, 120)->setMessage(kr("서명이 존재하지 않습니다."));
			m_alarm->show();
		}
		else if (type == Notificator::ErrorNoSaveFile)
		{
			m_alarm->initSize(350, 120)->setMessage(kr("서명을 저장할 수 없습니다."));
			m_alarm->show();
		}
		else if (type == Notificator::ErrorNoRent)
		{
			m_alarm->initSize(350, 120)->setMessage(kr("대출번호가 잘못되었습니다."));
			m_alarm->show();
		}
		else if (type == Notificator::ErrorNoBarcode)
		{
			m_alarm->initSize(350, 120)->setMessage(kr("자산번호가 잘못되었습니다."));
			m_alarm->show();
		}
		//else if (type == Notificator::ConfirmedRent)
		//{
		//	result = noti->result();
		//	QString msg = "";
		//	if (result) msg = kr("정상적으로 처리되었습니다.");
		//	else msg = noti->message();
		//	m_alarm->initSize(350, 120)->setMessage(msg);
		//	m_alarm->show();
		//}
		else if (type == Notificator::DVISearch)
		{
			m_barcoder->recognize();
		}
		else if (type == Notificator::OpenFromBorrow)
		{
			FormBorrow* form = new FormBorrow(500, 450);
			form->show();
		}
		else if (type == Notificator::OpenFromReturn)
		{
			FormReturn* form = new FormReturn(500, 450);
			form->show();
		}
		else if (type == Notificator::DVIBorrowed || type == Notificator::DVIReturned)
		{
			result = noti->result();
			QString msg = "";
			if (result)
			{
				m_barcoder->hide();
				m->setPageNumber(1);
				initListDVC();
				QTimer::singleShot(500, this, SLOT(netGetDeviceList()));
				msg = kr("정상적으로 처리되었습니다.");
			}
			else {
				msg = noti->message();
			}
			if (!msg.isEmpty())
			{
				m_alarm->initSize(350, 120)->setMessage(msg);
				m_alarm->show();
			}
		}
		else if (type == Notificator::Signed)
		{
			QString msg = "";
			result = noti->result();
			if (result) {
				msg = kr("정상적으로 처리되었습니다.");
				QString tag = m_cmdProviderList->selectedTag();
				if(!tag.compare(TAG_MNG_LIST)) updateMNGSign();
				else if (!tag.compare(TAG_MNT_LIST)) updateMNTCheckTable();
			}
			else msg = noti->message();

			if (!msg.isEmpty())
			{
				m_alarm->initSize(350, 120)->setMessage(msg);
				m_alarm->show();
			}
		}
		else if (type == Notificator::SignForMonth)
		{
			QTimer::singleShot(500, this, SLOT(netSignForMonth()));
		}
		else if (type == Notificator::MNGList)
		{
			updateUI();
		}
		else
		{
			result = noti->result();
			QString msg = noti->message();
			if (!result && !msg.isEmpty())
			{
				m_alarm->initSize(350, 120)->setMessage(msg);
				m_alarm->show();
			}
		}
		m->alarm(false);
	}
}
#pragma endregion

void ViewHomePC::clearAutoLogin()
{
	s->setId("");
	s->setPass("");
	s->loginAuto(false);
}
void ViewHomePC::initWidgets()
{
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
	if (m_contentRow2 != nullptr)
	{
		delete m_contentRow2;
		m_contentRow2 = nullptr;
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
}
void ViewHomePC::initContentRow1()
{
	m_contentRow1 = (new CPWidget(m_styleContent->width(), m_styleContent->hRow01, new QHBoxLayout))
		->initAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	m_content->layout()->addWidget(m_contentRow1);

	int wGrid1_1 = 200;
	int wGrid1_2 = 0;
	int wGrid1_3 = m_contentRow1->width() - wGrid1_1;

	QString tag = m_cmdProviderList->selectedTag();
	if (!tag.compare(TAG_MNG_LIST) || !tag.compare(TAG_MNT_LIST)) {
		wGrid1_1 = m_contentRow1->width() / 3;
		wGrid1_2 = m_contentRow1->width() / 3;
		wGrid1_3 = m_contentRow1->width() / 3;
	}

	m_contentGrid1_1 = (new CPWidget(wGrid1_1, m_styleContent->hRow01, new QHBoxLayout))
		->initAlignment(Qt::AlignLeft | Qt::AlignVCenter)->initContentsMargins(10, 0, 0, 0)->initSpacing(10)
		->append((new CPLabel(20, 20))->initImage(":/imgs/circle.png"))
		->append((new CPLabel(m_styleContent->wGrid1_1 - 40, m_styleContent->hRow01, m_titleTxt))->initFontSize(20)
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
}
void ViewHomePC::initContentRow2()
{
	int hRow02 = 0;
	QString tag = m_cmdProviderList->selectedTag();
	if (!tag.compare(TAG_MNG_LIST)) hRow02 = 60;
	m_styleContent->setHRow02(hRow02);

	m_contentRow2 = (new CPWidget(m_styleContent->width(), m_styleContent->hRow02(), new QHBoxLayout))
		->initAlignment(Qt::AlignCenter)->initContentsMargins(55, 10, 0, 0)->initSpacing(10);
	m_content->layout()->addWidget(m_contentRow2);

	m_lbSign1 = (new CPLabel(60, 30, kr("O")))->initStyleSheet("background:white; border:1px solid black")->initAlignment(Qt::AlignCenter);
	m_lbSign2 = (new CPLabel(60, 30, kr("X")))->initStyleSheet("background:white; border:1px solid black")->initAlignment(Qt::AlignCenter);
	m_lbSign3 = (new CPLabel(60, 30, kr("X")))->initStyleSheet("background:white; border:1px solid black")->initAlignment(Qt::AlignCenter);
	m_zoneSign = (new CPWidget(180, 60, new QHBoxLayout))->initStyleSheet("border: 1px solid black;")
		->append((new CPWidget(60, 60, new QVBoxLayout))->append((new CPLabel(60, 20, kr("담당자")))->initAlignment(Qt::AlignCenter))->append(m_lbSign1))
		->append((new CPWidget(60, 60, new QVBoxLayout))->append((new CPLabel(60, 20, kr("파트장")))->initAlignment(Qt::AlignCenter))->append(m_lbSign2))
		->append((new CPWidget(60, 60, new QVBoxLayout))->append((new CPLabel(60, 20, kr("결재자")))->initAlignment(Qt::AlignCenter))->append(m_lbSign3));

	Button* metaBtn = m_styleContent->btnSign();
	m_btnSign = new Command(metaBtn, [=]() {
		QString userNamePart = m->user()->namePart();
		int currentYear = m_currentYear.toInt();
		int currentMonth = m_currentMonth.toInt();
		foreach(Sign* s, m->signatures())
		{
			if (!userNamePart.compare(s->namePart()) && currentYear == s->year() && currentMonth == s->month())
			{
				int noSign = s->noSign();
				FormSignature* sg = new FormSignature(s->noSign(), 500, 250);
				sg->show();
				return;
			}
		}
	}, true);
}
void ViewHomePC::initStyles()
{
	/*** GET STYLE INSTANCES. ***/
	m_style = Style::instance()->main();
	m_styleHeader = m_style->header();
	m_styleFooter = m_style->footer();
	m_styleBody = m_style->body();
	m_styleContent = m_styleBody->content();
	m_styleSlide = m_styleBody->slide();
	/*** GET STYLE INSTANCES. END. ***/
}
void ViewHomePC::initParentLayout()
{
	setMinimumWidth(m_style->width()); setMinimumHeight(m_style->height());
	setLayout(new QVBoxLayout);
	layout()->setAlignment(Qt::AlignTop);
	layout()->setMargin(0);
	layout()->setSpacing(0);
}
void ViewHomePC::initBody()
{
	m_body = new QWidget(this);
	m_body->setLayout(new QHBoxLayout);
	m_body->layout()->setMargin(0);
	m_body->layout()->setSpacing(0);
	layout()->addWidget(m_body);
}
void ViewHomePC::initContent()
{
	m_content = new QWidget(this);
	m_content->setLayout(new QVBoxLayout);
	m_content->layout()->setAlignment(Qt::AlignLeft | Qt::AlignTop);
	m_content->layout()->setMargin(0);
	m_content->layout()->setSpacing(0);
	m_body->layout()->addWidget(m_content);
}
void ViewHomePC::initHeader()
{
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

	m_header->setStyleSheet("background: " + m_styleHeader->palette()->navy01);
	layout()->addWidget(m_header);
#pragma endregion
}
void ViewHomePC::initFooter()
{
	m_footer = new QWidget(this);
	m_footer->setStyleSheet("background: " + m_styleFooter->palette()->navy01);
	m_footer->setLayout(new QHBoxLayout);
	m_footer->setFixedSize(m_styleFooter->width(), m_styleFooter->height());
	m_footer->layout()->setAlignment(Qt::AlignCenter);
	m_footer->layout()->addWidget((new CPLabel(500, 25, m_styleFooter->txtCopyright))->initAlignment(Qt::AlignCenter)->initStyleSheet("color: white")->initFontSize(11));
	layout()->addWidget(m_footer);
}
void ViewHomePC::initSlideButton()
{
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

	m_btnLogout = new LogoutCommand(m_styleHeader->btnLogout(),
		[=]()
	{
		m_question->initSize(350, 120)->setMessage(kr("로그아웃 하시겠습니까?"));
		m_question->func = [=]() { n->logout()->request(); };
		m_question->show();
	}, true);

	m_btnDVCList = new Command(m_styleSlide->btnDVCList(),
		[=]()
	{
		if (!m_cmdProviderList->selectedTag().compare(TAG_DVC_LIST)) return;
		m->setPageNumber(1);
		initListDVC();
		netGetDeviceList();
	}, true);

	m_btnMNGList = new Command(m_styleSlide->btnMNGList(),
		[=]()
	{
		initListMNG();
		netGetRentList(0);
	}, true);

	m_btnMNTList = new Command(m_styleSlide->btnMNTList(),
		[=]()
	{
		initListMNT();
		netGetRentList(0);
	}, true);

	m_btnEMPList = new Command(m_styleSlide->btnEMPList(),
		[=]()
	{
		initListEMP();
		netGetEmployeeList();
	}, true);

	m_btnImExport = new Command(m_styleSlide->btnImExport(),
		[=]()
	{
		m_barcoder = new Barcoder(kr("대출/반납하기"), 520, 230);
		m_barcoder->show();
	}, true);

	m_cmdProviderList = new CommandProvider();
	m_cmdProviderList->append(m_btnDVCList);
	m_cmdProviderList->append(m_btnMNGList);
	m_cmdProviderList->append(m_btnMNTList);
	m_cmdProviderList->append(m_btnEMPList);
	m_cmdProviderList->append(m_btnImExport);
}
void ViewHomePC::initButtonsDVC()
{
	m_btnPrint = new Command(m_styleContent->btnPrint(),
		[=]() {	
		print(m_tableCommon);	
	}, true);
	m_btnPrint->initIcon(m_styleContent->btnPrint()->icon(), kr(m_styleContent->btnPrint()->name()));

	m_btnEdit = new Command(m_styleContent->btnEdit(),
		[=]()
	{
		if (m_tableCommon->currentRow() < 0) {
			m_alarm->initSize(350, 120)->setMessage(kr("수정할 장비를 선택하세요."));
			m_alarm->show();
			return;
		}
		if (!m_tableCommon->item(m_tableCommon->currentRow(), 0)->isSelected()) {
			m_alarm->initSize(350, 120)->setMessage(kr("수정할 장비를 선택하세요."));
			m_alarm->show();
			return;
		}
		for (int i = 0; i < m_tableCommon->columnCount(); i++)
			m_tableCommon->item(m_tableCommon->currentRow(), i)->setSelected(false);

		FormEdit* f = new FormEdit(m_tableCommon->currentRow(), 410, 340);
		f->show();
	}, true);
	m_btnEdit->initIcon(m_styleContent->btnEdit()->icon(), kr(m_styleContent->btnEdit()->name()));

	m_btnRemove = new Command(m_styleContent->btnRemove(),
		[=]()
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
			n->removeDevice(m->devices().at(m_tableCommon->currentRow())->noDevice())->request();
		};
		m_question->show();
	}, true);
	m_btnRemove->initIcon(m_styleContent->btnRemove()->icon(), kr(m_styleContent->btnRemove()->name()));

	m_btnNew = new Command(m_styleContent->btnNew(),
		[=]()
	{
		FormAdd* f = new FormAdd(540, 430);
		f->show();
	}, true);
	m_btnNew->initIcon(m_styleContent->btnNew()->icon(), kr(m_styleContent->btnNew()->name()));

	m_contentGrid1_3->append(m_btnNew)->append(m_btnEdit)->append(m_btnRemove)->append(m_btnPrint);
}
void ViewHomePC::initSlide()
{
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
	m_slide->setStyleSheet("background: " + m_styleHeader->palette()->navy02);
	m_slideCol01->setStyleSheet("background: " + m_styleHeader->palette()->navy03);
	m_body->layout()->addWidget(m_slide);

	m_slide->layout()->addWidget(m_slideCol01);
	m_slide->layout()->addWidget(m_slideCol02);
	m_slideCol02->append(m_btnDVCList);
	m_slideCol02->append(m_btnMNGList);
	m_slideCol02->append(m_btnMNTList);
	m_slideCol02->append(m_btnEMPList);

	m_emptyArea = (new CPLabel(0, 0, ""));
	m_slideCol02->append(m_emptyArea);
	m_slideCol02->append(m_btnImExport);
}
void ViewHomePC::initButtonsMNG()
{
	if (m_cmdProviderView != nullptr) m_cmdProviderView->clear();
	else m_cmdProviderView = new CommandProvider();

	m_btnPrint = new Command(m_styleContent->btnPrint(),
		[=]() {	print(m_tableCommon);	}, true);
	m_btnPrint->initIcon(m_styleContent->btnPrint()->icon(), kr(m_styleContent->btnPrint()->name()));

	m_btnViewAll = new Command(m_styleContent->btnViewAll(),
		[=]()
	{
		if (m_cmdProviderView->selectedTag().compare(TAG_VIEW_ALL))
		{
			m_cmdProviderView->select(TAG_VIEW_ALL);
			m_btnCalendarPrev->setVisible(false);
			m_lbCalendar->setVisible(false);
			m_btnCalendarNext->setVisible(false);
			netGetRentList(0);
			updateUI();
		}
	}, true);
	m_btnViewAll->initIcon(m_styleContent->btnViewAll()->icon(), kr(m_styleContent->btnViewAll()->name()));

	m_btnViewDate = new Command(m_styleContent->btnViewDate(),
		[=]()
	{
		if (m_cmdProviderView->selectedTag().compare(TAG_VIEW_DATE))
		{
			m_countMonth = 0;
			getCurrentDate();
			m_lbCalendar->initText(getCurrentDate(0));
			m_cmdProviderView->select(TAG_VIEW_DATE);
			m_btnCalendarPrev->setVisible(true);
			m_lbCalendar->setVisible(true);
			m_btnCalendarNext->setVisible(true);
			netGetRentList(1);
			updateUI();
			//updateMNGSign();
		}
	}, true);
	m_btnViewDate->initIcon(m_styleContent->btnViewDate()->icon(), kr(m_styleContent->btnViewDate()->name()));

	if (m->user()->typeAdmin() == User::SpecialList)
	{
		m_btnViewAll->initVisible(false);
		m_btnViewDate->initVisible(false);
	}
	else
	{
		m_btnViewAll->initVisible(true);
		m_btnViewDate->initVisible(true);
	}

	m_btnCalendarPrev = (new Command(m_styleContent->btnCalendarPrev(),
		[=]()
	{
		m_lbCalendar->initText(getCurrentDate(--m_countMonth));
		netGetRentList(1);
	}, true))->initVisible(false);

	m_btnCalendarNext = (new Command(m_styleContent->btnCalendarNext(),
		[=]()
	{
		m_lbCalendar->initText(getCurrentDate(++m_countMonth));
		netGetRentList(1);
	}, true))->initVisible(false);

	m_cmdProviderView->append(m_btnViewAll)->append(m_btnViewDate);
	m_cmdProviderView->select(TAG_VIEW_ALL);

}
void ViewHomePC::initButtonsMNT()
{
	m_btnPrint = new Command(m_styleContent->btnPrint(),
		[=]()
	{
		print(m_tableCommon);
	}, true);
	m_btnPrint->initIcon(m_styleContent->btnPrint()->icon(), kr(m_styleContent->btnPrint()->name()));

	m_btnCalendarPrev = (new Command(m_styleContent->btnCalendarPrev(),
		[=]()
	{
		m_lbCalendar->initText(getCurrentDate(--m_countMonth));
		netGetRentList(1);
		initListMNT(false);
	}, true));

	m_btnCalendarNext = (new Command(m_styleContent->btnCalendarNext(),
		[=]()
	{
		m_lbCalendar->initText(getCurrentDate(++m_countMonth));
		netGetRentList(1);
		initListMNT(false);
	}, true));

	m_contentGrid1_3->append(m_btnPrint);
}
void ViewHomePC::initButtonsEMP()
{
	m_btnPrint = new Command(m_styleContent->btnPrint(),
		[=]()
	{
		print(m_tableCommon);
	}, true);
	m_contentGrid1_3->append(m_btnPrint);
	m_btnPrint->initIcon(m_styleContent->btnPrint()->icon(), kr(m_styleContent->btnPrint()->name()));
}
void ViewHomePC::initMNGNaviCalendar()
{
	m_lbCalendar = (new CPLabel(120, 30, getCurrentDate(0)))->initVisible(false)
		->initAlignment(Qt::AlignCenter)->initFontSize(15);
	m_contentGrid1_2->append(m_btnCalendarPrev)->append(m_lbCalendar)->append(m_btnCalendarNext);
	m_contentGrid1_3->append(m_btnViewAll)->append(m_btnViewDate)->append(m_btnPrint);
}
void ViewHomePC::initTableDVC()
{
	newTable(m->devices().size(), TAG_DVC_LIST);
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
void ViewHomePC::initTableMNG()
{
	newTable(m->rents().size(), TAG_MNG_LIST);
	MetaTableMNG* castedMetaTable = qobject_cast<MetaTableMNG*>(m_metaTable);
	m_metaTable->setWidth(m_content->width());
	m_metaTable->setHeight(m_content->height() - m_contentRow1->height() - m_contentRow2->height());
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
		//m_tableCommon->setRowHeight(row, 50);
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
	Button* metaBtn = m_styleContent->btnCalendarNext();
	if (selectedTime.toInt() < tTime.toInt())
	{
		m_btnCalendarNext->initEnabled(true)->initStyleSheet(metaBtn->releasedStyle())
			->initEffect(metaBtn->releasedStyle(), metaBtn->selectedStyle(), metaBtn->hoveredStyle());
	}
	else
	{
		Palette* p = new Palette();
		m_btnCalendarNext->initEnabled(false)->initStyleSheet(p->btnSelectedStyleDiabled)
			->initDisabledEffect(p->btnSelectedStyleDiabled,
				p->btnSelectedStyleDiabled,
				p->btnSelectedStyleDiabled);
	}

	updateMNGSign();
}
void ViewHomePC::initTableMNT()
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
		hMntStack = hMntStack + cmd->height() + tb->height();
	}
	m_mntStack->setFixedSize(m_content->width() - 20, hMntStack);
	m_mntScrArea->setFixedSize(m_mntStack->width() + 20, m_content->height() - m_contentRow1->height());
	m_mntScrArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	/* Calendar Buttons */
	QString selectedTime = m_currentYear + m_currentMonth;
	QString tYear = QDateTime::currentDateTime().addMonths(0).toString("yyyy");
	QString tMonth = QDateTime::currentDateTime().addMonths(0).toString("MM");
	QString tTime = tYear + tMonth;
	Button* metaBtn = m_styleContent->btnCalendarNext();
	//qDebug() << selectedTime.toInt() << "/" << tTime.toInt();
	if (selectedTime.toInt() < tTime.toInt())
	{
		m_btnCalendarNext->initEnabled(true)->initStyleSheet(metaBtn->releasedStyle())
			->initEffect(metaBtn->releasedStyle(), metaBtn->selectedStyle(), metaBtn->hoveredStyle());
	}
	else
	{
		Palette* p = new Palette();
		m_btnCalendarNext->initEnabled(false)->initStyleSheet(p->btnSelectedStyleDiabled)
			->initDisabledEffect(p->btnSelectedStyleDiabled,
				p->btnSelectedStyleDiabled,
				p->btnSelectedStyleDiabled);
	}

	for (int i = 0; i < m->parts().size(); i++)
	{
		CPBoxSign* zoneSign = m_mntZoneSign.at(i);
		QString currentPartName = m->parts().at(i)->namePart();
		foreach(Sign* s, m->signatures())
		{
			QString objNamePart = s->namePart();
			if (objNamePart.compare(currentPartName)) continue;

			int objYear = s->year(); int objMonth = s->month();
			if (m_currentYear.toInt() != objYear || m_currentMonth.toInt() != objMonth) continue;

			int typeAdmin = m->user()->typeAdmin();
			int typeComplete = s->typeComplete();

			bool enable = false;
			if (typeAdmin == User::SpecialList) enable = typeComplete == 2 ? true : false; //보직자
			else if (typeAdmin == User::PartChair) enable = typeComplete == 1 ? true : false; //파트장
			else if (typeAdmin == User::PartManager) enable = typeComplete == 0 ? true : false; //담당자			
			zoneSign->initEanbleButton(enable);
			break;
		}

		//m_mntTables.at(i)->initWidth(m_content->width())->initPage();
	}
}
void ViewHomePC::initTableEMP()
{
	MetaTableEMP* metaTable = qobject_cast<MetaTableEMP*>(m_metaTable);
	m_metaTable->setWidth(m_content->width());
	m_metaTable->setHeight(m_content->height() - m_contentRow1->height());
	m_tableCommon->setRowCount(m->employees().size());
	m_tableCommon->setColumnCount(m_metaTable->header()->countCols());
	m_tableCommon->setFixedSize(m_metaTable->width(), m_metaTable->height());
	m_tableCommon->setHorizontalHeaderLabels(m_metaTable->header()->meta());
	m_tableCommon->horizontalHeader()->setFixedHeight(m_metaTable->header()->height());

	for (int row = 0; row < m->employees().size(); row++)
	{
		//m_tableCommon->setRowHeight(row, 50);
		Employee* dv = m->employees().at(row);
		QTableWidgetItem* item0 = new QTableWidgetItem(QString("%1").arg((row + 1) + (m->pageNumber() - 1)*COUNT_PAGE));
		item0->setTextAlignment(Qt::AlignCenter);
		m_tableCommon->setItem(row, 0, item0);

		QTableWidgetItem* item1 = new QTableWidgetItem(dv->nameUser());
		item1->setTextAlignment(Qt::AlignCenter);
		m_tableCommon->setItem(row, 1, item1);

		QTableWidgetItem* item2 = new QTableWidgetItem(dv->manager() ? "O" : "X");
		item2->setTextAlignment(Qt::AlignCenter);
		m_tableCommon->setItem(row, 2, item2);
	}
}
void ViewHomePC::updateBody()
{
	int wBody = m_styleBody->width();
	int hBody = m_styleBody->height();
	m_body->setFixedSize(wBody, hBody);
}
void ViewHomePC::updateContent()
{
	int wContent = m_styleContent->width();
	int hContent = m_styleContent->height();
	m_content->setFixedSize(wContent, hContent);
}
void ViewHomePC::updateHeader()
{
	int wHeader = m_styleHeader->width();
	int hHeader = m_styleHeader->height();
	m_header->setFixedSize(wHeader, hHeader);
	m_headerCol02->initWidth(m_styleHeader->width() - m_styleHeader->wCol01);
}
void ViewHomePC::updateFooter()
{
	int wFooter = m_styleFooter->width();
	int hFooter = m_styleFooter->height();
	m_footer->setFixedSize(wFooter, hFooter);
}
void ViewHomePC::updateSlideButtons()
{
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
}
void ViewHomePC::updateSlide()
{
	int wSlide = m_styleSlide->width();
	int wSlideCol01 = m_styleSlide->wCol01;
	int wSlideCol02 = wSlide - wSlideCol01;
	int hSlide = m_styleSlide->height();

	m_slide->setFixedSize(wSlide, hSlide);
	m_slideCol01->setFixedSize(wSlideCol01, hSlide);
	m_slideCol02->setFixedSize(wSlideCol02, hSlide);

	int count = m_cmdProviderList->count();
	switch (m->user()->typeAdmin())
	{
	case User::PartManager:
	case User::PartChair:
	case User::SpecialList:
	{
		count = count - 1;
		break;
	}
	}
	int hBtn = m_cmdProviderList->totalHeight() / m_cmdProviderList->count();
	m_emptyArea->setFixedSize(1, hSlide - (hBtn * count) - 10 * (count + 2));
}
void ViewHomePC::updateContentRow1()
{
	int wContent = m_styleContent->width();
	m_contentRow1->initWidth(wContent);

	int wGrid1_1 = 200; // m_contentRow1->width() / 2;
	int wGrid1_2 = 0;
	int wGrid1_3 = m_contentRow1->width() - wGrid1_1;
	QString tag = m_cmdProviderList->selectedTag();
	if (!tag.compare(TAG_MNG_LIST) || !tag.compare(TAG_MNT_LIST))
	{
		wGrid1_1 = m_contentRow1->width() / 3;
		wGrid1_2 = m_contentRow1->width() / 3;
		wGrid1_3 = m_contentRow1->width() / 3;
	}
	m_contentGrid1_1->setFixedWidth(wGrid1_1);
	m_contentGrid1_2->setFixedWidth(wGrid1_2);
	m_contentGrid1_3->setFixedWidth(wGrid1_3);
}
void ViewHomePC::updateContentRow2()
{
	int wContent = m_styleContent->width();

	QString tag = m_cmdProviderList->selectedTag();
	if (tag.compare(TAG_MNG_LIST)) return;

	int hRow02 = 0;
	tag = m_cmdProviderView->selectedTag();
	if (!tag.compare(TAG_VIEW_DATE)) hRow02 = 60;
	m_styleContent->setHRow02(hRow02);
	m_contentRow2->setFixedSize(wContent, hRow02);
	m_contentRow2->append(m_zoneSign)->append(m_btnSign);
	//m_tableSign->setHorizontalHeaderLabels(castedMetaTable->headerSign);
}
void ViewHomePC::updateMNGSign()
{
	if (m_cmdProviderList->selectedTag().compare(TAG_MNG_LIST)) return;
	foreach(Sign* s, m->signatures())
	{
		//qDebug() << p->namePart() << "/" << s->namePart();
		if (!m->user()->namePart().compare(s->namePart()))
		{
			if (m_currentYear.toInt() == s->year() && m_currentMonth.toInt() == s->month())
			{
				switch (s->typeComplete())
				{
				case 0:
				{
					m_lbSign1->initText("X");
					m_lbSign2->initText("X");
					m_lbSign3->initText("X");

					/*if(m->user()->typeAdmin() == User::PartManager)
					m_btnSign*/
					break;
				}
				case 1:
				{
					m_lbSign1->initText("O");
					m_lbSign2->initText("X");
					m_lbSign3->initText("X");
					break;
				}
				case 2:
				{
					m_lbSign1->initText("O");
					m_lbSign2->initText("O");
					m_lbSign3->initText("X");
					break;
				}
				case 3:
				{
					m_lbSign1->initText("O");
					m_lbSign2->initText("O");
					m_lbSign3->initText("O");
					break;
				}

				}
			}
		}
	}

	QString userPartName = m->user()->namePart();
	foreach(Sign* s, m->signatures())
	{
		QString objNamePart = s->namePart();
		if (objNamePart.compare(userPartName)) continue;

		int objYear = s->year(); int objMonth = s->month();
		if (m_currentYear.toInt() != objYear || m_currentMonth.toInt() != objMonth) continue;

		int typeAdmin = m->user()->typeAdmin();
		int typeComplete = s->typeComplete();
		bool enable = false;

		if (typeAdmin == User::SpecialList) enable = typeComplete == 2 ? true : false; //보직자
		else if (typeAdmin == User::PartChair) enable = typeComplete == 1 ? true : false; //파트장
		else if (typeAdmin == User::PartManager) enable = typeComplete == 0 ? true : false; //담당자

		int noSign = s->noSign();
		m_btnSign->initEnabled(enable);
		break;
	}
}
void ViewHomePC::updateMNTCheckTable()
{
	if (m_cmdProviderList->selectedTag().compare(TAG_MNT_LIST)) return;
	m_checkTable->updateTable();

	for (int i = 0; i < m->parts().size(); i++)
	{
		QString namePart = m->parts().at(i)->namePart();
		foreach(Sign* s, m->signatures())
		{
			if (!s->namePart().compare(namePart) && s->month() == m_currentMonth.toInt() && s->year() == m_currentYear.toInt())
			{
				int markType = s->typeComplete();
				if (markType == 0)
				{
					m_mntZoneSign.at(i)->initState("X", "X", "X");
					m_mntZoneSign.at(i)->initEanbleButton(false);
				}
				else if (markType == 1)
				{
					m_mntZoneSign.at(i)->initState("O", "X", "X");
					m_mntZoneSign.at(i)->initEanbleButton(false);
				}
				else if (markType == 2)
				{
					m_mntZoneSign.at(i)->initState("O", "O", "X");
					m_mntZoneSign.at(i)->initEanbleButton(true);
				}
				else
				{
					m_mntZoneSign.at(i)->initState("O", "O", "O");
					m_mntZoneSign.at(i)->initEanbleButton(false);
				}
			}
		}

		int itemCount = 0;
		for (int i = 0; i < m->rents().size(); i++)
		{
			if (!namePart.compare(m->rents().at(i)->namePart()))
				itemCount++;
		}

		CPTable* tb = m_mntTables.at(i);
		tb->initWidth(m_content->width())
			->initRowCount(itemCount)
			->initTableWidthPercent({ 0.03, 0.08, 0.10, 0.12 - 7, 0.09,
				0.10, 0.09, 0.12 - 7, 0.09, 0.10, 0.05, 0.03 })
			->initPage();

		for (int row = 0; row < m->rents().size(); row++)
		{
			//m_tableCommon->setRowHeight(row, 50);
			Rent* dv = m->rents().at(row);
			qDebug() << dv->namePart() << "/" << m->parts().at(i)->namePart();
			if (dv->namePart().compare(m->parts().at(i)->namePart())) continue;

			QTableWidgetItem* item0 = new QTableWidgetItem(QString("%1").arg(row + 1));
			item0->setTextAlignment(Qt::AlignCenter);
			tb->table()->setItem(row, 0, item0);

			QTableWidgetItem* item1 = new QTableWidgetItem(dv->noAsset());
			item1->setTextAlignment(Qt::AlignCenter);
			tb->table()->setItem(row, 1, item1);

			QTableWidgetItem* item2 = new QTableWidgetItem(dv->nameDevice());
			item2->setTextAlignment(Qt::AlignCenter);
			tb->table()->setItem(row, 2, item2);

			QTableWidgetItem* item3 = new QTableWidgetItem(dv->dateBorrowed());
			item3->setTextAlignment(Qt::AlignCenter);
			tb->table()->setItem(row, 3, item3);

			QTableWidgetItem* item4 = new QTableWidgetItem(dv->nameUser());
			item4->setTextAlignment(Qt::AlignCenter);
			tb->table()->setItem(row, 4, item4);

			CPLazyImage *lbSignBorrwed = new CPLazyImage(dv->signUser(), tb->table()->width() * 0.10);
			lbSignBorrwed->setFixedSize(tb->table()->width() * 0.10, 50);
			QHBoxLayout *lySignBorrwed = new QHBoxLayout();
			lySignBorrwed->addWidget(lbSignBorrwed);
			lySignBorrwed->setMargin(0);
			QWidget *wdSignBorrwed = new QWidget();
			wdSignBorrwed->setLayout(lySignBorrwed);
			wdSignBorrwed->setStyleSheet("border: 0px;");
			tb->table()->setCellWidget(row, 5, wdSignBorrwed);

			QTableWidgetItem* itemPP = new QTableWidgetItem(dv->purpose());
			itemPP->setTextAlignment(Qt::AlignCenter);
			tb->table()->setItem(row, 6, itemPP);

			QTableWidgetItem* item7 = new QTableWidgetItem(dv->dateReturned());
			item7->setTextAlignment(Qt::AlignCenter);
			tb->table()->setItem(row, 7, item7);

			QTableWidgetItem* item8 = new QTableWidgetItem(dv->nameAdmin());
			item8->setTextAlignment(Qt::AlignCenter);
			tb->table()->setItem(row, 8, item8);

			CPLazyImage *lbSignReturned = new CPLazyImage(dv->signAdmin(), tb->table()->width() * 0.10);
			lbSignReturned->setFixedSize(tb->table()->width() * 0.10, 50);
			QHBoxLayout *lySignReturned = new QHBoxLayout();
			lySignReturned->addWidget(lbSignReturned);
			lySignReturned->setMargin(0);
			QWidget *wdSignReturned = new QWidget();
			wdSignReturned->setLayout(lySignReturned);
			wdSignReturned->setStyleSheet("border: 0px;");
			tb->table()->setCellWidget(row, 9, wdSignReturned);

			QTableWidgetItem* itemSecu = new QTableWidgetItem(dv->initial() ? "O" : "X");
			itemSecu->setTextAlignment(Qt::AlignCenter);
			tb->table()->setItem(row, 10, itemSecu);

			QTableWidgetItem* item11 = new QTableWidgetItem(dv->completed() ? "O" : "X");
			item11->setTextAlignment(Qt::AlignCenter);
			tb->table()->setItem(row, 11, item11);
		}
	}
}
ViewHomePC::~ViewHomePC()
{

}