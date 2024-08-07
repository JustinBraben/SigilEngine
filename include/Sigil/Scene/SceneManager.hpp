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
		SceneManager();
		~SceneManager();

		void addScene(const std::string& name, std::shared_ptr<SceneBase> scene);
		void switchToScene(const std::string& name);

		std::shared_ptr<SceneBase> getCurrentScene();

	protected:
		std::shared_ptr<SceneBase> m_currentScene;

		SceneMap m_scenes;
	};
} // namespace Sigil

#endif // SIGIL_SCENE_MANAGER_HPP