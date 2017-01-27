#pragma once
#include "LayoutManager.h"
#include <memory>
#include "LayoutManagerImpls.h"
#include <algorithm>

using namespace GUI;
using namespace std;

namespace Views {

	enum EventType { COLOR, TOOL, UNDO };

	struct EventData {
		Surface brush;
		Uint32 color;
		SDL_Event origin_event;
	};

	struct GUIEvent {
		EventType type;
		EventData data;
	};

	class Button : public PixelSpace {
		protected:
		string m_name;
		public:
		Button() = delete;
		explicit Button(string name, Rectangle const& size, Uint32 const& fill) : PixelSpace(size.w, size.h, fill), m_name(name) { }
		explicit Button(string name, Rectangle const& size, string file) : PixelSpace(size.w, size.h, 0xFF), m_name(name) {
			m_surface = Surface(file);
		}

		bool setup_eventlistener(EventManager& e_mgr) override {
			e_mgr.subscribe(SDL_MOUSEBUTTONDOWN, [=](SDL_Event const& event){
				auto x = event.button.x;
				auto y = event.button.y;
				if (!(x >= m_last_pos.x && x <= m_last_pos.x + m_last_pos.w && y >= m_last_pos.y && y <= m_last_pos.y + m_last_pos.h)) {
					return false;
				}
				cout << m_name.c_str() << " WAS CLICKED" << endl;
				return true;
			});
			return true;
		}
	};

	class ColorPicker : public PixelSpace {
		private:
		struct rgb {
			double r;       // percent
			double g;       // percent
			double b;       // percent
		};

		rgb hsv2rgb(double h, double s, double v) {
			double      hh, p, q, t, ff;
			long        i;
			rgb         out;

			if (s <= 0.0) {       // < is bogus, just shuts up warnings
				out.r = v;
				out.g = v;
				out.b = v;
				return out;
			}
			hh = h;
			if (hh >= 360.0) hh = 0.0;
			hh /= 60.0;
			i = (long)hh;
			ff = hh - i;
			p = v * (1.0 - s);
			q = v * (1.0 - (s * ff));
			t = v * (1.0 - (s * (1.0 - ff)));

			switch (i) {
				case 0:
					out.r = v;
					out.g = t;
					out.b = p;
					break;
				case 1:
					out.r = q;
					out.g = v;
					out.b = p;
					break;
				case 2:
					out.r = p;
					out.g = v;
					out.b = t;
					break;

				case 3:
					out.r = p;
					out.g = q;
					out.b = v;
					break;
				case 4:
					out.r = t;
					out.g = p;
					out.b = v;
					break;
				case 5:
				default:
					out.r = v;
					out.g = p;
					out.b = q;
					break;
			}
			return out;

		}
		
		Surface m_selector;
		Surface m_hsv_wheel;
		int m_selector_x;
		int m_selector_y;
		bool dragging;
		Uint32 m_selected_color;


		public:
		ColorPicker() = delete;
		ColorPicker(int const& width, int const& height) : PixelSpace(width, height, 0x000000FF), m_selector(22, 22), dragging(false) {
			m_selector_x = 0;
			m_selector_y = 0;
			m_selected_color = 0xFF;
			generateField();
			render();
		}

		void generateField() {
			int width = get<0>(m_surface.size());
			int height = get<1>(m_surface.size());

			auto dx = 255.f / width;
			auto dy = 255.f / height;

			auto c_max = width / 2;

			for (int y = 0; y < height; y++) {
				for (int x = 0; x < width; x++) { 
					auto offset = 4 * ((y * width) + x);

					auto hue = 180 + atan2f(y - width / 2, x - height / 2) * (180.f / M_PI);
					auto saturation = sqrtf(powf(y - width / 2, 2) + powf(x - height / 2, 2)) / width;

					auto distance = sqrt(pow(x - width / 2, 2) + pow(y - height / 2, 2));
					auto normDist = distance / c_max;
					normDist = normDist < 0 ? 0 : normDist;
					normDist = normDist > 1 ? 1 : normDist;
					auto value = 1 - normDist;

					saturation = saturation < 1 ? 1 : saturation;
					auto hsv = hsv2rgb(hue, saturation, value);

					Surface surf(1, 1);
					auto color = (int(hsv.r * 255) << 24) | (int(hsv.g * 255) << 16) | (int(hsv.b * 255) << 8) | 0xFF;
					surf.fill(color);
					m_hsv_wheel.blit(surf, Rectangle(1, 1, x, y));

					/*


					Surface x(1, 1);
					auto color = (int(dx * i) << 24) + (int(dy * j) << 16) | 0xFF;
					x.fill(color);
					m_surface.blit(x, Rectangle(1, 1, i, j));
					*/
				}
			}
		}

