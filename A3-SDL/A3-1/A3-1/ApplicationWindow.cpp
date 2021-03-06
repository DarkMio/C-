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

void ApplicationWindow::set_pixel(int const & x, int const & y, Uint32 const & color) {
	SDL_Surface* pixel = SDL_CreateRGBSurface(0, 1, 1, 32,
						 0xff000000,
						 0x00ff0000,
						 0x0000ff00,
						 0x000000ff
						 );
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = 1;
	rect.h = 1;
	SDL_FillRect(pixel, NULL, color);
	SDL_BlitSurface(pixel, NULL, internalSurface->get_surface(), &rect);
}

void ApplicationWindow::update() {
	if (SDL_UpdateWindowSurface(window) < 0) {
		throw std::exception(SDL_GetError());
	}
}

std::tuple<int, int> ApplicationWindow::pos() {
	int result[2];
	SDL_GetWindowPosition(window, result, result + 1);
	return std::make_tuple(result[0], result[1]);
}

void ApplicationWindow::set_pos(int const & x, int const & y) {
	SDL_SetWindowPosition(window, x, y);
}

void ApplicationWindow::blit(int const& x, int const& y, Surface const& surface) {
	SDL_Surface* surf = surface.get_surface();
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = surf->w;
	rect.h = surf->h;
	SDL_BlitSurface(surf, NULL, internalSurface->get_surface(), &rect);
}

void ApplicationWindow::run() {
	int quit = 0;
	SDL_Event event;
	int i = 0;
	bool pressed = false;
	int old_x = 0;
	int old_y = 0;
	Uint32 color = 0xFFFFFFFF;
	while (!quit) { // ~10s
		i++;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = 1;
			}
			if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
				pressed = true;
				old_x = event.button.x;
				old_y = event.button.y;
			}
			if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT) {
				pressed = false;
			}
			if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_RIGHT) {
				color = 0;
				for (int i = 8; i < 32; i += 8) {
					int random = std::rand();
					random &= 0xFF;
					random = random << i;
					color |= random;
				}
				color |= 0x000000FF;
			}
		}
		
		if (pressed) {
			auto x = event.button.x;
			auto y = event.button.y;

			auto distance = std::sqrt(std::pow(old_x - x, 2) + std::pow(old_y - y, 2));
			auto frac = 1.f / distance;
			// std::cout << distance << std::endl;


			for (int i = 0; i < distance; i++) {
				auto nx = old_x + (x - old_x) * (frac * i);
				auto ny = old_y + (y - old_y) * (frac * i);
				set_pixel((int)nx, (int)ny, color);
			}

			old_x = x;
			old_y = y;


			// set_pixel(x, y, 0xFFFFFFFF);
		}

		// std::this_thread::sleep_for(std::chrono::milliseconds(33)); // 60fps;
		// set_pixel(i%640, i%480, 0xFFAA00AA+i + (i << 4));
		update();
	}
}
