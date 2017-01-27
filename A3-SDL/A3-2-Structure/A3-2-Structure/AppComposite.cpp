#include "AppComposite.h"

AppComposite::AppComposite() : m_window(640, 480, "Haram-Bae"), m_quit(false), m_lmgr() {
	

	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	m_lmgr = make_unique<HorizontalCloseLayout>();

	auto left = make_shared<VerticalLayout>();
	auto right = make_shared<VerticalLayout>();

	auto rightField = std::make_shared<Views::DrawPanel>(480, 480);
	rightField->setup_eventlistener(m_events);
	m_controller = Views::Controller(rightField);
	//	m_controller.registerDrawPanel(rightField);
	auto buttonsView = make_shared<Views::ButtonsView>(Rectangle(160, 480, 0, 0), m_events, make_shared<Views::Controller>(m_controller));


	left->add(buttonsView, 0);
	right->add(rightField, 0);

	m_lmgr->add(move(left), 0);
	m_lmgr->add(move(right), 0);

	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	double dif = duration_cast<nanoseconds>(t2 - t1).count();
	printf("Generation time: %lf nanoseconds.\n", dif);

	m_events.subscribe(SDL_QUIT, [=](SDL_Event const& event){
		m_quit = true;
		return true;
	});
	m_window.getSurface().fill(0xF3F4F5FF);

	m_frametime = high_resolution_clock::now(); // really the very last step
}

bool AppComposite::draw() {
	m_events.event_loop();

	auto current_time = high_resolution_clock::now();
	double dif = duration_cast<milliseconds>(current_time - m_frametime).count();

	if(dif > 17) {
		m_frametime = current_time;

		GUI::Rectangle rect(640, 480, 0, 0);
		if (m_lmgr->draw(m_window.getSurface(), rect)) {
			m_window.update();
		} else { }

		this_thread::sleep_for(milliseconds(10));
	}


	return !m_quit;
}
