#ifndef SIGIL_SCENE_MANAGER_HPP
#define SIGIL_SCENE_MANAGER_HPP

#include <Sigil/Scene/SceneBase.hpp>

#include <unordered_map>
#include <memory>
#include <string>

namespace Sigil
{
	using SceneMap = std::unordered_map<std::string, std::shared_ptr<SceneBase>>;

	class SceneManager
	{
	public:
		SceneManager();
		~SceneManager();

		void addScene(const std::string& name, std::shared_ptr<SceneBase> scene);
		void switchToScene(const std::string& name);


	protected:
		SceneMap m_scenes;
	};
}

#endif // SIGIL_SCENE_MANAGER_HPP