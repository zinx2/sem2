#pragma once
#include "cs_qheader.h"
#include "cs_component.h"
#include "cs_command.h"
typedef std::function<void()> FUNC;
class Question : public CPDialog
{
	Q_OBJECT
public:
	explicit Question(QString title, QString message, int width, int height, QWidget *parent = 0)
		: CPDialog(width, height, parent)
	{
		setModal(true);
		setWindowTitle(title);
		setLayout(new QVBoxLayout);
		layout()->setMargin(0);
		layout()->setSpacing(0);
		layout()->setAlignment(Qt::AlignTop);

		Command* btnConfirm = (new Command("confirm", kr("확인"), 80, 40))
			->initStyleSheet("background: #dedede;")->initEffect("background: #dedede;", "background: #c4c4c4;", "background: #dedede;")
			->initFunc([=]() { confirm(); });

		Command* btnCancel = (new Command("cancel", kr("취소"), 80, 40))
			->initStyleSheet("background: #dedede;")->initEffect("background: #dedede;", "background: #c4c4c4;", "background: #dedede;")
			->initFunc([=]() { cancel(); });

		m_lbMessage = (new CPLabel(width, height - 60, message))->initContentsMargins(20, 20, 20, 20)->initAlignment(Qt::AlignTop | Qt::AlignLeft);
		layout()->addWidget(m_lbMessage);

		CPWidget* wdBtn = (new CPWidget(width - 10, 60, new QHBoxLayout))->initSpacing(10)
			->initAlignment(Qt::AlignRight | Qt::AlignVCenter)->append(btnConfirm)->append(btnCancel);
		layout()->addWidget(wdBtn);
	}
	Question* initSize(int w, int h) { setFixedSize(w, h); return this; }
	Question* initNotificator(Notificator::UpdateType type) { 
		m_noti = new Notificator();
		m_noti->setResult(true);
		m_noti->setType(type);	
		m->setNotificator(m_noti);
		return this;
	}
	Question* setMessage(QString txt) { m_lbMessage->setText(txt); return this; }
	FUNC func;
	public slots:
	void confirm() {
		emit yes();		
		func();
		//m->setNotificator(m_noti);
		m->setModal(false);
		close();
	}

	void cancel() {
		close();
	}

private:
	CPWidget* m_zoneMessage;
	CPLabel* m_lbMessage;
	Notificator* m_noti;
};