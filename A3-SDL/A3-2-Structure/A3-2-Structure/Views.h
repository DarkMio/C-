#pragma once
#include "LayoutManager.h"
#include <memory>
#include "LayoutManagerImpls.h"

using namespace GUI;
using namespace std;

namespace Views {
	inline Uint32 randomColor() {
		Uint32 color = 0xFF;
		color |= rand() << 8;
		color |= rand() << 16;
		color |= rand() << 24;
		return color;
	}

	inline shared_ptr<LayoutManager> buildButtonRow() {
		auto layout = make_shared<HorizontalLayout>();

		layout->add(make_shared<PixelSpace>(35, 35, randomColor()), 0);
		layout->add(make_shared<PixelSpace>(35, 35, randomColor()), 0);
		layout->add(make_shared<PixelSpace>(35, 35, randomColor()), 0);
		return layout;
	}

	class ButtonsView : public VerticalCloseLayout {
		protected:
		Rectangle m_size;

		public:

		ButtonsView() = delete;
		explicit ButtonsView(Rectangle const& size) : m_size(size) {
			m_children.push_back(buildButtonRow());
			m_children.push_back(buildButtonRow());
			m_children.push_back(make_shared<PixelSpace>(120, 120, randomColor()));
		}
		virtual tuple<int, int> minimumSize() const override {
			return make_tuple(m_size.w, m_size.h);
		}
		virtual tuple<int, int> preferredSize() const override {
			return make_tuple(m_size.w, m_size.h);
		}

		virtual void add(shared_ptr<LayoutManager> layout, Uint32 const& lflags) override {
			cout << "Adding to ButtonsView is not allowed." << endl;
		};

	};

	class Button : public PixelSpace {
		
	};

}

