#include "ApplicationWindow.h"

ApplicationWindow::ApplicationWindow() : ApplicationWindow(640, 480, "An SDL2 Standard Window") {}

ApplicationWindow::ApplicationWindow(int const & width, int const & height, char * const & title) {
	window = SDL_CreateWindow(
		title,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		width,
		height,
		SDL_WINDOW_OPENGL
	);
	internalSurface = new Surface(SDL_GetWindowSurface(window));
}


ApplicationWindow::~ApplicationWindow() {
	SDL_DestroyWindow(window);
}

void ApplicationWindow::set_pixel(unsigned short const & x, unsigned short const & y, Uint32 const & color) {
	throw std::exception("Not implemented!");
}

void ApplicationWindow::update() {
	if (SDL_UpdateWindowSurface(window) < 0) {
		throw std::exception(SDL_GetError());
	}
}

int * ApplicationWindow::pos() {
	int result[2];
	SDL_GetWindowPosition(window, result, result + 1);
	return result;
}

void ApplicationWindow::set_pos(int const & x, int const & y) {
	SDL_SetWindowPosition(window, x, y);
}

void ApplicationWindow::blit(Surface const& surface) {
	throw std::exception("Not implemented.");
}

void ApplicationWindow::run() {
	int quit = 0;
	SDL_Event event;
	while (!quit) { // ~10s
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = 1;
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(33)); // 60fps;
			update();
		}

	}
}
