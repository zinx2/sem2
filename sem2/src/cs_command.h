#pragma once
#include "cs_qheader.h"
#include "cs_style.h"
#include <QStyle>

typedef std::function<void()> FUNC;
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
	Command* initWidth(int width) { setFixedWidth(width); return this; }
	Command* initStyleSheet(QString sheet) { setStyleSheet(sheet); return this; }
	Command* initEffect(QString released, QString selected, QString hovered = "")
	{
		m_releasedSheet = released;	m_hoveredSheet  = hovered; m_selectedSheet = selected;
		return this;
	}
	Command* initFunc(FUNC func) {
		m_cmd = func;
		return this;
	}

	Command* initStyleReleasedSheet(QString sheet) { m_releasedSheet = sheet; return this; }
	Command* initStyleHoveredSheet(QString sheet) { m_hoveredSheet = sheet; return this; }
	Command* initStyleSelectedSheet(QString sheet) { m_selectedSheet = sheet; return this; }
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
	int m_margin;
	void paintEvent(QPaintEvent* e)
	{
		QPushButton::paintEvent(e);

		if (!m_pixmap.isNull())
		{
			const int y = (height() - m_pixmap.height()) / 2; // add margin if needed
			QPainter painter(this);
			painter.drawPixmap(8, y, m_pixmap); // hardcoded horizontal margin

			QFont font = painter.font();
			font.setPointSize(font.pointSize() + 2);
			//font.setBold(true);
			painter.setFont(font);
			painter.drawText(66, height() / 2 + 5, m_txt);
		}
	}

	bool selected() { return m_selected; }
	Command* select(bool m) { m_selected = m; return this; }

protected:

	void mousePressEvent(QMouseEvent *event) override
	{
		setStyleSheet(m_selectedSheet);
	}
	void enterEvent(QEvent * event)
	{
		Q_UNUSED(event);
		setStyleSheet(m_hoveredSheet);
		/*Qt::CursorShape type = (ori == Qt::Vertical ? Qt::SizeHorCursor : Qt::SizeVerCursor);
		this->setCursor(QCursor(type));*/
	}
	void leaveEvent(QEvent * event)
	{
		Q_UNUSED(event);
		setStyleSheet(m_releasedSheet);
	}
	void mouseReleaseEvent(QMouseEvent *event) override
	{
		print("", "mouseReleaseEvent");
		setStyleSheet(m_releasedSheet);
		m_cmd();
	}

private:
	bool m_selected = false;
	QString m_tag;
	QString m_releasedSheet = "color: white; background-color: transparent;";
	QString m_hoveredSheet = "color: white; background-color: transparent;";
	QString m_selectedSheet = "color: white; background-color: transparent;";
	FUNC m_cmd;
};

class CommandProvider : public QObject
{
public:
	CommandProvider()
	{
		//d = Style::instance();
	}
	void releaseAll()
	{
		foreach(Command* c, m_commands)
		{
			c->select(false);
		}
	}
	void select(QString tag)
	{
		releaseAll();
		foreach(Command* c, m_commands)
		{
			if (!c->tag().compare(tag))
			{
				c->select(true);
			}
		}
	}
	CommandProvider* append(Command* command)
	{
		m_commands.append(command);
		return this;
	}
	Command* command(QString tag)
	{
		foreach(Command* c, m_commands)
		{
			if (!c->tag().compare(tag))
			{
				return c;
			}
		}
		return nullptr;
	}

	QString selectedTag() {
		foreach(Command* c, m_commands)
		{
			if (c->selected())
			{
				return c->tag();
			}
		}
		return "";
	}
	Command* command(int idx) { return m_commands.at(idx); }
	int totalHeight() { 
		int size = m_commands.size();
		if (size == 0) return 0;
		else {
			int h = 0;
			foreach(Command* c, m_commands)
				h += c->height();
			return h;
		}

	}
	int count() { return m_commands.size(); }
	QList<Command*> commands() { return m_commands; }
private:
	QList<Command*> m_commands;
	Style* d;
};
