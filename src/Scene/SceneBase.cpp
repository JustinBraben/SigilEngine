#include <Sigil/Engine.hpp>
#include <Sigil/Scene/SceneBase.hpp>

namespace Sigil 
{
	/*SceneBase::SceneBase()
		: m_engine(), m_name("BaseName") {}*/

	SceneBase::SceneBase(Engine& engine, const std::string& inputName)
		: m_engine(engine), m_name(inputName) {}

	SceneBase::~SceneBase() {}

	std::string SceneBase::getName() const
	{
		return m_name;
	}

	/*void SceneBase::registerKeyAction(SDL_Keycode key, KeyActionCallback callback)
	{
		m_keyBindings[key] = std::move(callback);
	}

	void SceneBase::registerMouseAction(Uint8 button, MouseActionCallback callback)
	{
		m_mouseBindings[button] = std::move(callback);
	}*/

    void SceneBase::registerKeyAction(const std::string& name, SDL_Keycode key)
    {
		KeyAction<SDL_KEYDOWN> actionPressed(name + "_Pressed", key);
		KeyAction<SDL_KEYUP> actionReleased(name + "_Released", key);
		m_actionManager.addKeyAction(actionPressed);
		m_actionManager.addKeyAction(actionReleased);
    }

    void SceneBase::registerMouseButtonAction(const std::string &name, Uint8 button)
    {
		MouseButtonAction<SDL_MOUSEBUTTONDOWN> actionPressed(name + "_Pressed", button);
		MouseButtonAction<SDL_MOUSEBUTTONUP> actionReleased(name + "_Released", button);
		m_actionManager.addMouseButtonAction(actionPressed);
		m_actionManager.addMouseButtonAction(actionReleased);
    }

    void SceneBase::registerKeyActionCallback(SDL_Keycode key, SDL_EventType eventType, KeyActionCallback callback)
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

    void SceneBase::registerMouseButtonActionCallback(Uint8 button, SDL_EventType eventType, MouseActionCallback callback)
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

    void SceneBase::handleKeyEvent(Engine &engine, const KeyEvent &event)
    {
		if (event.evnt_type == SDL_KEYDOWN) {
			auto it = m_keyPressCallbacks.find(event.key_evnt.keysym.sym);
			if (it != m_keyPressCallbacks.end()) {
				it->second(engine, event);
			}
		}

		if (event.evnt_type == SDL_KEYUP) {
			auto it = m_keyReleaseCallbacks.find(event.key_evnt.keysym.sym);
			if (it != m_keyReleaseCallbacks.end()) {
				it->second(engine, event);
			}
		}
    }

    void SceneBase::handleMouseEvent(Engine& engine, const MouseEvent& event) {
		if (event.evnt_type == SDL_MOUSEBUTTONDOWN) {
			auto it = m_mousePressCallbacks.find(event.mouse_evnt.button);
			if (it != m_mousePressCallbacks.end()) {
				it->second(engine, event);
			}
		}

		if (event.evnt_type == SDL_MOUSEBUTTONDOWN) {
			auto it = m_mouseReleaseCallbacks.find(event.mouse_evnt.button);
			if (it != m_mouseReleaseCallbacks.end()) {
				it->second(engine, event);
			}
		}
	}

	void SceneBase::handleKeyEventNew(Engine& engine, const SDL_Event& event) {
		// auto keydownAction = m_actionManager.getKeyAction<SDL_KEYDOWN>(event.key.keysym.sym);
		if (event.key.type == SDL_KEYDOWN)
		{
			auto keyPressIt = m_actionManager.getKeyPressActions().find(event.key.keysym.sym);
			if (keyPressIt != m_actionManager.getKeyPressActions().end()) {

				// auto keyPressCallbackIt = m_mousePressCallbacks.find(event.key.keysym.sym);
				// if (keyPressCallbackIt != m_mousePressCallbacks.end()){
				// 	keyPressCallbackIt->second(engine, event);
				// }
			}
		}

		if (event.key.type == SDL_KEYUP)
		{
			auto keyReleaseIt = m_actionManager.getKeyReleaseActions().find(event.key.keysym.sym);
			if (keyReleaseIt != m_actionManager.getKeyReleaseActions().end()) {
				// Run KeyReleaseAction callback that is associated with keyPressIt
			}
		}
	}

    void SceneBase::handleMouseEventNew(Engine &engine, const SDL_Event &event)
    {
		if (event.button.type == SDL_MOUSEBUTTONDOWN)
		{
			auto mousePressIt = m_actionManager.getMouseButtonPressActions().find(event.button.button);
			if (mousePressIt != m_actionManager.getMouseButtonPressActions().end()) {
				// Run KeyPressAction callback that is associated with keyPressIt
			}
		}

		if (event.button.type == SDL_MOUSEBUTTONUP)
		{
			auto mouseReleaseIt = m_actionManager.getMouseButtonReleaseActions().find(event.button.button);
			if (mouseReleaseIt != m_actionManager.getMouseButtonReleaseActions().end()) {
				// Run KeyReleaseAction callback that is associated with keyPressIt
			}
		}
    }

    void SceneBase::addSystem(SystemFunction system)
    {
		m_systems.push_back(std::move(system));
	}

	void SceneBase::runSystems(float deltaTime)
	{
		for (auto& system : m_systems)
		{
			system(m_registry, deltaTime);
		}
	}

	ActionManager& SceneBase::getActionManager()
	{
		return m_actionManager;
	}

	void SceneBase::clearRegistry()
	{
		m_registry.clear();
	}

	void SceneBase::initializeScene()
	{
		clearRegistry();
		initializeEntities();
	}
} // namespace Sigil