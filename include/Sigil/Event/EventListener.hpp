#ifndef SIGIL_EVENT_LISTENER_HPP
#define SIGIL_EVENT_LISTENER_HPP

#include <iostream>

#include <Sigil/Event/EventTypes.hpp>

namespace Sigil
{
	struct EventListener
	{
		void HandleQuit(const Sigil::Event_Quit&) { std::cout << "Escape event handled\n"; }
		void HandleKeyPress(const Sigil::Event_KeyPress& evntKey) { /* ... */ }
		void HandleKeyRelease(const Sigil::Event_KeyRelease& evntKey) { /* ... */ }
	};
} // namespace Sigil

#endif // SIGIL_EVENT_LISTENER_HPP