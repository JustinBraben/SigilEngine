#ifndef SIGIL_ENGINE_HPP
#define SIGIL_ENGINE_HPP

#include <Sigil/config.hpp>

namespace Sigil
{
	class Engine
	{
	public:
		Engine() = delete;
		Engine(Configuration& configuration);
		~Engine();

		void init();

	private:
		Configuration config;
	};
}

#endif // SIGIL_ENGINE_HPP