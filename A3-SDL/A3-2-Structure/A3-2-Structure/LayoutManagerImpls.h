#pragma once

#include "LayoutManager.h"
#include "EventManager.h"
#include <SDL_events.h>

namespace GUI {

	class HorizontalLayout : public LayoutMedian {
		public:
		virtual bool draw(Surface const& surface, Rectangle const& rect) const override;
	};

	class VerticalLayout : public LayoutMedian {
		public:
		virtual bool draw(Surface const& surface, Rectangle const& rect) const override;
	};

	class HorizontalCloseLayout : public HorizontalLayout {
		public:
		virtual bool draw(Surface const& surface, Rectangle const& rect) const override;
	};

	class VerticalCloseLayout : public VerticalLayout {
		public:
		virtual bool draw(Surface const& surface, Rectangle const& rect) const override;
	};

	class PixelSpace : public LayoutManager {
		private:
		Surface m_surface;
		std::tuple<int, int> m_minSize;
		mutable bool m_dirty;
		int old_x;
		int old_y;
		Uint32 m_color;
		mutable Rectangle m_last_pos;
		public:
		virtual std::tuple<int, int> preferredSize() const override;
		virtual std::tuple<int, int> minimumSize() const override;
		PixelSpace() = delete;
		PixelSpace(int const& width, int const& height, Uint32 const& fill);
		virtual bool draw(Surface const& surface, Rectangle const& rect) const override;
		virtual void add(std::shared_ptr<LayoutManager> layout, Uint32 const& lflags) override;
		virtual bool setup_eventlistener(EventManager& e_mgr);
	};
}