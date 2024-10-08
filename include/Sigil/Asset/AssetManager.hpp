#ifndef SIGIL_ASSET_MANAGER_HPP
#define SIGIL_ASSET_MANAGER_HPP

#include <Sigil/EngineFwd.hpp>
#include <Sigil/Asset/Animation.hpp>

#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <unordered_map>
#include <string>

namespace Sigil
{
	using TextureMap = std::unordered_map<std::string, SDL_Texture*>;
	using StringTexturePair = std::pair<std::string, SDL_Texture*>;
	using FontMap = std::unordered_map<std::string, TTF_Font*>;
	using StringFontPair = std::pair<std::string, TTF_Font*>;
	using AnimationMap = std::unordered_map<std::string, Animation>;
	using StringAnimationPair = std::pair<std::string, Animation>;

	class AssetManager
	{
	public:
		AssetManager(Engine& engine);
		~AssetManager();

		void init(SDL_Renderer* renderer);
		void deinit();

		void addTexture(const char* name, const char* file);
		SDL_Texture* getTexture(std::string& textureKey);

		void addFont(const char* name, const char* file, int fontSize);
		TTF_Font* getFont(std::string& textureKey);

		void addAnimation(const char* name, const char* textureName, size_t totalFrames, AnimationState state, size_t fps);
		Animation getAnimation(std::string& animationKey);

	private:
		Engine&			m_engine;
		SDL_Renderer*	m_renderer = NULL;
		TextureMap		m_textureMap;
		FontMap			m_fontMap;
		AnimationMap	m_animationMap;
	};
} // namespace Sigil

#endif // SIGIL_ASSET_MANAGER_HPP