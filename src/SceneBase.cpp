#include <Sigil/Engine.hpp>
#include <Sigil/SceneBase.hpp>

namespace Sigil 
{
	SceneBase::SceneBase()
		: m_name("BaseName") {}

	std::string SceneBase::getName() const
	{
		return m_name;
	}
}