#define SDL_MAIN_HANDLED
#include <Sigil/Sigil.hpp>
#include <iostream>
#include <memory>

class PlatformerMenuScene : public Sigil::SceneBase
{
public:
	PlatformerMenuScene(Sigil::Engine& engine, const std::string& name)
		: SceneBase(engine, name) {}

	void initializeEntities() override {}

	void update(float deltaTime) override {}

	void render(SDL_Renderer* renderer, float deltaTime) override {}
};

int main()
{
	json config_json;
	int return_code = 0;
	Uint8 r = 20, g = 125, b = 0, a = 255;

	// Setup config for game
	config_json["fps"] = 60;
	config_json["display"]["name"] = "Platformer";
	config_json["display"]["width"] = 1024;
	config_json["display"]["height"] = 768;
	config_json["display"]["fullscreen"] = false;
	config_json["display"]["resizeable"] = false;

	auto config_json_string = config_json.dump(4);
	std::cout << config_json_string << '\n';

	Sigil::Engine engine(config_json);

	engine.init();

	auto platformerMenuScene = std::make_shared<PlatformerMenuScene>(engine, "platformerMenuScene");
	engine.addNewScene("platformerMenuScene", platformerMenuScene);

	engine.run();

	return return_code;
}