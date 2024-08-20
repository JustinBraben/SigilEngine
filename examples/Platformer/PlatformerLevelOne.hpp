#ifndef PLATFORMER_LEVEL_ONE_HPP
#define PLATFORMER_LEVEL_ONE_HPP

#include <Sigil/Sigil.hpp>

#include "components.hpp"
//#include "Factories.hpp"

class PlatformerLevelOne : public Sigil::SceneBase
{
public:
	PlatformerLevelOne(Sigil::Engine& engine, const std::string& name)
		: SceneBase(engine, name) {}

	void initializeEntities() override
	{
		createPlayer(getRegistry(), 200, 300, 64, 64);
	}

	void update(float deltaTime) override
	{
		runSystems(deltaTime);
	}

	void render(float deltaTime) override 
	{
		auto* renderer = m_engine.getRenderer();
		SDL_SetRenderDrawColor(renderer, 122, 0, 0, 255);
		SDL_RenderClear(renderer);

		auto player_view = m_registry.view<const Position, const Velocity, const SpriteSize, const SpriteSource, const SpriteAnimator>();
		for (const auto [e, pos, vel, sprite_size, sprite_source, sprite_animator] : player_view.each())
		{
			std::string name = sprite_animator.name;
			auto* spriteTexture = m_engine.getAssetManager().getTexture(name);

			int srcX = sprite_source.w * static_cast<int>(sprite_animator.frame);

			SDL_Rect srcRect = { srcX, 0, sprite_source.w, sprite_source.h };
			SDL_Rect dstRect = { pos.x, pos.y, sprite_size.w, sprite_size.h };

			// SDL_RenderCopy(renderer, spriteTexture, &srcRect, &dstRect);
			SDL_RenderCopyEx(renderer, spriteTexture, &srcRect, &dstRect, 0.0, NULL, sprite_animator.flip);
		}
	}

	void createPlayer(entt::registry& world, int x, int y, int w, int h)
	{
		auto player = world.create();
		world.emplace<Position>(player, x, y);
		world.emplace<Velocity>(player, 0, 0);
		world.emplace<SpriteSize>(player, w, h);
		world.emplace<SpriteSource>(player, "Idle", 0, 0, 32, 32);

		size_t frame = 0, lastFrame = 10, fps = 30;
		world.emplace<SpriteAnimator>(player, "Idle", frame, lastFrame, 0.f, State::play, fps, 32, 32, SDL_FLIP_NONE);
		world.emplace<PlayerMovementInput>(player, false, false, false);
	}

	void createBlock(entt::registry& world, int x, int y, int w, int h, terrainType blockType)
	{
		auto block = world.create();
		world.emplace<Position>(block, x, y);
		world.emplace<SpriteSize>(block, w, h);

		switch (blockType)
		{
		case terrainType::Brick:
			world.emplace<SpriteSource>(block, "Terrain", 272, 64, 48, 48);
			break;
		case terrainType::Dirt:
			world.emplace<SpriteSource>(block, "Terrain", 96, 64, 48, 48);
			break;
		default:
			break;
		}
	}
};

#endif // PLATFORMER_LEVEL_ONE_HPP