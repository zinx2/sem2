#pragma once
#include "cs_qheader.h"
#include "cs_component.h"
#include "cs_command.h"
#include "cs_style.h"
class CPJoin : public QWidget
{
    Q_OBJECT
public:
    CPJoin(QWidget* parent = 0) : QWidget(parent)
    {
        setFixedSize(400, 435);
        setLayout(new QVBoxLayout);
        layout()->setMargin(0);
        layout()->setSpacing(10);
        layout()->setAlignment(Qt::AlignLeft | Qt::AlignTop);

        Palette* p = new Palette();
        m_btnConfirm = (new Command("id_confirm", kr("중복확인"), 100, 40))->initFontSize(15)->initStyleSheet(p->btnReleasedStyleNavy)
				->initEffect(p->btnReleasedStyleNavy, p->btnSelectedStyleNavy, p->btnHoveredStyleNavy)->initFontSize(12)->initFunc([=]() 
				{
				});
        m_btnEmp = (new Command("search_employee", kr("직원찾기"), 100, 40))->initFontSize(15)->initStyleSheet(p->btnReleasedStyleNavy)
                ->initEffect(p->btnReleasedStyleNavy, p->btnSelectedStyleNavy, p->btnHoveredStyleNavy)->initFontSize(12)->initFunc([=]() 
				{
				});
        m_btnPart = (new Command("search_part", kr("부서찾기"), 100, 40))->initFontSize(15)->initStyleSheet(p->btnReleasedStyleNavy)
                ->initEffect(p->btnReleasedStyleNavy, p->btnSelectedStyleNavy, p->btnHoveredStyleNavy)->initFontSize(12)->initFunc([=]() 
				{
				});
        m_btnClear = (new Command("edit_clear", kr("초기화"), 100, 40))->initFontSize(15)->initStyleSheet(p->btnReleasedStyleNavy)
                ->initEffect(p->btnReleasedStyleNavy, p->btnSelectedStyleNavy, p->btnHoveredStyleNavy)->initFontSize(12)->initFunc([=]() 
				{
				});
        m_btnJoin = (new Command("edit_finish", kr("완료하기"), 100, 40))->initFontSize(15)->initStyleSheet(p->btnReleasedStyleNavy)
                ->initEffect(p->btnReleasedStyleNavy, p->btnSelectedStyleNavy, p->btnHoveredStyleNavy)->initFontSize(12)->initFunc([=]() 
				{
				});

        m_edID = (new CPLineEdit(200, 40))->initAlignment(Qt::AlignCenter);
        m_edID->setPlaceholderText(kr("아이디를 입력하세요."));
        m_edPass = (new CPLineEdit(200, 40))->initAlignment(Qt::AlignCenter);
        m_edPass->setPlaceholderText(kr("비밀번호를 입력하세요."));
        m_edPassRe = (new CPLineEdit(200, 40))->initAlignment(Qt::AlignCenter);
        m_edPassRe->setPlaceholderText(kr("비밀번호를 다시 입력하세요."));
        m_edEmp = (new CPLineEdit(200, 40))->initAlignment(Qt::AlignCenter);
        m_edEmp->setPlaceholderText(kr("직원을 입력하세요."));
        m_edPart = (new CPLineEdit(200, 40))->initAlignment(Qt::AlignCenter);
        m_edPart->setPlaceholderText(kr("부서를 입력하세요."));

        m_row1 = (new CPWidget(width(), 40, new QHBoxLayout))->initAlignment(Qt::AlignLeft | Qt::AlignVCenter)->initSpacing(10)->initContentsMargins(10, 0, 0, 0);
        m_row1->append((new CPLabel(20, 20))->initImage(":/imgs/circle.png"))->append((new CPLabel(150, 20, kr("회원가입")))->initFontSize(15)->initAlignment(Qt::AlignLeft|Qt::AlignVCenter));

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

        m_row6 = (new CPWidget(width(), 85, new QHBoxLayout))->initAlignment(Qt::AlignRight | Qt::AlignBottom)->initSpacing(10)->initContentsMargins(0, 10, 0, 0);
        m_row6->append(m_btnClear)->append(m_btnJoin);

        layout()->addWidget(m_row1);
        layout()->addWidget(m_row2);
        layout()->addWidget(m_row3);
        layout()->addWidget(m_row4);
        layout()->addWidget(m_row5);
        layout()->addWidget(m_row6);
    }

private:
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
