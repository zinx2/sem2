#pragma once
#include "cs_qheader.h"
#include "cs_component.h"
#include "cs_command.h"

class Alarm : public CPDialog
{
	Q_OBJECT
public:
	explicit Alarm(QString title, QString message, int width, int height, QWidget *parent=0)
		: CPDialog(width, height, parent)
	{
		setModal(true);
		setWindowTitle(title);
		setLayout(new QVBoxLayout);
		layout()->setMargin(0);
		layout()->setSpacing(0);
		layout()->setAlignment(Qt::AlignTop);
		
		Command* btnConfirm = (new Command("confirm", kr("È®ÀÎ"), 80, 40))
			->initStyleSheet("background: #dedede;")->initEffect("background: #dedede;", "background: #c4c4c4;", "background: #dedede;")
			->initFunc([=]() { confirm(); });
		
		m_lbMessage = (new CPLabel(width, height - 60, message))->initContentsMargins(20, 20, 20, 20)->initAlignment(Qt::AlignTop | Qt::AlignLeft);
		layout()->addWidget(m_lbMessage);

		CPWidget* wdBtn = (new CPWidget(width - 10, 60, new QHBoxLayout))->initAlignment(Qt::AlignRight|Qt::AlignVCenter)->append(btnConfirm);
		layout()->addWidget(wdBtn);

		connect(this, SIGNAL(rejected()), this, SLOT(confirm()));
	}
	Alarm* initSize(int w, int h) { setFixedSize(w, h); return this; }
	Alarm* setMessage(QString txt) { m_lbMessage->setText(txt); return this; }
	public slots:
	void confirm() {
		emit yes();
		//m->alarm(false);
		m->setModal(false);
		close();
	}

private:
	CPWidget* m_zoneMessage;
	CPLabel* m_lbMessage;
};