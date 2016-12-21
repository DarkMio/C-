#include "Surface.h"



Surface::Surface() : Surface(640, 480) {}

Surface::Surface(size_t const& width, size_t const& height) {
	surface = SDL_CreateRGBSurface(0, width, height, 32,
								   0xff000000,
								   0x00ff0000,
								   0x0000ff00,
								   0x000000ff);
}

Surface::Surface(SDL_Surface* surf) {
	surface = surf;
}

Surface::Surface(char * path) {
	surface = SDL_LoadBMP(path);
	if (surface == nullptr) {
		throw std::exception(SDL_GetError());
	}
}

Surface::Surface(Surface const & copy) {
	surface = SDL_ConvertSurface(copy.surface, copy.surface->format, copy.surface->flags);
}

Surface::Surface(Surface && other) : surface(other.surface) {
	other.surface = nullptr;
}

Surface & Surface::operator=(Surface const & other) {
	if (surface != nullptr) {
		SDL_FreeSurface(surface);
	}
	surface = SDL_ConvertSurface(other.surface, other.surface->format, other.surface->flags);
	return *this;
}

Surface& Surface::operator=(Surface&& other) {
	if (this != &other) {
		if (surface != nullptr) {
			SDL_FreeSurface(surface);
		}
		std::swap(surface, other.surface);
	}
	return *this;
}

Surface::~Surface() {
	SDL_FreeSurface(surface);
}

void Surface::fill(Uint32 const& color) {
	if (SDL_FillRect(surface, NULL, color)) {
		throw std::exception(SDL_GetError());
	}
}

std::tuple<int, int> Surface::size() {
	return std::make_tuple(surface->w, surface->h);
}

SDL_Surface * Surface::get_surface() const {
	return surface;
}
