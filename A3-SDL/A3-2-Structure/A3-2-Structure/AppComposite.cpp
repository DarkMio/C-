#include "AppComposite.h"

AppComposite::AppComposite() : m_window(640, 480, "Haram-Bae") {
	m_surface = m_window.getSurface();
	m_lmgr = std::make_shared<GUI::PixelSpace>(20, 20, 0x3fff3fff);
}
void AppComposite::draw() {
	GUI::Rectangle rect(640, 480, 0, 0);
	if (m_lmgr->draw(m_window.getSurface(), rect)) {
		m_window.update();
	} else {
		std::cout << "Nothing to draw!" << std::endl;
	}
}
