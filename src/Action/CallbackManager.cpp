#include <Sigil/Action/CallbackManager.hpp>

namespace Sigil
{
	KeyActionCallbackMap& CallbackManager::getKeyPressCallbacks()
	{
		return m_keyPressCallbacks;
	}

	MouseButtonActionCallbackMap& CallbackManager::getMousePressCallbacks()
	{
		return m_mousePressCallbacks;
	}

	KeyActionCallbackMap& CallbackManager::getKeyReleaseCallbacks()
	{
		return m_keyReleaseCallbacks;
	}

	MouseButtonActionCallbackMap& CallbackManager::getMouseReleaseCallbacks()
	{
		return m_mouseReleaseCallbacks;
	}

	void CallbackManager::addKeyActionCallback(SDL_Keycode key, SDL_EventType eventType, KeyActionCallback callback)
	{
		if (eventType == SDL_KEYDOWN)
		{
			m_keyPressCallbacks[key] = std::move(callback);
		}
		else if (eventType == SDL_KEYUP)
		{
			m_keyReleaseCallbacks[key] = std::move(callback);
		}
	}

	void CallbackManager::addMouseButtonActionCallback(Uint8 button, SDL_EventType eventType, MouseButtonActionCallback callback)
	{
		if (eventType == SDL_MOUSEBUTTONDOWN)
		{
			m_mousePressCallbacks[button] = std::move(callback);
		}
		else if (eventType == SDL_MOUSEBUTTONUP)
		{
			m_mouseReleaseCallbacks[button] = std::move(callback);
		}
	}
} // namespace Sigil