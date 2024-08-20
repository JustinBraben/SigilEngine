#include <Sigil/Scene/SceneBase.hpp>
#include <Sigil/Engine.hpp>

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

    void SceneBase::registerKeyAction(const std::string& name, SDL_Keycode key)
    {
		KeyAction<SDL_KEYDOWN> actionPressed(name + "_Pressed", key);
		KeyAction<SDL_KEYUP> actionReleased(name + "_Released", key);
		getActionManager().addKeyAction(actionPressed);
		getActionManager().addKeyAction(actionReleased);
    }

    void SceneBase::registerMouseButtonAction(const std::string &name, Uint8 button)
    {
		MouseButtonAction<SDL_MOUSEBUTTONDOWN> actionPressed(name + "_Pressed", button);
		MouseButtonAction<SDL_MOUSEBUTTONUP> actionReleased(name + "_Released", button);
		getActionManager().addMouseButtonAction(actionPressed);
		getActionManager().addMouseButtonAction(actionReleased);
    }

    void SceneBase::registerKeyActionCallback(SDL_Keycode key, SDL_EventType eventType, KeyActionCallback callback)
    {
		getCallbackManager().addKeyActionCallback(key, eventType, callback);
    }

    void SceneBase::registerMouseButtonActionCallback(Uint8 button, SDL_EventType eventType, MouseButtonActionCallback callback)
    {
		getCallbackManager().addMouseButtonActionCallback(button, eventType, callback);
    }

    void SceneBase::handleKeyEvent(const KeyEvent &event)
    {
		if (event.evnt_type == SDL_KEYDOWN) {
			auto& keyPressCallBacksRef = getCallbackManager().getKeyPressCallbacks();
			auto it = keyPressCallBacksRef.find(event.key_evnt.keysym.sym);
			if (it != keyPressCallBacksRef.end()) {
				m_keyPressActionQueue.push(event);
			}
		}

		if (event.evnt_type == SDL_KEYUP) {
			auto& keyReleaseCallBacksRef = getCallbackManager().getKeyReleaseCallbacks();
			auto it = keyReleaseCallBacksRef.find(event.key_evnt.keysym.sym);
			if (it != keyReleaseCallBacksRef.end()) {
				m_keyReleaseActionQueue.push(event);
			}
		}
    }

    void SceneBase::handleMouseButtonEvent(const MouseButtonEvent& event) {
		if (event.evnt_type == SDL_MOUSEBUTTONDOWN) {
			auto& mousePressCallBacksRef = getCallbackManager().getMousePressCallbacks();
			auto it = mousePressCallBacksRef.find(event.mouse_evnt.button);
			if (it != mousePressCallBacksRef.end()) {
				m_mouseButtonPressActionQueue.push(event);
			}
		}

		if (event.evnt_type == SDL_MOUSEBUTTONDOWN) {
			auto& mouseReleaseCallBacksRef = getCallbackManager().getMouseReleaseCallbacks();
			auto it = mouseReleaseCallBacksRef.find(event.mouse_evnt.button);
			if (it != mouseReleaseCallBacksRef.end()) {
				m_mouseButtonReleaseActionQueue.push(event);
			}
		}
	}

	void SceneBase::processActions()
	{
		processKeyActions();
		processMouseActions();
	}

	void SceneBase::processKeyActions()
	{
		while (!m_keyPressActionQueue.empty())
		{
			auto action = m_keyPressActionQueue.front();
			auto& keyPressCallBacksRef = getCallbackManager().getKeyPressCallbacks();
			auto it = keyPressCallBacksRef.find(action.key_evnt.keysym.sym);
			if (it != keyPressCallBacksRef.end()) {
				it->second(m_engine, action);
			}
			m_keyPressActionQueue.pop();
		}

		while (!m_keyReleaseActionQueue.empty())
		{
			auto action = m_keyReleaseActionQueue.front();
			auto& keyReleaseCallBacksRef = getCallbackManager().getKeyReleaseCallbacks();
			auto it = keyReleaseCallBacksRef.find(action.key_evnt.keysym.sym);
			if (it != keyReleaseCallBacksRef.end()) {
				it->second(m_engine, action);
			}
			m_keyReleaseActionQueue.pop();
		}
	}

	void SceneBase::processMouseActions()
	{
		while (!m_mouseButtonPressActionQueue.empty())
		{
			auto action = m_mouseButtonPressActionQueue.front();
			auto& mouseButtonPressCallBacksRef = getCallbackManager().getMousePressCallbacks();
			auto it = mouseButtonPressCallBacksRef.find(action.mouse_evnt.button);
			if (it != mouseButtonPressCallBacksRef.end()) {
				it->second(m_engine, action);
			}
			m_mouseButtonPressActionQueue.pop();
		}

		while (!m_mouseButtonReleaseActionQueue.empty())
		{
			auto action = m_mouseButtonReleaseActionQueue.front();
			auto& mouseButtonReleaseCallBacksRef = getCallbackManager().getMouseReleaseCallbacks();
			auto it = mouseButtonReleaseCallBacksRef.find(action.mouse_evnt.button);
			if (it != mouseButtonReleaseCallBacksRef.end()) {
				it->second(m_engine, action);
			}
			m_mouseButtonReleaseActionQueue.pop();
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

	CallbackManager& SceneBase::getCallbackManager()
	{
		return m_callbackManager;
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