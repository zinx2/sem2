#pragma once
#include <QObject>
#include <QScreen>
#include <QDebug>
#include <QGuiApplication>

#define TAG_DVC_LIST "device_list"
#define TAG_MNG_LIST "management_list"
#define TAG_MNT_LIST "month_list"
#define TAG_EMP_LIST "employee_list"
#define TAG_IMEXPORT "im_export" 

#define TAG_VIEW_ALL "view_all"
#define TAG_VIEW_DATE "view_date"

class Palette {
public:
	const QString navy01 = "#143246";
	const QString navy02 = "#0a283c";
	const QString navy03 = "#001e32";
	const QString navy04 = "#26708d";


	const QString grary01 = "#eeeeee";
	const QString blue01 = "#2b78e4";
	const QString blue02 = "#6fa8dc";

	const QString testColor01 = "#eeeeee";
	const QString testColor02 = "#eeeeee";
	const QString testColor03 = "#17a05e";
	const QString testColor04 = "#4c8bf5";
	const QString testColor05 = "#364150";
	const QString testColor06 = "#1caf9a";
	const QString testColor07 = "#ffce44";

	const QString btnSelectedStyle = "color: white; background-color: #1caf9a; font-weight: bold;";
	const QString btnReleasedStyle01 = "color: black; background-color: #eeeeee;  border-radius:5px;";
	const QString btnReleasedStyle02 = "color: white; background-color: " + navy01 + ";  border-radius:5px;";
	const QString btnHoveredStyle = "color: white; background-color: blue; font-weight: bold;";

	const QString btnReleasedStyleGray = "color: black; background-color: #eeeeee;  border-radius:5px;";
	const QString btnHoveredStyleGray = btnReleasedStyleGray;
	const QString btnSelectedStyleGray = "color: black; background-color: #9b9b9b;  border-radius:5px;";

	const QString btnReleasedStyleNavy = "color: white; background-color: " + navy01 + ";  border-radius:5px;";
	const QString btnHoveredStyleNavy = btnReleasedStyleNavy;
	const QString btnSelectedStyleNavy = "color: white; background-color: #26708d;  border-radius:5px;";

	const QString btnReleasedStyleNavyNoRadius = "color: white; background-color: " + navy01;
	const QString btnHoveredStyleNavyNoRadius = "color: white; background-color: #1e5064";
	const QString btnSelectedStyleNavyNoRadius = "color: white; background-color: #26708d";

	const QString btnEnable = "color: white; background-color: #dedede";

	const QString btnReleasedStyleGrayNoRadius = "background: #dedede;";
	const QString btnHoveredStyleGrayNoRadius = "background: #c4c4c4;";
	const QString btnSelectedStyleGrayNoRadius = "background: #dedede;";

	const QString btnSelectedStyleDiabled = "background: #a0a0a0; color: #dddddd; border-radius:5px;";
};

class Font : public QObject
{
	Q_OBJECT
		Q_PROPERTY(int large  READ large  WRITE setLarge NOTIFY largeChanged)
		Q_PROPERTY(int midium READ midium WRITE setMidium NOTIFY midiumChanged)
		Q_PROPERTY(int small READ small WRITE setSmall NOTIFY smallChanged)

public:
	/* FONT NAME */
	const QString fontName = "nanumbarungothic.ttf";

	/* FONT SIZE */
	int large() { return m_large; }
	int midium() { return m_midium; }
	int small() { return m_small; }

	public slots :
	void setLarge(int m) { m_large = m; emit largeChanged(); }
	void setMidium(int m) { m_midium = m; emit midiumChanged(); }
	void setSmall(int m) { m_small = m; emit smallChanged(); }

signals:
	void largeChanged();
	void midiumChanged();
	void smallChanged();

protected:
	int m_large = 0;
	int m_midium = 0;
	int m_small = 0;
};

class StyleBasic : public QObject
{
	Q_OBJECT
		Q_PROPERTY(int width  READ width  WRITE setWidth NOTIFY widthChanged)
		Q_PROPERTY(int height READ height WRITE setHeight NOTIFY heightChanged)

public:
	StyleBasic() {
		m_palette = new Palette();
		m_font = new Font();
	}

