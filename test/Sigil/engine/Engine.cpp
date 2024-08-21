#include <gtest/gtest.h>
#include <Sigil/Sigil.hpp>

class TestScene : public Sigil::SceneBase
{
public:
	TestScene(Sigil::Engine& engine, const std::string& name)
		: SceneBase(engine, name) {}

	void initializeEntities() override {}

	void update(float deltaTime) override {}

	void render(float deltaTime) override {}
};

TEST(Engine, Basic) {
	json config_json;
	config_json["fps"] = 60;
	config_json["display"]["name"] = "Falling Blocks";
	config_json["display"]["width"] = 1024;
	config_json["display"]["height"] = 768;
	config_json["display"]["fullscreen"] = false;
	config_json["display"]["resizeable"] = false;

	Sigil::Engine engine(config_json);

	ASSERT_TRUE(!engine.getConfig().empty());
	ASSERT_EQ(2, engine.getConfig().size());

	auto testScene = std::make_shared<TestScene>(engine, "testScene");
	engine.addNewScene("testScene", testScene);

	ASSERT_EQ(1, engine.getSceneManager().getSceneMap().size());
}

TEST(Engine, Advanced) {
	json config_json;
	config_json["fps"] = 144;
	config_json["display"]["name"] = "Advanced";
	config_json["display"]["width"] = 1024;
	config_json["display"]["height"] = 768;
	config_json["display"]["fullscreen"] = true;
	config_json["display"]["resizeable"] = true;

	Sigil::Engine engine(config_json);

	ASSERT_TRUE(!engine.getConfig().empty());
	ASSERT_EQ(2, engine.getConfig().size());

	auto testScene = std::make_shared<TestScene>(engine, "testScene");
	engine.addNewScene("testScene", testScene);

	ASSERT_EQ(1, engine.getSceneManager().getSceneMap().size());
}