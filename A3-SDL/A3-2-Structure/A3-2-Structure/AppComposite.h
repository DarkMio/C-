#pragma once

#include "Window.h"
#include "LayoutManager.h"
#include "LayoutManagerImpls.h"
#include "EventManager.h"
#include <iostream>
#include <chrono>
#include <thread>
#include "Views.h"


// #include "Controller.h"
using namespace std;
using namespace std::chrono;

class AppComposite {
	private:
	SDL_Wrap::Window m_window;
	high_resolution_clock::time_point m_frametime;

	Views::Controller m_controller;
	// SDL_Wrap::Surface m_surface;
	
	bool m_quit;
	shared_ptr<LayoutManager> m_lmgr;
	EventManager m_events;
	public:
	AppComposite();
	bool draw();
	~AppComposite() { /* m_window.~Window();*/ };
};

