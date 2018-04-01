#pragma once
#include <QDebug>
#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPalette>
#include <QResizeEvent>
#include <QLineEdit>

#include <QTableView>
#include <QTableWidget>
#include <QTableWidgetItem>

#include <QMutex>
#include <QTextEdit>
#include <QScrollArea>

#include <QMutexLocker>
#include <QList>
#include <QHeaderView>
#include <QScrollBar>

#include <QDialog>
#include <QLabel>

#include <QDir>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>

#include <QMessageBox>
#include <QCheckBox>
#include <QDateTime>

#include <QRadioButton>
#include <QTimer>
//
//#include "cs_qheader.h"
//#include "cs_design.h"
//#include "cs_networker.h"
//#include "cs_model.h"
//#include "cs_command.h"
#include <QtCore/QTextCodec>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
static QString kr(const char *strKor)
{
    static QTextCodec *codec = QTextCodec::codecForName("eucKR"); //"eucKR"
    //static QTextCodec *codec = QTextCodec::codecForName("UTF-8"); //"eucKR"
    return codec->toUnicode(strKor);
}

static void print(QWidget* obj)
{
    QPrinter printer;
    QPrintDialog *dialog = new QPrintDialog(&printer);
    if (dialog->exec() == QDialog::Accepted)
    {
        QPainter painter(&printer);
        obj->render(&painter);
    }
}

static void print(QString tag, int num1, int num2)
{
	qDebug() << tag << ": " << num1 << " / " << num2;
}
static void print(QString tag, int num)
{
	qDebug() << tag << ": " << num;
}
static void print(QString tag, QString str)
{
	qDebug() << tag << ": " << str;
}
