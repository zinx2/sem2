﻿#pragma once
#include <QMainWindow>
#include "cs_style.h"
#include "cs_component.h"
#include "cs_command.h"
#include "cs_metatable.h"

#define TAG_DVC_LIST "device_list"
#define TAG_MNG_LIST "management_list"
#define TAG_MNT_LIST "month_list"
#define TAG_EMP_LIST "employee_list"

class ViewHome : public QWidget
{
    Q_OBJECT

public:
    ViewHome(QWidget *parent = 0);
    ~ViewHome();

	void initializeUI();
	public slots:
	void updateUI();

protected:
	void resizeEvent(QResizeEvent *event) override;

private:
	bool initedUI = false;

	StyleMain* m_style;

	StyleMainBody* m_styleBody;
	QWidget* m_body;

	StyleMainHeader* m_styleHeader;
	QWidget* m_header;
	CPLabel* m_headerCol01;
	CPWidget* m_headerCol02;

	StyleMainContent* m_styleContent;
	QWidget* m_content;
	CPWidget* m_contentRow1;
	CPWidget* m_contentGrid1_2 = nullptr;
	CPLabel* m_lbCurrentContent;
	CPWidget* m_contentRow2;

	StyleMainSlide* m_styleSlide;
	QWidget* m_slide;	
	QWidget* m_slideCol01;
	CPWidget* m_slideCol02;
	
	StyleMainFooter* m_styleFooter;
	QWidget* m_footer;

	MetaTable* m_metaTable = nullptr;
	QTableWidget* m_tableDVC = nullptr;
	QTableWidget* m_tableEMP = nullptr;

	Command* m_btnLogout;
	Command* m_btnPrint;
	Command* m_btnEdit;
	Command* m_btnRemove;
	Command* m_btnNew;

	Command* m_btnDVCList;
	Command* m_btnMNGList;
	Command* m_btnMNTList;
	Command* m_btnEMPList;
	CommandProvider* m_cmdProvider;

	CPWidget* m_navi = nullptr;
	CPLabel* m_lbNavi;
	Command* m_btnNaviLeft;
	Command* m_btnNaviRight;

	void initDVCList();
	void initMNGList();
	void initMNTList();
	void initEMPList();

	void newTable(int rowCount, QString tag);
	void newNavi();
	void newMetaTable(QString tag);
	bool isCurrentMetaTable(QString tag);
};