#include <Sigil/config.hpp>

namespace Sigil
{
	/*Configuration::Configuration(std::string& configJsonPath)
	{
		std::ifstream configJsonPathStream(configJsonPath);
		config_json = json::parse(configJsonPathStream);
	}*/

	Configuration& Configuration::setParam(const std::string &paramName, const std::string &value)
	{
		config_json[paramName] = value;
		return *this;
	}
    Configuration& Configuration::setParam(const std::string &paramName, int value)
    {
        return setParam(paramName, std::to_string(value));
    }
    Configuration& Configuration::setParam(const std::string &paramName, bool value)
    {
        return setParam(paramName, std::to_string(value));
    }
    Configuration& Configuration::setParam(const std::string &paramName, float value)
    {
        return setParam(paramName, std::to_string(value));
    }
}