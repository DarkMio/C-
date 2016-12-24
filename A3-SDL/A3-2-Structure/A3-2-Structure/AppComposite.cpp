#include "AppComposite.h"

AppComposite::AppComposite() : m_window(640, 480, "Haram-Bae") {
	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	m_surface = m_window.getSurface();
	m_lmgr = std::make_shared<GUI::VerticalLayout>();
	Uint32 color = 0xFFFFFFFF;
	for (int j = 0; j < 48; j++) {
		color = 0xFFFFFFFF - (0x03000000 * j);
		auto lmgr = std::make_shared<GUI::HorizontalCloseLayout>();
		for (int i = 0; i < 64; i++) {
			lmgr->add(std::make_shared<GUI::PixelSpace>(10, 10, color), GUI::LayoutFlags::botleft);
			color -= 0x00010100;
		}
		m_lmgr->add(lmgr, GUI::LayoutFlags::botleft);
		//color -= 0x01000100;
	}

	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	double dif = duration_cast<nanoseconds>(t2 - t1).count();
	printf("Generation time: %lf nanoseconds.\n", dif);
}
void AppComposite::draw() {
	
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	GUI::Rectangle rect(640, 480, 0, 0);
	if (m_lmgr->draw(m_window.getSurface(), rect)) {
		m_window.update();
	} else {
		std::cout << "Nothing to draw!" << std::endl;
	}
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	double dif = duration_cast<nanoseconds>(t2 - t1).count();
	printf("Drawcall time: %lf nanoseconds.\n", dif);

}
