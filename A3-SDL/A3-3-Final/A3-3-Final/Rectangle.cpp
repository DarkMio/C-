#include "Rectangle.h"

namespace GUI {
	Rectangle::Rectangle() {}

	Rectangle::Rectangle(
		unsigned int const& width,
		unsigned int const& height,
		unsigned int const& x,
		unsigned int const& y
	) : w(width), h(height), x(x), y(y) {};

	Rectangle::~Rectangle() {}
}