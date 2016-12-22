#include <SDL.h>
#include <exception>
#include <tuple>
#include "GUIUtility.h"

#pragma once
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
	void blit(Surface const& other, GUI::Rectangle const& rect);
	std::tuple<int, int> size();
	SDL_Surface* get_surface() const;
};

