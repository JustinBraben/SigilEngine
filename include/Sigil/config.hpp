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
		std::string getString(const std::string& param, const std::string& _default = std::string()) const;
		int getParamAsInt(const std::string& param, int _default = 0) const;
		int getParamAsBool(const std::string& param, bool _default = false) const;
		int getParamAsFloat(const std::string& param, float _default = 0.0f) const;

		Configuration& setStringParam(const std::string& param, const std::string& value);
		Configuration& setIntParam(const std::string& param, const std::string& value);
		Configuration& setBoolParam(const std::string& param, const std::string& value);
		Configuration& setFloatParam(const std::string& param, const std::string& value);

	private:
		json config_json;
	};
}

#endif // SIGIL_CONFIG_HPP