	/* VIEW SIZE */
	int width() { return m_width; }
	int height() { return m_height; }
	QSize size() { return QSize(m_width, m_height); }

	/* COLOR */
	Palette* palette() { return m_palette; }
	Font* font() { return m_font; }

	public slots :
	void setWidth(int m) { m_width = m; emit widthChanged(); }
	void setHeight(int m) { m_height = m; emit heightChanged(); }

signals:
	void widthChanged();
	void heightChanged();

protected:
	int m_width = 0;
	int m_height = 0;

	Palette* m_palette;
	Font* m_font;
};

class Button : public StyleBasic
{
	Q_OBJECT
		Q_PROPERTY(const char* name READ name WRITE setName NOTIFY nameChanged)
		Q_PROPERTY(QString icon READ icon WRITE setIcon NOTIFY iconChanged)
		Q_PROPERTY(bool visible READ visible WRITE setVisible NOTIFY visibleChanged)
public:
	const char* name() { return m_name; }
	QString icon() { return m_icon; }
	QString tag() { return m_tag; }
	QString releasedStyle() { return m_releasedStyle; }
	QString hoveredStyle() { return m_hoveredStyle; }
	QString selectedStyle() { return m_selectedStyle; }
	QString disabledReleasedStyle() { return m_disabledReleasedStyle; }
	QString disabledHoveredStyle() { return  m_disabledHoveredStyle; }
	QString disabledSelectedStyle() { return m_disabledSelectedStyle; }
	bool visible() { return m_visible; }

	public slots :
	void setName(const char* m) { m_name = m; emit nameChanged(); }
	void setIcon(QString m) { m_icon = m; emit iconChanged(); }
	void setTag(QString m) { m_tag = m; }
	void setReleasedStyle(QString m) { m_releasedStyle = m; }
	void setHoveredStyle(QString m) { m_hoveredStyle = m; }
	void setSelectedStyle(QString m) { m_selectedStyle = m; }
	void setDisabledReleasedStyle(QString m) { m_disabledReleasedStyle = m; }
	void setDisabledHoveredStyle(QString m) { m_disabledHoveredStyle = m; }
	void setDisabledSelectedStyle(QString m) { m_disabledSelectedStyle = m; }
	void setVisible(bool m) { m_visible = m; }

signals:
	void nameChanged();
	void iconChanged();
	void visibleChanged();

protected:
	const char* m_name;
	QString m_icon = "";
	QString m_tag = "";
	QString m_releasedStyle = "";
	QString m_hoveredStyle = "";
	QString m_selectedStyle = "";
	QString m_disabledReleasedStyle = "";
	QString m_disabledHoveredStyle = "";
	QString m_disabledSelectedStyle = "";
	bool m_visible;
};

class NavyButton : public Button
{
public:
	NavyButton()
	{
		setReleasedStyle(palette()->btnReleasedStyleNavy);
		setHoveredStyle(palette()->btnHoveredStyleNavy);
		setSelectedStyle(palette()->btnSelectedStyleNavy);
		setDisabledReleasedStyle(palette()->btnSelectedStyleDiabled);
		setDisabledHoveredStyle(palette()->btnSelectedStyleDiabled);
		setDisabledSelectedStyle(palette()->btnSelectedStyleDiabled);
	}
};

