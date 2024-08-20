#ifndef PLATFORMER_LEVEL_ONE_HPP
#define PLATFORMER_LEVEL_ONE_HPP

#include <Sigil/Sigil.hpp>

#include "components.hpp"
//#include "Factories.hpp"

class PlatformerLevelOne : public Sigil::SceneBase
{
public:
	PlatformerLevelOne(Sigil::Engine& engine, const std::string& name, json sceneJson)
		: SceneBase(engine, name, sceneJson) {}

	void initializeEntities() override
	{
		for (const auto& entry : m_sceneJson["entities"]["Players"])
		{
			auto gridPosX = entry["GridPosition"]["x"].template get<int>();
			auto gridPosY = entry["GridPosition"]["y"].template get<int>();
			auto gridSizeW = entry["GridSize"]["w"].template get<int>();
			auto gridSizeH = entry["GridSize"]["h"].template get<int>();
			createPlayer(getRegistry(), GridPosition{ gridPosX, gridPosY }, GridSize{ gridSizeW, gridSizeH });
		}

		for (const auto& entry : m_sceneJson["entities"]["Terrain"]["Bricks"])
		{
			auto gridPosX = entry["GridPosition"]["x"].template get<int>();
			auto gridPosY = entry["GridPosition"]["y"].template get<int>();
			auto gridSizeW = entry["GridSize"]["w"].template get<int>();
			auto gridSizeH = entry["GridSize"]["h"].template get<int>();
			createBlock(getRegistry(), GridPosition{ gridPosX, gridPosY }, GridSize{ gridSizeW, gridSizeH }, terrainType::Brick);
		}
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

		renderTerrain();
		renderPlayer();
	}

	void renderTerrain()
	{
		auto* renderer = m_engine.getRenderer();
		SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
		auto block_view = m_registry.view<const Position, const SpriteSize, const SpriteSource>(entt::exclude<SpriteAnimator>);
		for (const auto [e_block, pos, sprite_size, sprite_source] : block_view.each())
		{
			std::string name = sprite_source.name;
			auto* spriteTexture = m_engine.getAssetManager().getTexture(name);

			SDL_Rect srcRect = { sprite_source.x, sprite_source.y, sprite_source.w, sprite_source.h };
			SDL_Rect dstRect = { pos.x, pos.y, sprite_size.w, sprite_size.h };

			SDL_RenderCopyEx(renderer, spriteTexture, &srcRect, &dstRect, 0.0, NULL, SDL_FLIP_NONE);
		}
	}

	void renderPlayer()
	{
		auto* renderer = m_engine.getRenderer();
		auto player_view = m_registry.view<const Position, const Velocity, const SpriteSize, const SpriteSource, const SpriteAnimator>();
		for (const auto [e, pos, vel, sprite_size, sprite_source, sprite_animator] : player_view.each())
		{
			std::string name = sprite_animator.name;
			auto* spriteTexture = m_engine.getAssetManager().getTexture(name);

			int srcX = sprite_source.w * static_cast<int>(sprite_animator.frame);

			SDL_Rect srcRect = { srcX, 0, sprite_source.w, sprite_source.h };
			SDL_Rect dstRect = { pos.x, pos.y, sprite_size.w, sprite_size.h };

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

	void createPlayer(entt::registry& world, GridPosition gridPos, GridSize gridSize)
	{
		auto player = world.create();
		world.emplace<Position>(player, gridPos.x * gridSize.w, gridPos.y * gridSize.h);
		world.emplace<Velocity>(player, 0, 0);
		world.emplace<SpriteSize>(player, gridSize.w, gridSize.h);
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

	void createBlock(entt::registry& world, GridPosition gridPos, GridSize gridSize, terrainType blockType)
	{
		auto block = world.create();
		world.emplace<Position>(block, gridPos.x * gridSize.w, gridPos.y * gridSize.h);
		world.emplace<SpriteSize>(block, gridSize.w, gridSize.h);

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