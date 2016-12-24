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
		virtual std::tuple<int, int> preferredSize() const = 0;
		virtual std::tuple<int, int> minimumSize() const = 0;
		virtual bool draw(Surface const& surface, Rectangle const& rect) const = 0;
		virtual void add(std::shared_ptr<LayoutManager> layout, Uint32 const& lflags) = 0;
		virtual ~LayoutManager() {};
	};
}