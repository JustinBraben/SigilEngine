#include <Sigil/Asset/Animation.hpp>
#include <Sigil/Engine.hpp>

namespace Sigil
{
	Animation::Animation()
		:	m_texture(NULL),
			m_currentFrameIndex(0),
			m_elapsed(0),
			m_state(AnimationState::Pause),
			m_fps(0)
	{
		m_frameIndexes.push_back(0);
	}

	Animation::Animation(SDL_Texture* texture, size_t frameIndexes)
		: m_texture(texture), m_frameIndexes(frameIndexes)
	{
		for (size_t count = 0; count < frameIndexes; count++)
		{
			m_frameIndexes.push_back(count);
		}
	}

	Animation::Animation(SDL_Texture* texture, size_t frameIndexes, size_t currentFrameIndex, float elapsed, AnimationState animationState, size_t fps)
		:	m_texture(texture),
			m_currentFrameIndex(currentFrameIndex),
			m_elapsed(elapsed),
			m_state(animationState),
			m_fps(fps)
	{
		for (size_t count = 0; count < frameIndexes; count++)
		{
			m_frameIndexes.push_back(count);
		}
	}

	Animation::~Animation()
	{

	}
} // namespace Sigil