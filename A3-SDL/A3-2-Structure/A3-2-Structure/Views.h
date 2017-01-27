#pragma once
#include "LayoutManager.h"
#include <memory>
#include "LayoutManagerImpls.h"
#include <algorithm>
#include "Math_Helper.h"

using namespace GUI;
using namespace std;

namespace Views {


	enum EventType { COLOR, TOOL, UNDO };

	enum EventTool { PENCIL, BRUSH, SPRAY, STAR};

	struct EventData {
		Surface brush;
		Uint32 color;
		SDL_Event origin_event;
	};

	struct GUIEvent {
		EventType type;
		EventTool tool;
		EventData data;
	};

	class HistoryPanel : public PixelSpace {
		protected:

		public:
		HistoryPanel(int const& width, int const& height) : PixelSpace(width, height, 0x00) {}

		void notify(vector<vector<shared_ptr<Surface>>> const& steps) {
			auto size = clamp(4, 1, int(steps.size()));
			auto width = get<0>(m_minSize);

			m_surface.fill(0xF3F4F5FF);

			for (int i = 1; i < size; i++) {
				vector<shared_ptr<Surface>> element = *(steps.end() - i);
				Surface tmp(480, 480);
				for (int x = 0; x < 3; x++) {
					for (int y = 0; y < 3; y++) {
						tmp.blit(*element[x * 3 + y], Rectangle(160, 160, x * 160, y * 160));
					}
				}
				m_surface.blit(Surface(tmp.get_surface(), Rectangle(width / 3, width / 3, 0, 0)), Rectangle(width / 3, width / 3, (2 - (i - 1)) * (width / 3), 0));
			}
			m_dirty = true;
		}

		Surface& giff_diretide() {
			return m_surface;
		}

	};

	class DrawPanel : public PixelSpace {
		protected:
		Surface m_brush;
		bool m_clicked;
		HistoryPanel m_history;
		vector<shared_ptr<Surface>> m_current_step;
		vector<vector<shared_ptr<Surface>>> m_steps;

		void undo() {
			if(m_steps.size() > 1) {
				m_surface.fill(0xFF);
				m_steps.erase(m_steps.end() - 1);

				auto size = m_surface.size();
				auto chunk = get<0>(size) / 3;

				m_current_step = m_steps.back();
				for(int x = 0; x < 3; x++) {
					for(int y = 0; y < 3; y++) {
						m_surface.blit(*m_current_step[x * 3 + y], Rectangle(chunk, chunk, x * chunk, y * chunk));
					}
				}
				m_dirty = true;
				m_history.notify(m_steps);
			}
			/*
			if (steps.size() > 1) {
				m_surface.fill(0xFF);
				steps.erase(steps.end() - 1);
				// steps.pop_back();
				auto size = steps.back().size();
				m_surface.blit(steps.back(), Rectangle(get<0>(size), get<1>(size), 0, 0));
				m_dirty = true;
				m_history.notify(steps);
			}
			*/
		}

