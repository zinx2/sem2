#pragma once

#include <QTextEdit>
#include <QLabel>
#include <QWidget>
#include <QBoxLayout>
#include <QLineEdit>
#include "cs_file.h"
class CPTextEdit : public QTextEdit
{
	Q_OBJECT
public:
	CPTextEdit(int width, QWidget *parent = 0) : QTextEdit(parent)
	{
		setFixedSize(width, 25);
		setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		setStyleSheet("background:white;");
		QFont f = font();
		f.setPointSize(10);
		setFont(f);
	}
	CPTextEdit* initAlignment(Qt::Alignment alignment) { setAlignment(alignment); return this; }
	CPTextEdit* initHeight(int height) { setFixedHeight(height); return this; }
	CPTextEdit* initReadOnly(bool readOnley) { setReadOnly(readOnley); return this; }
	CPTextEdit* initText(QString txt) { setText(txt); return this; }
	CPTextEdit* initFontSize(int pt) {
		QFont font = this->font();
		font.setPointSize(pt);
		this->setFont(font);
		return this;
	}
};
class CPLineEdit : public QLineEdit
{
	Q_OBJECT
public:
	CPLineEdit(int width, QWidget *parent = 0) : QLineEdit(parent)
	{
		setFixedSize(width, 25);
		setStyleSheet("background:white;");
		QFont f = font();
		f.setPointSize(10);
		setFont(f);
	}
	CPLineEdit* initAlignment(Qt::Alignment alignment) { setAlignment(alignment); return this; }
	CPLineEdit* initHeight(int height) { setFixedHeight(height); return this; }
	CPLineEdit* initReadOnly(bool readOnley) { setReadOnly(readOnley); return this; }
	CPLineEdit* initText(QString txt) { setText(txt); return this; }
	CPLineEdit* initFontSize(int pt) {
		QFont font = this->font();
		font.setPointSize(pt);
		this->setFont(font);
		return this;
	}
};
class CPLabel : public QLabel
{
	Q_OBJECT
public:
	CPLabel(int width, int height, QString txt, QWidget *parent = 0) : QLabel(txt, parent)
	{
		setFixedSize(width, height);
		setAlignment(Qt::AlignVCenter | Qt::AlignRight);
		initFontType("NanumBarunGothic");
		//setStyleSheet("background:white;");
		//QFont f = font();
		//f.setPointSize(10);
		//setFont(f);
	}
	CPLabel* initAlignment(Qt::Alignment alignment) { setAlignment(alignment); return this; }
	CPLabel* initContentsMargins(int left, int right, int top, int bottom)
	{
		setContentsMargins(left, top, right, bottom);
		return this;
	}
	CPLabel* initFontSize(int pt) {
		QFont font = this->font();
		font.setPointSize(pt);
		this->setFont(font);
		return this;
	}
	CPLabel* initFontBold() {
		QFont font = this->font();
		font.setBold(true);
		this->setFont(font);
		return this;
	}
	CPLabel* initFontType(QString name) {
		QFont oldFont = this->font();		
		this->setFont(QFont(name, oldFont.pointSize(), oldFont.weight()));
		return this;
	}
	CPLabel* initStyleSheet(QString sheet)
	{
		setStyleSheet(sheet);
		return this;
	}
};

class CPWidget : public QWidget
{
	Q_OBJECT
public:
	CPWidget(int width, int height, QLayout* ly, QWidget *parent = 0) : QWidget(parent)
	{
		setFixedSize(width, height);
		setLayout(ly);
		//layout()->setAlignment(Qt::AlignVCenter);
		layout()->setSpacing(0);
		layout()->setMargin(0);
	}
	CPWidget* initContentsMargins(int left, int right, int top, int bottom)
	{
		setContentsMargins(left, top, right, bottom);
		return this;
	}
	CPWidget* initStyleSheet(QString sheet)
	{
		setStyleSheet(sheet);
		return this;
	}
	CPWidget* initAlignment(Qt::Alignment alignment)
	{
		layout()->setAlignment(alignment);
		return this;
	}
	CPWidget* initEnabled(bool enabled)
	{
		setEnabled(enabled);
		return this;
	}
	CPWidget* initSpacing(int space)
	{
		layout()->setSpacing(space);
		return this;
	}
	CPWidget* initWidth(int width)
	{
		setFixedWidth(width);
		return this;
	}
	CPWidget* append(QWidget* w)
	{
		layout()->addWidget(w);
		return this;
	}

};
class CPLazyImage : public QLabel
{
	Q_OBJECT
public:
	CPLazyImage(QString url, int width)
	{
		QUrl imgUrl(url); m_width = width;
		fd = new FileDownloader(imgUrl);
		connect(fd, SIGNAL(downloaded()), this, SLOT(loadImage()));
	}

signals:
	public slots :
		void loadImage()
	{
		m_pixmap.loadFromData(fd->downloadedData());
		if (!m_pixmap.isNull())
			m_pixmap = m_pixmap.scaled(m_width, m_width, Qt::KeepAspectRatio);
		setPixmap(m_pixmap);
	}
private:
	FileDownloader* fd;
	QPixmap m_pixmap;
	int m_width;
};
class CPPixmap : public QObject
{
	Q_OBJECT

public:
	CPPixmap(QString url)
	{
		QUrl imgUrl(url);
		fd = new FileDownloader(imgUrl);
		connect(fd, SIGNAL(downloaded()), this, SLOT(loadImage()));
	}
	QPixmap* source() { return m_pixmap; }
signals:
	public slots :
		void loadImage()
	{
		m_pixmap->loadFromData(fd->downloadedData());
	}

private:
	FileDownloader* fd;
	QPixmap* m_pixmap;
};

class CPHorizontalGrid : public QWidget
{
	Q_OBJECT
public:
	CPHorizontalGrid(int width, int height, QWidget *parent = 0) : QWidget(parent)
	{
		setFixedSize(width, height);
		setLayout(new QHBoxLayout);
		layout()->setAlignment(Qt::AlignHCenter);
		layout()->setSpacing(10);
		layout()->setMargin(10);
	}
	CPHorizontalGrid* initContentsMargins(int left, int right, int top, int bottom)
	{
		setContentsMargins(left, top, right, bottom);
		return this;
	}
};