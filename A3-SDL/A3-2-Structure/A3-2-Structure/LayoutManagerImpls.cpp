#include "LayoutManagerImpls.h"

bool GUI::HorizontalLayout::draw(Surface const& surface, Rectangle const& rect) const {
	int allocated_space = rect.w / m_children.size();
	return abstractDraw(surface, rect,
		[&rect, &allocated_space](int const& iter_cnt, auto const& current_element) {
			return Rectangle(allocated_space, rect.h, rect.x + allocated_space * iter_cnt, rect.y);
		}
	);
}

bool GUI::VerticalLayout::draw(Surface const & surface, Rectangle const & rect) const {
	int allocated_space = rect.h / m_children.size();
	return abstractDraw(surface, rect,
		[&rect, &allocated_space](int const& iter_cnt, auto const& current_element) {
			return Rectangle(rect.w, allocated_space, rect.x, rect.y + allocated_space * iter_cnt);
		}
	);
}

std::tuple<int, int> GUI::PixelSpace::preferredSize() const {
	return m_surface.size();
}

std::tuple<int, int> GUI::PixelSpace::minimumSize() const {
	return m_surface.size();
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

bool GUI::HorizontalCloseLayout::draw(Surface const & surface, Rectangle const & rect) const {
	int used_width = 0;
	return abstractDraw(surface, rect,
	[&rect, &used_width](int const& iter_cnt, auto const& element) {
		int child_x = std::get<0>(element->preferredSize());
		Rectangle x = Rectangle(child_x, rect.h, used_width, rect.y);
		used_width += child_x;
		return x;
	}
	);
}