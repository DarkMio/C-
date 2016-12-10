#include <SDL.h>
#include <exception>

#pragma once
class Surface {
	SDL_Surface* surface;
	public:
	Surface();
	Surface(SDL_Surface* surf);
	Surface(char* path);
	~Surface();
	void fill(Uint32 const&);
	int* size();
	SDL_Surface* get_surface() const;
};