class StyleMainSlide : public StyleBasic
{
	Q_OBJECT
		Q_PROPERTY(bool extended READ extended WRITE extend NOTIFY extendedChanged)
public:
	StyleMainSlide()
	{
		m_width = widthFold;

		m_btnExt = new Button();
		m_btnExt->setTag("");
		m_btnExt->setWidth(20);
		m_btnExt->setHeight(height());
		m_btnExt->setIcon("");
		m_btnExt->setName("◀");
		m_btnExt->setReleasedStyle(btnExtReleasedSheet);
		m_btnExt->setHoveredStyle(btnExtHoverdSheet);
		m_btnExt->setSelectedStyle(btnExtReleasedSheet);

		m_btnDVCList = new Button();
		m_btnDVCList->setTag(TAG_DVC_LIST);
		m_btnDVCList->setHeight(50);
		m_btnDVCList->setIcon(":/imgs/devices_36dp.png");
		m_btnDVCList->setReleasedStyle(palette()->btnReleasedStyle01);
		m_btnDVCList->setHoveredStyle(palette()->btnHoveredStyleGray);
		m_btnDVCList->setSelectedStyle(palette()->btnSelectedStyleGray);

		m_btnMNGList = new Button();
		m_btnMNGList->setTag(TAG_MNG_LIST);
		m_btnMNGList->setHeight(50);
		m_btnMNGList->setIcon(":/imgs/management_36dp.png");
		m_btnMNGList->setReleasedStyle(palette()->btnReleasedStyleGray);
		m_btnMNGList->setHoveredStyle(palette()->btnHoveredStyleGray);
		m_btnMNGList->setSelectedStyle(palette()->btnSelectedStyleGray);

		m_btnMNTList = new Button();
		m_btnMNTList->setTag(TAG_MNT_LIST);
		m_btnMNTList->setHeight(50);
		m_btnMNTList->setIcon(":/imgs/calendar_36dp.png");
		m_btnMNTList->setReleasedStyle(palette()->btnReleasedStyleGray);
		m_btnMNTList->setHoveredStyle(palette()->btnHoveredStyleGray);
		m_btnMNTList->setSelectedStyle(palette()->btnSelectedStyleGray);

		m_btnEMPList = new Button();
		m_btnEMPList->setTag(TAG_EMP_LIST);
		m_btnEMPList->setHeight(50);
		m_btnEMPList->setIcon(":/imgs/employee_36dp.png");
		m_btnEMPList->setReleasedStyle(palette()->btnReleasedStyleGray);
		m_btnEMPList->setHoveredStyle(palette()->btnHoveredStyleGray);
		m_btnEMPList->setSelectedStyle(palette()->btnSelectedStyleGray);

		m_btnImExport = new Button();
		m_btnImExport->setHeight(50);
		m_btnImExport->setIcon(":/imgs/imexport_36dp.png");
		m_btnImExport->setReleasedStyle(palette()->btnReleasedStyleGray);
		m_btnImExport->setHoveredStyle(palette()->btnHoveredStyleGray);
		m_btnImExport->setSelectedStyle(palette()->btnSelectedStyleGray);

		extend(false);
	}

	const int widthSpread = 200;
	const int widthFold = 90;

	const int wBtnExtended = 160;
	const int wBtnFolded = 50;

	const int wCol01 = 20;
	const int hBtnExt = 30;	/* 확장하기 버튼 */

	const QString btnExtReleasedSheet = "border:0px; background: transparent; color:white;";
	const QString btnExtHoverdSheet = "border:0px; background: #1e5064; color:white;";

	Button* btnExt() { return m_btnExt; }
	Button* btnDVCList() { return m_btnDVCList; }
	Button* btnMNGList() { return m_btnMNGList; }
	Button* btnMNTList() { return m_btnMNTList; }
	Button* btnEMPList() { return m_btnEMPList; }
	Button* btnImExport() { return m_btnImExport; }

	bool extended() { return m_extended; }

	public slots :
	void extend(bool m) {
		m_extended = m;
		if (m_extended) {
			m_width = widthSpread;
			m_btnDVCList->setName("장비목록");
			m_btnMNGList->setName("관리대장");
			m_btnMNTList->setName("월별점검");
			m_btnEMPList->setName("직원관리");
			m_btnImExport->setName("대출/반납");

			m_btnDVCList->setWidth(wBtnExtended);
			m_btnMNGList->setWidth(wBtnExtended);
			m_btnMNTList->setWidth(wBtnExtended);
			m_btnEMPList->setWidth(wBtnExtended);
			m_btnImExport->setWidth(wBtnExtended);
		}
		else {
			m_width = widthFold;
			m_btnDVCList->setName("");
			m_btnMNGList->setName("");
			m_btnMNTList->setName("");
			m_btnEMPList->setName("");
			m_btnImExport->setName("");

			m_btnDVCList->setWidth(wBtnFolded);
			m_btnMNGList->setWidth(wBtnFolded);
			m_btnMNTList->setWidth(wBtnFolded);
			m_btnEMPList->setWidth(wBtnFolded);
			m_btnImExport->setWidth(wBtnFolded);
		}
		emit extendedChanged();
	}

signals:
	void extendedChanged();

private:
	bool m_extended = false;

