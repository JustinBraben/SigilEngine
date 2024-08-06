#ifndef SIGIL_SCENE_BASE_HPP
#define SIGIL_SCENE_BASE_HPP

#include <string>

namespace Sigil 
{
	class SceneBase
	{
	public:
		SceneBase();

		virtual void load() = 0;
		virtual void unload() = 0;

		std::string getName() const;

	protected:
		std::string m_name;
	};
}

#endif // SIGIL_SCENE_BASE_HPP