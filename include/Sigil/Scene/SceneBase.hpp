#ifndef SIGIL_SCENE_BASE_HPP
#define SIGIL_SCENE_BASE_HPP

#include <Sigil/EngineFwd.hpp>
#include <Sigil/Action/ActionManager.hpp>

#include <string>

namespace Sigil 
{
	class SceneBase
	{
	public:
		SceneBase();
		SceneBase(std::string& inputName);
		~SceneBase();

		std::string getName() const;

		ActionManager& getActionManagerRef();

	protected:
		std::string m_name;
		ActionManager m_actionManager;
	};
} // namespace Sigil

#endif // SIGIL_SCENE_BASE_HPP