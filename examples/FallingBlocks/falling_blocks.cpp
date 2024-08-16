#define SDL_MAIN_HANDLED
#include <Sigil/Sigil.hpp>
#include <iostream>
#include <memory>

#include "components.hpp"

// Aliases for commonly used component lists
using BlockComponents = entt::type_list<Position, Velocity, SpriteSize>;
using TextComponents = entt::type_list<Position, Text>;
using SpriteComponents = entt::type_list<Position, Velocity, SpriteSize, Sprite>;

template <class Registry>
concept IsRegistry = std::is_base_of_v<entt::registry, Registry>;

// used to create a view based on the entt::type_list you wish to use
template<IsRegistry Registry, typename... Components>
auto create_view(Registry& registry, entt::type_list<Components...>)
{
	return registry.template view<Components...>();
}

class FallingBlocksScene : public Sigil::SceneBase
{
public:
	FallingBlocksScene(Sigil::Engine& engine, const std::string& name)
		: SceneBase(engine, name) {}

	void initializeEntities() override
	{
		auto block = m_registry.create();
		m_registry.emplace<Position>(block, 400, 384);
		m_registry.emplace<Velocity>(block, -150, 150);
		m_registry.emplace<SpriteSize>(block, 100, 100);

		auto text = m_registry.create();
		m_registry.emplace<Position>(text, 400, 400);
		SDL_Color foregroundColor = { 255, 255, 255 };
		SDL_Color backgroundColor = { 0, 0, 255 };
		m_registry.emplace<Text>(text, "FallingBlockScene", foregroundColor, backgroundColor);

		auto sprite = m_registry.create();
		m_registry.emplace<Position>(sprite, 200, 300);
		m_registry.emplace<Velocity>(sprite, 150, -150);
		m_registry.emplace<SpriteSize>(sprite, 52, 76);
		m_registry.emplace<Sprite>(sprite, "flower");
	}

	void update(float deltaTime) override
	{
		// Implement scene-specific update logic here
		// You can convert deltaTime to seconds if needed:
		/*double deltaSeconds = static_cast<double>(deltaTime) / SDL_GetPerformanceFrequency();*/
		runSystems(deltaTime);
		// Use deltaSeconds for time-based updates
	}

	void render(SDL_Renderer* renderer, float deltaTime) override
	{
		SDL_SetRenderDrawColor(renderer, 0, 122, 0, 255);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
		auto block_view = m_registry.view<const Position, const SpriteSize>(entt::exclude<Sprite>);
		for (const auto [e_block, pos, sprite_size] : block_view.each())
		{
			SDL_Rect block_rect = { pos.x, pos.y, sprite_size.w, sprite_size.h };
			SDL_RenderFillRect(renderer, &block_rect);
		}

		// TODO: proof of concept font rendering
		auto text_view = m_registry.view<const Position, const Text>();
		for (const auto [e, pos, text] : text_view.each())
		{
			std::string fontName = "dejavu-sans";
			auto* font = m_engine.getAssetManager().getFont(fontName);
			/*TTF_Font* font = TTF_OpenFont("./resources/fonts/dejavu-sans.book.ttf", 12);*/
			SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.str, text.foregroundColor);
			auto* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
			SDL_Rect textRect = { pos.x, pos.y, textSurface->w, textSurface->h };
			SDL_RenderCopy(renderer, texture, NULL, &textRect);

			SDL_DestroyTexture(texture);
			SDL_FreeSurface(textSurface);
		}

		auto sprite_view = create_view(m_registry, SpriteComponents{});
		for (const auto [e, pos, vel, sprite_size, sprite] : sprite_view.each())
		{
			SDL_Rect spriteRect = { pos.x, pos.y, sprite_size.w, sprite_size.h };
			std::string name = sprite.name;
			auto* spriteTexture = m_engine.getAssetManager().getTexture(name);

			SDL_RenderCopy(renderer, spriteTexture, NULL, &spriteRect);
		}
	}
};

class SceneA : public Sigil::SceneBase
{
public:
	SceneA(Sigil::Engine& engine, const std::string& name)
		: SceneBase(engine, name) {}

	void initializeEntities() override
	{
		auto block = m_registry.create();
		m_registry.emplace<Position>(block, 200, 384);
		m_registry.emplace<Velocity>(block, 0, -200);
		m_registry.emplace<SpriteSize>(block, 100, 100);
	}

	void update(float deltaTime) override
	{
		// Implement scene-specific update logic here
		// You can convert deltaTime to seconds if needed:
		/*double deltaSeconds = static_cast<double>(deltaTime) / SDL_GetPerformanceFrequency();*/
		runSystems(deltaTime);
		// Use deltaSeconds for time-based updates
	}

