#include <Sigil/Renderer.hpp>

namespace Sigil
{
	void Renderer::set_renderer(SDL_Renderer* inputRenderer)
	{
		m_renderer = inputRenderer;
	}

	bool Renderer::clear()
	{
		if (SDL_RenderClear(m_renderer) != 0)
        {
			SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not RenderClear SDL. SDL_Error: %s", SDL_GetError());
            return false;
        }

        return true;
	}

	void Renderer::present()
	{
		SDL_RenderPresent(m_renderer);
	}
} // namespace Sigil