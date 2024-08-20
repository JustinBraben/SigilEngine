#ifndef SIGIL_CALLBACK_MANAGER_HPP
#define SIGIL_CALLBACK_MANAGER_HPP

#include <Sigil/Action/ActionTypes.hpp>

#include <SDL2/SDL.h>
#include <string>
#include <unordered_map>
#include <concepts>

namespace Sigil
{
	using KeyActionCallbackMap = std::unordered_map<SDL_Keycode, KeyActionCallback>;
	using MouseButtonActionCallbackMap = std::unordered_map<Uint8, MouseButtonActionCallback>;

	class CallbackManager
	{
	public:
		CallbackManager() = default;
		~CallbackManager() = default;
	protected:
		std::unordered_map<SDL_Keycode, KeyActionCallback> m_keyPressCallbacks;
		std::unordered_map<Uint8, MouseButtonActionCallback> m_mousePressCallbacks;
		std::unordered_map<SDL_Keycode, KeyActionCallback> m_keyReleaseCallbacks;
		std::unordered_map<Uint8, MouseButtonActionCallback> m_mouseReleaseCallbacks;
	};
} // namespace Sigil

#endif // SIGIL_CALLBACK_MANAGER_HPP