	void render(SDL_Renderer* renderer, float deltaTime) override
	{
		SDL_SetRenderDrawColor(renderer, 122, 0, 0, 255);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
		auto block_view = m_registry.view<const Position, const SpriteSize>();
		for (const auto [e_block, pos, sprite_size] : block_view.each())
		{
			SDL_Rect block_rect = { pos.x, pos.y, sprite_size.w, sprite_size.h };
			SDL_RenderFillRect(renderer, &block_rect);
		}
	}
};

class SceneB : public Sigil::SceneBase
{
public:
	SceneB(Sigil::Engine& engine, const std::string& name)
		: SceneBase(engine, name) {}

	void initializeEntities() override
	{
		auto block = m_registry.create();
		m_registry.emplace<Position>(block, 600, 384);
		m_registry.emplace<Velocity>(block, 200, 0);
		m_registry.emplace<SpriteSize>(block, 100, 100);
	}

	void update(float deltaTime) override
	{
		// Implement scene-specific update logic here
		// You can convert deltaTime to seconds if needed:
		/*double deltaSeconds = static_cast<double>(deltaTime) / SDL_GetPerformanceFrequency();*/
		runSystems(deltaTime);
		// Use deltaSeconds for time-based updates
	}

	void render(SDL_Renderer* renderer, float deltaTime) override
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 122, 255);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
		auto block_view = m_registry.view<const Position, const SpriteSize>();
		for (const auto [e_block, pos, sprite_size] : block_view.each())
		{
			SDL_Rect block_rect = { pos.x, pos.y, sprite_size.w, sprite_size.h };
			SDL_RenderFillRect(renderer, &block_rect);
		}
	}
};

