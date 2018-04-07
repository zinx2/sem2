#pragma once
#include "cs_qheader.h"
#include "cs_component.h"
#include "cs_command.h"
#include "cs_style.h"
class CPLogin : public QWidget
{
	Q_OBJECT
public:
	CPLogin(QWidget* parent = 0) : QWidget(parent)
	{
		setFixedSize(400, 280);
		setLayout(new QVBoxLayout);
		layout()->setMargin(0);
		layout()->setSpacing(10);
		layout()->setAlignment(Qt::AlignLeft | Qt::AlignTop);

		      Palette* p = new Palette();
		      m_btnClose = (new Command("close", "X", 40, 30))->initFontSize(18)->initStyleSheet(p->btnReleasedStyleNavyNoRadius)
		              ->initEffect(p->btnReleasedStyleNavyNoRadius, p->btnSelectedStyleNavyNoRadius, p->btnHoveredStyleNavyNoRadius);
		      m_btnLogin = (new Command("login", kr("로그인"), 90, 90))->initFontSize(20)->initStyleSheet(p->btnReleasedStyleNavyNoRadius)
		              ->initEffect(p->btnReleasedStyleNavyNoRadius, p->btnSelectedStyleNavyNoRadius, p->btnHoveredStyleNavyNoRadius);

		      m_row1 = (new CPWidget(width(), 30, new QHBoxLayout))->initAlignment(Qt::AlignRight | Qt::AlignVCenter)->append(m_btnClose);
		      layout()->addWidget(m_row1);

		      m_row2 = (new CPWidget(width(), 6, new QHBoxLayout))->initAlignment(Qt::AlignLeft | Qt::AlignVCenter)
		              ->initSpacing(5)->initContentsMargins(40, 0, 0, 0)
		              ->append((new CPLabel(36, 6))->initImage(":/imgs/logo.png"));
		      layout()->addWidget(m_row2);

		      m_row3 = (new CPWidget(width(), 25, new QHBoxLayout))->initAlignment(Qt::AlignLeft | Qt::AlignVCenter)
		              ->initContentsMargins(40, 0, 0, 0);

		      m_row3->append((new CPLabel(m_row3->width(), m_row3->height(), kr("온라인평생교육원 자산 관리 시스템")))
		                  ->initAlignment(Qt::AlignLeft|Qt::AlignVCenter)->initFontSize(16));
		      layout()->addWidget(m_row3);

		      m_row4 = (new CPWidget(340, 90, new QHBoxLayout))->initAlignment(Qt::AlignLeft | Qt::AlignTop)
		              ->initContentsMargins(40, 0, 0, 0)->initSpacing(10);
		      layout()->addWidget(m_row4);

		      m_edID = (new CPLineEdit(200, 40));
		      m_edID->setPlaceholderText(kr("아이디"));

		      m_edPass = (new CPLineEdit(200, 40));
		      m_edPass->setPlaceholderText(kr("비밀번호"));

		m_row4->append((new CPWidget(200, 90, new QVBoxLayout))->initAlignment(Qt::AlignLeft | Qt::AlignTop)
			->initSpacing(10)->append(m_edID)->append(m_edPass))->append(m_btnLogin);


	}

	private:
	    Command* m_btnClose;
	    Command* m_btnLogin;
	    CPWidget* m_row1;
	    CPWidget* m_row2;
	    CPWidget* m_row3;
	    CPWidget* m_row4;
	    CPWidget* m_row4_1;
	    CPWidget* m_row5;
	    CPWidget* m_row6;
	    CPWidget* m_row7;
	
	    CPLineEdit* m_edID;
	    CPLineEdit* m_edPass;

};
