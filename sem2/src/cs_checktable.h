#pragma once
#include "cs_qheader.h"

class CheckTable : public QWidget
{
	Q_OBJECT
public:
	CheckTable()
	{
		setFixedSize(500, 12 * 30 + 24);
		setLayout(new QVBoxLayout);
		layout()->setSpacing(0);
		layout()->setMargin(0);
		layout()->setAlignment(Qt::AlignLeft | Qt::AlignTop);

		QWidget* main = new QWidget(this);
		main->setFixedSize(1080, 12 * 30 + 4);
		main->setLayout(new QVBoxLayout);
		main->layout()->setSpacing(0);
		main->layout()->setMargin(0);
		main->layout()->setAlignment(Qt::AlignLeft | Qt::AlignTop);
		scrollArea = new QScrollArea(this);
		scrollArea->setWidget(main);
		layout()->addWidget(scrollArea);

		QWidget* hwd = new QWidget(this);
		hwd->setFixedSize(1080, 30);
		hwd->setLayout(new QHBoxLayout);
		hwd->layout()->setSpacing(0);
		hwd->layout()->setMargin(0);
		hwd->layout()->setAlignment(Qt::AlignLeft | Qt::AlignTop);
		hwd->setStyleSheet("background:yellow");
		main->layout()->addWidget(hwd);

		for (int i = 0; i < 12; i++)
		{
			QString mthTxt = QString("%1").arg(i + 1) + kr("¿ù");
			QLabel* lbMth = new QLabel(mthTxt);
			lbMth->setFixedSize(90, 30);
			lbMth->setAlignment(Qt::AlignCenter);
			//lbMth->layout()->setAlignment(Qt::AlignCenter);
			lbMth->setStyleSheet("border:1px solid gray; background:#eeeeee");
			hwd->layout()->addWidget(lbMth);
		}

		QWidget* wd = new QWidget(this);
		wd->setFixedSize(1080, 11 * 30 + 2);
		wd->setLayout(new QHBoxLayout);
		wd->layout()->setSpacing(0);
		wd->layout()->setMargin(0);
		wd->layout()->setAlignment(Qt::AlignLeft | Qt::AlignTop);
		main->layout()->addWidget(wd);

		for (int i = 0; i < 12; i++)
		{
			QTableWidget* table = new QTableWidget(this);
			table->setRowCount(10);
			//m_monthTable->setSelectionBehavior(QAbstractItemView::SelectRows);
			table->horizontalHeader()->setStyleSheet("QHeaderView::section { background-color:#eeeeee }");
			table->setStyleSheet("background:orange;");
			table->setSelectionMode(QAbstractItemView::NoSelection);
			table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
			table->verticalHeader()->hide();
			wd->layout()->addWidget(table);

			table->setFixedWidth(90);
			table->setFixedHeight(11 * 30 + 2);
			table->setColumnCount(3);
			QStringList head; head << "A" << "B" << "C";
			table->setHorizontalHeaderLabels(head);
			table->horizontalHeader()->setFixedHeight(30);
			table->setColumnWidth(0, 30);
			table->setColumnWidth(1, 30);
			table->setColumnWidth(2, 30);
		}
	}
private:
	QList<QTableWidget*> m_monthTables;
	QScrollArea* scrollArea;
};