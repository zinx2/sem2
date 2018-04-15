#pragma once
#include "cs_qheader.h"
#include "cs_component.h"
#include "cs_signature.h"
#include "cs_question.h"
#include "cs_networker.h"
#include "cs_question.h"
#include "cs_command.h"
#include "cs_model.h"
class FormSignature : public CPDialog
{
	Q_OBJECT
public:
	explicit FormSignature(int noSign, int width, int height, QWidget* parent=0) :  
		CPDialog(width, height, parent)
	{
		m_noSing = noSign;
		setWindowTitle(kr("서명하기"));
		setFixedSize(width, height);
		setLayout(new QVBoxLayout);
		layout()->setSpacing(0);
		layout()->setMargin(0);

		m_net = NetWorker::instance();
		setModal(true);

		Palette* p = new Palette();
		Command* btnConfirm = (new GrayCommand("confirm", kr("확인"), 70, 30))
			->initFunc([=]() { confirm(); });
		Command* btnCancel = (new GrayCommand("cancel", kr("취소"), 70, 30))
			->initFunc([=]() { cancel(); });

		m_signZone = new Signature(this);
		m_signZone->setFixedSize(width - 20, 175);

		layout()->addWidget(
			(new CPWidget(width, 200, new QHBoxLayout, this))
			->initAlignment(Qt::AlignCenter)->initSpacing(10)
			->initContentsMargins(10, 10, 0, 0)
			->append(m_signZone));


		layout()->addWidget((new CPWidget(width, 30, new QHBoxLayout))
			->initAlignment(Qt::AlignRight | Qt::AlignVCenter)
			->initSpacing(10)->initContentsMargins(0, 10, 0, 0)
			->append(btnConfirm)->append(btnCancel));

	};

	void setParent(Notificator::UpdateType type)
	{
		m_updateType = type;
	}

	public slots:
	void confirm()
	{
		if (!m_signZone->toImage()) return;
		m->setMessageInt(m_noSing);
		m_net->uploadFileSignForMonth(QDir::currentPath() + "/tmp.jpg")->request();
		close();
		//qDebug() << "confirm";
		//m_question = new Question(
		//	kr("알림"),
		//	kr("서명을 완료하시겠습니까?\n\n"), 300, 180);
		//m_question->func = [=]() {};
		//m_question->show();

		//connect(m_question, SIGNAL(yes()), this, SLOT(allow()));
		//connect(m_question, SIGNAL(no()), this, SLOT(none()));

	}
	void allow()
	{
		m_net->uploadFileSignForMonth(QDir::currentPath() + "/tmp.jpg")->request();

		disconnect(m_question, SIGNAL(yes()), this, SLOT(allow()));

		m_question->close();
		close();
	}
	void cancel()
	{
		qDebug() << "cancel";
		//m->setModal(false);
		close();
	}

private:
	
	int m_noSing = 0;
	Notificator::UpdateType m_updateType;
	QString m_urlSign = "";
	Question* m_question;
	NetWorker* m_net;
	Signature* m_signZone = nullptr;
};