# 2D Game Engine Design Using C++, SDL, and EnTT

## Overview

This document outlines the basic steps and ideas for utilizing the custom 2D game engine built with C++, SDL, and EnTT. The engine structure revolves around scenes, action managers, and event listeners.

## Engine Initialization

```cpp
// Initialize the engine
engine.init();
```

## Scene Creation

All scenes must inherit from the `SceneBase` class provided by the engine.

```cpp
// scenes must be created based on SceneBase
class SceneA : public Sigil::SceneBase{};
```

## Adding and Managing Scenes

Scenes are managed by the engine's scene manager. Below is an example of adding a scene and switching to it.

```cpp
// Add your first scene
auto sceneA = std::make_shared<SceneA>();
engine.sceneManager().addScene("sceneA", sceneA);
engine.switchToScene("sceneA");
```

## Action Management

The engine allows for the registration of actions, such as keyboard inputs, that can trigger specific functions.

```cpp
// Register a keyboard action to exit the game when ESCAPE is pressed
engine.getCurrentScene()->actionManager().registerKeyboardAction("exit_game", SDLK_ESCAPE);
```

## Event Listening

Events can be listened for within the current scene, enabling the game to respond to user inputs or other events.

```cpp
struct listener {
    void example_func_to_trigger(const SDL_KeyCode keycode) { std::cout << "Pressed key : " << keycode << '\n'; }
};
// Using the currentScene, listen for events of relevance
auto currentScene = engine.getCurrentScene();
engine.addListener(currentScene, event, listener, &listener::example_func_to_trigger);
```