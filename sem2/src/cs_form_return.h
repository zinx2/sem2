#pragma once
#include "cs_qheader.h"
#include "cs_component.h"
#include "cs_question.h"
#include "cs_signature.h"
#include "cs_command.h"
#include "cs_selector_employee.h"
#define TAG_FORM_RETURN "form_return"
class FormReturn : public CPDialog
{
	Q_OBJECT
public:
	//type 0:����, 1:�ݳ�
	explicit FormReturn(int width, int height, QWidget *parent = 0) : CPDialog(width, height, parent)
	{
		setWindowTitle(kr("�ݳ��ϱ�"));
		setFixedSize(width, height);
		setLayout(new QVBoxLayout);
		layout()->setSpacing(0);
		layout()->setMargin(0);

		m_net = NetWorker::instance();
		setModal(true);
		Palette* p = new Palette();
		btnConfirm = (new Command("confirm", kr("Ȯ��"), 70, 30))
			->initStyleSheet(p->btnReleasedStyleGrayNoRadius)
			->initEffect(p->btnReleasedStyleGrayNoRadius, p->btnHoveredStyleGrayNoRadius, p->btnSelectedStyleGrayNoRadius)
			->initDisabledEffect(p->btnReleasedStyleGrayNoRadius, p->btnHoveredStyleGrayNoRadius, p->btnSelectedStyleGrayNoRadius)
			->initEnabled(false)->initFunc([=]() { confirm(); });
		Command* btnCancel = (new Command("cancel", kr("���"), 70, 30))
			->initStyleSheet(p->btnReleasedStyleGrayNoRadius)->initEffect(p->btnReleasedStyleGrayNoRadius, p->btnHoveredStyleGrayNoRadius, p->btnSelectedStyleGrayNoRadius)
			->initFunc([=]() { cancel(); });
		Command* btnInit = (new Command("init", kr("�ʱ�ȭ"), 70, 30))
			->initStyleSheet(p->btnReleasedStyleGrayNoRadius)->initEffect(p->btnReleasedStyleGrayNoRadius, p->btnHoveredStyleGrayNoRadius, p->btnSelectedStyleGrayNoRadius)
			->initFunc([=]() { init(); });
		Command* btnEmployee = (new Command("search_part", kr("����ã��"), 70, 30))
			->initStyleSheet(p->btnReleasedStyleGrayNoRadius)->initEffect(p->btnReleasedStyleGrayNoRadius, p->btnHoveredStyleGrayNoRadius, p->btnSelectedStyleGrayNoRadius)
			->initFunc([=]()
		{
			SelectorEmployee* selector = new SelectorEmployee(kr("����ã��"), 400, 500);
			selector->setParent(this);
			selector->setTag(TAG_FORM_RETURN);
			selector->show();
		});

		m_lbMessage = new QLabel(kr("������ �����ϼ���."));
		m_lbMessage->setFixedSize(width - 250, 25);
		m_lbMessage->setAlignment(Qt::AlignVCenter | Qt::AlignRight);

		m_device = m->searchedDevice();
		/* ROW 1 */
		edNameDevice = (new CPDialogLineEdit(200, m_device->nameDevice()))->initReadOnly(true);
		edNoAsset = (new CPDialogLineEdit(170, m_device->noAsset()))->initReadOnly(true);
		layout()->addWidget(
			(new CPWidget(width, 45, new QHBoxLayout))
			->initContentsMargins(0, 0, 0, 0)
			->append(new CPLabel(35, 25, kr("����")))
			->append(edNameDevice)
			->append(new CPLabel(60, 25, kr("�ڻ��ȣ")))
			->append(edNoAsset));

		/* ROW 2 */
		edNameUserOrAdmin = (new CPDialogLineEdit(130))->initReadOnly(true);
		edDateBorrowedOrReturned = (new CPDialogLineEdit(170))->initReadOnly(true)->initText(QDateTime::currentDateTime().toString("yyyy-MM-dd"));
		layout()->addWidget(
			(new CPWidget(width, 45, new QHBoxLayout))
			->initContentsMargins(2, 0, 0, 0)
			->append(new CPLabel(35, 25, kr("Ȯ����")))
			->append(edNameUserOrAdmin)
			->append(btnEmployee)
			->append(new CPLabel(55, 25, kr("�ݳ���")))
			->append(edDateBorrowedOrReturned));

		/* ROW 3 */
		edUse = (new CPTextEdit(width - 60, this))->initHeight(50)->initText(m_device->memo())->initReadOnly(true);
		layout()->addWidget(
			(new CPWidget(width, 60, new QHBoxLayout))
			->initContentsMargins(0, 0, 0, 0)
			->append((new CPLabel(35, 60, kr("�뵵")))->initAlignment(Qt::AlignTop | Qt::AlignRight)->initContentsMargins(0, 0, 0, 0))
			->append(edUse));

		/* ROW 4 */
		rbYes = new QRadioButton(kr("��"), this);
		rbYes->setFixedWidth(50);
		rbNo = new QRadioButton(kr("�ƴϿ�"), this);
		rbNo->setFixedWidth(70);
		rbNo->setChecked(true);
		layout()->addWidget(
			(new CPWidget(width, 35, new QHBoxLayout))
			->initContentsMargins(10, 0, 0, 0)->initAlignment(Qt::AlignLeft)
			->append((new CPLabel(130, 25, kr("��������(�ʱ�ȭ) ����")))->initAlignment(Qt::AlignVCenter | Qt::AlignLeft))
			->append(rbYes)
			->append(rbNo));

		/* ROW 5 */
		szSign = new Signature(this);
		szSign->setFixedSize(width - 20, 175);
		layout()->addWidget(
			(new CPWidget(width, 210, new QVBoxLayout))
			->initContentsMargins(10, 0, 0, 0)
			->append((new CPLabel(70, 25, kr("����")))->initAlignment(Qt::AlignBottom))
			->append(szSign));

		layout()->addWidget((new CPWidget(width, 30, new QHBoxLayout))
			->initAlignment(Qt::AlignRight | Qt::AlignVCenter)
			->initSpacing(10)->initContentsMargins(0, 10, 0, 0)
			->append(m_lbMessage)->append(btnInit)->append(btnConfirm)->append(btnCancel));

		//height = 35 + 75 + 35 + 210 + 35;
		//m_wdContents->setFixedHeight(height);
		setFixedHeight(height + 20);

		connect(edNameDevice, SIGNAL(textChanged(const QString &)), this, SLOT(activate(const QString &)));
		connect(edNoAsset, SIGNAL(textChanged(const QString &)), this, SLOT(activate(const QString &)));
		connect(edNameUserOrAdmin, SIGNAL(textChanged(const QString &)), this, SLOT(activate(const QString &)));
		connect(edDateBorrowedOrReturned, SIGNAL(textChanged(const QString &)), this, SLOT(activate(const QString &)));
		connect(edUse, SIGNAL(textChanged()), this, SLOT(activate()));
		connect(this, SIGNAL(rejected()), this, SLOT(cancel()));

		connect(m, SIGNAL(alarmedChanged()), this, SLOT(recognize()));
	}

