#ifndef SIGIL_ACTION_MANAGER_HPP
#define SIGIL_ACTION_MANAGER_HPP

#include <SDL2/SDL.h>
#include <string>
#include <unordered_map>
#include <concepts>

namespace Sigil
{
	// Concept to constrain key event types
	template<typename T>
	concept KeyEventType = std::same_as<T, SDL_EventType> &&
		(std::same_as<std::decay_t<T>, std::decay_t<decltype(SDL_KEYDOWN)>> ||
			std::same_as<std::decay_t<T>, std::decay_t<decltype(SDL_KEYUP)>>);

	template<KeyEventType EventType>
	struct KeyCodePressOrRelease {
		SDL_Keycode m_keycode;
		EventType m_eventType;
	};

	template<KeyEventType EventType>
	class KeyAction
	{
	public:
		KeyAction() = default;
		KeyAction(const std::string& name, SDL_Keycode keycode, EventType eventType)
			: m_name(name), m_keycode(keycode), m_eventType(eventType) {}

		const std::string& getName() const { return m_name; }
		SDL_Keycode getKeycode() const { return m_keycode; }
		EventType getEventType() const { return m_eventType; }
	private:
		std::string m_name = "NONE";
		SDL_Keycode m_keycode = SDLK_q;
		SDL_EventType m_eventType;
	};

	// Concept to constrain mouse button event types
	template<typename T>
	concept MouseButtonEventType = std::same_as<T, SDL_EventType> &&
		(std::same_as<std::decay_t<T>, std::decay_t<decltype(SDL_MOUSEBUTTONDOWN)>> ||
			std::same_as<std::decay_t<T>, std::decay_t<decltype(SDL_MOUSEBUTTONUP)>>);

	template<MouseButtonEventType EventType>
	struct MouseButtonPressOrRelease {
		Uint8 m_button;
		EventType m_eventType;
	};

	template<MouseButtonEventType EventType>
	class MouseButtonAction
	{
	public:
		MouseButtonAction() = default;
		MouseButtonAction(const std::string& name, Uint8 button, EventType eventType)
			: m_name(name), m_button(button), m_eventType(eventType) {}

		const std::string& getName() const { return m_name; }
		Uint8 getButton() const { return m_button; }
		EventType getEventType() const { return m_eventType; }

	private:
		std::string m_name = "NONE";
		Uint8 m_button = SDL_BUTTON_LEFT;
		SDL_EventType m_eventType;
	};

	using KeyActionMap = std::unordered_map<std::string, KeyCodePressOrRelease<SDL_EventType>>;
	using MouseButtonActionMap = std::unordered_map<std::string, MouseButtonPressOrRelease<SDL_EventType>>;

	class ActionManager
	{
	public:
		void addKeyAction(const KeyAction<SDL_EventType>& action) {
			m_keyActions[action.getName()] = { action.getKeycode(), action.getEventType() };
		}

		void addMouseButtonAction(const MouseButtonAction<SDL_EventType>& action) {
			m_mouseButtonActions[action.getName()] = { action.getButton(), action.getEventType() };
		}
	private:
		KeyActionMap m_keyActions;
		MouseButtonActionMap m_mouseButtonActions;
	};
} // namespace Sigil

#endif // SIGIL_ACTION_MANAGER_HPP