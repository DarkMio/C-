#include <SDL.h>
#include <thread>
#include <chrono>
#include "Surface.h"
#include <iostream>
#include <tuple>
#include <cmath>

#pragma once
class ApplicationWindow {
	SDL_Window *window;
	Surface *internalSurface;
	public:
	ApplicationWindow();
	ApplicationWindow(int const& width, int const& height, char* const& title="SDL Window");
	// we just disallow all that for now, no copy, no move.
	ApplicationWindow(ApplicationWindow const&) = delete;
	ApplicationWindow(ApplicationWindow&&) = delete;
	ApplicationWindow& operator=(ApplicationWindow const&) = delete;
	ApplicationWindow& operator=(ApplicationWindow&&) = delete;

	~ApplicationWindow();
	void set_pixel(int const& x, int const& y, Uint32 const& color);
	void update();
	std::tuple<int, int> pos();
	void set_pos(int const& x, int const& y);
	void blit(int const& x, int const& y, Surface const& surface);
	void run();
};

