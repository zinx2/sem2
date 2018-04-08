#pragma once
#include "cs_qheader.h"
#include "cs_component.h"
#include "cs_command.h"
#include "cs_style.h"
#include "cs_selector_employee.h"
#include "cs_selector_part.h"
#include "cs_networker.h"

#define TAG_JOIN_FIND_EMPLOYEE "join_find_emp"
#define TAG_JOIN_FIND_PART "join_find_part"
class CPJoin : public CPDialog
{
    Q_OBJECT
public:
    CPJoin() : CPDialog(400, 400)
    {
		setModal(true);
		setWindowTitle(kr("회원가입"));
        setFixedSize(400, 360);
        setLayout(new QVBoxLayout);
        layout()->setMargin(0);
        layout()->setSpacing(10);
        layout()->setAlignment(Qt::AlignLeft | Qt::AlignTop);

        Palette* p = new Palette();
        m_btnConfirm = (new Command("id_confirm", kr("중복확인"), 100, 40))->initFontSize(12)->initStyleSheet(p->btnReleasedStyleNavy)
                ->initEffect(p->btnReleasedStyleNavy, p->btnSelectedStyleNavy, p->btnHoveredStyleNavy)->initFunc([=]()
				{
				});
        m_btnEmp = (new Command("search_employee", kr("직원찾기"), 100, 40))->initFontSize(12)->initStyleSheet(p->btnReleasedStyleNavy)
                ->initEffect(p->btnReleasedStyleNavy, p->btnSelectedStyleNavy, p->btnHoveredStyleNavy)->initFunc([=]()
				{
			SelectorEmployee* selector = new SelectorEmployee(kr("직원찾기"), 400, 500);
			selector->setParent(this);
			selector->setTag(TAG_JOIN_FIND_EMPLOYEE);
			selector->show();
					
				});
        m_btnPart = (new Command("search_part", kr("부서찾기"), 100, 40))->initFontSize(12)->initStyleSheet(p->btnReleasedStyleNavy)
                ->initEffect(p->btnReleasedStyleNavy, p->btnSelectedStyleNavy, p->btnHoveredStyleNavy)->initFunc([=]()
				{
			SelectorPart* selector = new SelectorPart(kr("부서찾기"), 400, 500);
			selector->setParent(this);
			selector->setTag(TAG_JOIN_FIND_PART);
			selector->show();
				});
        m_btnClear = (new Command("edit_clear", kr("초기화"), 100, 40))->initFontSize(12)->initStyleSheet(p->btnReleasedStyleNavy)
                ->initEffect(p->btnReleasedStyleNavy, p->btnSelectedStyleNavy, p->btnHoveredStyleNavy)->initFunc([=]()
				{
			m_edID->setText("");
			m_edPass->setText("");
			m_edPassRe->setText("");
			m_edEmp->setText(kr("직원을 선택하세요."));
			m_edPart->setText(kr("부서를 선택하세요."));
				});
        m_btnJoin = (new Command("edit_finish", kr("완료하기"), 100, 40))->initFontSize(12)->initStyleSheet(p->btnReleasedStyleNavy)
                ->initEffect(p->btnReleasedStyleNavy, p->btnSelectedStyleNavy, p->btnHoveredStyleNavy)->initFunc([=]()
				{

			Notificator* noti = new Notificator();
			noti->setType(Notificator::None);
			noti->setResult(false);		
			noti->setMessage("");
			if(m_edID->text().isEmpty())
				noti->setMessage(kr("아이디를 입력하세요."));
			else if(m_edPass->text().isEmpty())
				noti->setMessage(kr("비밀번호를 입력하세요."));
			else if (m_edPassRe->text().isEmpty())
				noti->setMessage(kr("비밀번호를 확인하세요."));
			else if (m_edPassRe->text().compare(m_edPass->text()))
				noti->setMessage(kr("비밀번호가 일치하지 않습니다."));
			else if (m_edEmp->text().isEmpty() || m_selectedEmployee == nullptr)
				noti->setMessage(kr("직원을 선택하세요."));
			else if (m_edPart->text().isEmpty() || m_selectedPart == nullptr)
				noti->setMessage(kr("부서를 선택하세요."));

			if(!noti->message().isEmpty()) Model::instance()->setNotificator(noti);
			else {
				NetWorker::instance()->join(m_edID->text(), m_edPass->text(), m_selectedPart->noPart(), m_selectedEmployee->noUser())->request();
				close();
			}
			});

        m_edID = (new CPLineEdit(200, 40))->initAlignment(Qt::AlignCenter);
        m_edID->setPlaceholderText(kr("아이디를 입력하세요."));
        m_edPass = (new CPLineEdit(200, 40))->initAlignment(Qt::AlignCenter);
        m_edPass->setPlaceholderText(kr("비밀번호를 입력하세요."));
		m_edPass->setEchoMode(QLineEdit::Password);
		connect(m_edPass, SIGNAL(textChanged(const QString &)), this, SLOT(recognizePass(const QString &)));
        m_edPassRe = (new CPLineEdit(200, 40))->initAlignment(Qt::AlignCenter);
        m_edPassRe->setPlaceholderText(kr("비밀번호를 다시 입력하세요."));
		m_edPassRe->setEchoMode(QLineEdit::Password);
		connect(m_edPassRe, SIGNAL(textChanged(const QString &)), this, SLOT(recognizePassRe(const QString &)));
        m_edEmp = (new CPLineEdit(200, 40))->initAlignment(Qt::AlignCenter)->initReadOnly(true);
        m_edEmp->setText(kr("직원을 선택하세요."));
		m_edEmp->setStyleSheet("color: gray;");
        m_edPart = (new CPLineEdit(200, 40))->initAlignment(Qt::AlignCenter)->initReadOnly(true);
        m_edPart->setText(kr("부서를 선택하세요."));
		m_edPart->setStyleSheet("color: gray;");

        m_row1 = (new CPWidget(width(), 10, new QHBoxLayout))->initAlignment(Qt::AlignLeft | Qt::AlignVCenter)->initSpacing(10)->initContentsMargins(10, 0, 0, 0);
        //m_row1->append((new CPLabel(20, 20))->initImage(":/imgs/circle.png"))->append((new CPLabel(150, 20, kr("회원가입")))->initFontSize(15)->initAlignment(Qt::AlignLeft|Qt::AlignVCenter));

        m_row2 = (new CPWidget(width(), 40, new QHBoxLayout))->initAlignment(Qt::AlignLeft | Qt::AlignVCenter)->initSpacing(10);
        m_row2->append((new CPLabel(70, 40, kr("아이디")))->initAlignment(Qt::AlignRight|Qt::AlignVCenter))->append(m_edID)->append(m_btnConfirm);

        m_row3 = (new CPWidget(width(), 115, new QHBoxLayout))->initAlignment(Qt::AlignLeft | Qt::AlignTop)->initSpacing(10);
        m_lbCheckPass = (new CPLabel(200, 20, kr("")))->initAlignment(Qt::AlignRight|Qt::AlignVCenter)->initStyleSheet("color:red")->initFontSize(10);
        CPWidget* wdEdPass = (new CPWidget(200, 65, new QVBoxLayout))->initSpacing(5)->append(m_edPassRe)->append(m_lbCheckPass);

        m_row3->append((new CPLabel(70, 115, kr("비밀번호")))->initAlignment(Qt::AlignRight|Qt::AlignTop)->initContentsMargins(0, 0, 10, 0))
                ->append((new CPWidget(200, 115, new QVBoxLayout))->initSpacing(10)->append(m_edPass)->append(wdEdPass));

        m_row4 = (new CPWidget(width(), 40, new QHBoxLayout))->initAlignment(Qt::AlignLeft | Qt::AlignVCenter)->initSpacing(10);
        m_row4->append((new CPLabel(70, 40, kr("직원이름")))->initAlignment(Qt::AlignRight|Qt::AlignVCenter))->append(m_edEmp)->append(m_btnEmp);

        m_row5 = (new CPWidget(width(), 40, new QHBoxLayout))->initAlignment(Qt::AlignLeft | Qt::AlignVCenter)->initSpacing(10);
        m_row5->append((new CPLabel(70, 40, kr("부서이름")))->initAlignment(Qt::AlignRight|Qt::AlignVCenter))->append(m_edPart)->append(m_btnPart);

        m_row6 = (new CPWidget(width(), 55, new QHBoxLayout))->initAlignment(Qt::AlignRight | Qt::AlignBottom)->initSpacing(10)->initContentsMargins(0, 10, 0, 0);
        m_row6->append(m_btnClear)->append(m_btnJoin);

        layout()->addWidget(m_row1);
        layout()->addWidget(m_row2);
        layout()->addWidget(m_row3);
        layout()->addWidget(m_row4);
        layout()->addWidget(m_row5);
        layout()->addWidget(m_row6);
    }

