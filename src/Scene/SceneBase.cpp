#include <Sigil/Engine.hpp>
#include <Sigil/Scene/SceneBase.hpp>

namespace Sigil 
{
	SceneBase::SceneBase()
		: m_name("BaseName") {}

	SceneBase::SceneBase(const std::string& inputName)
		: m_name(inputName) {}

	SceneBase::~SceneBase() {}

	std::string SceneBase::getName() const
	{
		return m_name;
	}

	void SceneBase::registerKeyAction(SDL_Keycode key, KeyActionCallback callback)
	{
		m_keyBindings[key] = std::move(callback);
	}

	void SceneBase::registerMouseAction(Uint8 button, MouseActionCallback callback)
	{
		m_mouseBindings[button] = std::move(callback);
	}

	void SceneBase::handleKeyEvent(Engine& engine, const KeyEvent& event) {
		auto it = m_keyBindings.find(event.key_evnt.keysym.sym);
		if (it != m_keyBindings.end()) {
			it->second(engine, event);
		}
	}

	void SceneBase::handleMouseEvent(Engine& engine, const MouseEvent& event) {
		auto it = m_mouseBindings.find(event.mouse_evnt.button);
		if (it != m_mouseBindings.end()) {
			it->second(engine, event);
		}
	}
	
	void SceneBase::addSystem(SystemFunction system)
	{
		m_systems.push_back(std::move(system));
	}

	void SceneBase::runSystems(Uint64 deltaTime)
	{
		for (auto& system : m_systems)
		{
			system(m_registry, deltaTime);
		}
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