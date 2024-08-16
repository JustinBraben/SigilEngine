#include <Sigil/Scene/SceneManager.hpp>
#include <Sigil/Engine.hpp>

namespace Sigil
{
	/*SceneManager::SceneManager()
		: m_currentScene(nullptr) {}*/

	SceneManager::SceneManager(Engine& engine)
		: m_engine(engine) {}

	SceneManager::~SceneManager() 
	{
		
	}

	void SceneManager::addScene(const std::string& name, std::shared_ptr<SceneBase> scene) 
	{
		m_scenes.insert(NameScenePair(name, scene));
	}

	void SceneManager::switchToScene(const std::string& name) 
	{
		if (m_scenes.contains(name))
		{
			m_currentScene = m_scenes.at(name);
		}
		else
		{
			std::cout << "Tried to switch to scene : " << name << " which does not exist!\n";
		}
	}

	bool SceneManager::sceneExists(const std::string& name) const
	{
		return m_scenes.contains(name);
	}

	std::shared_ptr<SceneBase> SceneManager::getCurrentScene()
	{
		return m_currentScene;
	}
} // namespace Sigil