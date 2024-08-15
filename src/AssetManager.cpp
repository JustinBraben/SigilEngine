#include <Sigil/AssetManager.hpp>

namespace Sigil
{
	AssetManager::~AssetManager() 
	{
		// Must destroy all textures in the map
		for (auto [key, value] : m_textureMap)
		{
			SDL_DestroyTexture(value);
		}
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