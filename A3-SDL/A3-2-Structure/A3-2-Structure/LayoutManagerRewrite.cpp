
std::tuple<int, int> GUI::LayoutMedian::preferredSize() const {
	collectedSize([auto x]{return x->preferredSize();});
}

std::tuple<int, int> GUI::LayoutMedian::minimumSize() const {
	collectedSize([auto x]{return x->minimumSize();});
}

std::tuple<int, int> GUI::LayoutMedian::collectedSize(
	std::function<std::tuple<int, int>(std::shared_ptr<LayoutManager>)> callback) const {
	int x = 0;
	int y = 0;
	for(auto &c: m_children) {
		auto aSize = callback(c);
		x += std::get<0>(aSize);
		y += std::get<1>(aSize);
	}
	return std::tuple<int, int>(x, y);
}

bool GUI::LayoutMedian::abstractDraw(
	Surface const& surface,
	Rectangle const& rect,
	std::function<int(Rectangle, int)> spaceCalculator,
	std::function<Rectangle(int, Rectangle, int)> rectFactory
	) const {
	bool hasDrawn = false;
	int allocedSpace = spaceCalculator(rect, m_children.size());
	int i = 0;
	for(auto &c : m_children) {
		Rectangle drawSpace = rectFactory(i, rect, allocedSpace);
		hasDrawn |= m_children[i].draw(surface, drawSpace);
		i++;
	}
	return hasDrawn;
}

bool GUI::LayoutMedian::add(std::shared_ptr<LayoutManager> layout, Uint32 const& flags) {
	m_children.push(std::move(layout));
}

