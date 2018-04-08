#pragma once
#include "cs_qheader.h"
#include "cs_component.h"
#include "cs_command.h"
#include "cs_style.h"
#include "cs_join.h"
#include "cs_networker.h"
#include "cs_model.h"
#include "cs_settings.h"
#include "cs_component.h"

class ViewHome;
class CPLogin : public CPDialog
{
	Q_OBJECT
public:
	CPLogin(QWidget* parent = 0) : CPDialog(380, 280, parent)
	{
		setModal(true);
		s = Settings::instance();
		m = Model::instance();
		setWindowTitle(kr("로그인"));
		//setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
		setFixedSize(380, 280);
		setLayout(new QVBoxLayout);
		layout()->setMargin(0);
		layout()->setSpacing(10);
		layout()->setAlignment(Qt::AlignLeft | Qt::AlignTop);

		Palette* p = new Palette();
		//m_btnClose = (new Command("close", "X", 40, 30))->initFontSize(18)->initStyleSheet(p->btnReleasedStyleNavyNoRadius)
		//        ->initEffect(p->btnReleasedStyleNavyNoRadius, p->btnSelectedStyleNavyNoRadius, p->btnHoveredStyleNavyNoRadius);
		m_btnLogin = (new Command("login", kr("로그인"), 90, 90))->initFontSize(15)->initStyleSheet(p->btnReleasedStyleNavy)
			->initEffect(p->btnReleasedStyleNavy, p->btnSelectedStyleNavy, p->btnHoveredStyleNavy)
			->initFunc([=]() {

			QString id = m_edID->text();
			QString pass = m_edPass->text();
			if (id.isEmpty() || pass.isEmpty())
			{
				Notificator* noti = new Notificator();
				noti->setType(Notificator::None);
				noti->setResult(false);
				noti->setMessage(kr("아이디/비밀번호를 입력하세요."));
				m->setNotificator(noti);
			}
			else {
				NetWorker::instance()->login(m_edID->text(), m_edPass->text())->request();
			}
		});
		m_btnSearch = (new Command("search", kr("아이디/비밀번호 찾기"), 190, 30))->initFontSize(13)->initStyleSheet(p->btnReleasedStyleNavy)
			->initEffect(p->btnReleasedStyleNavy, p->btnSelectedStyleNavy, p->btnHoveredStyleNavy)->initFunc([=]() {
			Notificator* noti = new Notificator();
			noti->setType(Notificator::None);
			noti->setResult(false);
			noti->setMessage(kr("시스템 관리자(구본철)에게 문의하세요."));
			m->setNotificator(noti);
		});
		m_btnJoin = (new Command("join", kr("회원가입"), 100, 30))->initFontSize(13)->initStyleSheet(p->btnReleasedStyleNavy)
			->initEffect(p->btnReleasedStyleNavy, p->btnSelectedStyleNavy, p->btnHoveredStyleNavy)
			->initFunc([=]() {
			(new CPJoin())->show();
		});


		m_row1 = (new CPWidget(width(), 5, new QHBoxLayout))->initAlignment(Qt::AlignRight | Qt::AlignVCenter);
		layout()->addWidget(m_row1);

		m_row2 = (new CPWidget(width(), 6, new QHBoxLayout))->initAlignment(Qt::AlignLeft | Qt::AlignVCenter)
			->initSpacing(5)->initContentsMargins(40, 0, 0, 0)
			->append((new CPLabel(36, 6))->initImage(":/imgs/logo.png"));
		layout()->addWidget(m_row2);

		m_row3 = (new CPWidget(width(), 25, new QHBoxLayout))->initAlignment(Qt::AlignLeft | Qt::AlignVCenter)
			->initContentsMargins(40, 0, 0, 0);

		m_row3->append((new CPLabel(m_row3->width(), m_row3->height(), kr("온라인평생교육원 자산 관리 시스템")))
			->initAlignment(Qt::AlignLeft | Qt::AlignVCenter)->initFontSize(16));
		layout()->addWidget(m_row3);

		m_row4 = (new CPWidget(340, 90, new QHBoxLayout))->initAlignment(Qt::AlignLeft | Qt::AlignTop)
			->initContentsMargins(40, 0, 0, 0)->initSpacing(10);
		layout()->addWidget(m_row4);

		m_edID = (new CPLineEdit(200, 40))->initAlignment(Qt::AlignCenter);
		m_edID->setPlaceholderText(kr("아이디"));

		m_edPass = (new CPLineEdit(200, 40))->initAlignment(Qt::AlignCenter);
		m_edPass->setPlaceholderText(kr("비밀번호"));
		m_edPass->setEchoMode(QLineEdit::Password);

		m_row4->append((new CPWidget(200, 90, new QVBoxLayout))->initAlignment(Qt::AlignLeft | Qt::AlignTop)
			->initSpacing(10)->append(m_edID)->append(m_edPass))->append(m_btnLogin);

		m_row5 = (new CPWidget(width(), 20, new QHBoxLayout))->initAlignment(Qt::AlignLeft | Qt::AlignCenter)
			->initContentsMargins(40, 0, 0, 0);

		m_checkBox = new QCheckBox(kr("로그인 유지"));
		m_row5->layout()->addWidget(m_checkBox);
		connect(m_checkBox, SIGNAL(stateChanged(int)), this, SLOT(checkChanged(int)));
		layout()->addWidget(m_row5);

		m_row6 = (new CPWidget(width(), 1, new QHBoxLayout))->initAlignment(Qt::AlignLeft | Qt::AlignCenter)
			->initContentsMargins(40, 0, 0, 0)->append((new CPLabel(300, 1))->initStyleSheet("background: " + p->navy01));
		layout()->addWidget(m_row6);

		m_row7 = (new CPWidget(width(), 30, new QHBoxLayout))->initAlignment(Qt::AlignLeft | Qt::AlignCenter)
			->initContentsMargins(40, 0, 0, 0)->initSpacing(10)->append(m_btnSearch)->append(m_btnJoin);
		layout()->addWidget(m_row7);
	}
	void setParent(ViewHome* m)
	{
		m_parent = m;
	}

	public slots:
	void checkChanged(int state)
	{		
		s->loginAuto(state > 0 ? true : false);
	}
	void reject()
	{		
		hide();
		Notificator* noti = new Notificator();
		noti->setType(Notificator::Exit);
		m->setNotificator(noti);
	}

private:
	Command* m_btnClose;
	Command* m_btnLogin;
	Command* m_btnSearch;
	Command* m_btnJoin;

	CPWidget* m_row1;
	CPWidget* m_row2;
	CPWidget* m_row3;
	CPWidget* m_row4;
	CPWidget* m_row4_1;
	CPWidget* m_row5;
	CPWidget* m_row6;
	CPWidget* m_row7;
	CPWidget* m_row8;

	CPLineEdit* m_edID;
	CPLineEdit* m_edPass;

	QCheckBox* m_checkBox;

	ViewHome* m_parent;
	Model* m;
	Settings* s;

};
