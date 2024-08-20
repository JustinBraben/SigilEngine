#ifndef SIGIL_ACTION_TYPES_HPP
#define SIGIL_ACTION_TYPES_HPP

#include <Sigil/EngineFwd.hpp>
#include <SDL2/SDL.h>

#include <functional>

namespace Sigil
{
	struct KeyEvent {
		SDL_EventType evnt_type;
		SDL_KeyboardEvent key_evnt;
	};

	struct MouseButtonEvent {
		SDL_EventType evnt_type;
		SDL_MouseButtonEvent mouse_evnt;
	};

	using KeyActionCallback = std::function<void(Engine&, const KeyEvent&)>;
	using MouseButtonActionCallback = std::function<void(Engine&, const MouseButtonEvent&)>;
} // namespace Sigil

#endif // SIGIL_ACTION_TYPES_HPP