		void update_surface(int const& x, int const& y) {
			auto sSize = m_surface.size();
			auto bSize = m_brush.size();

			auto chunk = get<0>(sSize) / 3;

			auto bRadius_x = get<0>(bSize) / 2;
			auto bRadius_y = get<1>(bSize) / 2;

			auto brush_x = x - bRadius_x;
			auto brush_y = y - bRadius_y;

			auto spat_x = brush_x / chunk;
			auto spat_y = brush_y / chunk;

			auto local_x = brush_x % chunk;
			auto local_y = brush_y % chunk;

			auto upper_x = local_x + bRadius_x * 2;
			auto upper_y = local_y + bRadius_y * 2;

			auto lower_x = local_x - bRadius_x;
			auto lower_y = local_y - bRadius_y;

			auto blit_update = [&](auto const& lamdba_spat_x, auto const& lambda_spat_y) {
				auto element = m_current_step[lamdba_spat_x * 3 + lambda_spat_y];
				if (element.use_count() > 2) { // where we add new elements - 2 since we're keeping it up as a member
					cout << "Spatial Update: [x=" << lamdba_spat_x << ", y=" << lambda_spat_y << "] | uses: " << element.use_count() << endl;
					element = move(make_shared<Surface>(*element)); // make a new one
				} else {
					element->blit(m_brush, Rectangle(get<0>(bSize), get<1>(bSize), brush_x - lamdba_spat_x * chunk, brush_y - lambda_spat_y * chunk));
				}
				m_surface.blit(*element, Rectangle(chunk, chunk, lamdba_spat_x * chunk, lambda_spat_y * chunk));
				m_current_step[lamdba_spat_x * 3 + lambda_spat_y] = move(element);
			};

			bool right = upper_x > chunk && spat_x < 2;
			bool left = lower_x < 0 && spat_x > 0;
			bool top = lower_y < 0 && spat_y > 0;
			bool bot = upper_y > chunk && spat_y < 2;

			// neighbours 
			if(right) {	blit_update(spat_x + 1, spat_y);	}
			if(bot) { blit_update(spat_x, spat_y + 1); }
			if(left) { blit_update(spat_x - 1, spat_y); }
			if(top) { blit_update(spat_x, spat_y - 1); }

			// and diagonal neighbours
			if(top && left) {  blit_update(spat_x - 1, spat_y - 1); }
			if(top && right) { blit_update(spat_x + 1, spat_y - 1); }
			if(bot && left) {  blit_update(spat_x - 1, spat_y + 1); }
			if(bot && right) { blit_update(spat_x + 1, spat_y + 1); }
			
			blit_update(spat_x, spat_y);


			// m_surface.blit(m_brush, Rectangle(get<0>(bSize), get<1>(bSize), x, y));
			m_dirty = true;
		}

		void commit() {
			if (m_clicked) {
				// steps.emplace_back(Surface(m_surface));
				m_steps.emplace_back(m_current_step);
				auto tmp = vector<shared_ptr<Surface>>();
				for(auto const& c: m_current_step) {
					tmp.emplace_back(shared_ptr<Surface>(c));
				}
				m_current_step = tmp;
				m_history.notify(m_steps);
			}
		}

		public:
		DrawPanel() = delete;

		DrawPanel(int const& width, int const& height) : PixelSpace(width, height, 0x000000FF), m_brush(2, 2), m_clicked(false), m_history(160, 53) {
			m_brush.fill(0xFF);

			m_current_step = vector<shared_ptr<Surface>>();
			auto chunk = width / 3;
			for (int i = 0; i < 9; i++) {
				m_current_step.push_back(make_shared<Surface>(chunk, chunk));
			}
			m_steps.push_back(m_current_step);
		}

		bool setup_eventlistener(EventManager& e_mgr) override {
			e_mgr.subscribe(SDL_MOUSEBUTTONUP, [=](SDL_Event const& event) {
								commit();
				                m_clicked = false;
				                old_x = -1;
				                old_y = -1;
				                return false;
			                });

			e_mgr.subscribe(SDL_MOUSEBUTTONDOWN, [=](SDL_Event const& event) {
				                auto x = event.button.x;
				                auto y = event.button.y;

				                m_clicked = (x >= m_last_pos.x && x <= m_last_pos.x + m_last_pos.w && y >= m_last_pos.y && y <= m_last_pos.y + m_last_pos.h);
				                if (m_clicked) {
									update_surface(x - m_last_pos.x, y - m_last_pos.y);
				                }
				                // m_history.notify(steps);
				                return true;
			                });

			e_mgr.subscribe(SDL_MOUSEMOTION, [=](SDL_Event const& event) {
				                auto x = event.motion.x;
				                auto y = event.motion.y;


				                if (!(x >= m_last_pos.x && x <= m_last_pos.x + m_last_pos.w && y >= m_last_pos.y && y <= m_last_pos.y + m_last_pos.h)) {
					                return false;
				                }

				                if (!m_clicked) {
					                return false;
				                }
				                // and now relative positions
				                x -= m_last_pos.x;
				                y -= m_last_pos.y;

				                if (old_x < 0) {
					                old_x = x;
				                }

				                if (old_y < 0) {
					                old_y = y;
				                }

				                auto distance = std::sqrt(std::pow(old_x - x, 2) + std::pow(old_y - y, 2));
				                auto frac = 1.f / distance;

				                for (auto i = 0; i < distance; i++) {
					                auto nx = old_x + (x - old_x) * (frac * i);
					                auto ny = old_y + (y - old_y) * (frac * i);

									update_surface(nx, ny);

				                }
				                old_x = x;
				                old_y = y;
				                return true;
			                });

			return true;
		}

		

