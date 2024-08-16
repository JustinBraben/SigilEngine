#ifndef SIGIL_ANIMATION_HPP
#define SIGIL_ANIMATION_HPP

#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <vector>

namespace Sigil
{
	enum class AnimationState {
		Pause,
		Play
	};

	class Animation
	{
	public:
		Animation();
		Animation(SDL_Texture* texture, size_t frameIndexes);
		Animation(SDL_Texture* texture, size_t frameIndexes, size_t currentFrameIndex, float elapsed, AnimationState animationState, size_t fps);
		~Animation();
	private:
		SDL_Texture*		m_texture = NULL;

		// all index values of animation
		std::vector<size_t> m_frameIndexes;

		// Current frame of animation
		size_t				m_currentFrameIndex = 0;

		// time elapsed since last animating
		float				m_elapsed = 0;

		// pause or run the animation
		AnimationState		m_state = AnimationState::Pause;

		// fps the animation is expected to run at
		size_t				m_fps = 0;
	};
} // namespace Sigil

#endif // SIGIL_ANIMATION_HPP