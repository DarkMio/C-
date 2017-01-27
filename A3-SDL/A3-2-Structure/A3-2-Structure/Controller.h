#pragma once
#include "LayoutManagerImpls.h"
#include "Views.h"

namespace Views {
	struct GUIEvent;

	class Controller {
		protected:
		shared_ptr<DrawPanel> m_space;
		shared_ptr<GUI::PixelSpace> m_color;
		public:
		Controller() = delete;
		explicit Controller(shared_ptr<DrawPanel> const& drawspace, shared_ptr<GUI::PixelSpace> const& colorSelector) : 
		m_space(drawspace), m_color(colorSelector) {}
		void send(GUIEvent const& event) {
			switch(event.type) {
				case EventType::COLOR:
					break;
				case EventType::TOOL:
					break;
				case EventType::UNDO:
					break;
				default:
					break;
			}
		}
	};
}
