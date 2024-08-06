#include <Sigil/Engine.hpp>

namespace Sigil
{
    Engine::Engine(json configuration)
		: config(configuration)
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
		window = SDL_CreateWindow("Falling Blocks", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 768, SDL_WINDOW_SHOWN);
		if (window == nullptr)
		{
			SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create Window. SDL_Error: %s", SDL_GetError());
		}
	}
}
