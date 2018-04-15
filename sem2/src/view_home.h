#pragma once
#include <QMainWindow>
#include "cs_style.h"
#include "cs_component.h"
#include "cs_command.h"
#include "cs_metatable.h"
#include "cs_model.h"
#include "cs_alarm.h"
#include "cs_login.h"
#include "cs_settings.h"
#include "cs_networker.h"
#include "cs_question.h"
#include "cs_barcoder.h"

class CheckTable;
class ViewHome : public QWidget
{
    Q_OBJECT

public:
    ViewHome(QWidget *parent = 0);
    ~ViewHome();


	public slots:
	void updateUI();
	void netHandler();
	void netGetDeviceList(int searchType=0);
	void netGetRentList(int type);
	void netGetEmployeeList();
	void netLogin();
	void prev();
	void next();
	void updateMNGSign();
	void updateMNTCheckTable();
	void initListDVC();

protected:
	void resizeEvent(QResizeEvent *event) override;

private:
	int m_countMonth = 0;
	bool m_initedUI = false;
	QString m_currentYear;
	QString m_currentMonth;

	Alarm* m_alarm;
	Question* m_question;
	Barcoder* m_barcoder;
	CPLogin* m_login = nullptr;

	Model* m;
	Settings* s;
	NetWorker* n;
	StyleMain* m_style;

	StyleMainBody* m_styleBody;
	QWidget* m_body;

	StyleMainHeader* m_styleHeader;
	QWidget* m_header;
	CPLabel* m_headerCol01;
	CPWidget* m_headerCol02;
	//CPWidget* m_headerCol03;

	StyleMainContent* m_styleContent;
	QWidget* m_content;
	CPWidget* m_wdSign = nullptr;
	CPWidget* m_contentRow1 = nullptr;
	CPWidget* m_contentGrid1_1 = nullptr;
	CPWidget* m_contentGrid1_2 = nullptr;
	CPWidget* m_contentGrid1_3 = nullptr;

	CPWidget* m_contentRow2 = nullptr;

	StyleMainSlide* m_styleSlide;
	QWidget* m_slide;	
	QWidget* m_slideCol01;
	CPWidget* m_slideCol02;
	CPLabel* m_emptyArea;
	
	StyleMainFooter* m_styleFooter;
	QWidget* m_footer;

	MetaTable* m_metaTable = nullptr;
	QTableWidget* m_tableCommon = nullptr;
	QTableWidget* m_tableEMP = nullptr;
	QTableWidget* m_tableSign = nullptr;

	Command* m_btnCheckExt;
	QList<Command*> m_btnsPartExt;
	CommandProvider* m_cmdProviderExt;

	QList<CPTable*> m_mntTables;
	QList<CPBoxSign*> m_mntZoneSign;

	Command* m_btnSlideExt;

	Command* m_btnLogout;
	Command* m_btnPrint;
	Command* m_btnEdit;
	Command* m_btnRemove;
	Command* m_btnNew;

	Command* m_btnViewAll; /* 전체보기 */
	Command* m_btnViewDate;
	Command* m_btnSign;
	CommandProvider* m_cmdProviderView = nullptr;

	Command* m_btnDVCList;
	Command* m_btnMNGList;
	Command* m_btnMNTList;
	Command* m_btnEMPList;
	Command* m_btnImExport;
	CommandProvider* m_cmdProviderList;

	//CPWidget* m_navi = nullptr;
	QWidget* m_navi = nullptr;
	CPLabel* m_lbNavi;
	CPLabel* m_lbUserInfo;

	Command* m_btnNaviPrev;
	Command* m_btnNaviNext;

	Command* m_btnCalendarPrev;
	Command* m_btnCalendarNext;
	CPLabel* m_lbCalendar;

	CheckTable* m_checkTable = nullptr;
	CPWidget* m_mntStack = nullptr;
	QScrollArea* m_mntScrArea = nullptr;

	CPWidget* m_zoneSign = nullptr;
	CPLabel* m_lbSign1 = nullptr;
	CPLabel* m_lbSign2 = nullptr;
	CPLabel* m_lbSign3 = nullptr;


	void initListMNG();
	void initListMNT(bool skip = true);
	void initListMNT2();
	void initListEMP();
	bool initPage(QString tag, QString titleTxt, bool pass = false);

	void newTable(int rowCount, QString tag);
	void newNavi();
	//bool isCurrentMetaTable(QString tag);

	QString getCountDevice();
	QString getCurrentDate(int month=0);
	void clearAutoLogin();
	
	void initWidgets();
	void initContentRow1();
	void initContentRow2();

	void initParent();
	void initStyles();
	void initParentLayout();
	void initBody();
	void initContent();
	void initHeader();
	void initFooter();
	void initSlide();
	void initSlideButton();
	void initMNGNaviCalendar();

	void initButtonsDVC();
	void initButtonsMNG();
	void initButtonsMNT();
	void initButtonsEMP();

	void initTableDVC();
	void initTableMNG();
	void initTableMNT();
	void initTableEMP();

	void updateHeader();
	void updateFooter();
	void updateBody();
	void updateContent();
	void updateSlideButtons();
	void updateSlide();
	void updateContentRow1();
	void updateContentRow2();

	QString m_titleTxt;
	QString m_selectedPart = "";
};
