#define SDL_MAIN_HANDLED
#include <Sigil/Sigil.hpp>
#include <iostream>
#include <memory>
#include <fstream>

#include "components.hpp"

class PlatformerMenuScene : public Sigil::SceneBase
{
public:
	PlatformerMenuScene(Sigil::Engine& engine, const std::string& name)
		: SceneBase(engine, name) {}

	void initializeEntities() override {}

	void update(float deltaTime) override {}

	void render(SDL_Renderer* renderer, float deltaTime) override {}
};

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

	void render(SDL_Renderer* renderer, float deltaTime) override {}
};

int main()
{
	std::ifstream inputConfig("./resources/config_files/platformer_config.json");
	json configJson = json::parse(inputConfig);
	int return_code = 0;
	Uint8 r = 20, g = 125, b = 0, a = 255;

	auto configJsonString = configJson.dump(4);
	std::cout << configJsonString << '\n';

	Sigil::Engine engine(configJson);

	engine.init();

	auto platformerMenuScene = std::make_shared<PlatformerMenuScene>(engine, "platformerMenuScene");
	engine.addNewScene("platformerMenuScene", platformerMenuScene);

	auto platformerLevelOne = std::make_shared<PlatformerLevelOne>(engine, "platformerLevelOne");
	engine.addNewScene("platformerLevelOne", platformerLevelOne);
	engine.setCurrentScene("platformerLevelOne");
	
	Sigil::KeyAction<SDL_KEYDOWN> jumpPressed("Jump_Pressed", SDLK_SPACE);
	Sigil::KeyAction<SDL_KEYDOWN> rightPressed("Right_Pressed", SDLK_d);
	Sigil::KeyAction<SDL_KEYDOWN> leftPressed("Left_Pressed", SDLK_a);
	Sigil::KeyAction<SDL_KEYUP> jumpReleased("Jump_Released", SDLK_SPACE);
	Sigil::KeyAction<SDL_KEYUP> rightReleased("Right_Released", SDLK_d);
	Sigil::KeyAction<SDL_KEYUP> leftReleased("Left_Released", SDLK_a);
	engine.getCurrentScene()->getActionManager().addKeyAction(jumpPressed);
	engine.getCurrentScene()->getActionManager().addKeyAction(rightPressed);
	engine.getCurrentScene()->getActionManager().addKeyAction(leftPressed);
	engine.getCurrentScene()->getActionManager().addKeyAction(jumpReleased);
	engine.getCurrentScene()->getActionManager().addKeyAction(rightReleased);
	engine.getCurrentScene()->getActionManager().addKeyAction(leftReleased);

	engine.run();

	return return_code;
}