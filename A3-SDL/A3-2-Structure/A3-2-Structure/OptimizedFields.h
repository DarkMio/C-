#pragma once
#include "LayoutManagerImpls.h"

using namespace GUI;
using namespace std;
class OptimizedFields {
	protected:
	unique_ptr<LayoutManager> m_layoutRoot;
	GUI::EventManager m_events;
	vector<PixelSpace> m_spaces;

	public:
	bool m_quit;

	OptimizedFields(int const& width, int const& height) : m_events(), m_quit(false) {
		m_events.subscribe(SDL_MOUSEBUTTONDOWN, [](SDL_Event const& event) {
			std::cout << "Button press: [" << event.button.x << "," << event.button.y << "]" << std::endl;
			return true;
		});

		m_events.subscribe(SDL_QUIT, [=](SDL_Event const& event) {
			m_quit = true;
			return false;
		});

		/*
		int widthSize = width / 2;
		int heightSize = height / 2;

		m_layoutRoot = make_unique<HorizontalLayout>();
		for (int j = 0; j < 2; j++) {
			Uint32 color = 0xFFFFFFFF - (0x03000000 * j) - 0x00AAAA00;
			auto lmgr = std::make_shared<GUI::VerticalLayout>();
			for (int i = 0; i < 2; i++) {
				auto pixels = std::make_shared<GUI::PixelSpace>(widthSize, heightSize, color);
				pixels->setup_eventlistener(m_events);
				lmgr->add(pixels, GUI::LayoutFlags::botleft);

				// lmgr->add(std::make_shared<GUI::PixelSpace>(10, 10, color), GUI::LayoutFlags::botleft);

				color -= 0x00010100;
			}
			m_layoutRoot->add(lmgr, GUI::LayoutFlags::botleft);
			color -= 0x01000100;
		}
		*/

		m_layoutRoot = make_unique<HorizontalCloseLayout>();

		auto left = make_shared<VerticalLayout>();
		auto right = make_shared<VerticalLayout>();

		left->add(make_shared<GUI::PixelSpace>(160, 480, 0x3AA0A0FF), 0);
		right->add(make_shared<GUI::PixelSpace>(480, 480, 0xAAAAAAFF), 0);

		m_layoutRoot->add(move(left), 0);
		m_layoutRoot->add(move(right), 0);
	};

	bool draw(Surface const& surf) {
		m_events.event_loop();


		SDL_Surface* x = surf.get_surface();
		Rectangle r(x->w, x->h, 0, 0);
		return m_layoutRoot->draw(surf, r);
	}


	~OptimizedFields() {};
};

