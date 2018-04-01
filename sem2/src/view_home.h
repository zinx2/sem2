﻿#pragma once
#include <QMainWindow>
#include "cs_style.h"
#include "cs_component.h"
#include "cs_command.h"

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
	CPWidget* m_contentGrid1_2;
	CPLabel* m_lbCurrentContent;
	CPWidget* m_contentRow02;

	StyleMainSlide* m_styleSlide;
	QWidget* m_slide;	
	QWidget* m_slideCol01;
	CPWidget* m_slideCol02;
	
	StyleMainFooter* m_styleFooter;
	QWidget* m_footer;

	Command* m_btnLogout;
	Command* m_btnPrint;
	Command* m_btnEdit;
	Command* m_btnRemove;
	Command* m_btnNew;

	Command* m_btnDVCList;
	Command* m_btnMNGList;
	Command* m_btnMNTList;
	Command* m_btnEMPList;

	void initDVCList();
	void initMNGList();
	void initMNTList();
	void initEMPList();
};
