#ifndef SIGIL_ACTION_MANAGER_HPP
#define SIGIL_ACTION_MANAGER_HPP

#include <SDL2/SDL.h>
#include <string>
#include <unordered_map>
#include <concepts>

namespace Sigil
{
	// Concept to constrain key event types
	template<auto T>
	concept KeyEventType =
		T == SDL_KEYDOWN || T == SDL_KEYUP;

	template<auto EventType> requires KeyEventType<EventType>
	struct KeyCodePressOrRelease {
		SDL_Keycode m_keycode;
		static constexpr SDL_EventType m_eventType = static_cast<SDL_EventType>(EventType);
	};

	template<auto EventType> requires KeyEventType<EventType>
	class KeyAction
	{
	public:
		KeyAction() = default;
		KeyAction(const std::string& name, SDL_Keycode keycode)
			: m_name(name), m_keycode(keycode) {}

		const std::string& getName() const { return m_name; }
		SDL_Keycode getKeycode() const { return m_keycode; }
		static constexpr SDL_EventType getEventType() { return static_cast<SDL_EventType>(EventType); }

	private:
		std::string m_name = "NONE";
		SDL_Keycode m_keycode = SDLK_q;
	};

	// Concept to constrain mouse button event types
	template<auto T>
	concept MouseButtonEventType =
		T == SDL_MOUSEBUTTONDOWN || T == SDL_MOUSEBUTTONUP;

	template<auto EventType> requires MouseButtonEventType<EventType>
	struct MouseButtonPressOrRelease {
		Uint8 m_button;
		static constexpr SDL_EventType m_eventType = static_cast<SDL_EventType>(EventType);
	};

	template<auto EventType> requires MouseButtonEventType<EventType>
	class MouseButtonAction
	{
	public:
		MouseButtonAction() = default;
		MouseButtonAction(const std::string& name, Uint8 button)
			: m_name(name), m_button(button) {}

		const std::string& getName() const { return m_name; }
		Uint8 getButton() const { return m_button; }
		static constexpr SDL_EventType getEventType() { return static_cast<SDL_EventType>(EventType); }

	private:
		std::string m_name = "NONE";
		Uint8 m_button = SDL_BUTTON_LEFT;
	};

	using KeyPressActionMap = std::unordered_map<std::string, KeyCodePressOrRelease<SDL_KEYDOWN>>;
	using MouseButtonPressActionMap = std::unordered_map<std::string, MouseButtonPressOrRelease<SDL_MOUSEBUTTONDOWN>>;
	using KeyReleaseActionMap = std::unordered_map<std::string, KeyCodePressOrRelease<SDL_KEYUP>>;
	using MouseButtonReleaseActionMap = std::unordered_map<std::string, MouseButtonPressOrRelease<SDL_MOUSEBUTTONUP>>;

	class ActionManager
	{
	public:
		template<auto EventType> requires KeyEventType<EventType>
		void addKeyPressAction(const KeyAction<EventType>& action) {
			if (EventType == SDL_KEYDOWN)
			{
				m_keyPressActions[action.getName()] = { action.getKeycode() };
			}
			else
			{
				m_keyReleaseActions[action.getName()] = { action.getKeycode() };
			}
		}

		template<auto EventType> requires MouseButtonEventType<EventType>
		void addMouseButtonPressAction(const MouseButtonAction<EventType>& action) {
			if (EventType == SDL_MOUSEBUTTONDOWN) 
			{
				m_mouseButtonPressActions[action.getName()] = { action.getButton() };
			}
			else
			{
				m_mouseButtonReleaseActions[action.getName()] = { action.getButton() };
			}
		}

	private:
		KeyPressActionMap m_keyPressActions;
		KeyReleaseActionMap m_keyReleaseActions;
		MouseButtonPressActionMap m_mouseButtonPressActions;
		MouseButtonReleaseActionMap m_mouseButtonReleaseActions;
	};
} // namespace Sigil

#endif // SIGIL_ACTION_MANAGER_HPP