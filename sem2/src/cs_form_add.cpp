#include "cs_form_add.h"
#include "cs_component.h"
#include "cs_question.h"
#include "cs_command.h"
#include "cs_model.h"
#include "cs_networker.h"
#include "cs_selector_part.h"
#include "cs_component.h"
#include "cs_style.h"

FormAdd::FormAdd(int width, int height, QWidget *parent)
	: CPDialog(width, height, parent)
{
	setWindowTitle(kr("장비추가"));
	setFixedSize(width, height);
	setLayout(new QVBoxLayout);
	layout()->setSpacing(0);
	layout()->setMargin(0);

	m_net = NetWorker::instance();
	setModal(true);

	Palette* p = new Palette();
	btnConfirm = (new Command("confirm", kr("확인"), 70, 30))
	->initStyleSheet(p->btnReleasedStyleGrayNoRadius)->initEffect(p->btnReleasedStyleGrayNoRadius, p->btnHoveredStyleGrayNoRadius, p->btnSelectedStyleGrayNoRadius)
	->initEnabled(false)->initFunc([=]() { confirm();});
	Command* btnCancel = (new Command("cancel", kr("취소"), 70, 30))
		->initStyleSheet(p->btnReleasedStyleGrayNoRadius)->initEffect(p->btnReleasedStyleGrayNoRadius, p->btnHoveredStyleGrayNoRadius, p->btnSelectedStyleGrayNoRadius)
		->initFunc([=]() { cancel(); });
	Command* btnSaerch = (new Command("search", kr("부서찾기"), 70, 30))
		->initStyleSheet(p->btnReleasedStyleGrayNoRadius)->initEffect(p->btnReleasedStyleGrayNoRadius, p->btnHoveredStyleGrayNoRadius, p->btnSelectedStyleGrayNoRadius)
		->initFunc([=]() { search(); });
	Command* btnInit = (new Command("init", kr("초기화"), 70, 30))
		->initStyleSheet(p->btnReleasedStyleGrayNoRadius)->initEffect(p->btnReleasedStyleGrayNoRadius, p->btnHoveredStyleGrayNoRadius, p->btnSelectedStyleGrayNoRadius)
		->initFunc([=]() { init(); });

	m_lbMessage = new QLabel(kr("장비명을 입력해주세요."));
	m_lbMessage->setFixedSize(width - 250, 25);
	m_lbMessage->setAlignment(Qt::AlignVCenter | Qt::AlignRight);

	m_edNameDevice = (new CPLineEdit(200, 35, this))->initAlignment(Qt::AlignCenter);
	layout()->addWidget(
		(new CPWidget(width, 35, new QHBoxLayout, this))
		->initAlignment(Qt::AlignLeft)->initSpacing(10)
		->initContentsMargins(10, 10, 0, 0)
		->append((new CPLabel(50, 25, kr("장비명"))))
		->append(m_edNameDevice));

	m_edNoAsset = (new CPLineEdit(200, 35, this))->initAlignment(Qt::AlignCenter);
	layout()->addWidget(
		(new CPWidget(width, 35, new QHBoxLayout, this))
		->initAlignment(Qt::AlignLeft)->initSpacing(10)
		->initContentsMargins(10, 10, 0, 0)
		->append(new CPLabel(50, 25, kr("자산번호")))
		->append(m_edNoAsset));

	m_edPart = (new CPLineEdit(200, 35, this))->initReadOnly(true)->initText(kr("시스템파트"))->initAlignment(Qt::AlignCenter);
	layout()->addWidget(
		(new CPWidget(width, 35, new QHBoxLayout, this))
		->initAlignment(Qt::AlignLeft)->initSpacing(10)
		->initContentsMargins(10, 10, 0, 0)
		->append(new CPLabel(50, 25, kr("소속파트")))
		->append(m_edPart)
	/*->append(btnSaerch)*/);

	m_edPrice = (new CPLineEdit(200, 35, this))->initAlignment(Qt::AlignCenter);
	layout()->addWidget(
		(new CPWidget(width, 35, new QHBoxLayout, this))
		->initAlignment(Qt::AlignLeft)->initSpacing(10)
		->initContentsMargins(10, 10, 0, 0)
		->append(new CPLabel(50, 25, kr("취득금액")))
		->append(m_edPrice));

	m_edDate = (new CPLineEdit(200, 35, this))->initAlignment(Qt::AlignCenter);
	layout()->addWidget(
		(new CPWidget(width, 35, new QHBoxLayout, this))
		->initAlignment(Qt::AlignLeft)->initSpacing(10)
		->initContentsMargins(10, 10, 0, 0)
		->append(new CPLabel(50, 25, kr("취득일자")))
		->append(m_edDate));

	m_edMemo = (new CPTextEdit(width - 80, this))->initHeight(50);
	layout()->addWidget(
		(new CPWidget(width, 60, new QHBoxLayout, this))
		->initAlignment(Qt::AlignLeft)->initSpacing(10)
		->initContentsMargins(10, 10, 0, 0)
		->append((new CPLabel(50, 50, kr("비고")))->initAlignment(Qt::AlignTop | Qt::AlignRight)->initContentsMargins(0, 0, 5, 0))
		->append(m_edMemo));

	layout()->addWidget((new CPWidget(width, 30, new QHBoxLayout))
		->initAlignment(Qt::AlignRight | Qt::AlignVCenter)
		->initSpacing(10)->initContentsMargins(0, 10, 0, 0)
		->append(m_lbMessage)->append(btnInit)->append(btnSaerch)->append(btnCancel));

	//height = 35 * 5 + 5 + 95;
	//m_wdContents->setFixedHeight(height);
	setFixedHeight(height + 10);

	connect(btnConfirm, SIGNAL(clicked()), this, SLOT(confirm()));
	connect(btnCancel, SIGNAL(clicked()), this, SLOT(cancel()));
	connect(btnInit, SIGNAL(clicked()), this, SLOT(init()));
	connect(m_edMemo, SIGNAL(textChanged()), this, SLOT(activate()));
	connect(btnSaerch, SIGNAL(clicked()), this, SLOT(search()));
	connect(this, SIGNAL(rejected()), this, SLOT(cancel()));


	connect(m_edNameDevice, SIGNAL(textChanged(const QString &)), this, SLOT(activate(const QString &)));
	connect(m_edNoAsset, SIGNAL(textChanged(const QString &)), this, SLOT(recognize(const QString &)));
	connect(m_edPart, SIGNAL(textChanged(const QString &)), this, SLOT(activate(const QString &)));
	connect(m_edPrice, SIGNAL(textChanged(const QString &)), this, SLOT(activate(const QString &)));
	connect(m_edDate, SIGNAL(textChanged(const QString &)), this, SLOT(activate(const QString &)));
}
void FormAdd::search()
{
	SelectorPart* selector = new SelectorPart(kr("부서찾기"), 400, 500, this);
	selector->setParent(this);
	selector->show();
}
void FormAdd::recognize(const QString & str)
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
			m_lbMessage->setText(kr("이미 등록된 장비입니다."));
			btnConfirm->setEnabled(false);
			return;
		}
	}
	if (searchedCnt == 0)
	{
		m_lbMessage->setText(kr("등록 가능한 장비입니다."));
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
void FormAdd::activate(const QString & str)
{
	btnConfirm->setDisabled(
		m_edNameDevice->text().isEmpty() ||
		m_edNoAsset->text().isEmpty() ||
		m_edPart->text().isEmpty() ||
		m_edPrice->text().isEmpty() ||
		m_edDate->text().isEmpty());

	if (m_edNameDevice->text().isEmpty())
	{
		m_lbMessage->setText(kr("장비명을 입력해주세요."));
	}
	else if (m_edNoAsset->text().isEmpty())
	{
		m_lbMessage->setText(kr("자산번호를 입력해주세요."));
	}
	else if (m_edPrice->text().isEmpty())
	{
		m_lbMessage->setText(kr("취득금액을 입력해주세요."));
	}
	else if (m_edDate->text().isEmpty())
	{
		m_lbMessage->setText(kr("취득일을 입력해주세요."));
	}
	else
	{
		m_lbMessage->setText("");
	}
}
void FormAdd::check(int state)
{
	if (state > 0) activate();
}
void FormAdd::setData(QString noAsset)
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
void FormAdd::confirm()
{
	qDebug() << "confirm";

	QString strNameDevice = kr("장비명 : ") + m_edNameDevice->text() + "\n";
	QString strNoAsset = kr("자산번호 : ") + m_edNoAsset->text() + "\n";
	QString strPart = kr("소속파트 : ") + m_edPart->text() + "\n";
	QString strPrice = kr("취득금액 : ") + m_edPrice->text() + "\n";
	QString strDate = kr("취득일자 : ") + m_edDate->text() + "\n";
	QString strMemo = kr("비고 : ") + m_edMemo->toPlainText() + "\n";

	m_question = new Question(
		kr("알림"),
		kr("장비를 추가하시겠습니까?\n\n")
		+ strNameDevice
		+ strNoAsset
		+ strPart
		+ strPrice
		+ strDate
		+ strMemo, 300, 180);
	m_question->show();

	connect(m_question, SIGNAL(yes()), this, SLOT(allow()));
	connect(m_question, SIGNAL(no()), this, SLOT(none()));

}
void FormAdd::cancel()
{
	qDebug() << "cancel";
	//m->setModal(false);
	close();
}
void FormAdd::allow()
{
	qDebug() << "allow";
	QString strNameDevice = kr("장비명 : ") + m_edNameDevice->text() + "\n";
	QString strNoAsset = kr("자산번호 : ") + m_edNoAsset->text() + "\n";
	QString strPart = kr("소속파트 : ") + m_edPart->text() + "\n";
	QString strPrice = kr("취득금액 : ") + m_edPrice->text() + "\n";
	QString strDate = kr("취득일자 : ") + m_edDate->text() + "\n";
	QString strMemo = kr("비고 : ") + m_edMemo->toPlainText() + "\n";

	m_net->addDevice(
		1/*m_part->noPart()*/,
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

void FormAdd::none()
{
	qDebug() << "none";
	m_question->hide();
}
void FormAdd::notify(int row)
{
	m_part = m->parts().at(row);
	m_edPart->setText(m_part->namePart());
	update();
}

void FormAdd::init()
{
	m_edNameDevice->setText("");
	m_edNoAsset->setText("");
	m_edPrice->setText("");
	m_edDate->setText("");
	m_edMemo->setText("");
	m_edNameDevice->setText("");
}
