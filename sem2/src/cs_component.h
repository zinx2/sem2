#pragma once

#include <QTextEdit>
#include <QLabel>
#include <QWidget>
#include <QBoxLayout>
#include <QLineEdit>
#include "cs_file.h"
#include "cs_metatable.h"

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
    CPLineEdit(int width, int height=25, QWidget *parent = 0) : QLineEdit(parent)
	{
        setFixedSize(width, height);
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
	CPLabel(int width, int height, QString txt="", QWidget *parent = 0) : QLabel(txt, parent)
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
	CPLabel* initImage(QString path)
	{
		setPixmap(QPixmap(path));
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

class CPTable : public QWidget
{
	Q_OBJECT
public:
	CPTable(MetaTable* meta, int itemCount)
	{
		m_meta = meta;
		m_itemCount = itemCount;
		setStyleSheet("background:#2dd0d2");
		setLayout(new QVBoxLayout);
		layout()->setSpacing(0);
		layout()->setMargin(0);
		layout()->setAlignment(Qt::AlignLeft | Qt::AlignTop);

		m_table = new QTableWidget(this);
		m_table->setRowCount(m_itemCount);
		m_table->setSelectionBehavior(QAbstractItemView::SelectRows);
		m_table->setSelectionMode(QAbstractItemView::SingleSelection);
		m_table->horizontalScrollBar()->setDisabled(true);
		m_table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		m_table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		m_table->verticalHeader()->hide();
		m_table->setColumnCount(m_meta->cols().size());

		m_table->setHorizontalHeaderLabels(m_meta->header()->meta());
	}
	CPTable* resize()
	{
		int idx = 0; int w = m_meta->width();
		qDebug() << "SIZE : " << w;
		while (idx < m_meta->cols().size()-1)
		{
			m_table->setColumnWidth(idx, m_meta->cols()[idx]);
			w = w - m_meta->cols()[idx++];
		}
		m_table->setColumnWidth(idx, w);	

		if (m_visible)
		{
			m_table->setFixedSize(m_meta->width(), m_meta->header()->height() + m_meta->hRow() * m_itemCount);
			setFixedSize(m_meta->width(), m_meta->header()->height() + m_meta->hRow() * m_itemCount);
		}
		else
		{
			m_table->setFixedSize(0, 0);
			setFixedSize(0, 0);
		}
		return this;
	}
	CPTable* initVible(bool visible)
	{
		m_visible = visible;
		return this;
	}
	CPTable* initWidth(int w)
	{
		m_meta->setWidth(w);
		return this;
	}
	int metaHeight()
	{
		return m_meta->height();
	}

	MetaTable* meta() { return m_meta; }

private:
	MetaTable* m_meta = nullptr;
	//CPWidget* m_main = nullptr;
	QTableWidget* m_table = nullptr;
	int m_itemCount = 0;
	bool m_visible = false;
};

class CPDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CPDialog(QString title, int w, int h, QWidget *parent=0) : QDialog(parent)
    {
        Qt::WindowFlags flags = windowFlags();
        Qt::WindowFlags helpFlag = Qt::WindowContextHelpButtonHint;
        flags = flags & (~helpFlag);

        setWindowTitle(title);
        setWindowFlags(flags);
        setFixedSize(w, h);
        setStyleSheet("background: orange");
        setLayout(new QVBoxLayout);

        m_wdContents = (new CPWidget(w, h-40, new QVBoxLayout))->initAlignment(Qt::AlignTop);
        layout()->addWidget(m_wdContents);

        m_wdTail = (new CPWidget(w, 50, new QHBoxLayout))->initSpacing(10)->initContentsMargins(0,0,10,0)
                    ->initAlignment(Qt::AlignVCenter|Qt::AlignRight);
        layout()->addWidget(m_wdTail);
    }

    explicit CPDialog(int w, int h, QWidget *parent=0) : QDialog(parent)
    {
        Qt::WindowFlags flags = windowFlags();
        Qt::WindowFlags helpFlag = Qt::WindowContextHelpButtonHint;
        flags = flags & (~helpFlag);

        setFixedSize(w, h);
    }

    virtual void notify(int index) {};

public slots:
    virtual void confirm() {};
    virtual void cancel() {};

signals:
    void yes();
    void no();

protected:
    CPWidget* m_wdContents = nullptr;
    CPWidget* m_wdTail = nullptr;
};
