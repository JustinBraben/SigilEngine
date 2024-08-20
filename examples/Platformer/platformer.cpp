#define SDL_MAIN_HANDLED
#include <Sigil/Sigil.hpp>
#include <iostream>
#include <memory>
#include <fstream>

#include "components.hpp"
#include "PlatformerLevelOne.hpp"

class PlatformerMenuScene : public Sigil::SceneBase
{
public:
	PlatformerMenuScene(Sigil::Engine& engine, const std::string& name)
		: SceneBase(engine, name) {}

	void initializeEntities() override {}

	void update(float deltaTime) override {}

	void render(float deltaTime) override {}
};

int main()
{
	std::ifstream inputConfig("./resources/config_files/platformer_config.json");
	json configJson = json::parse(inputConfig);
	int return_code = 0;
	/*Uint8 r = 20, g = 125, b = 0, a = 255;*/

	auto configJsonString = configJson.dump(4);
	std::cout << configJsonString << '\n';

	Sigil::Engine engine(configJson);

	engine.init();


	auto platformerMenuScene = std::make_shared<PlatformerMenuScene>(engine, "platformerMenuScene");
	engine.addNewScene("platformerMenuScene", platformerMenuScene);

	std::ifstream inputLevelConfig("./resources/config_files/platformerLevelOne.json");
	json inputLevelJson = json::parse(inputLevelConfig);
	auto platformerLevelOne = std::make_shared<PlatformerLevelOne>(engine, "platformerLevelOne", inputLevelJson);
	engine.addNewScene("platformerLevelOne", platformerLevelOne);
	engine.setCurrentScene("platformerLevelOne");

	engine.getCurrentScene()->initializeScene(inputLevelJson);

	// Add Actions to platformerLevelOne
	engine.getCurrentScene()->registerKeyAction("Jump", SDLK_SPACE);
	engine.getCurrentScene()->registerKeyAction("Right", SDLK_d);
	engine.getCurrentScene()->registerKeyAction("Left", SDLK_a);

	// Add Callbacks to platformerLevelOne
	engine.getCurrentScene()->registerKeyActionCallback(SDLK_ESCAPE, SDL_KEYUP, 
		[](Sigil::Engine& eng, const Sigil::KeyEvent& keyboardEvnt) {
			eng.quit();
		}
	);
	engine.getCurrentScene()->registerKeyActionCallback(SDLK_d, SDL_KEYDOWN,
		[](Sigil::Engine& eng, const Sigil::KeyEvent& keyboardEvnt) {
			auto& registry = eng.getCurrentScene()->getRegistry();
			auto view = registry.view<Position, Velocity, PlayerMovementInput>();
			for (auto [e, pos, vel, player_input] : view.each())
			{
				player_input.right = true;
			}
		}
	);
	engine.getCurrentScene()->registerKeyActionCallback(SDLK_d, SDL_KEYUP,
		[](Sigil::Engine& eng, const Sigil::KeyEvent& keyboardEvnt) {
			auto& registry = eng.getCurrentScene()->getRegistry();
			auto view = registry.view<Position, Velocity, PlayerMovementInput>();
			for (auto [e, pos, vel, player_input] : view.each())
			{
				player_input.right = false;
			}
		}
	);
	engine.getCurrentScene()->registerKeyActionCallback(SDLK_SPACE, SDL_KEYDOWN,
		[](Sigil::Engine& eng, const Sigil::KeyEvent& keyboardEvnt) {
			auto& registry = eng.getCurrentScene()->getRegistry();
			auto view = registry.view<Position, Velocity, PlayerMovementInput>();
			for (auto [e, pos, vel, player_input] : view.each())
			{
				player_input.jump = true;
			}
		}
	);
	engine.getCurrentScene()->registerKeyActionCallback(SDLK_SPACE, SDL_KEYUP,
		[](Sigil::Engine& eng, const Sigil::KeyEvent& keyboardEvnt) {
			auto& registry = eng.getCurrentScene()->getRegistry();
			auto view = registry.view<Position, Velocity, PlayerMovementInput>();
			for (auto [e, pos, vel, player_input] : view.each())
			{
				player_input.jump = false;
			}
		}
	);
	engine.getCurrentScene()->registerKeyActionCallback(SDLK_a, SDL_KEYDOWN,
		[](Sigil::Engine& eng, const Sigil::KeyEvent& keyboardEvnt) {
			auto& registry = eng.getCurrentScene()->getRegistry();
			auto view = registry.view<Position, Velocity, PlayerMovementInput>();
			for (auto [e, pos, vel, player_input] : view.each())
			{
				player_input.left = true;
			}
		}
	);
	engine.getCurrentScene()->registerKeyActionCallback(SDLK_a, SDL_KEYUP,
		[](Sigil::Engine& eng, const Sigil::KeyEvent& keyboardEvnt) {
			auto& registry = eng.getCurrentScene()->getRegistry();
			auto view = registry.view<Position, Velocity, PlayerMovementInput>();
			for (auto [e, pos, vel, player_input] : view.each())
			{
				player_input.left = false;
			}
		}
	);


	// Add Systems to platformerLevelOne

	// Add Velocity to Position to move components with Position/Velocity
	engine.getCurrentScene()->addSystem(
		[](entt::registry& registry, float deltaTime) {
			auto view = registry.view<Position, Velocity>();
			for (auto [e_block, pos, vel] : view.each())
			{
				auto xAdd = static_cast<float>(vel.x) * deltaTime;
				auto yAdd = static_cast<float>(vel.y) * deltaTime;
				pos.x += static_cast<int>(xAdd);
				pos.y += static_cast<int>(yAdd);
			}
		}
	);


	// Add velocity when player input found
	engine.getCurrentScene()->addSystem(
		[](entt::registry& registry, float deltaTime) {
			auto view = registry.view<Position, Velocity, PlayerMovementInput>();
			for (auto [e, pos, vel, player_input] : view.each())
			{
				vel.x += player_input.left ? -15 : 0;
				vel.x += player_input.right ? 15 : 0;
				
				vel.y += player_input.jump ? 15 : 0;

				// Speed limit
				vel.x < -45 ? -45 : vel.x;
				vel.y < -45 ? -45 : vel.y;
				vel.x > 45 ? 45 : vel.x;
				vel.y > 45 ? 45 : vel.y;
			}
		}
	);

	// Slow down player when not inputting but still moving
	engine.getCurrentScene()->addSystem(
		[](entt::registry& registry, float deltaTime) {
			auto view = registry.view<Position, Velocity, PlayerMovementInput>();
			for (auto [e, pos, vel, player_input] : view.each())
			{
				if (vel.x > 0 && !player_input.right)
				{
					vel.x -= 10;
					vel.x = vel.x < 0 ? 0 : vel.x;
				}
				if (vel.x < 0 && !player_input.left)
				{
					vel.x += 10;
					vel.x = vel.x > 0 ? 0 : vel.x;
				}
			}
		}
	);

	// Flip animate depending on vel
	engine.getCurrentScene()->addSystem(
		[](entt::registry& registry, float deltaTime) {
			auto view = registry.view<Position, Velocity, SpriteSize, SpriteAnimator>();
			for (auto [e, pos, vel, sprite_size, sprite_animator] : view.each())
			{
				if (vel.x < 0) 
				{
					sprite_animator.flip = SDL_FLIP_HORIZONTAL;
				}

				if (vel.x > 0)
				{
					sprite_animator.flip = SDL_FLIP_NONE;
				}
			}
		}
	);

	// Primary animate
	engine.getCurrentScene()->addSystem(
		[](entt::registry& registry, float deltaTime) {
			auto view = registry.view<Position, Velocity, SpriteSize, SpriteAnimator>();
			for (auto [e, pos, vel, sprite_size, sprite_animator] : view.each())
			{
				if (sprite_animator.state == State::play)
				{
					sprite_animator.elapsed += deltaTime;

					if (sprite_animator.elapsed > (1.0f / sprite_animator.fps))
					{
						sprite_animator.elapsed = 0.0f;

						if (sprite_animator.frame < sprite_animator.lastFrame) {
							sprite_animator.frame += 1;
						}
						else
						{
							sprite_animator.frame = 0;
						}
					}
				}
			}
		}
	);

	// Imagine using it like this
	// Sigil::KeyAction jump("Jump", SDLK_SPACE);
	// Then it generates a KeyUp and KeyDown for SDLK_SPACE

	// engine.getCurrentScene()->registerKeyActionNew("Jump", SDLK_SPACE);
	// engine.getCurrentScene()->registerActionCallback


	engine.run();

	return return_code;
}