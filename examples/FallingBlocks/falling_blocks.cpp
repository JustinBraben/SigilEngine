#define SDL_MAIN_HANDLED
#include <Sigil/Sigil.hpp>
#include <iostream>
#include <memory>

class FallingBlocksScene : public Sigil::SceneBase
{
	// Code goes here to extend the scene to your choosing
};

class SceneA : public Sigil::SceneBase{};

class SceneB : public Sigil::SceneBase{};

int main()
{
	json config_json;
	int return_code = 0;

	// Setup config for game
	config_json["fps"] = 60;
	config_json["display"]["name"] = "Falling Blocks";
	config_json["display"]["width"] = 1024;
	config_json["display"]["height"] = 768;
	config_json["display"]["fullscreen"] = false;
	config_json["display"]["resizeable"] = false;

	auto config_json_string = config_json.dump(4);
	std::cout << config_json_string << '\n';

	Sigil::Engine engine(config_json);

	engine.init(); 

	auto fallingBlockScene = std::make_shared<FallingBlocksScene>();
	engine.addNewScene("fallingBlockScene", fallingBlockScene);
	engine.setCurrentScene("fallingBlockScene");
	engine.getCurrentScene()->registerKeyAction(SDLK_ESCAPE, [](Sigil::Engine& eng, const Sigil::KeyEvent& keyboardEvnt) {
		if (keyboardEvnt.evnt_type == SDL_KEYDOWN) {
			eng.quit();
		}
	});
	engine.getCurrentScene()->registerKeyAction(SDLK_UP, [](Sigil::Engine& eng, const Sigil::KeyEvent& keyboardEvnt) {
		if (keyboardEvnt.evnt_type == SDL_KEYDOWN) {
			std::cout << "Up arrow pressed!\n";
		}
		if (keyboardEvnt.evnt_type == SDL_KEYUP) {
			std::cout << "Up arrow released!\n";
		}
	});

	auto sceneA = std::make_shared<SceneA>();
	auto sceneB = std::make_shared<SceneB>();
	engine.addNewScene("sceneA", sceneA);
	engine.addNewScene("sceneB", sceneB);

	engine.setCurrentScene("sceneA");
	engine.getCurrentScene()->registerKeyAction(SDLK_RIGHT, [](Sigil::Engine& eng, const Sigil::KeyEvent& keyboardEvnt) {
		if (keyboardEvnt.evnt_type == SDL_KEYUP) {
			std::cout << "Switching from sceneA to fallingBlockScene!\n";
			eng.setCurrentScene("fallingBlockScene");
		}
	});
	engine.getCurrentScene()->registerKeyAction(SDLK_ESCAPE, [](Sigil::Engine& eng, const Sigil::KeyEvent& keyboardEvnt) {
		if (keyboardEvnt.evnt_type == SDL_KEYDOWN) {
			std::cout << "There is no escape from sceneA...\n";
		}
	});

	engine.setCurrentScene("sceneB");
	engine.getCurrentScene()->registerKeyAction(SDLK_LEFT, [](Sigil::Engine& eng, const Sigil::KeyEvent& keyboardEvnt) {
		if (keyboardEvnt.evnt_type == SDL_KEYUP) {
			std::cout << "Switching from sceneB to fallingBlockScene!\n";
			eng.setCurrentScene("fallingBlockScene");
		}
	});
	engine.getCurrentScene()->registerKeyAction(SDLK_ESCAPE, [](Sigil::Engine& eng, const Sigil::KeyEvent& keyboardEvnt) {
		if (keyboardEvnt.evnt_type == SDL_KEYDOWN) {
			std::cout << "There is no escape from sceneB...\n";
		}
	});

	engine.setCurrentScene("fallingBlockScene");
	engine.getCurrentScene()->registerKeyAction(SDLK_LEFT, [](Sigil::Engine& eng, const Sigil::KeyEvent& keyboardEvnt) {
		if (keyboardEvnt.evnt_type == SDL_KEYUP) {
			std::cout << "Switching from fallingBlockScene to sceneA!\n";
			eng.setCurrentScene("sceneA");
		}
	});
	engine.getCurrentScene()->registerKeyAction(SDLK_RIGHT, [](Sigil::Engine& eng, const Sigil::KeyEvent& keyboardEvnt) {
		if (keyboardEvnt.evnt_type == SDL_KEYUP) {
			std::cout << "Switching from fallingBlockScene to sceneB!\n";
			eng.setCurrentScene("sceneB");
		}
	});

	engine.run();

	return return_code;
}