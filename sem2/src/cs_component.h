#pragma once

#include <QTextEdit>
#include <QLabel>
#include <QWidget>
#include <QBoxLayout>
#include <QLineEdit>
#include "cs_file.h"
#include "cs_metatable.h"
#include "cs_model.h"
#include "cs_style.h"
#include "cs_command.h"
typedef std::function<void()> FUNC;
class CPTextEdit : public QTextEdit
{
	Q_OBJECT
public:
	CPTextEdit(int width, QWidget *parent = 0) : QTextEdit(parent)
	{
		setFixedSize(width, 35);
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
	CPLabel* initText(QString txt)
	{
		setText(txt);
		return this;
	}
	CPLabel* initVisible(bool visible)
	{
		setVisible(visible);
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
	CPTable(MetaTable* meta)
	{
		m_meta = meta;
		setStyleSheet("background:#2dd0d2");
		setLayout(new QVBoxLayout);
		layout()->setSpacing(0);
		layout()->setMargin(0);
		setFixedHeight(0);
	}
	CPTable* initRowCount(int itemCount)
	{
		m_itemCount = itemCount;
		return this;
	}
	CPTable* initTableWidthPercent(QList<double> meta)
	{
		m_wMeta = meta;
		return this;
	}
	CPTable* initPage()
	{		
		if (m_itemCount > 0)
		{
			layout()->setAlignment(Qt::AlignLeft | Qt::AlignTop);
			if (m_lbEmpty != nullptr)
			{
				delete m_lbEmpty;
				m_lbEmpty = nullptr;
			}
			if (m_table != nullptr)
			{
				delete m_table;
				m_table = nullptr;
			}
			m_table = new QTableWidget;
			for(int i=0; i< m_wMeta.size(); i++)
			{
				double p = m_wMeta.at(i);
				m_table->setColumnWidth(i, m_meta->width() *p);
			}
			m_table->setRowCount(m_itemCount);
			m_table->setSelectionBehavior(QAbstractItemView::SelectRows);
			m_table->setSelectionMode(QAbstractItemView::SingleSelection);
			m_table->horizontalScrollBar()->setDisabled(true);
			m_table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
			m_table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
			m_table->verticalHeader()->hide();
			m_table->setColumnCount(m_meta->cols().size());
			m_table->setHorizontalHeaderLabels(m_meta->header()->meta());
			m_table->setFixedHeight(m_meta->hRow() * m_itemCount + m_table->horizontalHeader()->height());
			layout()->addWidget(m_table);
			initHeight(m_table->height());
			//setFixedHeight(m_table->height());
		}
		else
		{
			if (m_table != nullptr)
			{
				delete m_table;
				m_table = nullptr;
			}
			if (m_lbEmpty != nullptr)
			{
				delete m_lbEmpty;
				m_lbEmpty = nullptr;
			}
			m_lbEmpty = (new CPLabel(width(), 100, kr("항목이 존재하지 않습니다.")))->initAlignment(Qt::AlignCenter);			
			layout()->addWidget(m_lbEmpty);
			int hh = m_lbEmpty->height();
			initHeight(m_lbEmpty->height());
		}
		return this;
	}
	CPTable* resize()
	{
		int idx = 0; int w = m_meta->width();
		//qDebug() << "SIZE : " << w;
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
	CPTable* initHeight(int h)
	{
		m_meta->setHeight(h);
		return this;
	}
	QTableWidget* table()
	{
		return m_table;
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
	CPLabel* m_lbEmpty = nullptr;
	int m_itemCount = 0;
	bool m_visible = false;
	QList<double> m_wMeta;
};

class  CPDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CPDialog(QString title, int w, int h, QWidget *parent=0) : QDialog(parent)
    {
		m = Model::instance();
        Qt::WindowFlags flags = windowFlags();
        Qt::WindowFlags helpFlag = Qt::WindowContextHelpButtonHint;
        flags = flags & (~helpFlag);

        setWindowTitle(title);
        setWindowFlags(flags);
        setFixedSize(w, h);
        setLayout(new QVBoxLayout);

        m_wdContents = (new CPWidget(w, h-40, new QVBoxLayout))->initAlignment(Qt::AlignTop);
        layout()->addWidget(m_wdContents);

        m_wdTail = (new CPWidget(w, 60, new QHBoxLayout))->initSpacing(10)->initContentsMargins(0,10,0,0)
                    ->initAlignment(Qt::AlignVCenter|Qt::AlignRight);
        layout()->addWidget(m_wdTail);
    }

    explicit CPDialog(int w, int h, QWidget *parent=0) : QDialog(parent)
    {
		m = Model::instance();
        Qt::WindowFlags flags = windowFlags();
        Qt::WindowFlags helpFlag = Qt::WindowContextHelpButtonHint;
        flags = flags & (~helpFlag);

        setFixedSize(w, h);
    }

    virtual void notify(int index, QString tag="") {};

public slots:
    virtual void confirm() {};
    virtual void cancel() {};

signals:
    void yes();
    void no();

protected:
    CPWidget* m_wdContents = nullptr;
    CPWidget* m_wdTail = nullptr;
	Model* m; 
};

class CPBoxSign : public CPWidget
{
	Q_OBJECT
public:
	CPBoxSign(int width, int height, QLayout* ly, QWidget *parent = 0) : CPWidget(width, height, ly, parent)
	{
		initStyleSheet("border: 1px solid black;");
		initAlignment(Qt::AlignRight | Qt::AlignVCenter);

		m_lbSign1 = (new CPLabel(60, 30, kr("O")))->initStyleSheet("background:white; border:1px solid black")->initAlignment(Qt::AlignCenter);
		m_lbSign2 = (new CPLabel(60, 30, kr("O")))->initStyleSheet("background:white; border:1px solid black")->initAlignment(Qt::AlignCenter);
		m_lbSign3 = (new CPLabel(60, 30, kr("O")))->initStyleSheet("background:white; border:1px solid black")->initAlignment(Qt::AlignCenter);
		append((new CPLabel(60, 30, kr("서명 :   ")))->initAlignment(Qt::AlignRight | Qt::AlignVCenter)->initStyleSheet("border: 0px solid black;"));
		append((new CPWidget(60, 60, new QVBoxLayout))->append((new CPLabel(60, 20, kr("담당자")))->initAlignment(Qt::AlignCenter))->append(m_lbSign1));
		append((new CPWidget(60, 60, new QVBoxLayout))->append((new CPLabel(60, 20, kr("관리자")))->initAlignment(Qt::AlignCenter))->append(m_lbSign2));
		append((new CPWidget(60, 60, new QVBoxLayout))->append((new CPLabel(60, 20, kr("보직자")))->initAlignment(Qt::AlignCenter))->append(m_lbSign3));
		append(new CPWidget(10, 1, new QHBoxLayout));

		Button* metaBtn = Style::instance()->main()->body()->content()->btnSign();
		Command* m_btnSign =
			(new Command("sign", kr(""), metaBtn->width(), metaBtn->height()))
			->initStyleSheet(metaBtn->releasedStyle())
			->initEffect(metaBtn->releasedStyle(), metaBtn->selectedStyle(), metaBtn->hoveredStyle())
			->initIcon(metaBtn->icon())
			->initFunc([=]() {});
		append(m_btnSign);
	}

	CPBoxSign* initState(QString s1, QString s2, QString s3)
	{
		m_lbSign1->initText(s1);
		m_lbSign2->initText(s2);
		m_lbSign3->initText(s3);
		return this;
	}
	CPBoxSign* initFunc(FUNC func)
	{
		m_btnSign->initFunc(func);
		return this;
	}

private:
	CPLabel* m_lbSign1;
	CPLabel* m_lbSign2;
	CPLabel* m_lbSign3;
	Command* m_btnSign;
};

//class CPMNTTable : public QWidget
//{
//	Q_OBJECT
//public:
//	CPMNTTable(int width, int height= 0, QWidget* parent = 0) : QWidget(parent)
//	{
//		setLayout(new QVBoxLayout);
//		layout()->setSpacing(0);
//		layout()->setMargin(0);
//		setFixedSize(width, height);
//		initialize();
//		connect(this, SIGNAL(modelChanged()), this, SLOT(updateModel()));
//	}
//	CPMNTTable* setModel(QList<Rent*> m)
//	{
//		m_model.clear();
//		m_model = m;
//		emit modelChanged();
//		return this;
//	}
//	//CPMNTTable* initVisible(bool visibvle)
//	//{
//	//	if (m_boxSign != nullptr)
//	//		m_boxSign->initWidth(visibvle ? width() - 25 : 0);
//
//	//	m_table
//	//	m_lbEmpty
//	//	return this;
//	//}
//	CPMNTTable* invoke()
//	{
//
//		return this;
//	}
//	CPMNTTable* updateBoxSign(QString sign1, QString sign2, QString sign3)
//	{
//		m_boxSign->initState(sign1, sign2, sign3);
//		return this;
//	}
//	CPMNTTable* resize(int w, int h)
//	{
//		setFixedSize(w, h);
//		m_boxSign->initWidth(w - 25);
//		m_table->setFixedSize(w, m_table->height());
//		m_lbEmpty->setFixedSize(w, 100);
//		return this;
//	}
//	public slots:
//	void updateModel()
//	{
//		initialize();
//		if (m_model.size() == 0)
//		{
//			clearBoxSign();
//			clearTable();
//		}
//		else
//		{
//			clearLbEmpty();
//		}
//
//		m_table = new QTableWidget(this);
//		m_table->setRowCount(m_model.size());
//		m_table->setSelectionBehavior(QAbstractItemView::SelectRows);
//		m_table->setSelectionMode(QAbstractItemView::SingleSelection);
//		m_table->horizontalScrollBar()->setDisabled(true);
//		m_table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//		m_table->horizontalHeader()->setStyleSheet("QHeaderView::section { background-color:#eeeeee }");
//		m_table->verticalHeader()->hide();
//
//		
//		//m_table->setFixedSize(width(), height());
//		
//		QStringList fff; fff << "AA";
//		m_table->setHorizontalHeaderLabels(fff);
//		m_table->setColumnCount(1);
//		m_table->setColumnWidth(0, 50);
//		for (int row = 0; row < m_model.size(); row++)
//		{
//			Rent* r = m_model.at(row);
//			QTableWidgetItem* item0 = new QTableWidgetItem(QString("%1").arg(r->noAsset()));
//			item0->setTextAlignment(Qt::AlignCenter);
//			m_table->setItem(row, 0, item0);
//		}
//
//		m_table->setFixedHeight(m_table->horizontalHeader()->height() + m_cellHeight*m_model.size());
//		qDebug() << m_table->width() << "/" << m_table->height();
//		setFixedSize(m_table->width(), m_table->height());
//	}
//signals:
//	void modelChanged();
//private:
//	CPBoxSign* m_boxSign = nullptr;
//	void newBoxSign()
//	{
//		m_boxSign = new CPBoxSign(width() - 25, 0, new QHBoxLayout);
//	}
//	void clearBoxSign()
//	{
//		if (m_boxSign != nullptr)
//		{
//			delete m_boxSign;
//			m_boxSign = nullptr;
//		}
//	}
//
//	QTableWidget* m_table = nullptr;
//	void newTable()
//	{
//		m_table = new QTableWidget;
//	}
//	void clearTable()
//	{
//		if (m_table != nullptr)
//		{
//			delete m_table;
//			m_table = nullptr;
//		}
//	}
//
//	CPLabel* m_lbEmpty = nullptr;
//	void newLbEmpty()
//	{
//		m_lbEmpty = (new CPLabel(width(), 100, kr("항목이 없습니다.")));
//	}
//	void clearLbEmpty()
//	{
//		if (m_lbEmpty != nullptr)
//		{
//			delete m_lbEmpty;
//			m_lbEmpty = nullptr;
//		}
//	}
//
//	QList<Rent*> m_model;
//	int m_cellHeight = 30;
//
//	void initialize()
//	{
//		clear();
//		newBoxSign();
//		newTable();
//		newLbEmpty();
//		
//		layout()->addWidget(m_boxSign);
//		layout()->addWidget(m_lbEmpty);
//		layout()->addWidget(m_table);
//	}
//	void clear()
//	{
//		clearBoxSign();
//		clearTable();
//		clearLbEmpty();
//	}
//};