#pragma once

#include <tuple>
#include <SDL.h>
#include "Rectangle.h"
#include <iostream>

namespace SDL_Wrap {
	class Surface {
		SDL_Surface* surface;
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
		std::tuple<int, int> size();
		SDL_Surface* get_surface() const;
	};
}
