#include <Sigil/Action/ActionManager.hpp>

namespace Sigil
{
	void ActionManager::registerKeyboardAction(const std::string& name, SDL_Keycode key)
	{
		m_actionKeyboardMap.insert(NameKeyboardInputPair(name, key));
	}

	void ActionManager::registerMouseAction(const std::string& name, Uint8 button)
	{
		m_actionMouseMap.insert(NameMouseInputPair(name, button));
	}

	void ActionManager::registerJoystickAction(const std::string& name, Uint8 button)
	{
		m_actionJoystickMap.insert(NameJoystickInputPair(name, button));
	}

	bool ActionManager::isPressed(const std::string& name)
	{
		return m_actionActive[name];
	}

	bool ActionManager::isReleased(const std::string& name)
	{
		return !m_actionActive[name];
	}

	bool ActionManager::eventHandler(SDL_Event* evnt)
	{
		switch (evnt->type)
		{
		case SDL_KEYDOWN:
			for (auto& [action, key] : m_actionKeyboardMap)
			{
				if (key == evnt->key.keysym.sym)
				{
					m_actionActive.insert_or_assign(action, true);
					break;
				}
			}
			break;

		case SDL_KEYUP:
			for (auto& [action, key] : m_actionKeyboardMap)
			{
				if (key == evnt->key.keysym.sym)
				{
					m_actionActive.insert_or_assign(action, false);
					break;
				}
			}
			break;

		case SDL_MOUSEBUTTONDOWN:
			for (auto& [action, button] : m_actionMouseMap)
			{
				if (button == evnt->button.button)
				{
					m_actionActive.insert_or_assign(action, true);
					break;
				}
			}
			break;

		case SDL_MOUSEBUTTONUP:
			for (auto& [action, button] : m_actionMouseMap)
			{
				if (button == evnt->button.button)
				{
					m_actionActive.insert_or_assign(action, false);
					break;
				}
			}
			break;

		default:
			break;
		}

		return true;
	}

	entt::dispatcher& ActionManager::getKeyboardEventDispatcherRef() 
	{
		return m_keyboardEventDispatcher;
	}
} // namespace Sigil