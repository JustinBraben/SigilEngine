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
	engine.sceneManager().addScene("fallingBlockScene", fallingBlockScene);
	engine.sceneManager().switchToScene("fallingBlockScene");
	engine.sceneManager().getCurrentScene()->actionManager().registerKeyboardAction("ui_quit", SDLK_ESCAPE);

	auto sceneA = std::make_shared<SceneA>();
	auto sceneB = std::make_shared<SceneB>();
	engine.sceneManager().addScene("sceneA", sceneA);
	engine.sceneManager().addScene("sceneB", sceneB);

	engine.sceneManager().switchToScene("sceneA");
	engine.sceneManager().getCurrentScene()->actionManager().registerKeyboardAction("MoveTo_SceneB", SDLK_RIGHT);
	engine.sceneManager().switchToScene("sceneB");
	engine.sceneManager().getCurrentScene()->actionManager().registerKeyboardAction("MoveTo_SceneA", SDLK_LEFT);

	// TODO: Work on mainLoop queueProcessHandler
	// use it to take action such as moving scenes
	// or quiting the window
	engine.sceneManager().switchToScene("fallingBlockScene");
	 engine.mainLoop().processListHandler(
	 	[&](Uint32)
	 	{
	 		if (engine.sceneManager().getCurrentScene()->actionManager().isPressed("ui_quit"))
	 		{
	 			engine.mainLoop().quit();
	 		}
	 	}
	 );

	engine.mainLoop().run();

	return return_code;
}