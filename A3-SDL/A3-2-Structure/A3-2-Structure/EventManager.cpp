#include "EventManager.h"



GUI::EventManager::EventManager() : m_event_map() {}

void GUI::EventManager::subscribe(SDL_EventType const& type, function<bool(SDL_Event const&)> const& function) {
	auto x = m_event_map.find(type);
	if (x == m_event_map.end()) {
		m_event_map[type] = vector<std::function<bool(SDL_Event const&)>>();
	}
	m_event_map[type].push_back(function);
}

bool GUI::EventManager::unsubscribe(SDL_EventType const& type, function<bool(SDL_Event const&)> const&) {
	// TODO: Not implemented
	return false;
}

bool GUI::EventManager::event_loop() {
	bool has_called = false;

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		for (auto it = m_event_map.begin(); it != m_event_map.end(); ++it) {
			if (it->first != event.type) {
				continue;
			}
			for (auto callback : it->second) {
				callback(event);
				has_called |= true;
			}
		}
	}
	return has_called;
}



GUI::EventManager::~EventManager() {}
