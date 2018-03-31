#pragma once
#include "cs_qheader.h"
#include "cs_style.h"
#include <QStyle>
class Command : public QPushButton
{
public:
	Command(QString tag, QString name, int width, int height) : m_tag(tag)
	{
		this->setFixedSize(width, height);
		QFont font = this->font();
		font.setPointSize(12);
		this->setFont(font);
		this->setText(name);
		initFontType("NanumBarunGothic");
	}
	QString tag() { return m_tag; }
	Command* initStyleSheet(QString sheet) { setStyleSheet(sheet); return this; }
	Command* initFontSize(int pt) {
		QFont font = this->font();
		font.setPointSize(pt);
		this->setFont(font);
		return this;
	}
	Command* initFontType(QString name) {
		QFont oldFont = this->font();
		this->setFont(QFont(name, oldFont.pointSize(), oldFont.weight()));
		return this;
	}
	Command* initName(QString name) { setText(name); return this; }
	Command* initIcon(QString iconPath) {
		QPixmap pixmap(iconPath);
		QIcon icon(pixmap);
		setIcon(icon);
		setIconSize(pixmap.rect().size());
		return this;
	};
	Command* initIcon(QString iconPath, QString txt) {
		QPixmap pixmap(iconPath);
		m_pixmap = pixmap;
		m_txt = txt;
		return this;
	};
	QPixmap m_pixmap;
	QString m_txt;
	void paintEvent(QPaintEvent* e)
	{
		QPushButton::paintEvent(e);

		if (!m_pixmap.isNull())
		{
			const int y = (height() - m_pixmap.height()) / 2; // add margin if needed
			QPainter painter(this);
			painter.drawPixmap(40, y, m_pixmap); // hardcoded horizontal margin

			QFont font = painter.font();
			font.setPointSize(font.pointSize() + 5);
			font.setBold(true);
			painter.setFont(font);
			painter.drawText(100, height() / 2 + 5, m_txt);
		}
	}
private:
	QString m_tag;
};
//
//class CommandProvider : public QObject
//{
//public:
//	CommandProvider()
//	{
//		d = Style::instance();
//	}
//	void releaseAll()
//	{
//		foreach(Command* c, m_commands)
//		{
//			c->setStyleSheet(d->c().btnReleasedStyle);
//		}
//	}
//	void select(QString tag)
//	{
//		releaseAll();
//		foreach(Command* c, m_commands)
//		{
//			if (!c->tag().compare(tag))
//			{
//				c->setStyleSheet(d->c().btnSelectedStyle);
//			}
//		}
//	}
//	void append(Command* command)
//	{
//		command->setStyleSheet(d->c().btnReleasedStyle);
//		m_commands.append(command);
//	}
//	Command* command(QString tag)
//	{
//		foreach(Command* c, m_commands)
//		{
//			if (!c->tag().compare(tag))
//			{
//				return c;
//			}
//		}
//		return nullptr;
//	}
//
//	QList<Command*> commands() { return m_commands; }
//private:
//	QList<Command*> m_commands;
//	Style* d;
//};
