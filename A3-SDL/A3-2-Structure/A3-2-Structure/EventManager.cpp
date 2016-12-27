#include "EventManager.h"



GUI::EventManager::EventManager() : m_event_map() {}

void GUI::EventManager::subscribe(SDL_EventType const& type, function<bool(SDL_Event const&)> const& function) {
	auto x = m_event_map.find(type);
	if (x == m_event_map.end()) {
		// TODO: m_event_map[type] = vector<function<bool(SDL_Event const&)>>();
	}
	m_event_map[type].push_back(function);
}

bool GUI::EventManager::unsubscribe(SDL_EventType const& type, function<bool(SDL_Event const&)> const&) {
	return false;
}



GUI::EventManager::~EventManager() {}
