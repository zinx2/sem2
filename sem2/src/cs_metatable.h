#pragma once
#include "cs_qheader.h"

class Meta : public QObject
{
	Q_OBJECT
		Q_PROPERTY(int width READ width WRITE setWidth NOTIFY widthChanged)
		Q_PROPERTY(int height READ height WRITE setHeight NOTIFY heightChanged)
public:
	int width() { return m_width; }
	int height() { return m_height; }

	public slots :
	void setWidth(int m) { m_width= m; }
	void setHeight(int m) { m_height = m; }

signals:
	void widthChanged();
	void heightChanged();

private:
	int m_width = 0;
	int m_height = 0;
};

class MetaHeader : public Meta
{
	Q_OBJECT
public:
	QStringList meta() { return m_metaHeader; }

	public slots :
	void setMeta(QStringList m) { m_metaHeader = m; }
	int countCols() { return m_metaHeader.size(); }

private:
	QStringList m_metaHeader;
};

class MetaTable : public Meta
{
	Q_OBJECT
public:
	MetaTable()
	{
		m_header = new MetaHeader();
		m_header->setHeight(30);
		connect(this, &MetaTable::widthChanged, [=]() { m_header->setWidth(width()); });
	}
	MetaHeader* header() { return m_header; }
	int hNavi() { return m_hNavi; }
	void setHNavi(int m) { m_hNavi = m; }
private:
	int m_hNavi = 0;
	MetaHeader* m_header;
};
class MetaTableDVC : public MetaTable
{
	Q_OBJECT
public:
	MetaTableDVC()
	{
		QStringList metaHeader; 
		metaHeader << kr("번호") << kr("자산번호") << kr("장비명")
			<< kr("취득금액") << kr("취득일자") << kr("대출여부") << kr("비고");
		header()->setMeta(metaHeader);
		setHNavi(50);
	}
	const int hRow = 30;
	const int wCol1 = 50;
	const int wCol2 = 150;
	const int wCol3 = 200;
	const int wCol4 = 150;
	const int wCol5 = 150;
	const int wCol6 = 55;
};

class MetaTableEMP : public MetaTable
{
	Q_OBJECT
public:
	MetaTableEMP()
	{
		QStringList metaHeader;
		metaHeader << kr("111번호") << kr("자산번호") << kr("장비명")
			<< kr("취득금액") << kr("취득일자") << kr("대출여부") << kr("비고");
		header()->setMeta(metaHeader);
		setHNavi(0);
	}
	const int hRow = 30;
	const int wCol1 = 50;
	const int wCol2 = 150;
	const int wCol3 = 200;
	const int wCol4 = 150;
	const int wCol5 = 150;
	const int wCol6 = 55;
};

class MetaTableMNT : public MetaTable
{
	Q_OBJECT
public:
	MetaTableMNT()
	{
		QStringList metaHeader;
		//metaHeader << kr("333번호") << kr("자산번호") << kr("장비명")
		//	<< kr("취득금액") << kr("취득일자") << kr("대출여부") << kr("비고");
		for (int i = 0; i < 12; i++)
		{
			metaHeader << kr("담당자") << kr("관리자") << kr("보직자");
		}
		header()->setMeta(metaHeader);
		setHNavi(0);
	}
	const int hRow = 30;
	const int wCol = 40;
};

class MetaTableCheck : public QObject
{
	Q_OBJECT
		Q_PROPERTY(int wView READ wView WRITE setWView NOTIFY wViewChanged)
		Q_PROPERTY(int hView READ hView WRITE setHView NOTIFY hViewChanged)
		Q_PROPERTY(int wCell READ wCell WRITE setWCell NOTIFY wCellChanged)
		Q_PROPERTY(int wMonth READ wMonth WRITE setWMonth NOTIFY wMonthChanged)
public:
	MetaTableCheck()
	{
		for (int i = 0; i < 12; i++)
		{
			QString mthTxt = QString("%1").arg(i + 1) + kr("월");
			metaMonths << mthTxt;
		}
		metaSignatory << kr("담") << kr("관") << kr("보");
		m_parts.append(kr("A파트")); m_parts.append(kr("B파트")); m_parts.append(kr("C파트"));
		m_parts.append(kr("D파트")); m_parts.append(kr("E파트")); m_parts.append(kr("F파트"));
		m_parts.append(kr("G파트")); m_parts.append(kr("H파트")); m_parts.append(kr("I파트"));
		m_parts.append(kr("J파트"));
	}

	const int wTable = 1180;
	const int hTable = 12 * 30 + 4;
	const int wPart = 100;
	//const int wMonth = 90;
	const int wSignatory = 30;
	const int hCol = 290;
	//const int wCell = 30;
	const int hCell = 30;

	QList<QString> metaMonths;
	QList<QString> metaSignatory;
	QList<QString> parts() { return m_parts; }
	void setParts(QList<QString> m) 
	{
		m_parts.clear();
		m_parts = m;
	}

	int wView() { return m_wView; }
	int hView() { return m_hView; }
	int wCell() { return m_wCell; }
	int wMonth() { return m_wMonth; }

	public slots:
	void setWView(int m) { m_wView = m; emit wViewChanged(); }
	void setHView(int m) { m_hView = m; emit hViewChanged(); }
	void setWCell(int m) { m_wCell = m; emit wCellChanged(); }
	void setWMonth(int m) { m_wMonth = m; emit wMonthChanged(); }

signals:
	void wViewChanged();
	void hViewChanged();
	void wCellChanged();

private:
	QList<QString> m_parts;
	int m_wView = 980;
	int m_hView = 12 * 30 + 24;
	int m_wCell = 30;
	int m_wMonth = m_wCell*3;
};

class MetaTableMNG : public MetaTable
{
	Q_OBJECT
public:
	MetaTableMNG()
	{
		QStringList metaHeader;
		metaHeader << kr("222번호") << kr("자산번호") << kr("장비명")
			<< kr("취득금액") << kr("취득일자") << kr("대출여부") << kr("비고");
		header()->setMeta(metaHeader);
		setHNavi(50);
	}
	const int hRow = 30;
	const int wCol1 = 50;
	const int wCol2 = 150;
	const int wCol3 = 200;
	const int wCol4 = 150;
	const int wCol5 = 150;
	const int wCol6 = 55;
};
