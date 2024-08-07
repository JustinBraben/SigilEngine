#ifndef SIGIL_EVENT_DISPATCHER_HPP
#define SIGIL_EVENT_DISPATCHER_HPP

#include <entt/signal/dispatcher.hpp>

namespace Sigil
{
	class EventDispatcher
	{
	public:
		EventDispatcher();
		~EventDispatcher();


	private:
		entt::dispatcher m_eventDispatcher;
	};
} // namespace Sigil

#endif // SIGIL_EVENT_DISPATCHER_HPP