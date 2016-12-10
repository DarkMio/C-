#include "Surface.h"



Surface::Surface() :Surface(
	surface = SDL_CreateRGBSurface(0, 640, 480, 32,
								   0xff000000,
								   0x00ff0000,
								   0x0000ff00,
								   0x000000ff)
) {}

Surface::Surface(SDL_Surface* surf) {
	surface = surf;
}

Surface::~Surface() {
	SDL_FreeSurface(surface);
}

void Surface::fill(Uint32 const& color) {
	if (SDL_FillRect(surface, NULL, color)) {
		throw std::exception(SDL_GetError());
	}
}

int* Surface::size() {
	return new int[2] {surface->w, surface->h};
}

SDL_Surface * Surface::get_surface() const {
	return surface;
}
