#include <Sigil/Asset/AssetManager.hpp>
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
			auto name = entry.at("name").template get<std::string>();
			auto path = entry.at("path").template get<std::string>();
			m_engine.getAssetManager().addFont(name.c_str(), path.c_str(), 18);
		}

		for (const auto& entry : m_engine.getConfig()["resources"]["textures"])
		{
			std::cout << "Name : " << entry.at("name") << ", Path: " << entry.at("path") << '\n';
			auto name = entry.at("name").template get<std::string>();
			auto path = entry.at("path").template get<std::string>();
			m_engine.getAssetManager().addTexture(name.c_str(), path.c_str());
		}

		for (const auto& entry : m_engine.getConfig()["resources"]["animation"])
		{
			std::cout << "Name : " << entry.at("name") << ", Path: " << entry.at("path") << '\n';
			auto name = entry.at("name").template get<std::string>();
			auto path = entry.at("path").template get<std::string>();
			auto totalFrames = entry.at("totalFrames").template get<size_t>();
			auto fps = entry.at("fps").template get<size_t>();
			m_engine.getAssetManager().addAnimation(name.c_str(), name.c_str(), totalFrames, AnimationState::Pause, fps);
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

	void AssetManager::addTexture(const char* name, const char* file)
	{
		auto* texture = IMG_LoadTexture(m_renderer, file);
		if (texture == nullptr)
		{
			SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not load texture for m_texture. SDL_Error: %s", SDL_GetError());
		}
		else
		{
			// Use the file name as the key for the texture
			/*std::string file_as_string = file;
			auto found = file_as_string.find_last_of("/\\");
			auto file_name = file_as_string.substr(found + 1);*/
			m_textureMap.insert(StringTexturePair(name, texture));
		}
	}

	SDL_Texture* AssetManager::getTexture(std::string& textureKey)
	{
		auto* texture = m_textureMap.at(textureKey);
		return texture;
	}

	void AssetManager::addFont(const char* name, const char* file, int fontSize)
	{
		auto* font = TTF_OpenFont(file, fontSize);
		if (font == nullptr)
		{
			SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create load font for m_font. SDL_Error: %s", SDL_GetError());
		}
		else
		{
			// Use the file name as the key for the texture
			/*std::string file_as_string = file;
			auto found = file_as_string.find_last_of("/\\");
			auto file_name = file_as_string.substr(found + 1);*/
			m_fontMap.insert(StringFontPair(name, font));
		}
	}

	TTF_Font* AssetManager::getFont(std::string& textureKey)
	{
		auto* font = m_fontMap.at(textureKey);
		return font;
	}

	void AssetManager::addAnimation(const char* name, const char* textureName, size_t totalFrames, AnimationState state, size_t fps)
	{
		if (m_textureMap.contains(textureName))
		{
			std::string textureNameString = textureName;
			auto* animationTexture = getTexture(textureNameString);
			Animation animation(animationTexture, totalFrames, 0, 0.f, state, fps);
			m_animationMap.insert(StringAnimationPair(name, animation));
		}
		else
		{
			std::cout << "Could not find texture : " << textureName << " to use for animation : " << name << '\n';
		}

	}
	Animation AssetManager::getAnimation(std::string& animationKey)
	{
		auto animation = m_animationMap.at(animationKey);
		return animation;
	}
} // namespace Sigil