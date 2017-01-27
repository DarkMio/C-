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
			auto pixelThing = make_shared<Button>("ColorField", Rectangle(160, 160, 0, 0), randomColor());
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

