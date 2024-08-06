#ifndef SIGIL_ENGINE_HPP
#define SIGIL_ENGINE_HPP

#include <Sigil/renderer.hpp>

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace Sigil
{
	class Engine
	{
	public:
		Engine() = delete;
		Engine(json configuration);
		~Engine();

		void init();

		SDL_Window* window;

	private:
		json config;

		Renderer m_renderer;
	};
}

#endif // SIGIL_ENGINE_HPP