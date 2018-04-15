#pragma once
#include "cs_qheader.h"
#include "cs_component.h"
#include "cs_signature.h"
#include "cs_question.h"
#include "cs_networker.h"
#include "cs_selector_part.h"
#include "cs_question.h"
#include "cs_command.h"
#include "cs_model.h"
#define TAG_FORM_ADD "form_add"
class FormAdd : public CPDialog
{
	Q_OBJECT
public:
	//type 0:����, 1:�ݳ�
	explicit FormAdd(int width, int height, QWidget *parent = 0) : CPDialog(width, height, parent)
	{
		setWindowTitle(kr("����߰�"));
		setFixedSize(width, height);
		setLayout(new QVBoxLayout);
		layout()->setSpacing(0);
		layout()->setMargin(0);

		m_net = NetWorker::instance();
		setModal(true);

		Palette* p = new Palette();
		btnConfirm = (new GrayCommand("confirm", kr("Ȯ��"), 70, 30))->initEnabled(false)
			->initFunc([=]() { confirm(); });
		Command* btnCancel = (new GrayCommand("cancel", kr("���"), 70, 30))
			->initFunc([=]() { cancel(); });
		Command* btnInit = (new GrayCommand("init", kr("�ʱ�ȭ"), 70, 30))
			->initFunc([=]() { init(); });
		Command* btnPart = (new Command("search_part", kr("�μ�ã��"), 70, 30))
			->initFunc([=]()
		{
			SelectorPart* selector = new SelectorPart(kr("�μ�ã��"), 400, 500);
			selector->setParent(this);
			selector->setTag(TAG_FORM_ADD);
			selector->show();
		});

		m_lbMessage = new QLabel(kr("������ �Է����ּ���."));
		m_lbMessage->setFixedSize(width - 250, 25);
		m_lbMessage->setAlignment(Qt::AlignVCenter | Qt::AlignRight);

		m_edNameDevice = (new CPLineEdit(200, 35, this))->initAlignment(Qt::AlignCenter);
		layout()->addWidget(
			(new CPWidget(width, 35, new QHBoxLayout, this))
			->initAlignment(Qt::AlignLeft)->initSpacing(10)
			->initContentsMargins(10, 10, 0, 0)
			->append((new CPLabel(50, 25, kr("����"))))
			->append(m_edNameDevice));

		m_edNoAsset = (new CPLineEdit(200, 35, this))->initAlignment(Qt::AlignCenter);
		layout()->addWidget(
			(new CPWidget(width, 35, new QHBoxLayout, this))
			->initAlignment(Qt::AlignLeft)->initSpacing(10)
			->initContentsMargins(10, 10, 0, 0)
			->append(new CPLabel(50, 25, kr("�ڻ��ȣ")))
			->append(m_edNoAsset));

		m_edPart = (new CPLineEdit(200, 35, this))->initReadOnly(true)->initText(kr(""))->initAlignment(Qt::AlignCenter);
		layout()->addWidget(
			(new CPWidget(width, 35, new QHBoxLayout, this))
			->initAlignment(Qt::AlignLeft)->initSpacing(10)
			->initContentsMargins(10, 10, 0, 0)
			->append(new CPLabel(50, 25, kr("�Ҽ���Ʈ")))
			->append(m_edPart)->append(btnPart));

		m_edPrice = (new CPLineEdit(200, 35, this))->initAlignment(Qt::AlignCenter);
		layout()->addWidget(
			(new CPWidget(width, 35, new QHBoxLayout, this))
			->initAlignment(Qt::AlignLeft)->initSpacing(10)
			->initContentsMargins(10, 10, 0, 0)
			->append(new CPLabel(50, 25, kr("���ݾ�")))
			->append(m_edPrice));

		m_edDate = (new CPLineEdit(200, 35, this))->initAlignment(Qt::AlignCenter);
		layout()->addWidget(
			(new CPWidget(width, 35, new QHBoxLayout, this))
			->initAlignment(Qt::AlignLeft)->initSpacing(10)
			->initContentsMargins(10, 10, 0, 0)
			->append(new CPLabel(50, 25, kr("�������")))
			->append(m_edDate));

		m_edMemo = (new CPTextEdit(width - 80, this))->initHeight(50);
		layout()->addWidget(
			(new CPWidget(width, 60, new QHBoxLayout, this))
			->initAlignment(Qt::AlignLeft)->initSpacing(10)
			->initContentsMargins(10, 10, 0, 0)
			->append((new CPLabel(50, 50, kr("���")))->initAlignment(Qt::AlignTop | Qt::AlignRight)->initContentsMargins(0, 0, 5, 0))
			->append(m_edMemo));

		layout()->addWidget((new CPWidget(width, 30, new QHBoxLayout))
			->initAlignment(Qt::AlignRight | Qt::AlignVCenter)
			->initSpacing(10)->initContentsMargins(0, 10, 0, 0)
			->append(m_lbMessage)->append(btnInit)->append(btnConfirm)->append(btnCancel));

		//height = 35 * 5 + 5 + 95;
		//m_wdContents->setFixedHeight(height);
		setFixedHeight(height + 10);

		connect(m_edMemo, SIGNAL(textChanged()), this, SLOT(activate()));
		connect(this, SIGNAL(rejected()), this, SLOT(cancel()));

		connect(m_edNameDevice, SIGNAL(textChanged(const QString &)), this, SLOT(activate(const QString &)));
		connect(m_edNoAsset, SIGNAL(textChanged(const QString &)), this, SLOT(recognize(const QString &)));
		connect(m_edPart, SIGNAL(textChanged(const QString &)), this, SLOT(activate(const QString &)));
		connect(m_edPrice, SIGNAL(textChanged(const QString &)), this, SLOT(activate(const QString &)));
		connect(m_edDate, SIGNAL(textChanged(const QString &)), this, SLOT(activate(const QString &)));
	}

