#ifndef SIGIL_ENGINE_HPP
#define SIGIL_ENGINE_HPP

#include <Sigil/Renderer.hpp>
#include <Sigil/Scene/SceneManager.hpp>

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <nlohmann/json.hpp>
#include <entt/signal/dispatcher.hpp>

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

		SceneManager& getSceneManagerRef();
		entt::dispatcher& getKeyboardEventDispatcherRef();

		SDL_Window* window;

	private:
		json m_config;

		SceneManager m_sceneManager;
		Renderer m_renderer;

		entt::dispatcher m_keyboardEventDispatcher;

		bool m_running;
	};
}

#endif // SIGIL_ENGINE_HPP