	Button* m_btnExt;
	Button* m_btnDVCList;
	Button* m_btnMNGList;
	Button* m_btnMNTList;
	Button* m_btnEMPList;
	Button* m_btnImExport;
};
class StyleMainHeader : public StyleBasic {
public:
	StyleMainHeader()
	{
		m_height = 60;
		font()->setLarge(24);
		font()->setMidium(18);
		font()->setSmall(14);

		m_btnLogout = new Button();
		m_btnLogout->setTag("logout");
		m_btnLogout->setName("로그아웃");
		m_btnLogout->setWidth(120);
		m_btnLogout->setHeight(40);
		m_btnLogout->setIcon(":/imgs/logout_24dp.png");
		m_btnLogout->setReleasedStyle(palette()->btnReleasedStyleGray);
		m_btnLogout->setHoveredStyle(palette()->btnHoveredStyleGray);
		m_btnLogout->setSelectedStyle(palette()->btnSelectedStyleGray);
	}
	const int wCol01 = 500;
	const char* txtTitle = "e-koreatech 자산 관리 시스템";
	Button* btnLogout() { return m_btnLogout; }

private:
	Button* m_btnLogout;
};

class StyleMainFooter : public StyleBasic {
public:
	StyleMainFooter()
	{
		m_height = 40;
		font()->setMidium(12);
	}
	const QString txtCopyright = "Copyright 2018. OLEI. All rights reserved.";
};

class StyleMainContent : public StyleBasic {
	Q_OBJECT
public:
	StyleMainContent()
	{
		m_btnPrint = new NavyButton();
		m_btnPrint->setTag("print");
		m_btnPrint->setName("인쇄하기");
		m_btnPrint->setWidth(110);
		m_btnPrint->setHeight(40);
		m_btnPrint->setIcon(":/imgs/printer_24dp.png");

		m_btnNew = new NavyButton();
		m_btnNew->setName("추가하기");
		m_btnNew->setWidth(110);
		m_btnNew->setHeight(40);
		m_btnNew->setIcon(":/imgs/plus_24dp.png");

		m_btnRemove = new NavyButton();
		m_btnRemove->setName("삭제하기");
		m_btnRemove->setWidth(110);
		m_btnRemove->setHeight(40);
		m_btnRemove->setIcon(":/imgs/remove_24dp.png");

		m_btnEdit = new NavyButton();
		m_btnEdit->setName("수정하기");
		m_btnEdit->setTag("edit");
		m_btnEdit->setWidth(110);
		m_btnEdit->setHeight(40);
		m_btnEdit->setIcon(":/imgs/edit_24dp.png");

		m_btnNaviLeft = new NavyButton();
		m_btnNaviLeft->setName("◀");
		m_btnNaviLeft->setWidth(30);
		m_btnNaviLeft->setHeight(30);

		m_btnNaviRight = new NavyButton();
		m_btnNaviRight->setName("▶");
		m_btnNaviRight->setWidth(30);
		m_btnNaviRight->setHeight(30);

		m_btnViewAll = new NavyButton();
		m_btnViewAll->setTag(TAG_VIEW_ALL);
		m_btnViewAll->setName("전체보기");
		m_btnViewAll->setWidth(110);
		m_btnViewAll->setHeight(40);
		m_btnViewAll->setIcon(":/imgs/all_24dp.png");

		m_btnViewDate = new NavyButton();
		m_btnViewDate->setTag(TAG_VIEW_DATE);
		m_btnViewDate->setName("월별보기");
		m_btnViewDate->setWidth(110);
		m_btnViewDate->setHeight(40);
		m_btnViewDate->setIcon(":/imgs/calendar2_24dp.png");

		m_btnCalendarPrev = new NavyButton();
		m_btnCalendarPrev->setTag("cal_prev");
		m_btnCalendarPrev->setName("◀");
		m_btnCalendarPrev->setWidth(30);
		m_btnCalendarPrev->setHeight(30);

		m_btnCalendarNext = new NavyButton();
		m_btnCalendarPrev->setTag("cal_next");
		m_btnCalendarNext->setName("▶");
		m_btnCalendarNext->setWidth(30);
		m_btnCalendarNext->setHeight(30);

		m_btnSign = new NavyButton();
		m_btnSign->setWidth(40);
		m_btnSign->setHeight(40);
		m_btnSign->setTag("sign");
		m_btnSign->setName("");
		m_btnSign->setIcon(":/imgs/sign_24dp.png");

	}
	const int wGrid1_1 = 350;
	const int hRow01 = 60;

