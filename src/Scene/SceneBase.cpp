#include <Sigil/Engine.hpp>
#include <Sigil/Scene/SceneBase.hpp>

namespace Sigil 
{
	SceneBase::SceneBase()
		: m_name("BaseName") {}

	SceneBase::SceneBase(std::string& inputName)
		: m_name(inputName) {}

	SceneBase::~SceneBase() {}

	std::string SceneBase::getName() const
	{
		return m_name;
	}

	ActionManager& SceneBase::actionManager()
	{
		return m_actionManager;
	}
} // namespace Sigil