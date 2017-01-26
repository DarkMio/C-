#pragma once

#include <memory>
#include <iostream>
#include <vector>
#include <functional>
#include <tuple>
#include "Surface.h"
#include "Rectangle.h"

using namespace std;
using namespace SDL_Wrap;

namespace GUI {
	template<typename T>
	bool draw(T const& x, Surface const& surface, Rectangle const& rect) {
		x.draw(surface, rect);
	}

	template<typename T>
	tuple<int, int> minimumSize(T const& x) {
		return x.minimumSize();
	}

	template<typename T>
	tuple<int, int> preferredSize(T const& x) {
		return x.preferredSize();
	}

	class Drawable {
		public:
		template<typename T>
		Drawable(T x) : p_(make_shared<Model<T>>(move(x))) {};

		friend tuple<int, int> preferredSize(Drawable const& x) {
			return x.p_->preferredSize_();
		}

		friend tuple<int, int> minimumSize(Drawable const& x) {
			return x.p_->minimumSize_();
		}

		friend bool draw(Drawable const& x, Surface const& surface, Rectangle const& rect) {
			return x.p_->draw_(surface, rect);
		}

		private:

		struct Concept {
			virtual ~Concept() = default;
			virtual tuple<int, int> preferredSize_() const = 0;
			virtual tuple<int, int> minimumSize_() const = 0;
			virtual bool draw_(SDL_Wrap::Surface const& surface, GUI::Rectangle const& rect) const = 0;
		};

		template<typename T>
		struct Model : Concept {
			Model(T x) : data_(move(x)) {}
			tuple<int, int> preferredSize_() const override { return preferredSize(data_); }
			tuple<int, int> minimumSize_() const override { return minimumSize(data_); }
			bool draw_(Surface const& surface, Rectangle const& rect) const override { return draw(data_, surface, rect); }

			T data_;
		};

		shared_ptr<Concept> p_;
	};

	using Layout = vector<Drawable>;

	inline bool draw(Layout const& x, Surface const& surface, Rectangle const& rect) {
		bool retVal = false;
		for (Drawable const& element : x) {
			retVal |= draw(element, surface, rect);
		}
		return retVal;
	};

	inline tuple<int, int> minimumSize(Layout const& layout) {
		int x = 0;
		int y = 0;
		for (auto const& c : layout) {
			auto size = minimumSize(c);
			x += std::get<0>(size);
			y += std::get<1>(size);
		}
		return tuple<int, int>(x, y);
	}

	inline tuple<int, int> preferredSize(Layout const& layout) {
		int x = 0;
		int y = 0;
		for (auto const& c : layout) {
			auto size = minimumSize(c);
			x += std::get<0>(size);
			y += std::get<1>(size);
		}
		return tuple<int, int>(x, y);
	}

	/*-
	class ManagedLayout {
		protected:
		vector<Layout> m_layout;
		function<Rectangle (Rectangle const&, int const&, int const&)> next;
		public:
		ManagedLayout() = delete;
		ManagedLayout(Layout const& layout, function<Rectangle(Rectangle const&, int const&, int const&)> const& func) : m_layout(layout), next(func) {}


		inline friend bool draw(ManagedLayout const& x, Surface const& surface, Rectangle const& rect) {
			bool retVal = false;
			for (int i = 0; i < x.m_layout.size(); i++) {
				retVal |= draw(x.m_layout[i], surface, x.next(rect, i, x.m_layout.size()));
			}
			return retVal;
		}

		inline friend tuple<int, int> minimumSize(ManagedLayout const& layout) {
			minimumSize(layout.m_layout);
		}
		inline friend tuple<int, int> preferredSize(ManagedLayout const& layout) {
			preferredSize(layout.m_layout);
		}
	};
	/*
	using ManagedLayout = tuple<Layout, unique_ptr<LayoutManager>>;
	inline bool draw(ManagedLayout const& x, Surface const& surface, Rectangle const& rect) {
		bool retVal = false;
		for(int i = 0; i < get<0>(x).size(); i++) {
			retVal |= draw(get<0>(x)[i], surface, get<1>(x)->next(rect, i, get<0>(x).size()));
		}
		return retVal;
	}
	inline tuple<int, int> minimumSize(ManagedLayout const& layout) {
		minimumSize(get<0>(layout));
	}
	inline tuple<int, int> preferredSize(ManagedLayout const& layout) {
		preferredSize(get<0>(layout));
	}
	*/
	class PixelSpace {
		private:
		Surface m_surface;
		tuple<int, int> m_minSize;
		bool mutable m_dirty;
		public:
		PixelSpace() = delete;
		PixelSpace(int const& width, int const& height, Uint32 const& fill) {
			SDL_Surface* surf = SDL_CreateRGBSurface(0, width, height, 32,
													 0xff000000,
													 0x00ff0000,
													 0x0000ff00,
													 0x000000ff);
			m_surface = Surface(move(surf));
			m_surface.fill(fill);
			m_minSize = tuple<int, int>(width, height);
			m_dirty = true;
		}

		friend inline tuple<int, int> minimumSize(PixelSpace const& pixel) {
			return pixel.m_minSize;
		}

		friend inline tuple<int, int> preferredSize(PixelSpace const& pixel) {
			return pixel.m_minSize;
		}

		friend inline bool draw(PixelSpace const& pixel, Surface const& surface, Rectangle const& rect) {
			if (pixel.m_dirty) {
				surface.blit(pixel.m_surface, rect);
				pixel.m_dirty = false;
				return true;
			}
			return false;
		}
	};

	
}