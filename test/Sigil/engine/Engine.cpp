#include <gtest/gtest.h>
#include <Sigil/Sigil.hpp>

TEST(Lib, Engine) {
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
}