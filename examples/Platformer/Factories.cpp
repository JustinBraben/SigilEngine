#include "Factories.hpp"

void Factories::createPlayer(entt::registry& world, int x, int y, int w, int h)
{
	auto player = world.create();
	world.emplace<Position>(player, x, y);
	world.emplace<Velocity>(player, 0, 0);
	world.emplace<SpriteSize>(player, w, h);
	world.emplace<SpriteSource>(player, "Idle", 0, 0, 32, 32);

	size_t frame = 0, lastFrame = 10, fps = 30;
	world.emplace<SpriteAnimator>(player, "Idle", frame, lastFrame, 0.f, State::play, fps, 32, 32);
}

void Factories::createBlock(entt::registry& world, int x, int y, int w, int h, terrainType blockType)
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