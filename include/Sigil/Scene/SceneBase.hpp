#ifndef SIGIL_SCENE_BASE_HPP
#define SIGIL_SCENE_BASE_HPP

#include <Sigil/EngineFwd.hpp>

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

	protected:
		std::string m_name;
	};
}

#endif // SIGIL_SCENE_BASE_HPP