		bool draw(Surface const& surface, Rectangle const& rect) const override {
			m_dirty |= m_last_pos.h != rect.h || m_last_pos.w != rect.w || m_last_pos.x != rect.x || m_last_pos.y != rect.y;

			if (m_dirty) {
				m_last_pos = rect;
				surface.blit(m_surface, rect);
				m_dirty = false;

				m_history.draw(surface, Rectangle(160, 53, 1, 427));
				// surface.blit(static_cast<HistoryPanel>(m_history).giff_diretide(), Rectangle(160, 53, 1, 427));
				return true;
			}
			return false;
		}

		void receive(GUIEvent const& event) {

			auto blit = [=]() {
					Surface tmp = Surface(event.data.brush);
					auto bSize = tmp.size();
					auto bWidth = get<0>(bSize);
					auto bHeight = get<1>(bSize);

					m_brush = Surface(bWidth, bHeight);
					m_brush.blit(tmp, Rectangle(bWidth, bHeight, 0, 0));
				};

			switch (event.type) {
				case EventType::TOOL:
					blit();
					m_color = Uint32(event.data.color);
					break;
				case EventType::COLOR:
					m_color = Uint32(event.data.color);
					// tmp = Surface(m_brush.get_surface());
					break;
				case EventType::UNDO:
					undo();
					return;
				default:
					break;
			}
			Uint32* pixels_brush = static_cast<Uint32 *>(m_brush.get_surface()->pixels); // get pixel array
			auto bSize = m_brush.size();
			auto bWidth = get<0>(bSize);
			auto bHeight = get<1>(bSize);
			// m_color &= 0xFFFFFF40;
			auto colorize = [=]() {
					for (unsigned int x = 0; x < get<0>(bSize); x++) {
						for (unsigned int y = 0; y < get<1>(bSize); y++) {
							auto pixel = pixels_brush[m_brush.get_surface()->w * y + x];
							auto r = (pixel & 0xFF000000) >> 24;
							auto g = (pixel & 0x00FF0000) >> 16;
							auto b = (pixel & 0x0000FF00) >> 8;
							auto a = (pixel & 0xFF) >> 0;
							if (a == 0x00) {
								continue;
							}
							else if (r == 255 || g == 255 || b == 255) {
								pixel = 0x00;
							}
							else {
								pixel = m_color;
							}
							pixels_brush[m_brush.get_surface()->w * y + x] = pixel;
						}
					}
				};
			// m_brush.get_surface()->pixels = pixels;
			colorize();
		};
	};


	class Controller {
		protected:
		shared_ptr<DrawPanel> m_space;
		Uint32 m_color;

		static void loadBrush(Views::GUIEvent& event) {
			switch (event.tool) {
				case Views::STAR:
					event.data.brush = Surface("star_brush.bmp");
					break;
				case Views::BRUSH:
					event.data.brush = Surface("circle_brush.bmp");
					break;
				case Views::PENCIL:
					event.data.brush = Surface("pencil_brush.bmp");
					break;
				default:
					event.data.brush = Surface("pencil_brush.bmp");
			}
		}

		public:
		Controller() : m_color(0x00) {};
		explicit Controller(shared_ptr<DrawPanel> const& drawspace) : m_space(drawspace), m_color(0x00) {}

		void send(Views::GUIEvent event) {
			switch (event.type) {
				case Views::EventType::COLOR:
					m_color = event.data.color;
					break;
				case Views::EventType::TOOL:
					// collectColor(event);
					event.data.color = m_color;
					loadBrush(event);
					break;
				case Views::EventType::UNDO:
					break;
				default:
					break;
			}
			m_space->receive(event);
		}
	};


	class ColorPicker : public PixelSpace {
		private:
		struct rgb {
			double r; // percent
			double g; // percent
			double b; // percent
		};

