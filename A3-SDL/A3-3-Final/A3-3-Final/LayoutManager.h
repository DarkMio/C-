#pragma once

#include "Rectangle.h"
#include <memory>
#include <vector>
#include "Drawable.h"

/**
 * Stateless Positioning Tool
 * could probably even be class less
 */

using namespace std;

namespace GUI {

	class LayoutManager {
		public:
		virtual Rectangle next(Rectangle const& totalSpace, unsigned int count, unsigned int size) = 0;
		virtual void add(unique_ptr<LayoutManager> const& child) = 0;
		virtual bool draw(Surface const& surf, Rectangle const& rect) = 0;
		virtual ~LayoutManager() {};
	};

	class HorizontalLayout : public LayoutManager {
		Layout m_layout;
		vector<unique_ptr<LayoutManager>> m_children;
		public:
		explicit HorizontalLayout(Layout const& layout) { m_layout = layout; }
		virtual Rectangle next(Rectangle const& totalSpace, unsigned int count, unsigned int size) override {
			int chunkedSize = totalSpace.w / size;
			return Rectangle(chunkedSize, totalSpace.h, totalSpace.x + chunkedSize * count, totalSpace.y);
		}
		virtual void add(unique_ptr<LayoutManager> const& child) override {
			m_children.push_back(child);
		}

		virtual bool draw(Surface const& surf, Rectangle const& rect) override {
			bool retVal = false;
			retVal |= GUI::draw(m_layout, surf, rect);
			for(int i = 0; i < m_children.size(); i++) {
				retVal |= m_children[i]->draw(surf, next(rect, i, m_children.size()));
			}
			return retVal;
		}
	};

	class VerticalLayout : public LayoutManager {
		Layout m_layout;
		vector<unique_ptr<LayoutManager>> m_children;
		public:
		explicit VerticalLayout(Layout const& layout) { m_layout = layout; }
		virtual Rectangle next(Rectangle const& totalSpace, unsigned int count, unsigned int size) override {
			int chunkedSize = totalSpace.h / size;
			return Rectangle(totalSpace.w, chunkedSize, totalSpace.x, totalSpace.y + chunkedSize * count);
		}
		virtual void add(unique_ptr<LayoutManager> const& child) override {
			m_children.push_back(child);
		}
		virtual bool draw(Surface const& surf, Rectangle const& rect) override {
			bool retVal = false;
			retVal |= GUI::draw(m_layout, surf, rect);
			for (int i = 0; i < m_children.size(); i++) {
				retVal |= m_children[i]->draw(surf, next(rect, i, m_children.size()));
			}
			return retVal;
		}
	};

}