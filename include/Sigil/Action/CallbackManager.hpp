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

		KeyActionCallbackMap& getKeyPressCallbacks();
		MouseButtonActionCallbackMap& getMousePressCallbacks();
		KeyActionCallbackMap& getKeyReleaseCallbacks();
		MouseButtonActionCallbackMap& getMouseReleaseCallbacks();

		void addKeyActionCallback(SDL_Keycode key, SDL_EventType eventType, KeyActionCallback callback);
		void addMouseButtonActionCallback(Uint8 button, SDL_EventType eventType, MouseButtonActionCallback callback);
	protected:
		KeyActionCallbackMap m_keyPressCallbacks;
		MouseButtonActionCallbackMap m_mousePressCallbacks;
		KeyActionCallbackMap m_keyReleaseCallbacks;
		MouseButtonActionCallbackMap m_mouseReleaseCallbacks;
	};
} // namespace Sigil

#endif // SIGIL_CALLBACK_MANAGER_HPP