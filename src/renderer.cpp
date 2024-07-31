#include <Sigil/renderer.hpp>

namespace Sigil
{
	void Renderer::set_renderer(SDL_Renderer* rdr)
	{
		renderer = rdr;
	}

	bool Renderer::clear()
	{
		return true;
	}

	void Renderer::present()
	{
		SDL_RenderPresent(renderer);
	}
}