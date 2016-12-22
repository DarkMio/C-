#include "Canvas.h"



Canvas::Canvas() : m_surface() {}

Canvas::Canvas(SDL_Surface * surface) : m_surface(surface) {}

Canvas::Canvas(size_t const& width, size_t const& height) : m_surface(width, height) {}

std::tuple<int, int> Canvas::size() {
	return m_surface.size();
}

void Canvas::update() { 
	m_updateHandler();
}

void Canvas::setUpdateHandler(std::function<void()> const& handler) {
	m_updateHandler = handler;
}

Canvas::~Canvas() {}


namespace GUI {
	Canvas::Canvas(
		size_t const& width, size_t const& height,
		LayoutManager lmgr
	) : m_lmgr(lmgr) {};
	std::tuple<int, int> Canvas::size() const { return m_lmgr.size(); }
	bool Canvas::draw(Surface const& surface, Rectangle const& rect) { 
		return false | m_lmgr.draw();
	};
	void Canvas::add(Canvas const& canvas, LayoutFlags const& lflgs) {
		m_lmgr.add(canvas, lflgs);
	};
	Canvas::~Canvas() {};

	// ----

	PixelCanvas::PixelCanvas(){};
	PixelCanvas::PixelCanvas(size_t const& width, size_t const& height, LayoutManager lmgr, LayoutFlags lflgs) = 0;
	PixelCanvas::PixelCanvas(char* imagePath) : m_surface(imagePath) {	}
	PixelCanvas::PixelCanvas(size_t const& width, size_t const& height) : m_surface(width, height) {};
	std::tuple<int, int> PixelCanvas::size() const {
		return m_surface.size();
	};
	bool PixelCanvas::draw(Surface const& surface, Rectangle const& rect) {
		m_surface.blit(surface, rect);
		return true;
	}
	void PixelCanvas::add(Canvas const& canvas, LayoutFlags lflgs) {
		std::cout << "Illegal: A PixelCanvas cannot have any children!" << std::endl;
		throw Exception("A PixelCanvas cannot have any children!");
	}

}