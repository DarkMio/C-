#include "Surface.h"

namespace SDL_Wrap {


	Surface::Surface() : Surface(640, 480) {}

	Surface::Surface(size_t const& width, size_t const& height) {
		m_surface = SurfacePtr(
			SDL_CreateRGBSurface(0, width, height, 32,
								 0xff000000,
								 0x00ff0000,
								 0x0000ff00,
								 0x000000ff)
		);
	}

	Surface::Surface(SDL_Surface* surf) {
		m_surface = SurfacePtr(surf);
	}

	Surface::Surface(string path) {
		char arr[1024];
		strcpy_s(arr, path.c_str());

		m_surface = SurfacePtr(SDL_LoadBMP(arr));
		if (m_surface == nullptr) {
			throw std::exception(SDL_GetError());
		}
	}

	Surface::Surface(SDL_Surface* src, GUI::Rectangle const& dstSize) {

		m_surface = SurfacePtr(SDL_CreateRGBSurface(src->flags, dstSize.w, dstSize.h, src->format->BitsPerPixel,
												 src->format->Rmask, src->format->Gmask, src->format->Bmask, src->format->Amask));

		double    _stretch_factor_x = (static_cast<double>(dstSize.w) / static_cast<double>(src->w)),
			_stretch_factor_y = (static_cast<double>(dstSize.h) / static_cast<double>(src->h));

		Uint32 *pixels = static_cast<Uint32 *>(m_surface->pixels); // get pixel array
		Uint32 *srcPxl = static_cast<Uint32 *>(src->pixels); // get pixel array


		auto ReadPixel = [=](Uint32 x, Uint32 y) -> Uint32 {
			return Sint32(srcPxl[(y * src->w) + x]);
		};

		auto DrawPixel = [=](SDL_Surface* surf, Uint32 x, Uint32 y, Uint32 color){
			pixels[(y * surf->w) + x] = color;
		};

		for (Uint32 y = 0; y < src->h; y++) {
			for (Uint32 x = 0; x < src->w; x++) {
				for (Uint32 o_y = 0; o_y < _stretch_factor_y; ++o_y) {
					for (Uint32 o_x = 0; o_x < _stretch_factor_x; ++o_x) {
						auto color = ReadPixel(x, y);
						DrawPixel(m_surface.get(),
								  Uint32(_stretch_factor_x * x) + o_x,
								  Uint32(_stretch_factor_y * y) + o_y,
								  color
						);
					}
				}
			}
		}
	}

	Surface::Surface(Surface const & copy) {
		m_surface = SurfacePtr(SDL_ConvertSurface(copy.m_surface.get(), copy.m_surface->format, copy.m_surface->flags));
	}

	Surface::Surface(Surface && other) : m_surface(move(other.m_surface)) {
		other.m_surface = nullptr;
	}

	Surface & Surface::operator=(Surface const & other) {
		m_surface = SurfacePtr(SDL_ConvertSurface(other.m_surface.get(), other.m_surface->format, other.m_surface->flags));
		return *this;
	}

	Surface& Surface::operator=(Surface&& other) {
		if (this != &other) {
			/*
			if (m_surface != nullptr) {
			SDL_FreeSurface(m_surface);
			}
			*/
			std::swap(m_surface, other.m_surface);
		}
		return *this;
	}

	Surface::~Surface() {

		/*
		if (m_surface == nullptr) {
		std::cout << "Surface DTOR came across a m_surface with a nptr" << std::endl;
		} else if (m_surface->refcount < 0) {
		std::cout << "Surface DTOR came across a m_surface with negative ref cnt" << std::endl;
		} else {
		SDL_FreeSurface(m_surface.get());
		}
		*/
	}

	void Surface::fill(Uint32 const& color) {
		if (SDL_FillRect(m_surface.get(), NULL, color)) {
			throw std::exception(SDL_GetError());
		}
	}

	void Surface::blit(Surface const& other, GUI::Rectangle const& rect) const {
		SDL_Rect rectangle;
		rectangle.x = rect.x;
		rectangle.y = rect.y;
		rectangle.w = rect.w;
		rectangle.h = rect.h;
		SDL_BlitSurface(other.m_surface.get(), NULL, m_surface.get(), &rectangle);
		// SDL_BlitSurface(m_surface, NULL, other.get_surface(), &rectangle);
	}

	std::tuple<int, int> Surface::size() const {
		return std::make_tuple(m_surface->w, m_surface->h);
	}

	SDL_Surface* Surface::get_surface() const {
		return m_surface.get();
	}

}