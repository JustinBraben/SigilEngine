#ifndef SIGIL_SCENE_BASE_HPP
#define SIGIL_SCENE_BASE_HPP

#include <Sigil/EngineFwd.hpp>
#include <Sigil/Event/EventTypes.hpp>
#include <Sigil/Action/ActionManager.hpp>

#include <string>
#include <unordered_map>
#include <vector>
#include <functional>

#include <SDL2/SDL.h>
#include <entt/entity/registry.hpp>

namespace Sigil 
{
	class SceneBase
	{
	public:
		SceneBase() = delete;
		SceneBase(Engine& engine, const std::string& inputName);
		~SceneBase();

		std::string getName() const;

		// TODO: Deprecate
		//ActionManager& getActionManagerRef();

		void registerKeyAction(SDL_Keycode key, KeyActionCallback callback);
		void registerMouseAction(Uint8 button, MouseActionCallback callback);
		void handleKeyEvent(Engine& engine, const KeyEvent& event);
		void handleMouseEvent(Engine& engine, const MouseEvent& event);

		using SystemFunction = std::function<void(entt::registry&, float)>;
		void addSystem(SystemFunction system);
		void runSystems(float deltaTime);

		ActionManager& getActionManager();

		void clearRegistry();
		void initializeScene();
		virtual void initializeEntities() = 0;

		virtual void update(float deltaTime) = 0;
		virtual void render(SDL_Renderer* renderer, float deltaTime) = 0;

	protected:
		Engine& m_engine;
		std::string m_name;
		std::unordered_map<SDL_Keycode, KeyActionCallback> m_keyBindings;
		std::unordered_map<Uint8, MouseActionCallback> m_mouseBindings;
		ActionManager m_actionManager;
		entt::registry m_registry;
		std::vector<SystemFunction> m_systems;

	};
} // namespace Sigil

#endif // SIGIL_SCENE_BASE_HPP