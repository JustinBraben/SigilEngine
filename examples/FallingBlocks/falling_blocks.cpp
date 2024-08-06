#include <Sigil/sigil.hpp>
#include <iostream>

int main()
{
	json config_json;
	int return_code = 0;

	config_json["fps"] = 60;
	config_json["display"]["width"] = 1024;
	config_json["display"]["height"] = 768;
	config_json["display"]["fullscreen"] = false;
	config_json["display"]["resizeable"] = false;

	auto config_json_string = config_json.dump(4);
	std::cout << config_json_string << '\n';

	Sigil::Engine engine(config_json);

	engine.init();

	// TODO: Work on action system, and registering them to exit an SDL window
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

	// auto testscene = make_shared<TestScene>();
	// engine.scenes().add_scene("test", testscene);
	// engine.scenes().switch_to_scene("test");

	// engine.mainloop().run();

	return return_code;
}