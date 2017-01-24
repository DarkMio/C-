#pragma once

#include <memory>
#include <tuple>
#include <SDL.h>
#include "Rectangle.h"
#include <iostream>

using namespace std;

namespace SDL_Wrap {
	struct SDL_Deleter {
		void operator()(SDL_Surface*  ptr) { if (ptr) SDL_FreeSurface(ptr); }
		void operator()(SDL_Texture*  ptr) { if (ptr) SDL_DestroyTexture(ptr); }
		void operator()(SDL_Renderer* ptr) { if (ptr) SDL_DestroyRenderer(ptr); }
		void operator()(SDL_Window*   ptr) { if (ptr) SDL_DestroyWindow(ptr); }
		void operator()(SDL_RWops*    ptr) { if (ptr) SDL_RWclose(ptr); }
	};

	using SurfacePtr = std::unique_ptr<SDL_Surface, SDL_Deleter>;
	using TexturePtr = std::unique_ptr<SDL_Texture, SDL_Deleter>;
	using RendererPtr = std::unique_ptr<SDL_Renderer, SDL_Deleter>;
	using WindowPtr = std::unique_ptr<SDL_Window, SDL_Deleter>;
	using RWopsPtr = std::unique_ptr<SDL_RWops, SDL_Deleter>;

	class Surface {
		SurfacePtr surface;
		public:
		Surface();
		Surface(size_t const& width, size_t const& height);
		Surface(SDL_Surface* surf);
		Surface(char* path);
		Surface(Surface const& copy); // Copy Constructor
		Surface(Surface&& other); // Move Constructor
		Surface& operator=(Surface const& other); // Copy Assignment
		Surface& operator=(Surface&& other); // Move Assignment
		~Surface();
		void fill(Uint32 const&);
		void blit(Surface const& other, GUI::Rectangle const& rect) const;
		std::tuple<int, int> size() const;
		// SDL_Surface* get_surface() const;
	};
}
