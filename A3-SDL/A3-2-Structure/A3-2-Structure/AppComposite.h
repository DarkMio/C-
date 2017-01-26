#pragma once

#include "Window.h"
#include "LayoutManager.h"
#include "LayoutManagerImpls.h"
#include "EventManager.h"
#include <iostream>
#include <chrono>
#include "OptimizedFields.h"
using namespace std;
using namespace std::chrono;

class AppComposite {
	private:
	SDL_Wrap::Window m_window;
	// SDL_Wrap::Surface m_surface;
	
	bool m_quit;
	OptimizedFields m_lmgr;
	public:
	AppComposite();
	bool draw();
	~AppComposite() { /* m_window.~Window();*/ };
};

