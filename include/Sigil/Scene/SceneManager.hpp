#ifndef SIGIL_SCENE_MANAGER_HPP
#define SIGIL_SCENE_MANAGER_HPP

#include <Sigil/EngineFwd.hpp>
#include <Sigil/Scene/SceneBase.hpp>

#include <unordered_map>
#include <memory>
#include <string>
#include <iostream>

namespace Sigil
{
	using SceneMap = std::unordered_map<std::string, std::shared_ptr<SceneBase>>;
	using NameScenePair = std::pair<std::string, std::shared_ptr<SceneBase>>;

	class SceneManager
	{
	public:
		SceneManager() = delete;
		SceneManager(Engine& engine);
		~SceneManager();

		void addScene(const std::string& name, std::shared_ptr<SceneBase> scene);
		void switchToScene(const std::string& name);

		bool sceneExists(const std::string& name) const;

		std::shared_ptr<SceneBase> getCurrentScene();
		SceneMap& getSceneMap();

	protected:
		Engine& m_engine;
		std::shared_ptr<SceneBase> m_currentScene;
		SceneMap m_scenes;
	};
} // namespace Sigil

#endif // SIGIL_SCENE_MANAGER_HPP