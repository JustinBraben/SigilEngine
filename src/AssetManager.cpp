#include <Sigil/AssetManager.hpp>
#include <Sigil/Engine.hpp>

namespace Sigil
{
	AssetManager::AssetManager(Engine& engine)
		: m_engine(engine) {}

	AssetManager::~AssetManager() 
	{
		deinit();
	}

	void AssetManager::init(SDL_Renderer* renderer)
	{
		m_renderer = renderer;

		for (const auto& entry : m_engine.getConfig()["resources"]["fonts"])
		{
			std::cout << "Name : " << entry.at("name") << ", Path: " << entry.at("path") << '\n';
			auto path = entry.at("path").template get<std::string>();
			m_engine.getAssetManager().addFont(m_renderer, path.c_str());
		}
	}

	void AssetManager::deinit()
	{
		// Must destroy all textures in the map
		for (auto [key, value] : m_textureMap)
		{
			if (value != nullptr)
			{
				SDL_DestroyTexture(value);
			}
		}

		m_textureMap.clear();

		for (auto [key, value] : m_fontMap)
		{
			if (value != nullptr)
			{
				TTF_CloseFont(value);
			}
		}

		m_fontMap.clear();
	}

	void AssetManager::addTexture(SDL_Renderer* renderer, const char* file)
	{
		auto* texture = IMG_LoadTexture(renderer, file);
		if (texture == nullptr)
		{
			SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create load texture for m_texture. SDL_Error: %s", SDL_GetError());
		}
		else
		{
			// Use the file name as the key for the texture
			std::string file_as_string = file;
			auto found = file_as_string.find_last_of("/\\");
			auto file_name = file_as_string.substr(found + 1);
			m_textureMap.insert(StringTexturePair(file_name, texture));
		}
	}

	SDL_Texture* AssetManager::getTexture(std::string& textureKey)
	{
		auto* texture = m_textureMap.at(textureKey);
		return texture;
	}

	void AssetManager::addFont(SDL_Renderer* renderer, const char* file)
	{
		auto* font = TTF_OpenFont(file, 28);
		if (font == nullptr)
		{
			SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create load font for m_font. SDL_Error: %s", SDL_GetError());
		}
		else
		{
			// Use the file name as the key for the texture
			std::string file_as_string = file;
			auto found = file_as_string.find_last_of("/\\");
			auto file_name = file_as_string.substr(found + 1);
			m_fontMap.insert(StringFontPair(file_name, font));
		}
	}

	TTF_Font* AssetManager::getFont(std::string& textureKey)
	{
		auto* font = m_fontMap.at(textureKey);
		return font;
	}
} // namespace Sigil