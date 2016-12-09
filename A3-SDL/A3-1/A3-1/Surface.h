#include <SDL.h>
#include <exception>

#pragma once
class Surface {
	SDL_Surface* surface;
	public:
	Surface();
	Surface(SDL_Surface* surf);
	~Surface();
	void fill(Uint32 const&);
	int* size();
};

