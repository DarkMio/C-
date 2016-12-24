#include "LayoutManagerImpls.h"

std::tuple<int, int> GUI::HorizontalLayout::preferredSize() const {
	int x = 0;
	int y = 0;
	for (auto c : m_children) {
		auto prefSize = c->preferredSize();
		x += std::get<0>(prefSize);
		y += std::get<1>(prefSize);
	}
	return std::tuple<int, int>(x, y);
}

std::tuple<int, int> GUI::HorizontalLayout::minimumSize() const {
	int x = 0;
	int y = 0;
	for (auto c : m_children) {
		auto minSize = c->minimumSize();
		x += std::get<0>(minSize);
		y += std::get<1>(minSize);
	}
	return std::tuple<int, int>(x, y);
}

bool GUI::HorizontalLayout::draw(Surface const & surface, Rectangle const & rect) const {
	bool hasDrawn = false;
	unsigned int distributed = rect.w / m_children.size();
	int i = 0;
	for (auto &c : m_children) {
		Rectangle drawSpace(distributed, rect.h, rect.x + distributed * i, rect.y);
		hasDrawn |= m_children[i]->draw(surface, drawSpace);
		i++;
	}

	return hasDrawn;
}

void GUI::HorizontalLayout::add(std::shared_ptr<LayoutManager> layout, Uint32 const & lflags) {
	m_children.push_back(std::move(layout));
	// omit flags
}

GUI::HorizontalLayout::~HorizontalLayout() {}

std::tuple<int, int> GUI::VerticalLayout::preferredSize() const {
	int x = 0;
	int y = 0;
	for (auto c : m_children) {
		auto prefSize = c->preferredSize();
		x += std::get<0>(prefSize);
		y += std::get<1>(prefSize);
	}
	return std::tuple<int, int>(x, y);
}

std::tuple<int, int> GUI::VerticalLayout::minimumSize() const {
	int x = 0;
	int y = 0;
	for (auto c : m_children) {
		auto minSize = c->minimumSize();
		x += std::get<0>(minSize);
		y += std::get<1>(minSize);
	}
	return std::tuple<int, int>(x, y);
}

bool GUI::VerticalLayout::draw(Surface const & surface, Rectangle const & rect) const {
	bool hasDrawn = false;
	unsigned int distributed = rect.h / m_children.size();
	int i = 0;
	for (auto& c : m_children) {
		Rectangle drawSpace(rect.w, distributed, rect.x, rect.y + distributed * i);
		hasDrawn |= m_children[i]->draw(surface, drawSpace);
		i++;
	}

	return hasDrawn;
}

void GUI::VerticalLayout::add(std::shared_ptr<LayoutManager> layout, Uint32 const & lflags) {
	m_children.push_back(std::move(layout));
}

GUI::VerticalLayout::~VerticalLayout() {
	// m_children.~vector();
}

std::tuple<int, int> GUI::PixelSpace::preferredSize() const {
	return m_minSize;
}

std::tuple<int, int> GUI::PixelSpace::minimumSize() const {
	return m_minSize;
}

GUI::PixelSpace::PixelSpace(int const & width, int const & height, Uint32 const & fill) {
	SDL_Surface* surf = SDL_CreateRGBSurface(0, width, height, 32,
											 0xff000000,
											 0x00ff0000,
											 0x0000ff00,
											 0x000000ff);
	m_surface = Surface(surf);
	m_surface.fill(fill);
	m_minSize = std::tuple<int, int>(width, height);
	m_dirty = true;
}

bool GUI::PixelSpace::draw(Surface const & surface, Rectangle const & rect) const {
	if (m_dirty) {
		surface.blit(m_surface, rect);
		m_dirty = false;
		return true;
	}
	return false;
}

void GUI::PixelSpace::add(std::shared_ptr<LayoutManager> layout, Uint32 const & lflags) {
	throw std::exception("Pixel Space may never have children.");
}

GUI::PixelSpace::~PixelSpace() {}

std::tuple<int, int> GUI::HorizontalCloseLayout::preferredSize() const {
	int x = 0;
	int y = 0;
	for (auto c : m_children) {
		auto prefSize = c->preferredSize();
		x += std::get<0>(prefSize);
		y += std::get<1>(prefSize);
	}
	return std::tuple<int, int>(x, y);
}

std::tuple<int, int> GUI::HorizontalCloseLayout::minimumSize() const {
	int x = 0;
	int y = 0;
	for (auto c : m_children) {
		auto minSize = c->minimumSize();
		x += std::get<0>(minSize);
		y += std::get<1>(minSize);
	}
	return std::tuple<int, int>(x, y);
}

bool GUI::HorizontalCloseLayout::draw(Surface const & surface, Rectangle const & rect) const {
	bool hasDrawn = false;
	int usedWidth = 0;
	for (auto c : m_children) {
		int child_x = std::get<0>(c->preferredSize());
		hasDrawn |= c->draw(surface, Rectangle(child_x, rect.h, usedWidth, rect.y));
		usedWidth += child_x;
	}
	return hasDrawn;
}

void GUI::HorizontalCloseLayout::add(std::shared_ptr<LayoutManager> layout, Uint32 const & lflags) {
	m_children.push_back(layout);
}

GUI::HorizontalCloseLayout::~HorizontalCloseLayout() {}
