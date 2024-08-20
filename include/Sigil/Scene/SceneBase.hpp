#ifndef SIGIL_SCENE_BASE_HPP
#define SIGIL_SCENE_BASE_HPP

#include <Sigil/EngineFwd.hpp>
#include <Sigil/Action/ActionTypes.hpp>
#include <Sigil/Action/ActionManager.hpp>
#include <Sigil/Action/CallbackManager.hpp>

#include <string>
#include <unordered_map>
#include <vector>
#include <queue>
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

		void registerKeyAction(const std::string& name, SDL_Keycode key);
		void registerMouseButtonAction(const std::string& name, Uint8 button);
		void registerKeyActionCallback(SDL_Keycode key, SDL_EventType eventType, KeyActionCallback callback);
		void registerMouseButtonActionCallback(Uint8 button, SDL_EventType eventType, MouseButtonActionCallback callback);
		void handleKeyEvent(const KeyEvent& event);
		void handleMouseButtonEvent(const MouseButtonEvent& event);

		void processActions();
		void processKeyActions();
		void processMouseActions();

		using SystemFunction = std::function<void(entt::registry&, float)>;
		void addSystem(SystemFunction system);
		void runSystems(float deltaTime);

		ActionManager& getActionManager();
		CallbackManager& getCallbackManager();

		void clearRegistry();
		void initializeScene();
		virtual void initializeEntities() = 0;

		virtual void update(float deltaTime) = 0;
		virtual void render(SDL_Renderer* renderer, float deltaTime) = 0;

	protected:
		Engine& m_engine;
		std::string m_name;
		ActionManager m_actionManager;
		CallbackManager m_callbackManager;
		std::queue<KeyEvent> m_keyPressActionQueue;
		std::queue<MouseButtonEvent> m_mouseButtonPressActionQueue;
		std::queue<KeyEvent> m_keyReleaseActionQueue;
		std::queue<MouseButtonEvent> m_mouseButtonReleaseActionQueue;
		entt::registry m_registry;
		std::vector<SystemFunction> m_systems;

	};
} // namespace Sigil

#endif // SIGIL_SCENE_BASE_HPP