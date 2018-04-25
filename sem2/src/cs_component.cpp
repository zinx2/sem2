#include "cs_component.h"
#include "cs_settings.h"
#include "cs_alarm.h"
#include "cs_question.h"
#include "cs_networker.h"

Page::Page(int width, int height, QLayout* ly, QWidget *parent) : QWidget(parent)
{
	setFixedSize(width, height);
	setLayout(ly);

	layout()->setSpacing(0);
	layout()->setMargin(0);

	m = Model::instance();
	n = NetWorker::instance();
	s = Settings::instance();

	m_alarm = new Alarm(kr("알림"), "", 350, 200);
	m_question = new Question(kr("알림"), "", 350, 200);
}

CPWidget::CPWidget(int width, int height, QLayout* ly, QWidget *parent) : QWidget(parent)
{
	setFixedSize(width, height);
	setLayout(ly);
	//layout()->setAlignment(Qt::AlignVCenter);
	layout()->setSpacing(0);
	layout()->setMargin(0);
}