﻿#include "cs_style.h"
#include "cs_model.h"
Style* Style::m_instance = nullptr;
Model* Model::m_instance = nullptr;

Style::Style() {
	m_main = new StyleMain();
}

void Style::initialize() {
	//m_main = new StyleMain();
    //m_menubarWidth = m_windowWidth;
    //m_menubarHeight = pt(50);

    //m_statusbarWidth = m_windowWidth;
    //m_statusbarHeight = pt(30);

    //m_borderFixedSize = pt(8);

    //m_explorerWidth = pt(250);// m_windowWidth / 3;
    //m_explorerHeight = m_windowHeight - m_menubarHeight - m_statusbarHeight;

    //m_logWidth = m_previewWidth;
    //m_logHeight = pt(200);//m_explorerHeight - m_previewHeight;

    //m_previewWidth = m_windowWidth - m_explorerWidth - m_borderFixedSize;
    //m_previewHeight = /*m_explorerHeight * 2 / 3*/ m_explorerHeight - m_logHeight - m_borderFixedSize;
}
