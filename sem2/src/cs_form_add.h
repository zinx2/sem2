#pragma once
#include "cs_qheader.h"
#include "cs_component.h"
#include "cs_signature.h"
#include "cs_question.h"
#include "cs_networker.h"

class FormAdd : public CPDialog
{
	Q_OBJECT
public:
	//type 0:¥Î√‚, 1:π›≥≥
	explicit FormAdd(int width, int height, QWidget *parent = 0);

	void setData(QString noAsset);
	void notify(int row);

	public slots:
	void confirm() override;
	void cancel() override;
	void allow();
	void none();
	void activate(const QString & str = "");
	void recognize(const QString & str = "");
	void search();
	void check(int state);
	void init();

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
};
