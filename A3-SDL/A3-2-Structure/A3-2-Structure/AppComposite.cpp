#include "AppComposite.h"
#include "Views.h"

AppComposite::AppComposite() : m_window(640, 480, "Haram-Bae"), m_quit(false), m_lmgr() {
	

	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	m_lmgr = make_unique<HorizontalCloseLayout>();

	auto left = make_shared<VerticalLayout>();
	auto right = make_shared<VerticalLayout>();

	auto rightField = std::make_shared<GUI::PixelSpace>(480, 480, 0xAAAAAAFF);
	rightField->setup_eventlistener(m_events);

	left->add(make_shared<Views::ButtonsView>(Rectangle(160, 480, 0, 0)), 0);
	right->add(rightField, 0);

	m_lmgr->add(move(left), 0);
	m_lmgr->add(move(right), 0);

	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	double dif = duration_cast<nanoseconds>(t2 - t1).count();
	printf("Generation time: %lf nanoseconds.\n", dif);

	m_events.subscribe(SDL_MOUSEBUTTONDOWN, [](SDL_Event const& event) {
		std::cout << "Button press: [" << event.button.x << "," << event.button.y << "]" << std::endl;
		return true;
	});

	m_events.subscribe(SDL_QUIT, [=](SDL_Event const& event){
		m_quit = true;
		return true;
	});
}

bool AppComposite::draw() {
	m_events.event_loop();
	GUI::Rectangle rect(640, 480, 0, 0);
	if (m_lmgr->draw(m_window.getSurface(), rect)) {
		m_window.update();
	} else {
		// std::cout << "Nothing to draw!" << std::endl;
	}
	return !m_quit;
}
