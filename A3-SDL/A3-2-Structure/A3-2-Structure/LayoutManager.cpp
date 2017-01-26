#include "LayoutManager.h"


tuple<int, int> GUI::LayoutMedian::preferredSize() const {
	return abstractSize([](shared_ptr<LayoutManager> x) { return x->preferredSize(); });
}

tuple<int, int> GUI::LayoutMedian::minimumSize() const {
	return abstractSize([](shared_ptr<LayoutManager> x) { return x->minimumSize(); });
}

tuple<int, int> GUI::LayoutMedian::abstractSize(
	function<tuple<int, int>(shared_ptr<LayoutManager> const&)> const& callback
) const {
	int x = 0;
	int y = 0;
	for (auto c : m_children) {
		auto aSize = callback(c);
		x += std::get<0>(aSize);
		y += std::get<1>(aSize);
	}
	return std::tuple<int, int>(x, y);
}

bool GUI::LayoutMedian::abstractDraw(
	Surface const& surface,
	Rectangle const& rect,
	function<Rectangle(int const& iter_cnt, shared_ptr<LayoutManager> const& element)> const& for_each_cb
) const  {
	bool hasDrawn = false;
	// welp, here are pre calculations
	int i = 0;
	for(auto c: m_children) {
		Rectangle rect = for_each_cb(i, c);
		hasDrawn |= c->draw(surface, rect);
		i++;
	}
	return hasDrawn;
}

void GUI::LayoutMedian::add(shared_ptr<LayoutManager> layout, Uint32 const& lflags) {
	m_children.push_back(std::move(layout));
}

