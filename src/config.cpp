#include <Sigil/config.hpp>

namespace Sigil
{
	/*Configuration::Configuration(std::string& configJsonPath)
	{
		std::ifstream configJsonPathStream(configJsonPath);
		config_json = json::parse(configJsonPathStream);
	}*/

	std::string Configuration::getString(const std::string& param, const std::string& _default) const
	{
		std::string result;

		// Get the parameter within member config_json using param string

		// If the param string is not found in the json, return the default value instead

		return result;
	}

	int Configuration::getParamAsInt(const std::string& param, int _default) const
	{
		return 0;
	}

	Configuration& Configuration::setStringParam(const std::string& param, const std::string& value)
	{
		// Set parameter within member config_json using param string

		// Then return itself
		return *this;
	}
}