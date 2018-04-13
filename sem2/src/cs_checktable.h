#pragma once
#include "cs_qheader.h"
#include "cs_metatable.h"
#include "cs_component.h"
#include "cs_model.h"
class CheckTable : public QWidget
{
	Q_OBJECT
public:
	CheckTable()
	{
		m = Model::instance();
		m_meta = new MetaTableCheck();
		connect(m_meta, &MetaTableCheck::wViewChanged, [=]() {
			setFixedSize(m_meta->wView(), m_meta->hView());
		});
		connect(m_meta, &MetaTableCheck::hViewChanged, [=]() {
			setFixedSize(m_meta->wView(), m_meta->hView());
		});		

		setFixedSize(m_meta->wView(), m_meta->hView());
		setLayout(new QVBoxLayout);
		layout()->setSpacing(0);
		layout()->setMargin(0);
		layout()->setAlignment(Qt::AlignLeft | Qt::AlignTop);


	}
	void updateTable() {
		m_meta->newMetaMonth();	

		if (m_wdTdCollection != nullptr)
		{
			delete m_wdTdCollection;
			m_wdTdCollection = nullptr;
		}

		if (m_wdMnt != nullptr)
		{
			delete m_wdMnt;
			m_wdMnt = nullptr;
		}

		if (m_wdPart != nullptr)
		{
			delete m_wdPart;
			m_wdPart = nullptr;
		}

		if (m_main != nullptr)
		{
			delete m_main;
			m_main = nullptr;
		}

		if (m_scrollArea != nullptr)
		{
			delete m_scrollArea;
			m_scrollArea = nullptr;
		}

		m_wdPart =
			(new CPWidget(m_meta->wPart, m_meta->hView(), new QVBoxLayout))
			->initAlignment(Qt::AlignLeft | Qt::AlignTop);

		m_wdPart->layout()->addWidget(
			(new CPLabel(m_meta->wPart, m_meta->hCell + 1, ""))
			->initAlignment(Qt::AlignCenter)->initStyleSheet("border-bottom:1px solid gray; background:white"));

		m_wdPart->layout()->addWidget(
			(new CPLabel(m_meta->wPart, m_meta->hCell, kr("서명인")))
			->initAlignment(Qt::AlignCenter)->initStyleSheet("border-bottom:1px solid gray; background:#eeeeee"));

		for (int i = 0; i < m->parts().size(); i++)
		{
			m_wdPart->layout()->addWidget(
				(new CPLabel(m_meta->wPart, m_meta->hCell, m_meta->parts().at(i)))
				->initAlignment(Qt::AlignCenter)->initStyleSheet("border-bottom:1px solid gray; background:#eeeeee"));
		}

		m_main = (new CPWidget(m_meta->wTable() - m_meta->wPart, m_meta->hView(), new QVBoxLayout))
			->initAlignment(Qt::AlignLeft | Qt::AlignTop);

		m_scrollArea = new QScrollArea(this);
		m_scrollArea->verticalScrollBar()->setDisabled(false);
		m_scrollArea->verticalScrollBar()->setVisible(false);
		m_scrollArea->setWidget(
			(new CPWidget(m_meta->wTable(), m_meta->hView(), new QHBoxLayout))
			->initAlignment(Qt::AlignLeft | Qt::AlignTop)
			->append(m_wdPart)
			->append(m_main));
		layout()->addWidget(m_scrollArea);

		m_wdMnt = (new CPWidget(m_meta->wTable() - m_meta->wPart, m_meta->hCell, new QHBoxLayout))
			->initAlignment(Qt::AlignLeft | Qt::AlignTop);
		m_main->layout()->addWidget(m_wdMnt);

		QLabel* lbMth;
		for (int i = 0; i < m_meta->metaMonths.size(); i++)
		{
			m_wdMnt->layout()->addWidget(
				(new CPLabel(m_meta->wCell() * 3, m_meta->hCell, m_meta->metaMonths.at(i) + kr("월")))
				->initAlignment(Qt::AlignCenter)->initStyleSheet("border-right:1px solid gray; border-left:1px solid gray; background:#eeeeee"));
		}

		m_wdTdCollection = (new CPWidget(m_meta->wTable() - m_meta->wPart, (m_meta->parts().size() + 1) * m_meta->hCell + 2, new QHBoxLayout))
			->initAlignment(Qt::AlignLeft | Qt::AlignTop);
		m_main->append(m_wdTdCollection);

		QMap<QString, int> rows;
		QList<Part*> parts = m->parts();
		for (int i = 0; i < parts.size(); i++)
			rows.insert(parts.at(i)->namePart(), i);
		for (int i = 0; i < m_meta->metaMonths.size(); i++)
		{
			QTableWidget* table = new QTableWidget(this);
			table->setRowCount(m_meta->parts().size());
			table->horizontalHeader()->setStyleSheet("QHeaderView::section { background-color:#eeeeee }");

			QString currentMonth = QDateTime::currentDateTime().toString("M");

			if (!currentMonth.compare(QString("%1").arg(i + 1)))
				table->setStyleSheet("QTableView {border-right:0px solid white; background-color: #0083B0}");
			else
				table->setStyleSheet("QTableView {border-right:0px solid white;}");
			table->setSelectionMode(QAbstractItemView::NoSelection);
			table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
			table->verticalHeader()->hide();
			m_wdTdCollection->layout()->addWidget(table);

			table->setFixedWidth(m_meta->wCell() * 3);
			table->setFixedHeight((m_meta->parts().size() + 1) * m_meta->hCell + 2);
			table->setColumnCount(3);
			table->setHorizontalHeaderLabels(m_meta->metaSignatory);
			table->horizontalHeader()->setFixedHeight(m_meta->hCell);
			table->setColumnWidth(0, m_meta->wCell());
			table->setColumnWidth(1, m_meta->wCell());
			table->setColumnWidth(2, m_meta->wCell());

			foreach(Sign* s, m->signatures())
			{
				if (m_meta->metaMonths[i].toInt() == s->month())
				{
					int row = rows[s->namePart()];
					
					QString mark1;
					QString mark2;
					QString mark3;

					int markType = s->typeComplete();
					if (markType == 0)
					{
						mark1 = "X";
						mark2 = "X";
						mark3 = "X";
					}
					else if (markType == 1)
					{
						mark1 = "O";
						mark2 = "X";
						mark3 = "X";
					}
					else if (markType == 2)
					{
						mark1 = "O";
						mark2 = "O";
						mark3 = "X";
					}
					else
					{
						mark1 = "O";
						mark2 = "O";
						mark3 = "O";
					}

					QTableWidgetItem* item0 = new QTableWidgetItem(mark1);
					item0->setTextAlignment(Qt::AlignCenter);
					table->setItem(row, 0, item0);

					QTableWidgetItem* item1 = new QTableWidgetItem(mark2);
					item1->setTextAlignment(Qt::AlignCenter);
					table->setItem(row, 1, item1);

					QTableWidgetItem* item2 = new QTableWidgetItem(mark3);
					item2->setTextAlignment(Qt::AlignCenter);
					table->setItem(row, 2, item2);
				}
			}
		}
	}
	void initWidth(int w) { m_meta->setWView(w); }
	void initHeight(int h) { m_meta->setHView(h); }
	void initSize(int w, int h=0) {
		m_meta->setWView(w);
		m_meta->setHView(m_meta->hView());
	}
	MetaTableCheck* meta() { return m_meta; }

private:
	QList<QTableWidget*> m_monthTables;
	QScrollArea* m_scrollArea = nullptr;
	MetaTableCheck* m_meta = nullptr;
	CPWidget* m_wdPart = nullptr;
	CPWidget* m_main = nullptr;
	CPWidget* m_wdMnt = nullptr;
	CPWidget* m_wdTdCollection = nullptr;
	Model* m;
};