	void setData(QString noAsset)
	{
		foreach(Device* d, m->devices())
		{
			if (!d->noAsset().compare(noAsset))
			{
				edNameDevice->setText(d->nameDevice());
				edNoAsset->setText(d->noAsset());
				edUse->setText(d->memo());
				QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd");
				edDateBorrowedOrReturned->setText(currentTime);
				break;
			}
		}
	}
	void notify(int row)
	{

	}

	public slots:
	void confirm()
	{
		qDebug() << "confirm";
		m_net->searchDeviceReturned(edNoAsset->text())->request();

	}
	void cancel() { close(); }
	void init() { szSign->init(); }
	void allow()
	{
		Rent* r = m->searchedRent();
		m->setMessageInt(r->noRent());
		m_net->returnDevice(edNoAsset->text(), rbYes->isChecked())->request();

		disconnect(m_question, SIGNAL(yes()), this, SLOT(allow()));

		m_question->close();
		close();
	}
	void none()
	{

	}
	void finish()
	{
		qDebug() << "finish";
		close();
	}
	void activate(const QString & str = "")
	{
		btnConfirm->setDisabled(
			edNameDevice->text().isEmpty() ||
			edNoAsset->text().isEmpty() ||
			edDateBorrowedOrReturned->text().isEmpty() ||
			edNameUserOrAdmin->text().isEmpty() ||
			edUse->toPlainText().isEmpty());

		if (edNameDevice->text().isEmpty())
		{
			m_lbMessage->setText(kr("������ �Է����ּ���."));
		}
		else if (edNoAsset->text().isEmpty())
		{
			m_lbMessage->setText(kr("�ڻ��ȣ�� �Է����ּ���."));
		}
		else if (edNameUserOrAdmin->text().isEmpty())
		{
			m_lbMessage->setText(kr("�����ڸ� �Է����ּ���."));
		}
		else if (edUse->toPlainText().isEmpty())
		{
			m_lbMessage->setText(kr("�뵵�� �Է����ּ���."));
		}
		else
		{
			m_lbMessage->setText("");
		}
	}
	void search()
	{
		SelectorEmployee* selector = new SelectorEmployee(kr("���� ã��"), 400, 500, this);
		selector->setParent(this);
		selector->show();
	}
	void alarm(bool isSuccess)
	{

	}
	void sign(bool isSuccess)
	{

	}

