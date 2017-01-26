#pragma once

#include <SDL.h>
#include "SDL_Pointer.h"
#include <tuple>
#include "Surface.h"

// #include "Surface"

namespace SDL_Wrap {
	class Window {
		private:
		WindowPtr m_window;
		Surface m_surface;

		public:
		Window();
		Window(int const& width, int const& height, char* const& title = "SDL Window");
		// we just disallow all that for now, no copy, no move.
		Window(Window const&) = delete;
		Window(Window&&) = delete;
		Window& operator=(Window const&) = delete;
		Window& operator=(Window&&) = delete;

		~Window();
		void set_pixel(int const& x, int const& y, Uint32 const& color);
		void update();
		Surface& getSurface();
		std::tuple<int, int> pos() const;
		void set_pos(int const& x, int const& y);
	};
}

