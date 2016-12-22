#pragma once

#include "Rectangle.h"
#include "Surface.h"
#include "Canvas.h"
#include <vector>
#include <exception>
#include <memory>

using namespace SDL_Wrap;

namespace GUI {
	enum LayoutFlags {
		default = 0,
		topright = 1 << 0,
		botleft = 1 << 1,
		spaced = 1 << 2,
		distributed = 1 << 3
	};

	class LayoutManager {
		public:
		virtual bool draw(Surface const& surface, Rectangle const& rect) const = 0;
		virtual void add(std::shared_ptr<LayoutManager> layout, LayoutFlags const& lflags) = 0;
		virtual ~LayoutManager() {};
	};

	class HorizontalLayout : public LayoutManager {
		private:
		std::vector<std::shared_ptr<LayoutManager>> m_children;
		public:
		virtual bool draw(Surface const& surface, Rectangle const& rect) const override;
		virtual void add(std::shared_ptr<LayoutManager> layout, LayoutFlags const& lflags) override;
		virtual ~HorizontalLayout() {
			// m_children.~vector();
		};
	};

	class VerticalLayout : public LayoutManager {
		private:
		std::vector<std::shared_ptr<LayoutManager>> m_children;
		public:
		virtual bool draw(Surface const& surface, Rectangle const& rect) const override;
		virtual void add(std::shared_ptr<LayoutManager> layout, LayoutFlags const& lflags) override;
		virtual ~VerticalLayout();
	};

	class PixelSpace : public LayoutManager {
		private:
		Surface m_surface;
		public:
		PixelSpace() = delete;
		PixelSpace(int const& width, int const& height, Uint32 const& fill);
		virtual bool draw(Surface const& surface, Rectangle const& rect) const override;
		virtual void add(std::shared_ptr<LayoutManager> layout, LayoutFlags const& lflags) {
			throw std::exception("Pixel Space may never have children.");
		}
		virtual ~PixelSpace() {
			// m_surface.~Surface();
		}
	};
}