	void setData(QString noAsset)
	{
		foreach(Device* d, m->devices())
		{
			if (!d->noAsset().compare(noAsset))
			{
				m_edNameDevice->setText(d->nameDevice());
				m_edNoAsset->setText(d->noAsset());
				QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd");
				m_edDate->setText(currentTime);
				break;
			}
		}
	}

	public slots:
	void confirm()
	{
		qDebug() << "confirm";

		QString strNameDevice = kr("���� : ") + m_edNameDevice->text() + "\n";
		QString strNoAsset = kr("�ڻ��ȣ : ") + m_edNoAsset->text() + "\n";
		QString strPart = kr("�Ҽ���Ʈ : ") + m_edPart->text() + "\n";
		QString strPrice = kr("���ݾ� : ") + m_edPrice->text() + "\n";
		QString strDate = kr("������� : ") + m_edDate->text() + "\n";
		QString strMemo = kr("��� : ") + m_edMemo->toPlainText() + "\n";

		m_question = new Question(
			kr("�˸�"),
			kr("��� �߰��Ͻðڽ��ϱ�?\n\n")
			+ strNameDevice
			+ strNoAsset
			+ strPart
			+ strPrice
			+ strDate
			+ strMemo, 300, 180);
		m_question->func = [=]() {};
		m_question->show();

		connect(m_question, SIGNAL(yes()), this, SLOT(allow()));
		connect(m_question, SIGNAL(no()), this, SLOT(none()));
	}