	void notify(int index, QString tag) 
	{
		if (!tag.compare(TAG_JOIN_FIND_PART))
		{
			m_selectedPart = m->parts().at(index);
			m_edPart->setText(m_selectedPart->namePart());
		}
		else if (!tag.compare(TAG_JOIN_FIND_EMPLOYEE))
		{
			m_selectedEmployee = m->employees().at(index);
			m_edEmp->setText(m_selectedEmployee->nameUser());
		}
	};

	public slots:
	void recognizePass(const QString &str)
	{
		if (!str.compare(m_edPassRe->text()))
		{
			m_lbCheckPass->setText(kr("비밀번호가 일치합니다."));
			m_lbCheckPass->setStyleSheet("color:blue");
		}			
		else
		{
			m_lbCheckPass->setText(kr("비밀번호가 일치하지 않습니다."));
			m_lbCheckPass->setStyleSheet("color:red");
		}
	}

	void recognizePassRe(const QString &str)
	{
		if (!str.compare(m_edPass->text()))
		{
			m_lbCheckPass->setText(kr("비밀번호가 일치합니다."));
			m_lbCheckPass->setStyleSheet("color:blue");
		}
		else
		{
			m_lbCheckPass->setText(kr("비밀번호가 일치하지 않습니다."));
			m_lbCheckPass->setStyleSheet("color:red");
		}
	}

private:
	
	Part* m_selectedPart = nullptr;
	Employee* m_selectedEmployee = nullptr;

    Command* m_btnConfirm;
    Command* m_btnEmp;
    Command* m_btnPart;
    Command* m_btnClear;
    Command* m_btnJoin;

    CPWidget* m_row1;
    CPWidget* m_row2;
    CPWidget* m_row3;
    CPWidget* m_row4;
    CPWidget* m_row4_1;
    CPWidget* m_row5;
    CPWidget* m_row6;


    CPLineEdit* m_edID;
    CPLineEdit* m_edPass;
    CPLineEdit* m_edPassRe;
    CPLineEdit* m_edEmp;
    CPLineEdit* m_edPart;

    CPLabel* m_lbCheckPass;
};
