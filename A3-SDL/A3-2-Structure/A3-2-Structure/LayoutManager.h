#pragma once

#include "Rectangle.h"
#include "Surface.h"
#include <vector>
#include <exception>
#include <memory>
#include <functional>

using namespace SDL_Wrap;
using namespace std;

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
		virtual tuple<int, int> preferredSize() const = 0;
		virtual tuple<int, int> minimumSize() const = 0;
		virtual bool draw(Surface const& surface, Rectangle const& rect) const = 0;
		virtual void add(shared_ptr<LayoutManager> layout, Uint32 const& lflags) = 0; 
		virtual ~LayoutManager() {};
	};

	class LayoutMedian : public LayoutManager {
		protected:
		vector<shared_ptr<LayoutManager>> m_children;
		virtual tuple<int, int> abstractSize(function<tuple<int, int>(shared_ptr<LayoutManager> const&)> const& callback) const;
		virtual bool abstractDraw(Surface const& surface, Rectangle const& rect, function<Rectangle(int const&, shared_ptr<LayoutManager> const&)> const&) const;
		public:
		virtual tuple<int, int> preferredSize() const;
		virtual tuple<int, int> minimumSize() const;
		virtual void add(shared_ptr<LayoutManager> layout, Uint32 const& lflags);
	};
}