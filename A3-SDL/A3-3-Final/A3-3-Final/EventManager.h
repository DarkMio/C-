#pragma once

#include "SDL_events.h"
#include <functional>
#include <map>
#include <vector>
#include <iostream>

using namespace std;

namespace GUI {
	/**
	 * This has no SDL_Wrap around event types, since it's not really necessary.
	 * Events are disposed upon handling and could most likely just clutter up memory. So just toss'em.
	 * 
	 * The base functionality of this EventManger are as following:
	 * void subscribe(...):
	 *    subscribing to an event type adds any form of call back into the event manager
	 * bool unsubscribe(...):
	 *    unsubscribes the exact same callback (probably useless) and returns true/false based if found
	 * bool event_loop():
	 *	  runs a full event loop, which is based on following pseudo code:
	 *    0. has_called = false;
	 *    1. SDL_event event;
	 *	  2. while(SDL_PollEvent(&event)):
	 *	  3.    for_each(SDL_EventType e_t in m_event_map):
	 *	  4.		if(event.type != e_t) continue;
	 *    5.	    has_called = true;
	 *	  5.        for_each(function<...> callback in m_event_map[e_t])
	 *	  6.			callback(event);
	 *    7. return has_called;
	 *    return type bool is mostly for debug reasons to see if the event queue actually reacted
	 *	  to an SDL_event.
	 *	  A function callback returns bool to indicate that it's inner state has been modified by this
	 *    event - which signals to enable a redraw. This could potentially enable sub-tree redrawing
	 *    in LayoutManager. ie LayoutManager could support sub-tree event manager (which could
	 *    potentially be memory intensive)
	 *
	 * The overall EventManager should not take longer to process through all events than a full draw call
	 * (Point of reference: 27.12.16 - 4.7ms for 48 * 64 non dirty pixel spaces)
	 */
	class EventManager {
		protected:
		// This literally goes down the rabbit hole (don't judge me)
		map<SDL_EventType, vector<function<bool(SDL_Event const&)>>> m_event_map;
		public:
		explicit EventManager();
		void subscribe(SDL_EventType const& type, function<bool(SDL_Event const&)> const&);
		bool unsubscribe(SDL_EventType const& type, function<bool(SDL_Event const&)> const&);
		bool event_loop();
		~EventManager();
	};
}