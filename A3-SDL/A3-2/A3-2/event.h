#pragma once

#include "pipeline.h"

#include <SDL_events.h>
#include <vector>
#include <list>
#include <tuple>
#include <functional>
#include <type_traits>
#include <cassert>



namespace mui {



	class Event;
	class MouseMoveEvent;
	class MouseButtonEvent;


	namespace tag {
		namespace {

			struct tag_t {};

			struct application_t : tag_t {} application;
			struct quit_t : application_t {} quit;
			struct terminating_t : application_t {} terminating;

			struct key_t : tag_t {} key;
			struct key_up_t : key_t {} key_up;
			struct key_down_t : key_t {} key_down;
			/*
			SDL_KEYDOWN        = 0x300, //< Key pressed
			SDL_KEYUP,                  //< Key released
			SDL_TEXTEDITING,            //< Keyboard text editing (composition)
			SDL_TEXTINPUT,              //< Keyboard text input
			SDL_KEYMAPCHANGED,          //< Keymap changed due to a system event such as an
			input language or keyboard layout change.
			*/

			struct mouse_t : tag_t {} mouse;
			struct mouse_move_t : mouse_t {} mouse_move;
			struct mouse_down_t : mouse_t {} mouse_down;
			struct mouse_up_t : mouse_t {} mouse_up;
			struct mouse_wheel_t : mouse_t {} mouse_wheel;

		}
	}


	namespace detail     // TODO go into cpp
	{
		//  ------------------------------------------------------------------------------------------
		// map tags to enums
		//  ------------------------------------------------------------------------------------------

		template <typename Tag>  struct sdl_enum;
		template <int e>  using enum_value = std::integral_constant<int, e>;

		template<> struct sdl_enum<tag::quit_t> : enum_value<SDL_QUIT> {};
		template<> struct sdl_enum<tag::mouse_move_t> : enum_value<SDL_MOUSEMOTION> {};
		template<> struct sdl_enum<tag::mouse_down_t> : enum_value<SDL_MOUSEBUTTONDOWN> {};
		template<> struct sdl_enum<tag::mouse_up_t> : enum_value<SDL_MOUSEBUTTONUP> {};
		template<> struct sdl_enum<tag::mouse_wheel_t> : enum_value<SDL_MOUSEWHEEL> {};


		template <typename Tag>  struct enum_range {
			// default: a range of only one value: the tag's enum
			using first = sdl_enum<Tag>;
			using last = sdl_enum<Tag>;
		};

		template <>  struct enum_range<tag::mouse_t> {
			using first = sdl_enum<tag::mouse_move_t>;
			using last = sdl_enum<tag::mouse_wheel_t>;
		};


		//  ------------------------------------------------------------------------------------------
		// map enums to tags
		//  ------------------------------------------------------------------------------------------

		template <int sdl_enum>  struct tag_for_enum;

		template <> struct tag_for_enum<SDL_MOUSEMOTION> { using type = tag::mouse_move_t; };
		template <> struct tag_for_enum<SDL_MOUSEBUTTONDOWN> { using type = tag::mouse_down_t; };
		template <> struct tag_for_enum<SDL_MOUSEBUTTONUP> { using type = tag::mouse_up_t; };
		template <> struct tag_for_enum<SDL_MOUSEWHEEL> { using type = tag::mouse_wheel_t; };



		template <typename Tag>  struct sdl_event;
		template <typename Tag>  using sdl_event_t = typename sdl_event<std::decay_t<Tag>>::type;

		template<> struct sdl_event<tag::mouse_t> { using type = SDL_MouseMotionEvent; };
		template<> struct sdl_event<tag::mouse_move_t> { using type = SDL_MouseMotionEvent; };
		template<> struct sdl_event<tag::mouse_down_t> { using type = SDL_MouseButtonEvent; };
		template<> struct sdl_event<tag::mouse_up_t> { using type = SDL_MouseButtonEvent; };



		template <typename Tag>  struct custom_event;
		template <typename Tag>  using custom_event_t = typename custom_event<std::decay_t<Tag>>::type;

		template<> struct custom_event<tag::mouse_t> { using type = MouseMoveEvent; };
		template<> struct custom_event<tag::mouse_move_t> { using type = MouseMoveEvent; };
		template<> struct custom_event<tag::mouse_down_t> { using type = MouseButtonEvent; };
		template<> struct custom_event<tag::mouse_up_t> { using type = MouseButtonEvent; };
	}



	//  ---------------------------------------------------------------------------------------------
	// Event Wrapper
	//  ---------------------------------------------------------------------------------------------

	class Event {
		protected:

		const SDL_Event  event;

		public:

		explicit Event(SDL_Event e) : event{e} {}

		int type() const { return event.type; }

		template <typename EventTag>
		auto cast(EventTag tag = {}) const {
			using rng = detail::enum_range<EventTag>;
			assert(rng::first::value <= type() && type() <= rng::last::value);
			return reinterpret_cast< detail::custom_event_t<EventTag> const& >(*this);
		}

	};

	class KeyEvent : public Event {
		public:
		bool up() const { return event.key.state == SDL_RELEASED; }
		bool down() const { return event.key.state == SDL_PRESSED; }
		int window_id() const { return event.key.windowID; }
		//Uint8 repeat;       /**< Non-zero if this is a key repeat */
		// SDL_Keysym keysym;  /**< The key that was pressed or released */
	};


	class MouseMoveEvent : public Event {
		public:
		int x() const { return event.motion.x; }
		int y() const { return event.motion.y; }
		bool up() const { return event.motion.state == SDL_RELEASED; }
		bool down() const { return event.motion.state == SDL_PRESSED; }
		int window_id() const { return event.motion.windowID; }
	};


	class MouseButtonEvent : public Event {
		public:
		int x() const { return event.button.x; }
		int y() const { return event.button.y; }
		bool up() const { return event.button.state == SDL_RELEASED; }
		bool down() const { return event.button.state == SDL_PRESSED; }
		int window_id() const { return event.button.windowID; }
	};










	//  ---------------------------------------------------------------------------------------------
	// Event Broadcast
	//  ---------------------------------------------------------------------------------------------

	// Not encapsulated well at the moment. could be own class to prtect the list of callabcks.

	using listener_t = std::function<bool(Event const&)>;
	std::list< listener_t >  listeners = {};

	void connect(listener_t l) {
		listeners.push_back(std::move(l));
	}

	void dispatch_sdl_event(SDL_Event ev) {
		for (auto b = listeners.begin(), e = listeners.end(); b != e; )
			if (!(*b)(Event{ ev })) {
				b = listeners.erase(b);
				e = listeners.end();
			} else
				++b;
	}



	//  ---------------------------------------------------------------------------------------------
	// Pipeline Extensions
	//  ---------------------------------------------------------------------------------------------

	auto events() {
		return pipeline::source(connect);
	}

	namespace tag {

		template <typename Tag>
		auto filter(Tag) {
			return
				pipeline::filter([](auto&& e) {
				using rng = detail::enum_range<Tag>;
				return (rng::first::value <= e.type() && e.type() <= rng::last::value);
			});
		}

		template <typename Tag>
		auto transform(Tag tag) {
			return  filter(tag)
				| pipeline::transform([tag](auto&& e) { return e.cast(tag); });
		}

	}

}