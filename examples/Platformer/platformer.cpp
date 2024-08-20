#define SDL_MAIN_HANDLED
#include <Sigil/Sigil.hpp>
#include <iostream>
#include <memory>
#include <fstream>

#include "components.hpp"
#include "PlatformerLevelOne.hpp"

class PlatformerMenuScene : public Sigil::SceneBase
{
public:
	PlatformerMenuScene(Sigil::Engine& engine, const std::string& name)
		: SceneBase(engine, name) {}

	void initializeEntities() override {}

	void update(float deltaTime) override {}

	void render(float deltaTime) override {}
};

int main()
{
	std::ifstream inputConfig("./resources/config_files/platformer_config.json");
	json configJson = json::parse(inputConfig);
	int return_code = 0;
	/*Uint8 r = 20, g = 125, b = 0, a = 255;*/

	auto configJsonString = configJson.dump(4);
	std::cout << configJsonString << '\n';

	Sigil::Engine engine(configJson);

	engine.init();

	auto platformerMenuScene = std::make_shared<PlatformerMenuScene>(engine, "platformerMenuScene");
	engine.addNewScene("platformerMenuScene", platformerMenuScene);

	auto platformerLevelOne = std::make_shared<PlatformerLevelOne>(engine, "platformerLevelOne");
	engine.addNewScene("platformerLevelOne", platformerLevelOne);
	engine.setCurrentScene("platformerLevelOne");

	engine.getCurrentScene()->registerKeyAction("Jump", SDLK_SPACE);
	engine.getCurrentScene()->registerKeyAction("Right", SDLK_d);
	engine.getCurrentScene()->registerKeyAction("Left", SDLK_a);

	engine.getCurrentScene()->registerKeyActionCallback(SDLK_ESCAPE, SDL_KEYUP, 
		[](Sigil::Engine& eng, const Sigil::KeyEvent& keyboardEvnt) {
			eng.quit();
		}
	);

	// Imagine using it like this
	// Sigil::KeyAction jump("Jump", SDLK_SPACE);
	// Then it generates a KeyUp and KeyDown for SDLK_SPACE

	// engine.getCurrentScene()->registerKeyActionNew("Jump", SDLK_SPACE);
	// engine.getCurrentScene()->registerActionCallback


	engine.run();

	return return_code;
}