		bool setup_eventlistener(EventManager& e_mgr) override {
			e_mgr.subscribe(SDL_MOUSEBUTTONDOWN, [=](SDL_Event const& event){
				auto x = event.button.x;
				auto y = event.button.y;
				if (!(x >= m_last_pos.x && x <= m_last_pos.x + m_last_pos.w && y >= m_last_pos.y && y <= m_last_pos.y + m_last_pos.h)) {
					return false;
				}
				dragging = true;
				x -= m_last_pos.x;
				y -= m_last_pos.y;
				m_selector_x = x - 11;
				m_selector_y = y - 11;

				render();
				m_dirty = true;

				return true;

			});

			e_mgr.subscribe(SDL_MOUSEBUTTONUP, [=](SDL_Event const& event){
				dragging = false;
				return false;
			});

			e_mgr.subscribe(SDL_MOUSEMOTION, [=](SDL_Event const& event){
				if(!dragging) {
					return false;
				}
				auto x = event.button.x;
				auto y = event.button.y;
				if (!(x >= m_last_pos.x && x <= m_last_pos.x + m_last_pos.w && y >= m_last_pos.y && y <= m_last_pos.y + m_last_pos.h)) {
					return false;
				}
				x -= m_last_pos.x;
				y -= m_last_pos.y;
				m_selector_x = x - 11;
				m_selector_y = y - 11;
				render();
				m_dirty = true;
				return true;
			});

			return true;
		}

		void render() {
			Uint32 *pixels = (Uint32 *)m_hsv_wheel.get_surface()->pixels; // get pixel array
			m_selected_color = pixels[(m_selector_y * m_hsv_wheel.get_surface()->w) + m_selector_x]; // pull out the specific color at pos

			m_selector.fill(m_selected_color);

			m_surface.blit(m_hsv_wheel, Rectangle(get<0>(m_minSize), get<0>(m_minSize), 0, 0));
			m_surface.blit(m_selector, Rectangle(22, 22, m_selector_x, m_selector_y));
			Surface side(2, 26);
			Surface top(26, 2);
			side.fill(0xFF);
			top.fill(0xFF);

			m_surface.blit(side, Rectangle(2, 26, m_selector_x - 2, m_selector_y - 2));
			m_surface.blit(side, Rectangle(2, 26, m_selector_x + 22, m_selector_y - 2));

			m_surface.blit(top, Rectangle(26, 2, m_selector_x - 2, m_selector_y - 2));
			m_surface.blit(top, Rectangle(26, 2, m_selector_x - 2, m_selector_y + 22));


		}

	};


	inline Uint32 randomColor() {
		Uint32 color = 0xFF;
		color |= rand() << 8;
		color |= rand() << 16;
		color |= rand() << 24;
		return color;
	}

	inline shared_ptr<LayoutManager> buildButtonRow(EventManager& e_mgr) {
		auto layout = make_shared<HorizontalCloseLayout>();
		auto button1 = make_shared<Button>("Pencil", Rectangle(53, 53, 0, 0), "pencil.bmp");
		button1->setup_eventlistener(e_mgr);
		auto button2 = make_shared<Button>("Fill", Rectangle(53, 53, 0, 0), "fill.bmp");
		button2->setup_eventlistener(e_mgr);
		auto button3 = make_shared<Button>("Eyedropper", Rectangle(53, 53, 0, 0), "eyedropper.bmp");
		button3->setup_eventlistener(e_mgr);
		auto button4 = make_shared<Button>("Eraser", Rectangle(53, 53, 0, 0), "eraser.bmp");
		button4->setup_eventlistener(e_mgr);
		layout->add(button1, 0);
		layout->add(button2, 0);
		layout->add(button3, 0);
		layout->add(button4, 0);
		return layout;
	}



