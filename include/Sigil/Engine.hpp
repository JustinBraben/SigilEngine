#ifndef SIGIL_ENGINE_HPP
#define SIGIL_ENGINE_HPP

#include <Sigil/Renderer.hpp>
#include <Sigil/MainLoop.hpp>

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace Sigil
{
	class Engine
	{
	public:
		Engine(json configuration);
		~Engine();

		void init();

		MainLoop& mainLoop();

		SDL_Window* window;

	private:
		json m_config;

		Renderer m_renderer;
		MainLoop m_mainLoop;
	};
}

#endif // SIGIL_ENGINE_HPP