#include "LayoutManager.h"

bool GUI::HorizontalLayout::draw(Surface const & surface, Rectangle const & rect) const {
	bool hasDrawn = false;
	unsigned int distributed = rect.w / m_children.size();
	int i = 0;
	for (auto &c : m_children) {
		Rectangle drawSpace(distributed, rect.h, rect.x + distributed * i, rect.y);
		i++;
		hasDrawn |= m_children.at(i)->draw(surface, drawSpace);
	}

	return hasDrawn;
}

void GUI::HorizontalLayout::add(std::shared_ptr<LayoutManager> layout, LayoutFlags const & lflags) {
	m_children.push_back(std::move(layout));
	// omit flags
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

void GUI::VerticalLayout::add(std::shared_ptr<LayoutManager> layout, LayoutFlags const & lflags) {
	m_children.push_back(std::move(layout));
}

GUI::VerticalLayout::~VerticalLayout() {
	// m_children.~vector();
}

GUI::PixelSpace::PixelSpace(int const & width, int const & height, Uint32 const & fill) {
	SDL_Surface* surf = SDL_CreateRGBSurface(0, 10, 10, 32,
									 0xff000000,
									 0x00ff0000,
									 0x0000ff00,
									 0x000000ff);
	m_surface = Surface(surf);
	m_surface.fill(fill);
}

bool GUI::PixelSpace::draw(Surface const & surface, Rectangle const & rect) const {
	surface.blit(m_surface, rect);

	return true;
}
