#pragma once

#include "IDrawable.h"
#include "Surface.h"
#include "GUIUtility.h"
#include "LayoutManager.h"
#include <vector>
#include <tuple>
#include <iostream>
#include <exception>


/**
	Here comes a reimagination:

	A Canvas can hold N Children
	A Canvas tells children the (maximum) size
	A Canvas generally has the desire to hit its maximum size - unless it has a smaller preferred size
	A Canvas has a state in which it spaces its Children (topleft, botright, spaced, distributed)
	A Canvas should contain a draw() method that is virtual
	A Canvas contains a layout by default

	A PixelCanvas has no children and derives from Canvas
	A PixelCanvas can have Callbacks while a Canvas cannot
	A PixelCanvas contains a Surface
	  - > to update the main application surface it throws this surface downwards to blit downwards
	      (therefore draw(Surface const& surface) down the chain)
	  - > a canvas might be able to upstream (Surface& draw())

	A Layout is more or less a helper object of a Canvas
	A Layout manages the size/offset calculation of a canvas
	A Canvas asks a Layout where it should place any child canvas
	  + - > This means that each canvas CAN have an actual size and gets set a maximum size
	  
	Tidbits:
			- Layouting could allow resizing, which would mean that either a layout calculates each frame
			  or on callbacks from SDL
*/
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

namespace GUI {
	class Canvas {
		private:
		ILayoutManager m_lmgr;
		public:
		Canvas() = delete;
		Canvas(size_t const& width, size_t const& height, ILayoutManager lmgr);
		std::tuple<int, int> size() const;
		bool draw(Surface const& surface, Rectangle const& rect); // downstream
		void add(Canvas const& canvas, LayoutFlags const& lflgs); // adding a new canvas element
		~Canvas();
	};

	class PixelCanvas : Canvas {
		private:
		Surface m_surface;
		std::tuple<int, int> m_size;
		public:
		PixelCanvas();
		PixelCanvas(size_t const& width, size_t const& height, ILayoutManager lmgr, LayoutFlags lflgs);
		PixelCanvas(char* imagePath);
		PixelCanvas(size_t const& width, size_t const& height);
		std::tuple<int, int> size() const;
		bool draw(Surface const& surface, Rectangle const& rect);
		void add(Canvas const& canvas, LayoutFlags lflgs);
	};
}

