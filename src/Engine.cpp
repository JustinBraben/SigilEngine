#include <Sigil/Engine.hpp>

namespace Sigil
{
    Engine::Engine(json configuration)
		:	m_config(configuration), 
			m_sceneManager(*this), 
			m_assetManager(*this),
			m_currentTime(0), 
			m_deltaTime(0), 
			m_previousTime(0), 
			m_running(false)
    {
    }

	Engine::~Engine()
	{
		deinit();
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

		m_window = SDL_CreateWindow(displayNameCString.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
		if (m_window == nullptr)
		{
			SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create Window. SDL_Error: %s", SDL_GetError());
		}

		m_renderer = SDL_CreateRenderer(m_window, NULL, SDL_RENDERER_ACCELERATED);
		if (m_renderer == nullptr)
		{
			SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create Renderer. SDL_Error: %s", SDL_GetError());
		}

		m_assetManager.init(m_renderer);

		// Start sending SDL_TextInput events
		SDL_StartTextInput();
	}

	void Engine::deinit()
	{
		SDL_StopTextInput();

		m_assetManager.deinit();

		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);

		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
	}

	// Main game loop
	void Engine::run()
	{
		m_running = true;
		m_previousTime = SDL_GetPerformanceCounter();
		Uint64 fpsUpdateInterval = SDL_GetPerformanceFrequency() / 2; // Update FPS twice per second
		Uint64 fpsLastUpdateTime = m_previousTime;
		int frameCount = 0;
		float fps = 0.0;

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
			}

			m_currentTime = SDL_GetPerformanceCounter();
			m_deltaTime = m_currentTime - m_previousTime;
			float deltaSeconds = ticksToSeconds(m_deltaTime);
			m_previousTime = m_currentTime;

			// Update game logic
			update(deltaSeconds);

			// Render the current scene
			render(deltaSeconds);

			// FPS calculation
			frameCount++;
			if (m_currentTime - fpsLastUpdateTime > fpsUpdateInterval)
			{
				fps = frameCount / ticksToSeconds(m_currentTime - fpsLastUpdateTime);
				frameCount = 0;
				fpsLastUpdateTime = m_currentTime;

				const auto currentSceneStr = m_sceneManager.getCurrentScene()->getName();

				// Update window title with FPS
				std::string title = "Scene : " + currentSceneStr + " FPS: " + std::to_string(static_cast<int>(std::round(fps)));
				SDL_SetWindowTitle(m_window, title.c_str());
			}

			// Add a small delay to control frame rate if needed
			SDL_Delay(16); // Roughly 60 FPS
		}
	}

	void Engine::quit()
	{
		m_running = false;
	}

	void Engine::update(float deltaTime)
	{
		auto currentScene = m_sceneManager.getCurrentScene();
		if (currentScene) {
			currentScene->update(deltaTime);
		}
	}

	void Engine::render(float deltaTime)
	{
		auto currentScene = m_sceneManager.getCurrentScene();
		if (currentScene)
		{
			currentScene->render(m_renderer, deltaTime);
		}

		SDL_RenderPresent(m_renderer);
	}

	// Handles Keyboard events relevant to the current scene
	void Engine::handleKeyEvent(const SDL_Event& event) 
	{
		KeyEvent keyEvent{ static_cast<SDL_EventType>(event.type), event.key };
		auto currentScene = m_sceneManager.getCurrentScene();
		if (currentScene) {
			currentScene->handleKeyEvent(*this, keyEvent);
		}
	}

	// Handles Mouse events relevant to the current scene
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


	float Engine::ticksToSeconds(Uint64 ticks) const
	{
		return static_cast<float>(ticks) / static_cast<float>(SDL_GetPerformanceFrequency());
	}
} // namespace Sigil