#ifndef SIGIL_ACTION_TYPES_HPP
#define SIGIL_ACTION_TYPES_HPP

#include <Sigil/EngineFwd.hpp>
#include <SDL2/SDL.h>

#include <string>
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

	template<typename Obj, typename Result, typename ...Args>
	struct Delegate
	{
		Obj x;
		Result(Obj::* f)(Args...);

		template<typename ...Ts>
		Result operator()(Ts&&... args)
		{
			return (x.*f)(forward<Ts>(args)...);
		}
	};

	template<typename Obj, typename Result, typename ...Args>
	auto make_delegate(const Obj& x, Result(Obj::* fun)(Args...))
		-> Delegate<Obj, Result, Args...>
	{
		Delegate<Obj, Result, Args...> result{ x, fun };
		return result;
	}

	using ActionCallback = std::function<void(Engine&)>;

	struct Action {
		std::string name;
		ActionCallback callback;
	};
} // namespace Sigil

#endif // SIGIL_ACTION_TYPES_HPP