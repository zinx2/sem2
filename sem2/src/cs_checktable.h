#pragma once
#include "cs_qheader.h"
#include "cs_metatable.h"
#include "cs_component.h"
class CheckTable : public QWidget
{
	Q_OBJECT
public:
	CheckTable()
	{
		meta = new MetaTableCheck();
		connect(meta, &MetaTableCheck::wViewChanged, [=]() { 		
			setFixedSize(meta->wView(), meta->hView());			
		});
		connect(meta, &MetaTableCheck::hViewChanged, [=]() {
			setFixedSize(meta->wView(), meta->hView());
		});

		setFixedSize(meta->wView(), meta->hView());
		setLayout(new QVBoxLayout);
		layout()->setSpacing(0);
		layout()->setMargin(0);
		layout()->setAlignment(Qt::AlignLeft | Qt::AlignTop);

		CPWidget* wdPart = 
			(new CPWidget(meta->wPart, (meta->parts().size() + 2) * meta->hCell, new QVBoxLayout))
			->initAlignment(Qt::AlignLeft | Qt::AlignTop);

		wdPart->layout()->addWidget(
			(new CPLabel(meta->wPart, meta->hCell - 1, ""))
			->initAlignment(Qt::AlignCenter)->initStyleSheet("border-bottom:1px solid gray; background:white"));

		wdPart->layout()->addWidget(
			(new CPLabel(meta->wPart, meta->hCell, kr("서명인")))
			->initAlignment(Qt::AlignCenter)->initStyleSheet("border-bottom:1px solid gray; background:#eeeeee"));

		for (int i = 0; i < 10; i++)
		{
			wdPart->layout()->addWidget(
				(new CPLabel(meta->wPart, meta->hCell, meta->parts().at(i)))
				->initAlignment(Qt::AlignCenter)->initStyleSheet("border-bottom:1px solid gray; background:#eeeeee"));
		}

		CPWidget* main = (new CPWidget(meta->wTable - meta->wPart, meta->hTable, new QVBoxLayout))
			->initAlignment(Qt::AlignLeft | Qt::AlignTop);

		scrollArea = new QScrollArea(this);
		scrollArea->setWidget(
			(new CPWidget(meta->wTable, meta->hTable, new QHBoxLayout))
			->initAlignment(Qt::AlignLeft | Qt::AlignTop)
			->append(wdPart)
			->append(main));
		layout()->addWidget(scrollArea);


		CPWidget* hwd = (new CPWidget(meta->wTable - meta->wPart, meta->hCell, new QHBoxLayout))
			->initAlignment(Qt::AlignLeft | Qt::AlignTop);
		main->layout()->addWidget(hwd);

		QLabel* lbMth;
		for (int i = 0; i < 12; i++)
		{
			hwd->layout()->addWidget(
				(new CPLabel(meta->wCell * 3, meta->hCell, QString("%1").arg(i + 1) + kr("월")))
				->initAlignment(Qt::AlignCenter)->initStyleSheet("border-right:1px solid gray; border-left:1px solid gray; background:#eeeeee"));
		}

		CPWidget* wd = (new CPWidget(meta->wTable - meta->wPart, (meta->parts().size() + 1) * meta->hCell + 2, new QHBoxLayout))
			->initAlignment(Qt::AlignLeft | Qt::AlignTop);
		main->append(wd);

		for (int i = 0; i < 12; i++)
		{
			QTableWidget* table = new QTableWidget(this);
			table->setRowCount(meta->parts().size());
			table->horizontalHeader()->setStyleSheet("QHeaderView::section { background-color:#eeeeee }");
			table->setStyleSheet("QTableView {border-right:0px solid white;}");
			table->setSelectionMode(QAbstractItemView::NoSelection);
			table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
			table->verticalHeader()->hide();
			wd->layout()->addWidget(table);

			table->setFixedWidth(meta->wCell * 3);
			table->setFixedHeight((meta->parts().size() + 1) * meta->hCell + 2);
			table->setColumnCount(3);
			table->setHorizontalHeaderLabels(meta->metaSignatory);
			table->horizontalHeader()->setFixedHeight(meta->hCell);
			table->setColumnWidth(0, meta->wCell);
			table->setColumnWidth(1, meta->wCell);
			table->setColumnWidth(2, meta->wCell);
		}
	}

	void initSize(int w, int h=0) {
		meta->setWView(w);
		meta->setHView(meta->hView());
	}
private:
	QList<QTableWidget*> m_monthTables;
	QScrollArea* scrollArea;
	MetaTableCheck* meta = nullptr;
};