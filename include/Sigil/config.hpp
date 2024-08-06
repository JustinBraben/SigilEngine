#ifndef SIGIL_CONFIG_HPP
#define SIGIL_CONFIG_HPP

#include <string>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace Sigil
{
	class Configuration
	{
	public:
		Configuration& setParam(const std::string& paramName, const std::string& value);
		Configuration& setParam(const std::string& paramName, int value);
		Configuration& setParam(const std::string& paramName, bool value);
		Configuration& setParam(const std::string& paramName, float value);
	private:
		json config_json;
	};
}

#endif // SIGIL_CONFIG_HPP