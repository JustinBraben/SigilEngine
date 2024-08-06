#ifndef SIGIL_RENDERER_HPP
#define SIGIL_RENDERER_HPP

#include "SDL2/SDL.h"

namespace Sigil
{
	class Renderer
	{
	public:
		Renderer() = delete;
		void set_renderer(SDL_Renderer* inputRenderer);

		bool clear();
		void present();

	private:
		SDL_Renderer* renderer;
	};
}

#endif // SIGIL_RENDERER_HPP