#ifndef PLATFORMER_LEVEL_ONE_HPP
#define PLATFORMER_LEVEL_ONE_HPP

#include <Sigil/Sigil.hpp>

#include "components.hpp"

class PlatformerLevelOne : public Sigil::SceneBase
{
public:
	PlatformerLevelOne(Sigil::Engine& engine, const std::string& name)
		: SceneBase(engine, name) {}

	void initializeEntities() override
	{
		auto player = m_registry.create();
		m_registry.emplace<Position>(player, 200, 300);
		m_registry.emplace<Velocity>(player, 0, 0);
		m_registry.emplace<SpriteSize>(player, 64, 64);
		m_registry.emplace<PlayerState>(player, PlayerState::Idle);
		size_t frame = 0, lastFrame = 10, fps = 30;
		m_registry.emplace<SpriteAnimator>(player, "Idle", frame, lastFrame, 0.f, State::play, fps, 32, 32);
	}

	void update(float deltaTime) override {}

	void render(float deltaTime) override {}
};

#endif // PLATFORMER_LEVEL_ONE_HPP