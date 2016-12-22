#pragma once

namespace GUI {
    class Rectangle {
        public:
        size_t w, h, x, y;
        Rectangle(size_t const& width, size_t const& height, size_t const& x, size_t const& y);
        ~Rectangle() {};
	};
}