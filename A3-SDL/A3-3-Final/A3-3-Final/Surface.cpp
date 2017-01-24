#include "Surface.h"

namespace SDL_Wrap {


	Surface::Surface() : Surface(640, 480) {}

	Surface::Surface(size_t const& width, size_t const& height) {
		surface = SurfacePtr(
			SDL_CreateRGBSurface(0, width, height, 32,
								 0xff000000,
								 0x00ff0000,
								 0x0000ff00,
								 0x000000ff)
		);
	}

	Surface::Surface(SDL_Surface* surf) {
		surface = SurfacePtr(surf);
	}

	Surface::Surface(char * path) {
		surface = SurfacePtr(SDL_LoadBMP(path));
		if (surface == nullptr) {
			throw std::exception(SDL_GetError());
		}
	}

	Surface::Surface(Surface const & copy) {
		surface = SurfacePtr(SDL_ConvertSurface(copy.surface.get(), copy.surface->format, copy.surface->flags));
	}

	Surface::Surface(Surface && other) : surface(move(other.surface)) {
		other.surface = nullptr;
	}

	Surface & Surface::operator=(Surface const & other) {
		surface = SurfacePtr(SDL_ConvertSurface(other.surface.get(), other.surface->format, other.surface->flags));
		return *this;
	}

	Surface& Surface::operator=(Surface&& other) {
		if (this != &other) {
			/*
			if (surface != nullptr) {
				SDL_FreeSurface(surface);
			}
			*/
			std::swap(surface, other.surface);
		}
		return *this;
	}

	Surface::~Surface() {

		/*
		if (surface == nullptr) {
			std::cout << "Surface DTOR came across a surface with a nptr" << std::endl;
		} else if (surface->refcount < 0) {
			std::cout << "Surface DTOR came across a surface with negative ref cnt" << std::endl;
		} else {
			SDL_FreeSurface(surface.get());
		}
		*/
	}

	void Surface::fill(Uint32 const& color) {
		if (SDL_FillRect(surface.get(), NULL, color)) {
			throw std::exception(SDL_GetError());
		}
	}

	void Surface::blit(Surface const& other, GUI::Rectangle const& rect) const {
		SDL_Rect rectangle;
		rectangle.x = rect.x;
		rectangle.y = rect.y;
		rectangle.w = rect.w;
		rectangle.h = rect.h;
		SDL_BlitSurface(other.surface.get(), NULL, surface.get(), &rectangle);
		// SDL_BlitSurface(surface, NULL, other.get_surface(), &rectangle);
	}

	std::tuple<int, int> Surface::size() const {
		return std::make_tuple(surface->w, surface->h);
	}
	/*
	SDL_Surface * Surface::get_surface() const {
		return surface;
	}
	*/
}