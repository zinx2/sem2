#pragma once
#include "cs_qheader.h"
#include "cs_component.h"
#include "cs_command.h"
#include "cs_networker.h"
#include "cs_style.h"
#include "cs_model.h"
class SelectorPart : public CPDialog
{
    Q_OBJECT
public:
    explicit SelectorPart(QWidget* parent=0) : CPDialog(kr("부서찾기"), 400, 500, parent)
    {
        m = Model::instance();
//        setWindowTitle(title);
//        setFixedSize(width, height);

        m_width = 400; m_height = 500;
//        setStyleSheet("background:#dedede");
        setModal(true);

        NetWorker* n = NetWorker::instance();
        n->getPartList()->request();

        Palette* p = new Palette();
        m_btnConfirm = (new Command("btn_confirm", kr("확인"), 80, 40))->initFontSize(12)->initStyleSheet(p->btnReleasedStyleNavy)
                ->initEffect(p->btnReleasedStyleNavy, p->btnSelectedStyleNavy, p->btnHoveredStyleNavy)->initFunc([=]()
                {
                    m_parent->notify(m_table->currentRow());
                    close();
                });

        m_btnCancel = (new Command("btn_cancel", kr("취소"), 80, 40))->initFontSize(12)->initStyleSheet(p->btnReleasedStyleNavy)
                ->initEffect(p->btnReleasedStyleNavy, p->btnSelectedStyleNavy, p->btnHoveredStyleNavy)->initFunc([=]()
                {
                    close();
                });


        m_wdTail->layout()->addWidget((new CPLabel(m_width-180, 25, kr("파트를 선택하세요.")))->initAlignment(Qt::AlignCenter));
        m_wdTail->layout()->addWidget(m_btnConfirm);
        m_wdTail->layout()->addWidget(m_btnCancel);
        m_wdTail->setStyleSheet("background: #dedede");

        m_zoneParts = new QWidget(this);
        m_zoneParts->setLayout(new QVBoxLayout);
        m_zoneParts->setFixedSize(m_width, m_height);
        m_zoneParts->layout()->setAlignment(Qt::AlignTop);
        m_zoneParts->layout()->setMargin(0);
        m_zoneParts->layout()->setSpacing(0);
        m_zoneParts->layout()->addWidget(m_wdTail);
        m_zoneParts->setStyleSheet("background: #dedede");
        m_wdContents->setStyleSheet("background: #dedede");

        refresh();
        connect(m, SIGNAL(partsChanged()), this, SLOT(refresh()));
    }

    void setParent(CPDialog* parent) { m_parent = parent; }

public slots:
    void refresh()
    {
        int cnt = m->countPart();
        if (cnt <= 0) return;

        if(m_table != nullptr)
            m_zoneParts->layout()->removeWidget(m_table);

        int columnCount = 3;
        QStringList tableHeader;
        tableHeader << "번호" << "이름" << "관리자";
        m_table = new QTableWidget(cnt, columnCount, this);
        m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
        m_table->setSelectionBehavior(QAbstractItemView::SelectRows);
        m_table->setSelectionMode(QAbstractItemView::SingleSelection);
        m_table->setFixedSize(m_width, m_cellHeight * cnt + m_table->horizontalHeader()->height());
        m_table->horizontalScrollBar()->setDisabled(true);
        m_table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        m_table->setStyleSheet("background: white");
        m_table->horizontalHeader()->setStyleSheet("QHeaderView::section { background-color:#eeeeee }");
        updateTable();
        m_table->setHorizontalHeaderLabels(tableHeader);
        m_table->verticalHeader()->hide();

        for (int row = 0; row < cnt; row++)
        {
            Part* dv = m->parts().at(row);

            QTableWidgetItem* item0 = new QTableWidgetItem(QString("%1").arg(row + 1));
            item0->setTextAlignment(Qt::AlignCenter);
            m_table->setItem(row, 0, item0);

            QTableWidgetItem* item1 = new QTableWidgetItem(dv->namePart());
            item1->setTextAlignment(Qt::AlignCenter);
            m_table->setItem(row, 1, item1);

            QTableWidgetItem* item2 = new QTableWidgetItem(dv->system() ? "O" : "X");
            item2->setTextAlignment(Qt::AlignCenter);
            m_table->setItem(row, 2, item2);

            m_cellHeight = m_table->cellWidget(0, 0)->height();
        }
        m_zoneParts->layout()->addWidget(m_table);
        update();

        connect(m_table, SIGNAL(itemSelectionChanged()), this, SLOT(activate()));

    }
    void activate() { m_btnConfirm->setEnabled(true);}

private:
    QWidget* m_zoneParts;
    QTableWidget* m_table = nullptr;
    Command* m_btnConfirm;
    Command* m_btnCancel;
    CPDialog* m_parent;
    Model* m;

    int m_width;
    int m_height;
    int m_cellHeight = 0;

    void updateTable()
    {
        m_table->setFixedSize(m_width, m_height);
        m_table->setColumnWidth(0, 50);
        m_table->setColumnWidth(1, 300);
        m_table->setColumnWidth(2, 50);
//        m_table->setStyleSheet("border: 0px;");
    }

};