		rgb hsv2rgb(double h, double s, double v) {
			double hh, p, q, t, ff;
			long i;
			rgb out;

			if (s <= 0.0) { // < is bogus, just shuts up warnings
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

		Surface m_brightness;

		int m_selector_x;
		int m_selector_y;
		bool dragging;
		Uint32 m_selected_color;

		shared_ptr<Controller> m_controller;

		public:
		ColorPicker() = delete;

		ColorPicker(int const& width, int const& height, shared_ptr<Controller> const& cont) : PixelSpace(width, height, 0x000000FF), m_selector(22, 22), m_brightness(width, 20), dragging(false), m_controller(cont) {
			m_selector_x = 0;
			m_selector_y = 0;
			m_selected_color = 0xFF;
			generateField();
			render();
		}

		void generateField() {
			int width = get<0>(m_surface.size());
			int height = get<1>(m_surface.size()) - 20;

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
			generateBrightnessGradient();
		}

		void generateBrightnessGradient() {
			auto width = get<0>(m_brightness.size());
			auto dx = 255.f / get<0>(m_brightness.size());

			for (int i = 0; i < width; i++) {
				auto val = int(dx * i);
				Surface local_grad(1, 20);
				auto color = val << 24 | val << 16 | val << 8 | 0xFF;
				local_grad.fill(color);

				m_brightness.blit(local_grad, Rectangle(1, 20, i, 0));
			}

			m_hsv_wheel.blit(m_brightness, Rectangle(get<0>(m_minSize), 20, 0, get<1>(m_minSize) - 20));
		}

		bool setup_eventlistener(EventManager& e_mgr) override {
			e_mgr.subscribe(SDL_MOUSEBUTTONDOWN, [=](SDL_Event const& event) {
				                auto x = event.button.x;
				                auto y = event.button.y;
				                if (!(x >= m_last_pos.x && x <= m_last_pos.x + m_last_pos.w && y >= m_last_pos.y && y <= m_last_pos.y + m_last_pos.h)) {
					                return false;
				                }
				                dragging = true;
				                x -= m_last_pos.x;
				                y -= m_last_pos.y;
				                m_selector_x = clamp(x, 0, int(m_last_pos.w));
				                m_selector_y = clamp(y, 0, int(m_last_pos.h)) ,

					                render();
				                m_dirty = true;

				                return true;

			                });

			e_mgr.subscribe(SDL_MOUSEBUTTONUP, [=](SDL_Event const& event) {
				                dragging = false;
				                return false;
			                });

			e_mgr.subscribe(SDL_MOUSEMOTION, [=](SDL_Event const& event) {
				                if (!dragging) {
					                return false;
				                }
				                auto x = event.button.x;
				                auto y = event.button.y;
				                if (!(x >= m_last_pos.x && x <= m_last_pos.x + m_last_pos.w && y >= m_last_pos.y && y <= m_last_pos.y + m_last_pos.h)) {
					                return false;
				                }
				                x -= m_last_pos.x;
				                y -= m_last_pos.y;
				                m_selector_x = clamp(x, 0, int(m_last_pos.w));
				                m_selector_y = clamp(y, 0, int(m_last_pos.h)) ,

					                render();
				                m_dirty = true;
				                return true;
			                });

			return true;
		}

		void render() {
			Uint32* pixels = static_cast<Uint32 *>(m_hsv_wheel.get_surface()->pixels); // get pixel array
			m_selected_color = pixels[(m_selector_y * m_hsv_wheel.get_surface()->w) + m_selector_x]; // pull out the specific color at pos

			m_selector.fill(m_selected_color);

			m_surface.blit(m_hsv_wheel, Rectangle(get<0>(m_minSize), get<0>(m_minSize), 0, 0));
			m_surface.blit(m_selector, Rectangle(22, 22, m_selector_x - 11, m_selector_y - 11));
			Surface side(2, 26);
			Surface top(26, 2);
			side.fill(0xFF);
			top.fill(0xFF);

			m_surface.blit(side, Rectangle(2, 26, m_selector_x - 2 - 11, m_selector_y - 2 - 11));
			m_surface.blit(side, Rectangle(2, 26, m_selector_x + 22 - 11, m_selector_y - 2 - 11));

			m_surface.blit(top, Rectangle(26, 2, m_selector_x - 2 - 11, m_selector_y - 2 - 11));
			m_surface.blit(top, Rectangle(26, 2, m_selector_x - 2 - 11, m_selector_y + 22 - 11));

			GUIEvent event;
			event.type = EventType::COLOR;
			event.data.color = m_selected_color;

			m_controller->send(event);
		}

		Uint32 selectedColor() const {
			return m_selected_color;
		}
	};


	class Button : public PixelSpace {
		protected:
		string m_name;
		shared_ptr<Controller> m_controller;
		public:
		Button() = delete;

		explicit Button(string name, Rectangle const& size, Uint32 const& fill, shared_ptr<Controller> cont)
			: PixelSpace(size.w, size.h, fill), m_name(name), m_controller(cont) { }

		explicit Button(string name, Rectangle const& size, string file, shared_ptr<Controller> cont)
			: PixelSpace(size.w, size.h, 0xFF), m_name(name), m_controller(cont) {
			m_surface = Surface(file);
		}

		bool setup_eventlistener(EventManager& e_mgr) override {
			e_mgr.subscribe(SDL_MOUSEBUTTONDOWN, [=](SDL_Event const& event) {
				                auto x = event.button.x;
				                auto y = event.button.y;
				                if (!(x >= m_last_pos.x && x <= m_last_pos.x + m_last_pos.w && y >= m_last_pos.y && y <= m_last_pos.y + m_last_pos.h)) {
					                return false;
				                }
				                cout << m_name.c_str() << " WAS CLICKED" << endl;


				                GUIEvent g_event;
				                g_event.type = EventType::TOOL;
				                g_event.data.origin_event = SDL_Event(event);

				                if (m_name == "Pencil") {
					                g_event.tool = EventTool::PENCIL;
				                }
				                else if (m_name == "Star") {
					                g_event.tool = EventTool::STAR;
				                }
				                else if (m_name == "Brush") {
					                g_event.tool = EventTool::BRUSH;
				                }
				                else if (m_name == "Undo") {
					                g_event.type = EventType::UNDO;
				                }


				                m_controller->send(g_event);

				                return true;
			                });
			return true;
		}
	};


	inline Uint32 randomColor() {
		Uint32 color = 0xFF;
		color |= rand() << 8;
		color |= rand() << 16;
		color |= rand() << 24;
		return color;
	}

	inline shared_ptr<LayoutManager> buildButtonRow(EventManager& e_mgr, shared_ptr<Controller> const& cont) {
		auto layout = make_shared<HorizontalCloseLayout>();
		auto button1 = make_shared<Button>("Pencil", Rectangle(53, 53, 0, 0), "pencil.bmp", cont);
		button1->setup_eventlistener(e_mgr);
		auto button2 = make_shared<Button>("Star", Rectangle(53, 53, 0, 0), "star.bmp", cont);
		button2->setup_eventlistener(e_mgr);
		auto button3 = make_shared<Button>("Brush", Rectangle(53, 53, 0, 0), "brush.bmp", cont);
		button3->setup_eventlistener(e_mgr);
		auto button4 = make_shared<Button>("Undo", Rectangle(53, 53, 0, 0), "undo.bmp", cont);
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
		shared_ptr<ColorPicker> m_cpicker;
		shared_ptr<Controller> m_controller;
		public:

		ButtonsView() = delete;

		explicit ButtonsView(Rectangle const& size, EventManager& e_mgr, shared_ptr<Controller> const& controller) : m_size(size), m_controller(controller) {
			m_children.push_back(buildButtonRow(e_mgr, m_controller));
			m_cpicker = make_shared<ColorPicker>(160, 180, controller);
			m_cpicker->setup_eventlistener(e_mgr);
			m_children.push_back(shared_ptr<ColorPicker>(m_cpicker));
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

		shared_ptr<ColorPicker> getPicker() const {
			return shared_ptr<ColorPicker>(m_cpicker);
		}

	};

}
