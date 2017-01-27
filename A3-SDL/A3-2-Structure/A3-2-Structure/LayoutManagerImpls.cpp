#include "LayoutManagerImpls.h"

bool GUI::HorizontalLayout::draw(Surface const& surface, Rectangle const& rect) const {
	int allocated_space = rect.w / m_children.size();
	return abstractDraw(surface, rect,
		[&rect, &allocated_space](int const& iter_cnt, auto const& current_element) {
			auto pos = current_element->preferredSize();
			return Rectangle(std::get<0>(pos), std::get<1>(pos), rect.x + allocated_space * iter_cnt, rect.y);
		}
	);
}

bool GUI::VerticalLayout::draw(Surface const & surface, Rectangle const & rect) const {
	int allocated_space = rect.h / m_children.size();
	return abstractDraw(surface, rect,
		[&rect, &allocated_space](int const& iter_cnt, auto const& current_element) {
			auto pos = current_element->preferredSize();
			return Rectangle(std::get<0>(pos), std::get<1>(pos), rect.x, rect.y + allocated_space * iter_cnt);
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
	old_x = -1;
	old_y = -1;
	m_color = 0xFFFFFFFF;
}

bool GUI::PixelSpace::draw(Surface const & surface, Rectangle const & rect) const {
	m_dirty |= m_last_pos.h != rect.h || m_last_pos.w != rect.w || m_last_pos.x != rect.x || m_last_pos.y != rect.y;

	if (m_dirty) {
		m_last_pos = rect;
		surface.blit(m_surface, rect);
		m_dirty = false;
		return true;
	}
	return false;
}

void GUI::PixelSpace::add(std::shared_ptr<LayoutManager> layout, Uint32 const & lflags) {
	throw std::exception("Pixel Space may never have children.");
}

bool GUI::PixelSpace::setup_eventlistener(EventManager& e_mgr) {
	auto set_pixel = [=](int nx, int ny, Uint32 color) {
		Surface x(1, 1);
		x.fill(color);
		m_surface.blit(x, Rectangle(1, 1, nx, ny));
		m_dirty |= true;
	};

	e_mgr.subscribe(SDL_MOUSEMOTION, [=](SDL_Event const& event) {
		// this is the absolute position

		auto x = event.motion.x;
		auto y = event.motion.y;

		if (!(x >= m_last_pos.x && x <= m_last_pos.x + m_last_pos.w && y >= m_last_pos.y && y <= m_last_pos.y + m_last_pos.h)) {
			old_x = -1;
			old_y = -1;
			return false;
		}

		// and now relative positions
		x -= m_last_pos.x;
		y -= m_last_pos.y;


		if (old_x == -1 || old_y == -1) {
			old_x = x;
			old_y = y;
		}

		auto distance = std::sqrt(std::pow(old_x - x, 2) + std::pow(old_y - y, 2));
		auto frac = 1.f / distance;

		for (int i = 0; i < distance; i++) {
			auto nx = old_x + (x - old_x) * (frac * i);
			auto ny = old_y + (y - old_y) * (frac * i);
			set_pixel(nx, ny, m_color);
		}

		old_x = x;
		old_y = y;
		return true;
	});

	e_mgr.subscribe(SDL_MOUSEBUTTONDOWN, [=](SDL_Event const& event) {
		if (event.button.button == SDL_BUTTON_RIGHT) {
			m_color = 0;
			for (int i = 8; i < 32; i += 8) {
				int random = std::rand();
				random &= 0xFF;
				random = random << i;
				m_color |= random;
			}
			m_color |= 0x000000FF;
		}
		return false;
	});



	return true;
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

bool GUI::VerticalCloseLayout::draw(Surface const& surface, Rectangle const& rect) const {
	int used_height = 0;
	return abstractDraw(surface, rect,
						[&rect, &used_height](int const& iter_cnt, auto const& element)
	{
		int child_y = std::get<1>(element->preferredSize());
		Rectangle y = Rectangle(rect.w, child_y, rect.x, used_height);
		used_height += child_y;
		return y;
	}
	);

}
