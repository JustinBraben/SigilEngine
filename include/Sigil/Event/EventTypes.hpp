#ifndef SIGIL_EVENT_TYPES_HPP
#define SIGIL_EVENT_TYPES_HPP

#include <Sigil/EngineFwd.hpp>
#include <SDL2/SDL.h>

#include <functional>

namespace Sigil
{
	struct KeyEvent {
		SDL_EventType evnt_type;
		SDL_KeyboardEvent key_evnt;
	};

	struct MouseEvent {
		SDL_EventType evnt_type;
		SDL_MouseButtonEvent mouse_evnt;
	};

	using KeyActionCallback = std::function<void(Engine&, const KeyEvent&)>;
	using MouseActionCallback = std::function<void(Engine&, const MouseEvent&)>;
} // namespace Sigil

#endif // SIGIL_EVENT_TYPES_HPP