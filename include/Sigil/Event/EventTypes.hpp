#ifndef SIGIL_EVENT_TYPES_HPP
#define SIGIL_EVENT_TYPES_HPP

#include <SDL2/SDL.h>

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
	struct Event_Quit		{};
	struct Event_OnClick	{ Sint32 mouseX, mouseY; };
	struct Event_KeyPress	{ SDL_KeyCode keycode; };
	struct Event_KeyRelease { SDL_KeyCode keycode; };
} // namespace Sigil

#endif // SIGIL_EVENT_TYPES_HPP