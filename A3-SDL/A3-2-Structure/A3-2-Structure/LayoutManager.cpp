#include "LayoutManager.h"


tuple<int, int> GUI::LayoutMedian::preferredSize() const {
	return abstractSize([](shared_ptr<LayoutManager> x) { return x->preferredSize(); });
}

tuple<int, int> GUI::LayoutMedian::minimumSize() const {
	return abstractSize([](shared_ptr<LayoutManager> x) { return x->minimumSize(); });
}

tuple<int, int> GUI::LayoutMedian::abstractSize(
	function<tuple<int, int>(shared_ptr<LayoutManager>)> const& callback) const {
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
	function<int(Rectangle, int)> const& spaceCalculator,
	function<Rectangle(int, Rectangle, int)> const& rectFactory
	) const {
	bool hasDrawn = false;
	int allocedSpace = spaceCalculator(rect, m_children.size());
	int i = 0;
	for (auto c : m_children) {
		Rectangle drawSpace = rectFactory(i, rect, allocedSpace);
		hasDrawn |= m_children[i]->draw(surface, drawSpace);
		i++;
	}
	return hasDrawn;
}

void GUI::LayoutMedian::add(shared_ptr<LayoutManager> layout, Uint32 const& lflags) {
	m_children.push_back(std::move(layout));
}

