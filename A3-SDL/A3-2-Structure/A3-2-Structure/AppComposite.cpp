#include "AppComposite.h"

AppComposite::AppComposite() : m_window(640, 480, "Haram-Bae"), m_quit(false), m_lmgr(640, 480) {
	

	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	// m_surface = m_window.getSurface();
	
	// m_lmgr = OptimizedFields(640, 480);
	/*

	auto pixels = std::make_shared<GUI::PixelSpace>(50, 50, 0x114411FF);
	pixels->setup_eventlistener(m_events);
	m_lmgr->add(pixels, GUI::LayoutFlags::botleft);

	pixels = std::make_shared<GUI::PixelSpace>(50, 50, 0x222222FF);
	pixels->setup_eventlistener(m_events);
	m_lmgr->add(pixels, GUI::LayoutFlags::botleft);

	pixels = std::make_shared<GUI::PixelSpace>(50, 50, 0x222222FF);
	pixels->setup_eventlistener(m_events);
	m_lmgr->add(pixels, GUI::LayoutFlags::botleft);

	pixels = std::make_shared<GUI::PixelSpace>(50, 50, 0x222222FF);
	pixels->setup_eventlistener(m_events);
	m_lmgr->add(pixels, GUI::LayoutFlags::botleft);

	*/

	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	double dif = duration_cast<nanoseconds>(t2 - t1).count();
	printf("Generation time: %lf nanoseconds.\n", dif);
}
bool AppComposite::draw() {
	m_quit = m_lmgr.m_quit;

	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	GUI::Rectangle rect(640, 480, 0, 0);
	if (m_lmgr.draw(m_window.getSurface())) {
		m_window.update();
	} else {
		// std::cout << "Nothing to draw!" << std::endl;
	}
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	double dif = duration_cast<nanoseconds>(t2 - t1).count();
	// printf("Drawcall time: %lf nanoseconds.\n", dif);
	return !m_quit;
}
