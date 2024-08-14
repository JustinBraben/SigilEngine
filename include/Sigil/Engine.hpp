#ifndef SIGIL_ENGINE_HPP
#define SIGIL_ENGINE_HPP

#include <SDL2/SDL.h>
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
		void quit();

		void handleKeyEvent(const SDL_Event& event);
		void handleMouseEvent(const SDL_Event& event);

		void addNewScene(const std::string& name, std::shared_ptr<SceneBase> scene);
		void setCurrentScene(const std::string& name);
		std::shared_ptr<SceneBase> getCurrentScene();

	private:

		void render();

		SDL_Window* m_window			= NULL;
		SDL_Renderer* m_renderer		= NULL;
		json m_config;

		SceneManager m_sceneManager;

		bool m_running;
	};
}

#endif // SIGIL_ENGINE_HPP