#pragma once
#include <QMainWindow>
#include "cs_style.h"
#include "cs_component.h"
#include "cs_command.h"
class ViewHome : public QWidget
{
    Q_OBJECT

public:
    ViewHome(QWidget *parent = 0);
    ~ViewHome();

	void initializeUI();
	void resizeWidget();
	public slots:
	void resize();

protected:
	void resizeEvent(QResizeEvent *event) override;

private:
	bool initedUI = false;

	StyleMain* m_style;

	StyleMainBody* m_styleBody;
	QWidget* m_body;

	StyleMainHeader* m_styleHeader;
	QWidget* m_header;

	StyleMainBody* m_styleContent;
	QWidget* m_content;

	StyleMainSlide* m_styleSlide;
	QWidget* m_slide;	
	
	StyleMainFooter* m_styleFooter;
	QWidget* m_footer;


};
