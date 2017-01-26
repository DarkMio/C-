#include "AppComposite.h"

AppComposite::AppComposite() : m_window(640, 480, "Haram-Bae"), m_events(), m_quit(false), m_layout() {

	auto vertLayout = [](GUI::Rectangle const& totalSpace, int const& count, int const& size) {
		int chunkedSize = totalSpace.h / size;
		return GUI::Rectangle(totalSpace.w, chunkedSize, totalSpace.x, totalSpace.y + chunkedSize * count);
	};

	auto horizLayout = [](GUI::Rectangle const& totalSpace, int const& count, int const& size) {
		int chunkedSize = totalSpace.w / size;
		return GUI::Rectangle(chunkedSize, totalSpace.h, totalSpace.x + chunkedSize * count, totalSpace.y);
	};

	// m_layout = GUI::LayoutGroup(move(make_tuple(GUI::Layout(), vertLayout))); // GUI::Layout(); // make_tuple(GUI::Layout(), move(make_unique<GUI::HorizotalLayout>()));
	m_events.subscribe(SDL_MOUSEBUTTONDOWN, [](SDL_Event const& event) {
		std::cout << "Button press: [" << event.button.x << "," << event.button.y << "]" << std::endl;
		return true;
	});

	high_resolution_clock::time_point t1 = high_resolution_clock::now();

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

	
	/*
	
	for (int j = 0; j < 48; j++) {
		Uint32 color = 0xFFFFFFFF - (0x03000000 * j) - 0x00AAAA00;
		//GUI::ManagedLayout lmgr = make_tuple(GUI::Layout(), move(make_unique<GUI::HorizotalLayout>()));
		auto lmgr = GUI::ManagedLayout();
		//lmgr.push_back(make_tuple())
		for (int i = 0; i < 64; i++) {
			auto pixels = std::make_shared<GUI::PixelSpace>(10, 10, color);
			lmgr.push_back(make_tuple(pixels, vertLayout));
			// pixels->setup_eventlistener(m_events);
			// get<0>(lmgr).push_back(pixels);

			// lmgr->add(std::make_shared<GUI::PixelSpace>(10, 10, color), GUI::LayoutFlags::botleft);

			color -= 0x00010100;
		}
		// get<0>(m_layout).push_back(lmgr);

		m_layout.push_back(make_tuple(lmgr, horizLayout));
		color -= 0x01000100;
	}
	
	*/

	GUI::ManagedLayout x;
	
	for(int i = 0; i < 10; i++) {
		Uint32 color = 0xFFF0FFFF - ((i * 100) << 16);
		GUI::ManagedLayout x;
		for(int j = 0; j < 10; j++) {
			color -= (1 * 50) << 24;
			x.push_back(make_tuple(GUI::PixelSpace(50 - 5 * 2, 50 - i * 2, color), horizLayout));
		}
		m_layout.push_back(make_tuple(x, vertLayout));
		// x.push_back(make_tuple(GUI::PixelSpace(50 - i * 5, 50 - i * 5, color), horizLayout));
	}

	for (int i = 0; i < 10; i++) {
		m_layout.push_back(make_tuple(x, vertLayout));
	}

	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	double dif = duration_cast<nanoseconds>(t2 - t1).count();
	cout << "Generation time: %lf nanoseconds." <<  dif << endl;
	m_events.subscribe(SDL_QUIT, [=](SDL_Event const& event) {
		m_quit = true;
		return false;
	});
}
bool AppComposite::draw() {
	
	m_events.event_loop();

	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	GUI::Rectangle rect(640, 480, 0, 0);
	if (GUI::draw(m_layout, m_window.getSurface(), rect)) {
		m_window.update();
	} else {
		// std::cout << "Nothing to draw!" << std::endl;
	}
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	double dif = duration_cast<nanoseconds>(t2 - t1).count();
	// printf("Drawcall time: %lf nanoseconds.\n", dif);
	return !m_quit;
}
