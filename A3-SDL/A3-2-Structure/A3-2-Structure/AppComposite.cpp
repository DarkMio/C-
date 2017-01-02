#include "AppComposite.h"

AppComposite::AppComposite() : m_window(640, 480, "Haram-Bae"), m_events(), m_quit(false) {
	m_events.subscribe(SDL_MOUSEBUTTONDOWN, [](SDL_Event const& event) {
		std::cout << "Button press: [" << event.button.x << "," << event.button.y << "]" << std::endl;
		return true;
	});

	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	m_surface = m_window.getSurface();
	
	m_lmgr = std::make_shared<GUI::VerticalLayout>();
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
	
	for (int j = 0; j < 48; j++) {
		Uint32 color = 0xFFFFFFFF - (0x03000000 * j) - 0x00AAAA00;
		auto lmgr = std::make_shared<GUI::HorizontalCloseLayout>();
		for (int i = 0; i < 64; i++) {
			auto pixels = std::make_shared<GUI::PixelSpace>(10, 10, color);
			pixels->setup_eventlistener(m_events);
			lmgr->add(pixels, GUI::LayoutFlags::botleft);

			// lmgr->add(std::make_shared<GUI::PixelSpace>(10, 10, color), GUI::LayoutFlags::botleft);

			color -= 0x00010100;
		}
		m_lmgr->add(lmgr, GUI::LayoutFlags::botleft);
		color -= 0x01000100;
	}

	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	double dif = duration_cast<nanoseconds>(t2 - t1).count();
	printf("Generation time: %lf nanoseconds.\n", dif);
	m_events.subscribe(SDL_QUIT, [=](SDL_Event const& event) {
		m_quit = true;
		return false;
	});
}
bool AppComposite::draw() {
	
	m_events.event_loop();

	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	GUI::Rectangle rect(640, 480, 0, 0);
	if (m_lmgr->draw(m_window.getSurface(), rect)) {
		m_window.update();
	} else {
		// std::cout << "Nothing to draw!" << std::endl;
	}
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	double dif = duration_cast<nanoseconds>(t2 - t1).count();
	// printf("Drawcall time: %lf nanoseconds.\n", dif);
	return !m_quit;
}
