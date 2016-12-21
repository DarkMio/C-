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