	class ButtonsView : public VerticalCloseLayout {
		protected:
		Rectangle m_size;

		public:

		ButtonsView() = delete;
		explicit ButtonsView(Rectangle const& size, EventManager& e_mgr) : m_size(size) {
			m_children.push_back(buildButtonRow(e_mgr));
			m_children.push_back(buildButtonRow(e_mgr));
			m_children.push_back(buildButtonRow(e_mgr));
			auto pixelThing = make_shared<ColorPicker>(160, 160);
			pixelThing->setup_eventlistener(e_mgr);
			auto undoPreview = make_shared<Button>("UndoField", Rectangle(60, 60, 0, 0), randomColor());
			undoPreview->setup_eventlistener(e_mgr);

			m_children.push_back(move(pixelThing));
			m_children.push_back(move(undoPreview));
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

	class DrawPanel : public PixelSpace {
		protected:
		Surface m_brush;
		bool m_clicked;

		public:
		DrawPanel() = delete;
		DrawPanel(int const& width, int const& height) : PixelSpace(width, height, 0x000000FF), m_brush(2, 2), m_clicked(false) {
			m_brush.fill(0xFFFFFFFF);

			
		}

		bool setup_eventlistener(EventManager& e_mgr) override {
			e_mgr.subscribe(SDL_MOUSEBUTTONUP, [=](SDL_Event const& event) {
				m_clicked = false;
				old_x = -1;
				old_y = -1;
				return false;
			});

			e_mgr.subscribe(SDL_MOUSEBUTTONDOWN, [=](SDL_Event const& event){
				auto x = event.button.x;
				auto y = event.button.y;
				
				m_clicked = (x >= m_last_pos.x && x <= m_last_pos.x + m_last_pos.w && y >= m_last_pos.y && y <= m_last_pos.y + m_last_pos.h);
				if (m_clicked) {
					auto brushSize = m_brush.size();
					auto rect = Rectangle(get<0>(brushSize), get<1>(brushSize), x - m_last_pos.x, y - m_last_pos.y);
					m_surface.blit(m_brush, rect);
					m_dirty = true;
				}
				return true;
			});

			e_mgr.subscribe(SDL_MOUSEMOTION, [=](SDL_Event const& event){
				auto x = event.motion.x;
				auto y = event.motion.y;


				if (!(x >= m_last_pos.x && x <= m_last_pos.x + m_last_pos.w && y >= m_last_pos.y && y <= m_last_pos.y + m_last_pos.h)) {
					return false;
				}

				if(!m_clicked) {
					return false;
				}
				m_dirty = true;
				// and now relative positions
				x -= m_last_pos.x;
				y -= m_last_pos.y;

				if(old_x < 0) {
					old_x = x;
				}

				if(old_y < 0) {
					old_y = y;
				}

				auto brushSize = m_brush.size();
				// m_surface.blit(m_brush, Rectangle(get<0>(brushSize) * 2, get<1>(brushSize) * 2, x, y));


				auto distance = std::sqrt(std::pow(old_x - x, 2) + std::pow(old_y - y, 2));
				auto frac = 1.f / distance;

				for (auto i = 0; i < distance; i++) {
					auto nx = old_x + (x - old_x) * (frac * i);
					auto ny = old_y + (y - old_y) * (frac * i);
					
					m_surface.blit(m_brush, Rectangle(get<0>(brushSize), get<1>(brushSize), nx, ny));
					// set_pixel(nx, ny, m_color);
				}

				old_x = x;
				old_y = y;
				return true;
			});

			return true;
		}

		void receive(GUIEvent const& event) {
			
		};
	};



}

