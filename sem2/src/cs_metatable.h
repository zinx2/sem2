#pragma once
#include "cs_qheader.h"

class MetaTable : public QObject
{
	Q_OBJECT

public:
	int widthHeader() { return m_widthHeader; }
	int heightHeader() { return m_heightHeader; }
	int widthTable() { return m_widthTable; }
	int heightTable() { return m_heightTable; }
	int heightCell() { return m_heightCell; }
	QStringList metaHeader() { return m_metaHeader; }

	public slots :
	void setWidthHeader(int m) { m_widthHeader = m; }
	void setHeightHeader(int m) { m_heightHeader = m; }
	void setWidthTable(int m) { m_widthTable = m; }
	void setHeightTable(int m) { m_heightTable = m; }
	void setHeightCell(int m) { m_heightCell = m; }
	void setMetaHeader(QStringList m) { m_metaHeader = m; }

private:
	int m_widthHeader = 0;
	int m_heightHeader = 0;
	int m_widthTable = 0;
	int m_heightTable = 0;
	int m_heightCell = 0;

	QStringList m_metaHeader;
};

class MetaDVCTable : public QObject
{
	Q_OBJECT
public:
	const int wHeader
private:

};

