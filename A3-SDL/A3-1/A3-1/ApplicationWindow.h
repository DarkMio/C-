#include <SDL.h>
#include <thread>
#include <chrono>
#include "Surface.h"

#pragma once
class ApplicationWindow {
	SDL_Window *window;
	Surface *internalSurface;
	public:
	ApplicationWindow();
	ApplicationWindow(int const& width, int const& height, char* const& title="SDL Window");
	~ApplicationWindow();
	void set_pixel(unsigned short const& x, unsigned short const& y, Uint32 const& color);
	void update();
	int* pos();
	void set_pos(int const& x, int const& y);
	void blit(Surface const& surface);
	void run();
};

