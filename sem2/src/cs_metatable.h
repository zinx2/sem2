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
		metaHeader << kr("333번호") << kr("자산번호") << kr("장비명")
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
