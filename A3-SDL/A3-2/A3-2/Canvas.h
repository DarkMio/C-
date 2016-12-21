#include "IDrawable.h"
#include "Surface.h"

#pragma once
/// <summary>
/// A Canvas manages multiple child elements.
/// </summary>
/// <seealso cref="IDrawable" />
class Canvas : IDrawable {
	private:
	Surface m_surface;
	std::function<void()> m_updateHandler;
	public:
	Canvas();
	Canvas(SDL_Surface*);
	Canvas(size_t const& width, size_t const& height);
	std::tuple<int, int> size();
	void update();
	void setUpdateHandler(std::function<void()> const&);
	~Canvas();
};

