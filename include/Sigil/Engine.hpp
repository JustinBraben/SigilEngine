#ifndef SIGIL_ENGINE_HPP
#define SIGIL_ENGINE_HPP

#include <Sigil/Renderer.hpp>
#include <Sigil/Scene/SceneManager.hpp>

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
		void run();

		SceneManager& getSceneManagerRef();

		SDL_Window* window;

	private:
		json m_config;

		SceneManager m_sceneManager;
		Renderer m_renderer;


		bool m_running;
	};
}

#endif // SIGIL_ENGINE_HPP