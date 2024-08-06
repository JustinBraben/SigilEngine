#define SDL_MAIN_HANDLED
#include <Sigil/Sigil.hpp>
#include <iostream>
#include <memory>

class FallingBlocksScene : public Sigil::SceneBase
{
	// Code goes here to extend the scene to your choosing
};

int main()
{
	json config_json;
	int return_code = 0;

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

	// engine.actions().register_keyboard_action("ui_quit", SDLK_ESCAPE);

	// engine.mainloop().queue_process_handler(
	// 	[&](Uint32)
	// 	{
	// 		if (engine.actions().is_action_pressed("ui_quit"))
	// 		{
	// 			engine.mainloop().quit();
	// 		}
	// 	}
	// );

	auto fallingBlockScene = std::make_shared<FallingBlocksScene>();
	engine.sceneManager().addScene("fallingBlockScene", fallingBlockScene);
	engine.sceneManager().switchToScene("fallingBlockScene");

	// TODO: Add actions to scene, as every scene should have their own actions
	// engine.sceneManager().getCurrentScene().actions().registerKeyboardAction("game_quit", SDLK_ESCAPE);

	engine.mainLoop().run();

	return return_code;
}