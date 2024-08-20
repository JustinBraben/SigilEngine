#ifndef FACTORIES_HPP
#define FACTORIES_HPP

#include <Sigil/Sigil.hpp>
#include "components.hpp"
namespace Factories 
{
	void createPlayer(entt::registry& world, int x, int y, int w, int h);

	void createBlock(entt::registry& world, int x, int y, int w, int h, terrainType blockType);
} // namespace Factories

#endif // FACTORIES_HPP