int main()
{
	json config_json;
	int return_code = 0;
	Uint8 r = 20, g = 125, b = 0, a = 255;

	// Setup config for game
	config_json["fps"] = 60;
	config_json["display"]["name"] = "Falling Blocks";
	config_json["display"]["width"] = 1024;
	config_json["display"]["height"] = 768;
	config_json["display"]["fullscreen"] = false;
	config_json["display"]["resizeable"] = false;
	config_json["display"]["background"]["color"]["r"] = r;
	config_json["display"]["background"]["color"]["g"] = g;
	config_json["display"]["background"]["color"]["b"] = b;
	config_json["display"]["background"]["color"]["a"] = a;
	config_json["resources"]["fonts"]["dejavu-sans"]["name"] = "dejavu-sans";
	config_json["resources"]["fonts"]["dejavu-sans"]["path"] = "./resources/fonts/dejavu-sans.book.ttf";
	config_json["resources"]["sprites"]["flower"]["name"] = "flower";
	config_json["resources"]["sprites"]["flower"]["path"] = "./resources/sprites/flower.png";

	auto config_json_string = config_json.dump(4);
	std::cout << config_json_string << '\n';

	Sigil::Engine engine(config_json);

	engine.init();

	auto fallingBlockScene = std::make_shared<FallingBlocksScene>(engine, "fallingBlockScene");
	engine.addNewScene("fallingBlockScene", fallingBlockScene);
	engine.setCurrentScene("fallingBlockScene");
	engine.getCurrentScene()->registerKeyAction(SDLK_ESCAPE, 
		[](Sigil::Engine& eng, const Sigil::KeyEvent& keyboardEvnt) {
			if (keyboardEvnt.evnt_type == SDL_KEYDOWN) {
				eng.quit();
			}
		}
	);
	engine.getCurrentScene()->registerKeyAction(SDLK_UP, 
		[](Sigil::Engine& eng, const Sigil::KeyEvent& keyboardEvnt) {
			if (keyboardEvnt.evnt_type == SDL_KEYDOWN) {
				std::cout << "Up arrow pressed!\n";
			}
			if (keyboardEvnt.evnt_type == SDL_KEYUP) {
				std::cout << "Up arrow released!\n";
			}
		}
	);

	auto sceneA = std::make_shared<SceneA>(engine, "sceneA");
	auto sceneB = std::make_shared<SceneB>(engine, "sceneB");
	engine.addNewScene("sceneA", sceneA);
	engine.addNewScene("sceneB", sceneB);

	engine.setCurrentScene("sceneA");
	engine.getCurrentScene()->registerKeyAction(SDLK_RIGHT, 
		[](Sigil::Engine& eng, const Sigil::KeyEvent& keyboardEvnt) {
			if (keyboardEvnt.evnt_type == SDL_KEYUP) {
				std::cout << "Switching from sceneA to fallingBlockScene!\n";
				eng.setCurrentScene("fallingBlockScene");
			}
		}
	);

	engine.getCurrentScene()->registerKeyAction(SDLK_ESCAPE, 
		[](Sigil::Engine& eng, const Sigil::KeyEvent& keyboardEvnt) {
			if (keyboardEvnt.evnt_type == SDL_KEYDOWN) {
				std::cout << "There is no escape from sceneA...\n";
			}
		}
	);

	engine.setCurrentScene("sceneB");
	engine.getCurrentScene()->registerKeyAction(SDLK_LEFT, 
		[](Sigil::Engine& eng, const Sigil::KeyEvent& keyboardEvnt) {
			if (keyboardEvnt.evnt_type == SDL_KEYUP) {
				std::cout << "Switching from sceneB to fallingBlockScene!\n";
				eng.setCurrentScene("fallingBlockScene");
			}
		}
	);
	engine.getCurrentScene()->registerKeyAction(SDLK_ESCAPE, 
		[](Sigil::Engine& eng, const Sigil::KeyEvent& keyboardEvnt) {
			if (keyboardEvnt.evnt_type == SDL_KEYDOWN) {
				std::cout << "There is no escape from sceneB...\n";
			}
		}
	);

	engine.setCurrentScene("fallingBlockScene");
	engine.getCurrentScene()->registerKeyAction(SDLK_LEFT, 
		[](Sigil::Engine& eng, const Sigil::KeyEvent& keyboardEvnt) {
			if (keyboardEvnt.evnt_type == SDL_KEYUP) {
				std::cout << "Switching from fallingBlockScene to sceneA!\n";
				eng.setCurrentScene("sceneA");
			}
		}
	);

	engine.getCurrentScene()->registerKeyAction(SDLK_RIGHT, 
		[](Sigil::Engine& eng, const Sigil::KeyEvent& keyboardEvnt) {
			if (keyboardEvnt.evnt_type == SDL_KEYUP) {
				std::cout << "Switching from fallingBlockScene to sceneB!\n";
				eng.setCurrentScene("sceneB");
			}
		}
	);

	// Setup some entities for each scene
	engine.setCurrentScene("sceneA");
	engine.getCurrentScene()->initializeEntities();

	engine.setCurrentScene("sceneB");
	engine.getCurrentScene()->initializeEntities();

	engine.setCurrentScene("fallingBlockScene");
	engine.getCurrentScene()->initializeEntities();

	// Setup systems for each scene
	engine.setCurrentScene("sceneA");
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
	engine.getCurrentScene()->addSystem(
		[](entt::registry& registry, float deltaTime) {
			auto view = registry.view<Position, Velocity, SpriteSize>();
			for (auto [e_block, pos, vel, sprite_size] : view.each())
			{
				if (pos.y < 0 || pos.y > 768 - sprite_size.h) {
					vel.y *= -1;
				}
			}
		}
	);

	engine.setCurrentScene("sceneB");
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
	engine.getCurrentScene()->addSystem(
		[](entt::registry& registry, float deltaTime) {
			auto view = registry.view<Position, Velocity, SpriteSize>();
			for (auto [e_block, pos, vel, sprite_size] : view.each())
			{
				if (pos.x < 0 || pos.x > 1024 - sprite_size.w) {
					vel.x *= -1;
				}
			}
		}
	);

	engine.setCurrentScene("fallingBlockScene");
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
	engine.getCurrentScene()->addSystem(
		[](entt::registry& registry, float deltaTime) {
			auto view = registry.view<Position, Velocity, SpriteSize>(entt::exclude<Sprite>);
			for (auto [e_block, pos, vel, sprite_size] : view.each())
			{
				if (pos.x < 0 || pos.x > 1024 - sprite_size.w) {
					vel.x *= -1;
				}

				if (pos.y < 0 || pos.y > 768 - sprite_size.h) {
					vel.y *= -1;
				}
			}
		}
	);
	engine.getCurrentScene()->addSystem(
		[](entt::registry& registry, float deltaTime) {
			auto view = registry.view<Position, Velocity, SpriteSize, Sprite>();
			for (auto [e_sprite, pos, vel, sprite_size, sprite] : view.each())
			{
				if (pos.x < 0 || pos.x > 1024 - sprite_size.w) {
					vel.x *= -1;
				}

				if (pos.y < 0 || pos.y > 768 - sprite_size.h) {
					vel.y *= -1;
				}
			}
		}
	);

	engine.run();

	return return_code;
}