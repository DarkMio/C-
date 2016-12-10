#include <SDL.h>
#include <exception>
#include <tuple>

#pragma once
class Surface {
	SDL_Surface* surface;
	public:
	Surface();
	Surface(SDL_Surface* surf);
	Surface(char* path);
	Surface(Surface const& copy) = delete; // Disable Copy Constructor
	Surface(Surface&& other); // Move Constructor
	Surface& operator=(Surface const& other); // Copy Assignment
	Surface& operator=(Surface&& other); // Move Assignment
	~Surface();
	void fill(Uint32 const&);
	std::tuple<int, int> size();
	SDL_Surface* get_surface() const;
};