	void notify(int index, QString tag)
	{
		if (!tag.compare(TAG_FORM_RETURN))
		{
			m_selectedEmployee = m->employees().at(index);
			edNameUserOrAdmin->setText(m_selectedEmployee->nameUser());
		}
	}

	void recognize()
	{
		if (m->alarmed() && m->notificator()->type() == Notificator::ConfirmedRent)
		{
			bool result = m->notificator()->result();
			if (result)
			{
				if (!szSign->toImage()) return;

				Rent* r = m->searchedRent();
				QString strNameDevice = kr("���� : ") + r->nameDevice() + "\n";
				QString strNoAsset = kr("�ڻ��ȣ : ") + r->noAsset() + "\n";
				QString strDate = kr("�ݳ���¥ : ") + r->dateBorrowed() + "\n";
				QString strNameUser = kr("Ȯ���� : ") + r->nameUser() + "\n";
				QString strUse = kr("�뵵 : ") + r->purpose() + "\n";

				m_question = new Question(
					kr("�˸�"),
					kr("�ݳ��ðڽ��ϱ�?\n\n")
					+ strNameDevice
					+ strNoAsset
					+ strDate
					+ strNameUser
					+ strUse, 300, 220);
				m_question->func = [=]() {};
				m_question->show();

				connect(m_question, SIGNAL(yes()), this, SLOT(allow()));
				connect(m_question, SIGNAL(no()), this, SLOT(none()));
			}
			else
				m->request(false, Notificator::None, kr("��� ������ Ȯ���� �� �����ϴ�."));

			update();
			m->alarm(false);
		}
	}

private:
	CPLineEdit* edNameDevice;
	CPLineEdit* edNoAsset;
	CPLineEdit* edNameUserOrAdmin;
	CPLineEdit* edDateBorrowedOrReturned;
	QTextEdit* edUse;

	QLabel* m_lbMessage;

	QRadioButton* rbYes;
	QRadioButton* rbNo;
	Command* btnConfirm;

	Signature* szSign;
	Question* m_question;

	Device* m_device;
	Employee* m_selectedEmployee;
	NetWorker* m_net;
	void error(QString message);
	int m_type;
};
