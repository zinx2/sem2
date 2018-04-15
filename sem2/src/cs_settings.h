#pragma once
#include <QSettings>

class Settings {

public:
	static Settings* instance() {
		if (m_instance == nullptr)
		{
			QSettings m_settings("olei", "sem");
			m_instance = new Settings();
		}
		return m_instance;
	}
	
	bool isLoginAuto() { 
		QSettings m_settings("olei", "sem");
		return m_settings.value("is_login_auto").toBool();
	}
	void loginAuto(bool m) {
		QSettings m_settings("olei", "sem");
		m_settings.setValue("is_login_auto", m); 
	}
	
	QString id() { 
		QSettings m_settings("olei", "sem");
		return m_settings.value("id").toString(); 
	}
	void setId(QString m) { 
		QSettings m_settings("olei", "sem");
		m_settings.setValue("id", m); 
	}

	QString pass() { 
		QSettings m_settings("olei", "sem");
		return m_settings.value("pass").toString(); 
	}
	void setPass(QString m) { 
		QSettings m_settings("olei", "sem");
		m_settings.setValue("pass", m); 
	}

private:
	//QSettings m_settings;
	static Settings* m_instance;

};