#ifndef SIGIL_ACTION_MANAGER_HPP
#define SIGIL_ACTION_MANAGER_HPP

#include <SDL2/SDL.h>

#include <unordered_map>
#include <string>

namespace Sigil
{
	using NameKeyboardInputPair = std::pair<std::string, SDL_Keycode>;
	using NameMouseInputPair = std::pair<std::string, Uint8>;
	using NameJoystickInputPair = std::pair<std::string, Uint8>;
	using NameActionActivePair = std::pair<std::string, bool>;


	class ActionManager
	{
	public:
		void registerKeyboardAction(const std::string& name, SDL_Keycode key);
		void registerMouseAction(const std::string& name, Uint8 button);
		void registerJoystickAction(const std::string& name, Uint8 button);

		bool isPressed(const std::string& name);
		bool isReleased(const std::string& name);

		bool eventHandler(SDL_Event* evnt);

	private:
		std::unordered_map<std::string, SDL_Keycode> m_actionKeyboardMap;
		std::unordered_map<std::string, Uint8> m_actionMouseMap;
		std::unordered_map<std::string, Uint8> m_actionJoystickMap;

		std::unordered_map<std::string, bool> m_actionActive;
	};
} // namespace Sigil

#endif // SIGIL_ACTION_MANAGER_HPP