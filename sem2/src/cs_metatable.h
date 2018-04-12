#pragma once
#include "cs_qheader.h"
#include "cs_model.h"
class Meta : public QObject
{
	Q_OBJECT
		Q_PROPERTY(int width READ width WRITE setWidth NOTIFY widthChanged)
		Q_PROPERTY(int height READ height WRITE setHeight NOTIFY heightChanged)
public:
	int width() { return m_width; }
	int height() { return m_height; }

	public slots :
		void setWidth(int m) { m_width = m; }
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

	QVector<int> cols() { return m_cols; }
	void setCols(QVector<int> m) { m_cols = m; }

	int hRow() { return m_hRow; }
	void setHRow(int m) { m_hRow = m; }

private:
	int m_hNavi = 0;
	int m_hRow = 30;
	MetaHeader* m_header;
	QVector<int> m_cols;
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
		metaHeader << kr("번호") << kr("이름") << kr("관리자") << kr("관리");
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
		metaHeader << kr("번호") << kr("자산번호") << kr("장비명")
			<< kr("취득금액") << kr("취득일자") << kr("대출여부") << kr("비고");
		header()->setMeta(metaHeader);
		setHNavi(0);
	}

	const QString btnExtReleasedSheet = "text-align:left; border:0px; color: white; background-color: #143246;";
	const QString btnExtHoverdSheet = "text-align:left; border:0px; color: white; background-color: #1e5064;";
	const QString txt1 = kr("  ▼  월별대장");
	const QString txt2 = kr("  ▲  월별대장");

	const int hRow = 30;
	const int wCol1 = 50;
	const int wCol2 = 150;
	const int wCol3 = 200;
	const int wCol4 = 150;
	const int wCol5 = 150;
	const int wCol6 = 55;
	const int hExt = 25;
};

class MetaTableExtendable : public MetaTable
{
	Q_OBJECT
		//Q_PROPERTY(bool extended READ extended WRITE extend NOTIFY extendedChanged)
		//Q_PROPERTY(int wView READ wView WRITE setWView NOTIFY wViewChanged)
		//Q_PROPERTY(int hView READ hView WRITE setHView NOTIFY hViewChanged)
		//Q_PROPERTY(int hTable READ hTable WRITE setHTable NOTIFY hTableChanged)

public:
	MetaTableExtendable()
	{
		QStringList metaHeader;
		metaHeader << kr("번호") << kr("자산번호") << kr("장비명")
			<< kr("취득금액") << kr("취득일자") << kr("대출여부") << kr("비고");
		header()->setMeta(metaHeader);
		setHNavi(0);
		setCols({ 50, 150, 200, 150, 150, 55, 200 });
		setHRow(30);
	}
	//const int hExt = 25;

	//bool extended() { return m_extended; }
	//int wView() { return m_wView; }
	//int hView() { return m_hView; }
	//int hTable() { return m_hTable; }
	//QString name() { return m_name; }
	//QString btnTxt() { 
	//	QString txt = m_extended ? "  ▼  " + m_name : "  ▲  " + m_name;
	//	return txt;
	//}

	//const QString btnExtReleasedSheet = "text-align:left; border:0px; color: white; background-color: #143246;";
	//const QString btnExtHoverdSheet = "text-align:left; border:0px; color: white; background-color: #1e5064;";

	//public slots:
	//void setWView(int m) { m_wView = m; emit wViewChanged(); }
	//void setHView(int m) { m_hView = m; emit hViewChanged(); }
	//void setHTable(int m) { m_hTable = m; emit hTableChanged(); }
	//void setName(QString m) { m_name = m; }
	//void extend(bool m) { m_extended = m; emit extendedChanged(); }

//signals:
	//void wViewChanged();
	//void hViewChanged();
	//void hTableChanged();
	//void extendedChanged();

//private:
	//bool m_extended = false;
	//int m_wView = wCol1 + wCol2 + wCol3 + wCol4 + wCol5 + wCol6;
	//int m_hView = 0;
	//int m_hTable = 0;
	//QString m_name = "";
};

class MetaTableCheck : public QObject
{
	Q_OBJECT
		Q_PROPERTY(int wView READ wView WRITE setWView NOTIFY wViewChanged)
		Q_PROPERTY(int hView READ hView WRITE setHView NOTIFY hViewChanged)
		Q_PROPERTY(int wCell READ wCell WRITE setWCell NOTIFY wCellChanged)
		Q_PROPERTY(int wMonth READ wMonth WRITE setWMonth NOTIFY wMonthChanged)
		Q_PROPERTY(int wTable READ wTable WRITE setWTable NOTIFY wTableChanged)
public:
	MetaTableCheck()
	{
		Model* m = Model::instance();
		//for (int i = 0; i < 12; i++)
		//{
		//	QString mthTxt = QString("%1").arg(i + 1) + kr("월");
		//	metaMonths << mthTxt;
		//}
		metaSignatory << kr("담당자") << kr("관리자") << kr("보직자");

		foreach(Part* p, m->parts())
			m_parts.append(p->namePart());

		QString partName = m_parts.at(0);
		foreach(Sign* s, m->signatures())
		{
			if (!partName.compare(s->namePart()))
				metaMonths << QString("%1").arg(s->month()) + kr("월");
		}

		m_hView = (m_parts.size() + 2) * hCell + 24;


	}

	//const int wTable = 1180;
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
	int wTable() { return m_wTable; }

	public slots:
	void setWView(int m) { m_wView = m; emit wViewChanged(); }
	void setHView(int m) { m_hView = m; emit hViewChanged(); }
	void setWCell(int m) { m_wCell = m; emit wCellChanged(); }
	void setWMonth(int m) { m_wMonth = m; emit wMonthChanged(); }
	void setWTable(int m) { m_wTable = m; emit wTableChanged(); }

signals:
	void wViewChanged();
	void hViewChanged();
	void wCellChanged();
	void wMonthChanged();
	void wTableChanged();

private:
	QList<QString> m_parts;
	int m_wView = 980;
	int m_hView = 12 * 30 + 24;
	int m_wCell = 50;
	int m_wMonth = m_wCell * 3;
	int m_wTable = wPart + 12 * 3 * m_wCell;
};

class MetaTableMNG : public MetaTable
{
	Q_OBJECT
public:
	MetaTableMNG()
	{
		QStringList metaHeader;
		metaHeader << kr("번호") << kr("자산번호") << kr("장비명")
			<< kr("대출날짜") << kr("대출자") << kr("서명") << kr("용도")
			<< kr("반납날짜") << kr("확인자") << kr("서명") << kr("보안점검") << kr("확인");
		header()->setMeta(metaHeader);

		headerSign << kr("담당자") << kr("파트장") << kr("보직자");

		setHNavi(50);
	}
	const int hRow = 30;
	const int wCol1 = 50;
	const int wCol2 = 150;
	const int wCol3 = 200;
	const int wCol4 = 150;
	const int wCol5 = 150;
	const int wCol6 = 55;
	QStringList headerSign;

};
