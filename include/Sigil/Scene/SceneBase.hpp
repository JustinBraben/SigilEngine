#ifndef SIGIL_SCENE_BASE_HPP
#define SIGIL_SCENE_BASE_HPP

#include <Sigil/EngineFwd.hpp>
#include <Sigil/Event/EventTypes.hpp>

#include <string>
#include <unordered_map>

namespace Sigil 
{
	class SceneBase
	{
	public:
		SceneBase();
		SceneBase(const std::string& inputName);
		~SceneBase();

		std::string getName() const;

		// TODO: Deprecate
		//ActionManager& getActionManagerRef();

		void registerKeyAction(SDL_Keycode key, KeyActionCallback callback);
		void registerMouseAction(Uint8 button, MouseActionCallback callback);
		void handleKeyEvent(Engine& engine, const KeyEvent& event);
		void handleMouseEvent(Engine& engine, const MouseEvent& event);

	protected:
		std::string m_name;
		std::unordered_map<SDL_Keycode, KeyActionCallback> m_keyBindings;
		std::unordered_map<Uint8, MouseActionCallback> m_mouseBindings;
	};
} // namespace Sigil

#endif // SIGIL_SCENE_BASE_HPP