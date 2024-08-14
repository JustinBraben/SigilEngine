#define SDL_MAIN_HANDLED
#include <Sigil/Sigil.hpp>
#include <Sigil/Event/EventTypes.hpp>
#include <iostream>
#include <memory>

class FallingBlocksScene : public Sigil::SceneBase
{
	// Code goes here to extend the scene to your choosing
};

class SceneA : public Sigil::SceneBase{};

class SceneB : public Sigil::SceneBase{};

struct KeyboardListener {
	void KeyDown(const Sigil::KeyEvent& keyboardEvnt) {
		switch (keyboardEvnt.evnt_type)
		{
		case SDL_KEYDOWN:
			std::cout << "KeyDown event emitted for key : " << keyboardEvnt.key_evnt.keysym.sym << '\n';
			break;
		default:
			break;
		}
	}
	static void KeyUp(const Sigil::Engine& engine, const Sigil::KeyEvent& keyboardEvnt) {
		
	}
};

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
	engine.getSceneManagerRef().addScene("fallingBlockScene", fallingBlockScene);
	engine.getSceneManagerRef().switchToScene("fallingBlockScene");
	engine.getSceneManagerRef().getCurrentScene()->getActionManagerRef().registerKeyboardAction("quit_game", SDLK_ESCAPE);
	// engine.getSceneManagerRef().getCurrentScene()->getActionManagerRef().registerKeyboardAction("move_up", SDLK_UP);
	engine.getSceneManagerRef().getCurrentScene()->getActionManagerRef().registerKeyboardAction("move_left", SDLK_LEFT);
	// engine.getSceneManagerRef().getCurrentScene()->getActionManagerRef().registerKeyboardAction("move_down", SDLK_DOWN);
	engine.getSceneManagerRef().getCurrentScene()->getActionManagerRef().registerKeyboardAction("move_right", SDLK_RIGHT);

	KeyboardListener kbListener;
	engine.getKeyboardEventDispatcherRef().sink<Sigil::KeyEvent>().connect<&KeyboardListener::KeyDown>(kbListener);

	auto sceneA = std::make_shared<SceneA>();
	auto sceneB = std::make_shared<SceneB>();
	engine.getSceneManagerRef().addScene("sceneA", sceneA);
	engine.getSceneManagerRef().addScene("sceneB", sceneB);

	engine.getSceneManagerRef().switchToScene("sceneA");
	engine.getSceneManagerRef().getCurrentScene()->getActionManagerRef().registerKeyboardAction("move_to_sceneB", SDLK_RIGHT);
	engine.getSceneManagerRef().switchToScene("sceneB");
	engine.getSceneManagerRef().getCurrentScene()->getActionManagerRef().registerKeyboardAction("move_to_sceneA", SDLK_LEFT);

	//engine.getKeyboardEventDispatcherRef().sink<Sigil::KeyEvent>().connect<&KeyboardListener::KeyUp>(kbListener);

	// TODO: Work on mainLoop queueProcessHandler
	// use it to take action such as moving scenes
	// or quiting the window
	/*engine.mainLoop().sceneManager().switchToScene("fallingBlockScene");
	engine.mainLoop().sinkEventQuit();*/

	// engine.mainLoop().m_eventDispatcher.sink<Sigil::Event_Quit>().connect<engine.mainLoop().m_eventListener.HandleQuit()>()

	/*engine.mainLoop().processListHandler(
		[&](Uint32)
		{
			if (engine.sceneManager().getCurrentScene()->actionManager().isPressed("ui_quit"))
			{
	 			engine.mainLoop().quit();
			}
		}
	 );*/

	engine.run();

	return return_code;
}