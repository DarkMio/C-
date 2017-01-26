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
	m_events.subscribe(SDL_MOUSEBUTTONDOWN, [=](SDL_Event const& event) {
		std::cout << "Button press: [" << event.button.x << "," << event.button.y << "]" << std::endl;
		// GUI::undo(history);
		return true;
	});

	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	GUI::ManagedLayout left;
	GUI::ManagedLayout right;

	left.push_back(make_tuple(GUI::PixelSpace(160, 480, 0x3AA0A0FF), horizLayout));
	right.push_back(make_tuple(GUI::PixelSpace(480, 480, 0xDDDDDDFF, m_events), horizLayout));

	m_layout.push_back(make_tuple(left, [](auto const& x, auto const& y, auto const& z) { return GUI::Rectangle(160, 480, 0, 0); }));
	m_layout.push_back(make_tuple(right, [](auto const& x, auto const& y, auto const& z) { return GUI::Rectangle(480, 480, 160, 0); }));

	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	int dif = duration_cast<nanoseconds>(t2 - t1).count();
	printf("Generation time: %ld nanoseconds.\n", dif);
	m_events.subscribe(SDL_QUIT, [=](SDL_Event const& event) {
		m_quit = true;
		return false;
	});
}
bool AppComposite::draw() {
	m_events.event_loop();
	GUI::Rectangle rect(640, 480, 0, 0);

	if (GUI::draw(m_layout, m_window.getSurface(), rect)) {
		m_window.update();
	}

	return !m_quit;
}
