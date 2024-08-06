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

	return return_code;
}