	void cancel()
	{
		qDebug() << "cancel";
		//m->setModal(false);
		close();
	}
	void allow()
	{
		qDebug() << "allow";
		QString strNameDevice = kr("���� : ") + m_edNameDevice->text() + "\n";
		QString strNoAsset = kr("�ڻ��ȣ : ") + m_edNoAsset->text() + "\n";
		QString strPart = kr("�Ҽ���Ʈ : ") + m_edPart->text() + "\n";
		QString strPrice = kr("���ݾ� : ") + m_edPrice->text() + "\n";
		QString strDate = kr("������� : ") + m_edDate->text() + "\n";
		QString strMemo = kr("��� : ") + m_edMemo->toPlainText() + "\n";

		m_net->addDevice(
			m_selectedPart->noPart(),
			m_edNameDevice->text(),
			m_edNoAsset->text(),
			m_edNoAsset->text(),
			m_edPrice->text(),
			m_edDate->text(),
			m_edMemo->toPlainText())->request();

		disconnect(m_question, SIGNAL(yes()), this, SLOT(allow()));

		m_question->close();
		close();
	}
	void none()
	{
		qDebug() << "none";
		m_question->hide();
	}
	void activate(const QString & str = "")
	{
		btnConfirm->setDisabled(
			m_edNameDevice->text().isEmpty() ||
			m_edNoAsset->text().isEmpty() ||
			m_edPart->text().isEmpty() ||
			m_edPrice->text().isEmpty() ||
			m_edDate->text().isEmpty());

		if (m_edNameDevice->text().isEmpty())
		{
			m_lbMessage->setText(kr("������ �Է����ּ���."));
		}
		else if (m_edNoAsset->text().isEmpty())
		{
			m_lbMessage->setText(kr("�ڻ��ȣ�� �Է����ּ���."));
		}
		else if (m_edPrice->text().isEmpty())
		{
			m_lbMessage->setText(kr("���ݾ��� �Է����ּ���."));
		}
		else if (m_edDate->text().isEmpty())
		{
			m_lbMessage->setText(kr("������� �Է����ּ���."));
		}
		else
		{
			m_lbMessage->setText("");
		}
	}
	void recognize(const QString & str = "")
	{
		QString barcode = m_edNoAsset->text();
		if (barcode.size() == 0) {
			activate();
			return;
		}
		if (barcode.at(barcode.size() - 1) == '\n')
		{
			QStringRef subString(&barcode, 0, barcode.size() - 1);
			m_edNoAsset->setText(subString.toString());
			barcode = subString.toString();
		}

		int searchedCnt = 0;
		foreach(Device* d, m->devices())
		{
			if (!d->noAsset().compare(barcode))
			{
				searchedCnt++;
				m_lbMessage->setText(kr("�̹� ��ϵ� ����Դϴ�."));
				btnConfirm->setEnabled(false);
				return;
			}
		}
		if (searchedCnt == 0)
		{
			m_lbMessage->setText(kr("��� ������ ����Դϴ�."));
			btnConfirm->setDisabled(
				m_edNameDevice->text().isEmpty() ||
				m_edNoAsset->text().isEmpty() ||
				m_edPart->text().isEmpty() ||
				m_edPrice->text().isEmpty() ||
				m_edDate->text().isEmpty());
		}
		//QTextCursor tmpCursor = m_edNoAsset->textCursor();
		//m_edNoAsset->moveCursor(QTextCursor::EndOfLine);
	}
	void search()
	{
		SelectorPart* selector = new SelectorPart(kr("�μ�ã��"), 400, 500, this);
		selector->setParent(this);
		selector->setTag(TAG_FORM_ADD);
		selector->show();
	}
	void check(int state)
	{
		if (state > 0) activate();
	}
	void init()
	{
		m_edNameDevice->setText("");
		m_edNoAsset->setText("");
		m_edPrice->setText("");
		m_edDate->setText("");
		m_edMemo->setText("");
		m_edNameDevice->setText("");
	}

	void notify(int index, QString tag)
	{
		if (!tag.compare(TAG_FORM_ADD))
		{
			m_selectedPart = m->parts().at(index);
			m_edPart->setText(m_selectedPart->namePart());
		}
	}
private:
	CPLineEdit* m_edNameDevice;
	CPLineEdit* m_edNoAsset;
	CPLineEdit* m_edPart;
	CPLineEdit* m_edPrice;
	CPLineEdit* m_edDate;
	CPTextEdit* m_edMemo;

	QLabel* m_lbMessage;

	QCheckBox* cbSecure;
	Command* btnConfirm;

	Question* m_question;

	Part* m_part;
	NetWorker* m_net;
	bool notified = false;
	void error(QString message);

	QMutex m_mtx;
	Part* m_selectedPart = nullptr;
};
