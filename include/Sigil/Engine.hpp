#ifndef SIGIL_ENGINE_HPP
#define SIGIL_ENGINE_HPP

#include <Sigil/EngineFwd.hpp>
#include <SDL2/SDL.h>
#include <Sigil/Scene/SceneManager.hpp>
#include <Sigil/Asset/AssetManager.hpp>
#include <Sigil/Action/ActionManager.hpp>
#include <Sigil/Timer.hpp>

#include <SDL_image.h>
#include <SDL_ttf.h>


namespace Sigil
{
	class Engine
	{
	public:
		Engine(json configuration);
		~Engine();

		void init();
		void deinit();
		void run();
		void quit();

		void update(float deltaTime);
		void render(float deltaTime);

		void handleKeyEvent(const SDL_Event& event);
		void handleMouseButtonEvent(const SDL_Event& event);

		void addNewScene(const std::string& name, std::shared_ptr<SceneBase> scene);
		void setCurrentScene(const std::string& name);
		std::shared_ptr<SceneBase> getCurrentScene();

		float ticksToSeconds(Uint64 ticks) const;

		json& getConfig() { return m_config; };
		SDL_Renderer* getRenderer() { return m_renderer; };
		AssetManager& getAssetManager() { return m_assetManager; };
		SceneManager& getSceneManager() { return m_sceneManager; };

	private:

		SDL_Window* m_window			= NULL;
		SDL_Renderer* m_renderer		= NULL;
		json m_config;

		SceneManager m_sceneManager;
		AssetManager m_assetManager;
		Uint64 m_previousTime;
		Uint64 m_currentTime;
		Uint64 m_deltaTime;
		Timer m_timer;
		float m_fps;
		bool m_running;
	};
} // namespace Sigil

#endif // SIGIL_ENGINE_HPP