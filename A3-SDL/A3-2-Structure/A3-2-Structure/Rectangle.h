#pragma once

namespace GUI {
	class Rectangle {
		public:
		unsigned int x, y, w, h;
		Rectangle();
		Rectangle(
			unsigned int const& width,
			unsigned int const& height,
			unsigned int const& x,
			unsigned int const& y
		);
		~Rectangle();
	};
}