	Button* btnPrint() { return m_btnPrint; }
	Button* btnNew() { return m_btnNew; }
	Button* btnRemove() { return m_btnRemove; }
	Button* btnEdit() { return m_btnEdit; }
	Button* btnNaviLeft() { return m_btnNaviLeft; }
	Button* btnNaviRight() { return m_btnNaviRight; }
	Button* btnViewAll() { return m_btnViewAll; }
	Button* btnViewDate() { return m_btnViewDate; }
	Button* btnCalendarPrev() { return m_btnCalendarPrev; }
	Button* btnCalendarNext() { return m_btnCalendarNext; }
	Button* btnSign() { return m_btnSign; }

	int hRow02() { return m_hRow02; }
	void setHRow02(int m) { m_hRow02 = m; }

private:
	Button* m_btnPrint;
	Button* m_btnNew;
	Button* m_btnRemove;
	Button* m_btnEdit;
	Button* m_btnNaviLeft;
	Button* m_btnNaviRight;
	Button* m_btnViewAll;
	Button* m_btnViewDate;
	Button* m_btnCalendarPrev;
	Button* m_btnCalendarNext;
	Button* m_btnSign;

	int m_hRow02 = 0;
};

class StyleMainBody : public StyleBasic {
	Q_OBJECT
public:
	StyleMainBody()
	{
		m_slide = new StyleMainSlide();
		m_content = new StyleMainContent();

		m_content->setWidth(m_width - m_slide->width());
		m_height = m_content->height();
		m_content->setHeight(m_height);
		m_slide->setHeight(m_height);

		connect(this, SIGNAL(widthChanged()), this, SLOT(initWidthBody()));
		connect(this, SIGNAL(heightChanged()), this, SLOT(initHeightBody()));
		connect(m_slide, SIGNAL(extendedChanged()), this, SLOT(initWidthBody()));
	}
	StyleMainContent* content() { return m_content; }
	StyleMainSlide* slide() { return m_slide; }

	public slots:
	void initWidthBody()
	{
		m_content->setWidth(m_width - m_slide->width());
	}
	void initHeightBody()
	{
		m_content->setHeight(m_height);
		m_slide->setHeight(m_height);
	}

private:
	StyleMainContent* m_content;
	StyleMainSlide* m_slide;
};

class StyleMain : public StyleBasic {
	Q_OBJECT
public:
	StyleMain()
	{
		m_width = 1200; m_height = 840;
		m_header = new StyleMainHeader();
		m_body = new StyleMainBody();
		m_footer = new StyleMainFooter();

		m_header->setWidth(m_width);
		m_body->setWidth(m_width);
		m_body->setHeight(m_height - m_header->height() - m_footer->height());
		m_footer->setWidth(m_width);

		connect(this, SIGNAL(widthChanged()), this, SLOT(initWidthHeader()));
		connect(this, SIGNAL(widthChanged()), this, SLOT(initWidthFooter()));
		connect(this, SIGNAL(widthChanged()), this, SLOT(initSizeBody()));
		connect(this, SIGNAL(heightChanged()), this, SLOT(initSizeBody()));
	};

	public slots:
	void initWidthHeader() { m_header->setWidth(m_width); }
	void initWidthFooter() { m_footer->setWidth(m_width); }
	void initSizeBody()
	{
		m_body->setWidth(m_width);
		m_body->setHeight(m_height - m_header->height() - m_footer->height());
	}

