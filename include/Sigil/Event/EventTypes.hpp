#ifndef SIGIL_EVENT_TYPES_HPP
#define SIGIL_EVENT_TYPES_HPP

#include <SDL2/SDL.h>

namespace Sigil
{
	struct Event_Quit {};
	struct Event_OnClick {Sint32 mouseX, mouseY};
} // namespace Sigil

#endif // SIGIL_EVENT_TYPES_HPP