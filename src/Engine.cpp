#include <Sigil/Engine.hpp>

namespace Sigil
{
    Engine::Engine(json configuration)
		: m_config(configuration), m_sceneManager()
    {
    }

	Engine::~Engine()
	{
		SDL_DestroyWindow(window);

		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
	}

	void Engine::init()
	{
		// Initialize SDL
		if (SDL_Init(SDL_INIT_VIDEO) != 0)
		{
			SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not initialize SDL. SDL_Error: %s", SDL_GetError());
		}

		// Initialize SDL_Image
		if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
		{
			SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not initialize SDL_Image. SDL_image Error: %s", IMG_GetError());
		}

		// Initialize SDL_ttf
		if (TTF_Init() != 0)
		{
			SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not initialize TTF. SDL_ttf Error: %s", TTF_GetError());
		}

		//Create window
		auto displayNameCString = m_config["display"]["name"].get<std::string>();
		auto width = m_config["display"]["width"].template get<int>();
		auto height = m_config["display"]["height"].template get<int>();

		window = SDL_CreateWindow(displayNameCString.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
		if (window == nullptr)
		{
			SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create Window. SDL_Error: %s", SDL_GetError());
		}

		m_running = true;
	}

	void Engine::run()
	{
		while (m_running)
		{
			SDL_Event evnt;
			while (SDL_PollEvent(&evnt))
			{
				switch (evnt.type)
				{
				case SDL_EventType::SDL_QUIT:
					quit();
					break;
				case SDL_KEYDOWN:
					handleKeyEvent(evnt);
					break;
				case SDL_KEYUP:
					handleKeyEvent(evnt);
					break;
				case SDL_MOUSEBUTTONDOWN:
					handleMouseEvent(evnt);
					break;
				case SDL_MOUSEBUTTONUP:
					handleMouseEvent(evnt);
					break;
				default:
					break;
				}

				//// Only enqueue keyboard events for the current scene
				//getSceneManagerRef().getCurrentScene()->getActionManagerRef().enqueueKeyboardEvent(m_keyboardEventDispatcher, &evnt);

				//// call update on dispatcher 
				//m_keyboardEventDispatcher.update();
			}
		}
	}

	void Engine::quit()
	{
		m_running = false;
	}

	void Engine::handleKeyEvent(const SDL_Event& event) 
	{
		KeyEvent keyEvent{ static_cast<SDL_EventType>(event.type), event.key };
		auto currentScene = m_sceneManager.getCurrentScene();
		if (currentScene) {
			currentScene->handleKeyEvent(*this, keyEvent);
		}
	}

	void Engine::handleMouseEvent(const SDL_Event& event) 
	{
		MouseEvent mouseEvent{ static_cast<SDL_EventType>(event.type), event.button };
		auto currentScene = m_sceneManager.getCurrentScene();
		if (currentScene) {
			currentScene->handleMouseEvent(*this, mouseEvent);
		}
	}

	void Engine::addNewScene(const std::string& name, std::shared_ptr<SceneBase> scene)
	{
		// TODO: Have this emit a compiler error if trying to add a scene with a name already used
		if (!m_sceneManager.sceneExists(name))
		{
			m_sceneManager.addScene(name, scene);
		}
	}

	void Engine::setCurrentScene(const std::string& name)
	{
		// TODO: Have this emit a compiler error if trying to add a scene with a name already used
		if (m_sceneManager.sceneExists(name))
		{
			m_sceneManager.switchToScene(name);
		}
	}

	std::shared_ptr<SceneBase> Engine::getCurrentScene()
	{
		// TODO: Have this emit a compiler error when trying to
		// getCurrentScene without any added yet
		return m_sceneManager.getCurrentScene();
	}

	SceneManager& Engine::getSceneManagerRef()
	{
		return m_sceneManager;
	}

	entt::dispatcher& Engine::getKeyboardEventDispatcherRef()
	{
		return m_keyboardEventDispatcher;
	}
} // namespace Sigil