	StyleMainHeader* header() { return m_header; }
	StyleMainBody*   body() { return m_body; }
	StyleMainFooter* footer() { return m_footer; }

private:
	StyleMainHeader* m_header;
	StyleMainBody*	 m_body;
	StyleMainFooter* m_footer;
};



class Style : public QObject {
	Q_OBJECT
		Q_PROPERTY(int widthWindow  READ widthWindow  WRITE setWidthWindow NOTIFY widthWindowChanged)
		Q_PROPERTY(int heightWindow READ heightWindow WRITE setHeightWindow NOTIFY heightWindowChanged)
		Q_PROPERTY(int widthMenu  READ widthMenu  WRITE setWidthMenu  NOTIFY widthMenuChanged)
		Q_PROPERTY(int heightMenu READ heightMenu WRITE setHeightMenu NOTIFY heightMenuChanged)
		Q_PROPERTY(int widthPage READ widthPage  WRITE setWidthPage  NOTIFY widthPageChanged)
		Q_PROPERTY(int heightPage READ heightPage WRITE setHeightPage NOTIFY heightPageChanged)
		Q_PROPERTY(int widthUtil READ widthUtil  WRITE setWidthUtil  NOTIFY widthUtilChanged)
		Q_PROPERTY(int heightUtil READ heightUtil WRITE setHeightUtil NOTIFY heightUtilChanged)
		Q_PROPERTY(int heightTitleBar READ heightTitleBar WRITE setHeightTitleBar NOTIFY heightTitleBarChanged)

private:
	Style();
	static Style* m_instance;
	Palette m_colors;
public:
	static Style* instance() {
		if (m_instance == nullptr) m_instance = new Style();
		return m_instance;
	}
	Palette palette() { return m_colors; }

	const int MIM_WINDOW_WIDTH = 1200;
	const int MIM_WINDOW_HEIGHT = 800;

	int widthWindow() const { return m_widthWindow; }
	int heightWindow() const { return m_heightWindow; }
	int widthMenu() const { return m_widthMenu; }
	int heightMenu() const { return m_heightMenu; }
	int widthPage() const { return m_widthPage; }
	int heightPage() const { return m_heightPage; }
	int widthUtil() const { return m_widthUtil; }
	int heightUtil() const { return m_heightUtil; }
	int heightTitleBar() const { return m_heightTitleBar; }
	void initialize();

	StyleMain* main() { return m_main; }

	public slots:
	int pt(int pixel) { return pixel * scaleFactor; }
	void setWidthWindow(const int &m) { m_widthWindow = m;  emit widthWindowChanged(); }
	void setHeightWindow(const int &m) { m_heightWindow = m; emit heightWindowChanged(); }
	void setWidthMenu(const int &m) { m_widthMenu = m; emit widthMenuChanged(); }
	void setHeightMenu(const int &m) { m_heightMenu = m; emit heightMenuChanged(); }
	void setWidthPage(const int &m) { m_widthPage = m; emit widthPageChanged(); }
	void setHeightPage(const int &m) { m_heightPage = m; emit heightPageChanged(); }
	void setWidthUtil(const int &m) { m_widthUtil = m; emit widthUtilChanged(); }
	void setHeightUtil(const int &m) { m_heightUtil = m; emit heightUtilChanged(); }
	void setHeightTitleBar(const int &m) { m_heightTitleBar = m; emit heightTitleBarChanged(); }

signals:
	void widthWindowChanged();
	void heightWindowChanged();
	void widthMenuChanged();
	void heightMenuChanged();
	void widthPageChanged();
	void heightPageChanged();
	void widthUtilChanged();
	void heightUtilChanged();
	void heightTitleBarChanged();

private:

	float scaleFactor = 1;
	int m_widthWindow = MIM_WINDOW_WIDTH;
	int m_heightWindow = MIM_WINDOW_HEIGHT;
	int m_widthMenu = pt(350);
	int m_heightMenu = m_heightWindow;

	int m_widthUtil = m_widthWindow;
	int m_heightUtil = pt(100);

	int m_widthPage = m_widthWindow;
	int m_heightPage = m_heightWindow;
	int m_heightTitleBar = 10;

	StyleMain* m_main;
};
//extern Design D;

