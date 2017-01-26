#pragma once

#include "Window.h"
#include "EventManager.h"
#include <iostream>
#include <chrono>
#include "Drawable.h"
using namespace std;
using namespace std::chrono;

class AppComposite {
	private:
	SDL_Wrap::Window m_window;
	// SDL_Wrap::Surface m_surface;
	GUI::EventManager m_events;
	GUI::ManagedLayout m_layout;
	bool m_quit;
	// std::shared_ptr<GUI::LayoutManager> m_lmgr;
	public:
	AppComposite();
	bool draw();
	~AppComposite() { /* m_window.~Window();*/ };
};
