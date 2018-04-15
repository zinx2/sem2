#pragma once
#include "cs_qheader.h"
#include "cs_component.h"
#include "cs_command.h"
#include "cs_signature.h"
#include "cs_model.h"
#include "cs_networker.h"
#include "cs_style.h"
class Barcoder : public CPDialog
{
    Q_OBJECT

public:

    explicit Barcoder(QString title, int width, int height, QWidget *parent = 0) : CPDialog(title, width, height, parent)
	{
		setModal(true);
		Command* btnInit = new Command("init", kr("초기화"), 70, 30);
		btnInit->setStyleSheet("background: #e1e1e1;");

		m_palette = new Palette();
		m_btnBorrow = (new GrayCommand("btn_borrow", kr("대출하기"), 80, 40))->initEnabled(false)
		->initFunc([=]() { 	m->request(true, Notificator::OpenFromBorrow); 	});
		
		m_btnReturn = (new GrayCommand("btn_return", kr("반납하기"), 80, 40))->initEnabled(false)
		->initFunc([=]() { 	m->request(true, Notificator::OpenFromReturn); 	});
		
		m_btnCancel = (new GrayCommand("btn_cancel", kr("취소"), 80, 40))
		->initFunc([=]() { 	cancel(); });
		
		m_btnSearch = (new GrayCommand("btn_search", kr("검색"), 80, 40))
		->initFunc([=]()
		{
			QString barcode = m_edBarcode->text();
			if (barcode.size() == 0) {
				m_lbNameDevice->setText(kr("자산번호를 입력해주세요."));
				return;
			}
			if (barcode.at(barcode.size() - 1) == '\n')
			{
				QStringRef subString(&barcode, 0, barcode.size() - 1);
				m_edBarcode->setText(subString.toString());
				m_edBarcode->setAlignment(Qt::AlignHCenter);
				barcode = subString.toString();
			}

			bool validate;
			int noDevice = barcode.toInt(&validate);
			if (validate)
				NetWorker::instance()->getDeviceInfo(noDevice)->request();
			else
				m_lbNameDevice->setText(kr("유효하지 않은 자산번호입니다."));
		});

		m_zoneBarcode = (new CPWidget(width, 70, new QVBoxLayout))->initAlignment(Qt::AlignTop)->initContentsMargins(10, 0, 0, 0)->initSpacing(5)
			->append((new CPLabel(width - 20, 25, kr("장비를 인식시켜 주세요.")))->initAlignment(Qt::AlignBottom));

		m_edBarcode = (new CPLineEdit(width - 130, 40))->initAlignment(Qt::AlignCenter);

		m_wdContents->initSpacing(10);
		m_zoneBarcode->append((new CPWidget(width, 40, new QHBoxLayout))->initSpacing(10)->initAlignment(Qt::AlignLeft)->append(m_edBarcode)->append(m_btnSearch));
		m_wdContents->layout()->addWidget(m_zoneBarcode);

		m_lbNameDevice = (new CPLabel(width - 20, 80))->initAlignment(Qt::AlignTop);
		m_zoneDevice = (new CPWidget(width, 75, new QVBoxLayout))->initAlignment(Qt::AlignTop)->initContentsMargins(10, 0, 0, 0)->append(m_lbNameDevice);
		m_wdContents->layout()->addWidget(m_zoneDevice);

		//m_wdTail->layout()->addWidget(btnInit);
		m_wdTail->layout()->addWidget(m_btnBorrow);
		m_wdTail->layout()->addWidget(m_btnReturn);
		m_wdTail->layout()->addWidget(m_btnCancel);
		m_wdTail->setContentsMargins(0, 0, 30, 0);

		connect(btnInit, SIGNAL(clicked()), this, SLOT(init()));		
		//connect(edBarcode, SIGNAL(textChanged()), this, SLOT(recognize()));
		connect(this, SIGNAL(rejected()), this, SLOT(cancel()));
		connect(m, SIGNAL(modalChanged()), this, SLOT(exit()));
		//connect(m, SIGNAL(alarmedChanged()), this, SLOT(recognize()));
	}

    public slots:
    void confirm()
	{
	}

    void cancel()
	{
		close();
	}
    void init()
	{
		m_lbNameDevice->setText("");
		m_edBarcode->setText("");
		m_edBarcode->setAlignment(Qt::AlignHCenter);
	}

    void recognize()
	{
		if (m->alarmed() && m->notificator()->type() == Notificator::DVISearch)
		{
			bool result = m->notificator()->result();
			if (result)
			{
				Device* d = m->searchedDevice();
				QString aboutDevice = d->nameDevice() + "\n";
				aboutDevice += d->borrowed() ?
					kr("반납되지 않은 장비입니다. \n반납을 원히사면 '반납하기' 버튼을 눌러주세요.") :
					kr("반납된 장비입니다. \n대출을 원하시면 '대출하기' 버튼을 눌러주세요.");
				
				m_btnReturn->setEnabled(d->borrowed()); /* 대출되지 않았을 때는 반납버튼 사용불가 */					
				m_btnBorrow->setEnabled(!d->borrowed());  /* 대출되지 않았을 때만 대출버튼 사용가능 */
				m_lbNameDevice->setText(aboutDevice);
			}
			else
			{
				m_btnReturn->initEnabled(false);
				m_btnBorrow->initEnabled(false);

				m_lbNameDevice->setText(kr("검색된 장비가 없습니다."));
			}
			update();
			m->alarm(false);
		}
	}
    void exit()
	{
		close();
	}


private:
    CPWidget* m_zoneBarcode;
    CPWidget* m_zoneDevice;

    CPLineEdit* m_edBarcode;
    CPLabel* m_lbNameDevice;
	Command* m_btnBorrow;
    Command* m_btnReturn;
	Command* m_btnCancel;
	Command* m_btnSearch;

//    DialogFormDeviceReturn* m_signature;

    bool doNext = false;
    int m_recognizationFinished = true;
    int m_noDevice = -1;

	Palette* m_palette;
};
