#pragma once

#include "Window.h"
#include "LayoutManager.h"
#include <iostream>

class AppComposite {
	private:
	SDL_Wrap::Window m_window;
	SDL_Wrap::Surface m_surface;
	std::shared_ptr<GUI::LayoutManager> m_lmgr;
	public:
	AppComposite();
	void draw();
	~AppComposite() { /* m_window.~Window();*/ };
};

