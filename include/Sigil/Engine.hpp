#ifndef SIGIL_ENGINE_HPP
#define SIGIL_ENGINE_HPP

#include <SDL2/SDL.h>
#include <Sigil/Scene/SceneManager.hpp>
#include <Sigil/AssetManager.hpp>

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

		void update(float deltaTime);
		void render(float deltaTime);

		void handleKeyEvent(const SDL_Event& event);
		void handleMouseEvent(const SDL_Event& event);

		void addNewScene(const std::string& name, std::shared_ptr<SceneBase> scene);
		void setCurrentScene(const std::string& name);
		std::shared_ptr<SceneBase> getCurrentScene();

		float ticksToSeconds(Uint64 ticks) const;

	private:

		SDL_Window* m_window			= NULL;
		SDL_Renderer* m_renderer		= NULL;
		json m_config;

		SceneManager m_sceneManager;
		AssetManager m_assetManager;
		Uint64 m_previousTime;
		Uint64 m_currentTime;
		Uint64 m_deltaTime;
		bool m_running;
	};
} // namespace Sigil

#endif // SIGIL_ENGINE_HPP